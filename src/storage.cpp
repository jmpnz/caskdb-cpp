/**
 * @file storage.cpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief This file contains the implementation of DiskStorage which abstracts
 * an on-disk Log-Structured hashmap.
 * @version 0.1
 * @date 2022-08-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "storage.hpp"

#include "entry.hpp"
#include "header.hpp"

namespace caskdb {

/**
 * @brief Construct a new Disk Storage:: Disk Storage object
 *
 * @param file_name
 */
DiskStorage::DiskStorage(const std::string& file_name)
    : file_name_(file_name), fm_(file_name), index_() {}

void DiskStorage::Put(const std::string& key, const std::string& value) {
  Entry entry = Entry(utilities::TimestampNow(), fm_.WriteCursorOffset(),
                      kHeaderSize + key.size() + value.size());

  index_.Put(key, entry);
}

}  // namespace caskdb
