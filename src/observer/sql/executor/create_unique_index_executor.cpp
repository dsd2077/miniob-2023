
#include "sql/executor/create_unique_index_executor.h"
#include "sql/stmt/create_unique_index_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "common/log/log.h"
#include "storage/table/table.h"

RC CreateUniqueIndexExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt(); // 获取stmt
  Session *session = sql_event->session_event()->session(); // 获取会话
  ASSERT(stmt->type() == StmtType::CREATE_UNIQUE_INDEX, 
         "create unique index executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateUniqueIndexStmt *create_unique_index_stmt = static_cast<CreateUniqueIndexStmt*>(stmt);

  Trx *trx = session->current_trx();  // 当前事务
  Table *table = create_unique_index_stmt->table();
  std::vector<FieldMeta> fields;
  create_unique_index_stmt->fields_metas(fields);
  return table->create_unique_index(trx, fields, create_unique_index_stmt->index_name().c_str());
  // Stmt *stmt = sql_event->stmt();
  // Session *session = sql_event->session_event()->session();
  // ASSERT(stmt->type() == StmtType::CREATE_UNIQUE_INDEX, 
  //        "create unique index executor can not run this command: %d", static_cast<int>(stmt->type()));

  // CreateUniqueIndexStmt *create_unique_index_stmt = static_cast<CreateUniqueIndexStmt *>(stmt);
  
  // Trx *trx = session->current_trx();
  // Table *table = create_unique_index_stmt->table();
  // std::vector<const FieldMeta*> fields_metas;
  // create_unique_index_stmt->fields_metas(fields_metas);
  // return table->create_unique_index(trx, fields_metas, create_unique_index_stmt->index_name().c_str());
}