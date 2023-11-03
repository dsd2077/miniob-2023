/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/12/14.
//

#include <utility>

#include "sql/optimizer/physical_plan_generator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/table_scan_physical_operator.h"
#include "sql/operator/index_scan_physical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/predicate_physical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/insert_physical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/update_physical_operator.h"
#include "sql/operator/delete_physical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/explain_physical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/join_physical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/calc_physical_operator.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/order_by_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/operator/groupby_logical_operator.h"
#include "sql/operator/groupby_physical_operator.h"

using namespace std;

RC PhysicalPlanGenerator::create(LogicalOperator &logical_operator, unique_ptr<PhysicalOperator> &oper,
      LogicalOperatorType parent_oper_type)
{
  RC rc = RC::SUCCESS;

  switch (logical_operator.type()) {
    case LogicalOperatorType::CALC: {
      return create_plan(static_cast<CalcLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;

    case LogicalOperatorType::TABLE_GET: {
      return create_plan(static_cast<TableGetLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::PREDICATE: {
      return create_plan(static_cast<PredicateLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::PROJECTION: {
      return create_plan(static_cast<ProjectLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::INSERT: {
      return create_plan(static_cast<InsertLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::DELETE: {
      return create_plan(static_cast<DeleteLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::UPDATE: {
      return create_plan(static_cast<UpdateLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::ORDER_BY: {
      return create_plan(static_cast<OrderByLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::EXPLAIN: {
      return create_plan(static_cast<ExplainLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::JOIN: {
      return create_plan(static_cast<JoinLogicalOperator &>(logical_operator), oper, parent_oper_type);
    } break;
    case LogicalOperatorType::GROUP_BY: {
      return create_plan(static_cast<GroupByLogicalOperator &>(logical_operator), oper);
    } break;

    default: {
      return RC::INVALID_ARGUMENT;
    }
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(TableGetLogicalOperator &table_get_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  vector<unique_ptr<Expression>> &predicates = table_get_oper.predicates();
  // 看看是否有可以用于索引查找的表达式
  Table *table = table_get_oper.table();

  Index *index = nullptr;
  ValueExpr *value_expr = nullptr;
  std::vector<ValueExpr> value_exprs;
  std::vector<const char *> expr_fields; // 记录表达式中所有的fields 
  // 查询谓词中是否有索引字段
  for (auto &expr : predicates) {
    if (expr->type() == ExprType::COMPARISON) {
      auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());
      // 简单处理，就找等值查询
      if (comparison_expr->comp() != EQUAL_TO) {
        continue;
      }

      unique_ptr<Expression> &left_expr = comparison_expr->left();
      unique_ptr<Expression> &right_expr = comparison_expr->right();
      // 左右比较的一边最少是一个值(表内condition)
      if (left_expr->type() != ExprType::VALUE && right_expr->type() != ExprType::VALUE) {
        continue;
      }

      // ComparitionExpr的左右并不一定是FieldExpr
      FieldExpr *field_expr = nullptr;
      if (left_expr->type() == ExprType::FIELD) {
        ASSERT(right_expr->type() == ExprType::VALUE, "right expr should be a value expr while left is field expr");
        field_expr = static_cast<FieldExpr *>(left_expr.get());
        value_expr = static_cast<ValueExpr *>(right_expr.get());
        value_exprs.emplace_back(*value_expr);
      } else if (right_expr->type() == ExprType::FIELD) {
        ASSERT(left_expr->type() == ExprType::VALUE, "left expr should be a value expr while right is a field expr");
        field_expr = static_cast<FieldExpr *>(right_expr.get());
        value_expr = static_cast<ValueExpr *>(left_expr.get());
        value_exprs.emplace_back(*value_expr);
      }

      if (field_expr == nullptr) {
        continue;
      }

      const Field &field = field_expr->field();
      expr_fields.emplace_back(field.field_name());
      // index = table->find_index_by_field(field.field_name());     // 查找该字段是否为索引字段
      // if (nullptr != index) {
      //   break;
      // }
    }
  }

  index = table->find_index_by_fields(expr_fields);

  if (index != nullptr) {
    ASSERT(value_expr != nullptr, "got an index but value expr is null ?");

    // const Value &value = value_expr->get_value();
    std::vector<Value> values;
    for(int i = 0 ; i < value_exprs.size() ; i ++ ) {
      values.emplace_back(value_exprs[i].get_value());
    }
    std::reverse(values.begin(), values.end());
    IndexScanPhysicalOperator *index_scan_oper = new IndexScanPhysicalOperator(
          table, index, table_get_oper.readonly(), 
          values, true /*left_inclusive*/, 
          values, true /*right_inclusive*/);
          
    index_scan_oper->set_predicates(std::move(predicates));
    oper = unique_ptr<PhysicalOperator>(index_scan_oper);
    oper->setParentOperType(parent_oper_type);
    LOG_TRACE("use index scan");
  } else {
    auto table_scan_oper = new TableScanPhysicalOperator(table, table_get_oper.readonly());
    table_scan_oper->set_predicates(std::move(predicates));
    oper = unique_ptr<PhysicalOperator>(table_scan_oper);
    oper->setParentOperType(parent_oper_type);
    LOG_TRACE("use table scan");
  }

  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(PredicateLogicalOperator &pred_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)  // 改成LogicalOperatorType
{
  vector<unique_ptr<LogicalOperator>> &children_opers = pred_oper.children();
  ASSERT(children_opers.size() == 1, "predicate logical operator's sub oper number should be 1");

  LogicalOperator &child_oper = *children_opers.front();

  unique_ptr<PhysicalOperator> child_phy_oper;
  RC rc;
  if(parent_oper_type == LogicalOperatorType::DELETE) {
    rc = create(child_oper, child_phy_oper, LogicalOperatorType::DELETE);
  }else {
    rc = create(child_oper, child_phy_oper, pred_oper.type());
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create child operator of predicate operator. rc=%s", strrc(rc));
    return rc;
  }

  vector<unique_ptr<Expression>> &expressions = pred_oper.expressions();
  ASSERT(expressions.size() == 1, "predicate logical operator's children should be 1");

  auto tp1 = expressions.front()->type();
  unique_ptr<Expression> expression = std::move(expressions.front());

  // 创建子查询的物理计划
  if (ExprType::CONJUNCTION == expression->type()) {
    ConjunctionExpr *temp = dynamic_cast<ConjunctionExpr *>(expression.get());
    assert(temp != nullptr);
    for (auto &expr : temp->children()) {  // child为ComparisonExpr
      create_plan_for_subquery(expr, parent_oper_type);
    }
  } else if (ExprType::COMPARISON == expression->type()) {
    create_plan_for_subquery(expression, parent_oper_type);
  }

  oper = unique_ptr<PhysicalOperator>(new PredicatePhysicalOperator(std::move(expression)));
  oper->add_child(std::move(child_phy_oper));
  oper->setParentOperType(parent_oper_type);
  return rc;
}

RC PhysicalPlanGenerator::create_plan_for_subquery(std::unique_ptr<Expression> &expr, LogicalOperatorType parent_oper_type) {
  RC rc = RC::SUCCESS;
  // process sub query
  if (ExprType::SUBQUERY == expr->type()) {
    SubQueryExpression *         sub_query_expr = dynamic_cast<SubQueryExpression *>(expr.get());
    unique_ptr<PhysicalOperator> physical_operator;
    ProjectLogicalOperator *logical_oper = dynamic_cast<ProjectLogicalOperator *>(sub_query_expr->get_logical_oper());
    if (RC::SUCCESS != (rc = create_plan(*logical_oper, physical_operator, parent_oper_type))) {
      return rc;
    }
    assert(nullptr != physical_operator);
    sub_query_expr->set_physical_oper(physical_operator.release());
    return RC::SUCCESS;
  } else if (ExprType::COMPARISON == expr->type()) {
    ComparisonExpr *temp = dynamic_cast<ComparisonExpr *>(expr.get());
    assert(temp != nullptr);

    if (RC::SUCCESS != (rc = create_plan_for_subquery(temp->left(), parent_oper_type))) {
      return rc;
    }
    return create_plan_for_subquery(temp->right(), parent_oper_type);
  }
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(ProjectLogicalOperator &project_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = project_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper, project_oper.type());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  ProjectPhysicalOperator *project_operator = new ProjectPhysicalOperator(project_oper.expressions());      



  if (child_phy_oper) {
    project_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(project_operator);

  oper->setParentOperType(parent_oper_type);

  LOG_TRACE("create a project physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(InsertLogicalOperator &insert_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  Table *table = insert_oper.table();
  vector<Value> &values = insert_oper.values();
  InsertPhysicalOperator *insert_phy_oper = new InsertPhysicalOperator(table, std::move(values));
  oper.reset(insert_phy_oper);
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(DeleteLogicalOperator &delete_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = delete_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();    
    rc = create(*child_oper, child_physical_oper, delete_oper.type());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new DeletePhysicalOperator(delete_oper.table()));

  oper->setParentOperType(parent_oper_type);

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(UpdateLogicalOperator &update_oper, std::unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type) {
  vector<unique_ptr<LogicalOperator>> &child_opers = update_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_physical_oper, update_oper.type());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new UpdatePhysicalOperator(update_oper.table(),std::move(update_oper.value()), update_oper.attribute_name()));

  oper->setParentOperType(parent_oper_type);

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ExplainLogicalOperator &explain_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = explain_oper.children();

  RC rc = RC::SUCCESS;
  unique_ptr<PhysicalOperator> explain_physical_oper(new ExplainPhysicalOperator);
  for (unique_ptr<LogicalOperator> &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper, explain_oper.type());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create child physical operator. rc=%s", strrc(rc));
      return rc;
    }

    explain_physical_oper->add_child(std::move(child_physical_oper));
  }

  oper = std::move(explain_physical_oper);
  oper->setParentOperType(parent_oper_type);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(JoinLogicalOperator &join_oper, unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  RC rc = RC::SUCCESS;

  vector<unique_ptr<LogicalOperator>> &child_opers = join_oper.children();
  if (child_opers.size() != 2) {
    LOG_WARN("join operator should have 2 children, but have %d", child_opers.size());
    return RC::INTERNAL;
  }

  unique_ptr<PhysicalOperator> join_physical_oper(new NestedLoopJoinPhysicalOperator);    
  for (auto &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    if(parent_oper_type == LogicalOperatorType::DELETE) {
      rc = create(*(child_oper.get()), child_physical_oper, LogicalOperatorType::DELETE);
    }else {
      rc = create(*(child_oper.get()), child_physical_oper, join_oper.type());
    }
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical child oper. rc=%s", strrc(rc));
      return rc;
    }

    join_physical_oper->add_child(std::move(child_physical_oper));
  }

  oper = std::move(join_physical_oper);
  oper->setParentOperType(parent_oper_type);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(CalcLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper,
        LogicalOperatorType parent_oper_type)
{
  RC rc = RC::SUCCESS;
  CalcPhysicalOperator *calc_oper = new CalcPhysicalOperator(std::move(logical_oper.expressions()));
  oper.reset(calc_oper);
  oper->setParentOperType(parent_oper_type);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(OrderByLogicalOperator &order_by_oper, std::unique_ptr<PhysicalOperator> &oper, LogicalOperatorType parent_oper_type) {
  vector<unique_ptr<LogicalOperator>> &child_opers = order_by_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_physical_oper, parent_oper_type);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new OrderByPhysicalOperator(order_by_oper.order_by_fields()));

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(GroupByLogicalOperator &groupby_oper, std::unique_ptr<PhysicalOperator> &oper) {
  vector<unique_ptr<LogicalOperator>> &child_opers = groupby_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }
  auto vec = groupby_oper.groupby_unit();
  auto vec1 = groupby_oper.agg_exprs();
  auto vec2 = groupby_oper.field_exprs();
  oper = unique_ptr<PhysicalOperator>(new GroupByPhysicalOperator(groupby_oper.groupby_unit(), groupby_oper.agg_exprs(), groupby_oper.field_exprs()));

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}