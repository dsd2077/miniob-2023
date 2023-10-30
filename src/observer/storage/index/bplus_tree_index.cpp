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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept
{
  close();
}

// T10修改：适应多列联合索引
RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s",
        file_name,
        index_meta.name()
        );
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);  // 调用父类构造函数，初始化索引的元信息和相应字段的元信息

  std::vector<AttrType> attrs;
  std::vector<int> attrs_lengths;
  for(int i = 0 ; i < field_meta.size() ; i ++ ) {
    attrs.emplace_back(field_meta[i].type());
    attrs_lengths.emplace_back(field_meta[i].len());
  }
  RC rc = index_handler_.create(file_name, attrs, attrs_lengths);  // 这里真正地创建索引文件，这里调用的是B+树句柄的create函数
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, rc:%s",
        file_name,
        index_meta.name(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully create index, file_name:%s, index:%s", file_name, index_meta.name());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s",
        file_name,
        index_meta.name()
    );
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);

  RC rc = index_handler_.open(file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, rc:%s",
        file_name,
        index_meta.name(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully open index, file_name:%s, index:%s", file_name, index_meta.name());
  return RC::SUCCESS;
}

// // 多列情况的索引
// RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> &fields_metas)
// {
//   if(inited_) {
//     std::vector<std::string> fields;
//     index_meta.fields(fields);
//     std::string res = "";
//     for(int i = 0 ; i < fields.size() ; i ++ ) {
//       if(i > 0) {
//         res += ",";
//       }
//       res += fields[i];
//     }
//     LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
//         file_name,
//         index_meta.name(),
//         res);
//     return RC::RECORD_OPENNED;
//   }

//   Index::init(index_meta, fields_metas);
  

//   inited_ = true;
  
// }

// RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> &fileds_metas)
// {

// }

RC BplusTreeIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index:%s", index_meta_.name());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid)
{
  // T10修改：这里需要将record中真正对应索引的字段取出，组成B+树中真正的Key
  
  // return index_handler_.insert_entry(record + field_meta_.offset(), rid);
  return index_handler_.insert_entry(record, rid);
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid)
{
  // return index_handler_.delete_entry(record + field_meta_.offset(), rid);
  return index_handler_.delete_entry(record, rid);
}

IndexScanner *BplusTreeIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync()
{
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler)
{}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept
{
  tree_scanner_.close();
}

RC BplusTreeIndexScanner::open(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid)
{
  return tree_scanner_.next_entry(*rid);
}

RC BplusTreeIndexScanner::destroy()
{
  delete this;
  return RC::SUCCESS;
}
