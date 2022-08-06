/**
 * @file index_mem.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief An in-memory key-value store implemented around an unordered_map.
 * @version 0.1
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include <unordered_map>

#include "entry.hpp"

namespace caskdb {

/**
 * @brief MemIndexMap implements an in-memory index using std::unordered_map.
 * It maps keys to their Entry metadata.
 */
class MemIndexMap {
 public:
  /**
   * @brief Store a key and value.
   *
   * @param key
   * @param value
   */
  void Put(std::string key, Entry value) { index_[key] = value; }
  /**
   * @brief Get a value by its key, if the key is not in the map the null entry
   * is returned, see kNullEntry.
   *
   * @param key
   * @return caskdb::Entry
   */
  caskdb::Entry Get(std::string key) {
    if (index_.contains(key)) {
      return index_[key];
    }
    return kNullEntry; 
  }

 private:
  std::unordered_map<std::string, caskdb::Entry> index_;
};

}  // namespace caskdb
