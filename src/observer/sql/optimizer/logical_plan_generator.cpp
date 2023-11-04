/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/groupby_logical_operator.h"
#include "sql/operator/groupby_physical_operator.h"

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include <memory>

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);  // table_oper可能是TableGetLogicalOperator（单表）或者JoinLogicalOperator(多表)

  const std::vector<Table *> &tables = select_stmt->tables();
  for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);   
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));    
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }
  std::unique_ptr<LogicalOperator> top_oper = std::move(table_oper);

  RC rc = RC::SUCCESS;
  // 构建inner_join_oper
  std::unique_ptr<LogicalOperator> inner_join_predicate_oper;     
  if (select_stmt->inner_join_filter_stmt() != nullptr) {
    rc = create_plan(select_stmt->inner_join_filter_stmt(), inner_join_predicate_oper);
    inner_join_predicate_oper->add_child(std::move(top_oper));      
    top_oper = std::move(inner_join_predicate_oper);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  // 这里的predicate_oper是where子句中的过滤条件
  unique_ptr<LogicalOperator> predicate_oper;     
  if (select_stmt->filter_stmt() != nullptr) {
    // 为子查询生成逻辑执行计划
    // bug:为子查询生成逻辑执行计划的过程中filter_stmt()->predicate()转移走了
    ConjunctionExpr * temp = dynamic_cast<ConjunctionExpr*>(select_stmt->filter_stmt()->predicate().get());
    assert(temp != nullptr);
    for (auto &expr : temp->children()) {   // child为ComparisonExpr
      create_plan_for_subquery(expr);
    }

    auto ty = select_stmt->filter_stmt()->predicate()->type();
    rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
    predicate_oper->add_child(std::move(top_oper));      
    top_oper = std::move(predicate_oper);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<LogicalOperator> order_by_oper;
  if (select_stmt->orderby_stmt() != nullptr) {
    rc = create_plan(select_stmt->orderby_stmt(), order_by_oper);
    order_by_oper->add_child(std::move(top_oper));      
    top_oper = std::move(order_by_oper);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  // 2 process groupby clause and aggrfunc fileds
  // 2.1 gen sort oper for groupby
  // OrderByLogicalOperator *sort_oper_for_groupby = nullptr;
  // if (nullptr != select_stmt->orderby_stmt_for_groupby()) {
  //   sort_oper_for_groupby = new SortOperator(select_stmt->orderby_stmt_for_groupby());
  //   sort_oper_for_groupby->add_child(top_op);
  //   top_op = sort_oper_for_groupby;
  //   delete_opers.emplace_back(sort_oper_for_groupby);
  // }

  // 2.2 get aggrfunc_exprs from projects
  std::vector<AggrFuncExpression *> aggr_exprs;
  for (auto project : select_stmt->projects()) {
    AggrFuncExpression::get_aggrfuncexprs(project, aggr_exprs);
  }

  // 2.3 get normal field_exprs from projects
  std::vector<FieldExpr *> field_exprs;
  for (auto project : select_stmt->projects()) {
    FieldExpr::get_fieldexprs_without_aggrfunc(project, field_exprs);
  }

  // 2.4 get aggrfunc_exprs field_exprs from havings
  // HavingStmt *having_stmt = select_stmt->having_stmt();
  // if (nullptr != having_stmt) {
  //   // TODO(wbj) unique
  //   for (auto hf : having_stmt->filter_units()) {
  //     AggrFuncExpression::get_aggrfuncexprs(hf->left(), aggr_exprs);
  //     AggrFuncExpression::get_aggrfuncexprs(hf->right(), aggr_exprs);
  //     FieldExpr::get_fieldexprs_without_aggrfunc(hf->left(), field_exprs);
  //     FieldExpr::get_fieldexprs_without_aggrfunc(hf->right(), field_exprs);
  //   }
  // }

  GroupByStmt *groupby_stmt = select_stmt->groupby_stmt();
  // 2.5 do check 
  if (!aggr_exprs.empty() && !field_exprs.empty()) {
    if (nullptr == groupby_stmt) {
      return RC::SQL_SYNTAX;
    }
    for (auto field_expr : field_exprs) {
      bool in_groupby = false;
      for (auto groupby_unit : groupby_stmt->groupby_units()) {
        if (field_expr->in_expression(groupby_unit->expr())) {
          in_groupby = true;
          break;
        }
      }
      if (!in_groupby) {
        return RC::SQL_SYNTAX;
      }
    }
  }

  // 2.6 gen groupby oper
  if (0 != aggr_exprs.size()) {
    GroupByStmt *groupby_stmt = select_stmt->groupby_stmt();
    groupby_stmt->groupby_units();
    unique_ptr<GroupByLogicalOperator> groupby_oper;
    if (groupby_stmt == nullptr) {
      groupby_oper = make_unique<GroupByLogicalOperator>(std::vector<GroupByUnit *>{}, aggr_exprs, field_exprs);
    } else {
      groupby_oper = make_unique<GroupByLogicalOperator>(groupby_stmt->groupby_units(), aggr_exprs, field_exprs);
    }
    groupby_oper->add_child(std::move(top_oper));
    top_oper = std::move(groupby_oper);
    // delete_opers.emplace_back(groupby_oper);
  }


  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator());
  auto &projects = select_stmt->projects();
  for (auto it = projects.begin(); it != projects.end(); it++) {    // select_attr 中的表达式转移到logical_oper中
    project_oper->add_project(*it);
  }
  project_oper->add_child(std::move(top_oper));

  logical_operator.swap(project_oper);

  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan_for_subquery(std::unique_ptr<Expression> &expr) {
  RC rc = RC::SUCCESS;
  // process sub query
  auto process_sub_query_expr = [&](std::unique_ptr<Expression> &expr) {
    if (ExprType::SUBQUERY == expr->type()) {
      SubQueryExpression* sub_query_expr = dynamic_cast<SubQueryExpression *>(expr.get()) ;
      SelectStmt *sub_select = sub_query_expr->get_sub_query_stmt();
      unique_ptr<LogicalOperator> logical_operator;
      if (RC::SUCCESS != (rc = create_plan(sub_select, logical_operator))) {   
        return rc;
      }
      assert(nullptr != logical_operator);
      sub_query_expr->set_logical_oper(logical_operator.release());
    }
    return RC::SUCCESS;
  };

  ComparisonExpr *temp = dynamic_cast<ComparisonExpr *>(expr.get());

  if (RC::SUCCESS != (rc = process_sub_query_expr(temp->left()))) {
    return rc;
  }

  return process_sub_query_expr(temp->right());
}

// 创建谓词执行计划
RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (filter_stmt->predicate() != nullptr) {
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(filter_stmt->predicate())));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // 为where子句创建计划
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;       // where子句
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));   // 逻辑算子的顺序并不等于物理算子的顺序，优化中可能会进行修改
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  // 为where子句创建计划
  Table *table = update_stmt->table();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false/*readonly*/));

  RC rc = RC::SUCCESS;
  unique_ptr<LogicalOperator> predicate_oper;       
  if( update_stmt->filter_stmt() != nullptr) {
    rc = create_plan(update_stmt->filter_stmt(), predicate_oper);
  }
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 获取stmt中的属性和值
  std::vector<std::string> attrs;
  std::vector<Value> vals;
  update_stmt->attributes_names(attrs);
  update_stmt->values(vals);

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, vals, attrs)); // update operator

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(OrderByStmt *order_by_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  logical_operator = nullptr;
  if (!order_by_stmt->orderby_units().empty()) {
    logical_operator = std::unique_ptr<LogicalOperator>(new OrderByLogicalOperator(order_by_stmt->orderby_units()));
  }
  return RC::SUCCESS;
}