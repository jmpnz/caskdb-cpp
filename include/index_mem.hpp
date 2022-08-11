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

#include <map>
#include <optional>
#include <string>

#include "entry.hpp"

namespace caskdb {

/**
 * @brief MemIndexMap implements an in-memory index using std::map.
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
  void Put(std::string key, Entry value) { index_.emplace(key, value); }

  /**
   * @brief Get a value by its key, if the key is not in the map returns an
   * empty value.
   * @param key
   * @return std::optional<caskdb::Entry>
   */
  std::optional<caskdb::Entry> Get(std::string key) {
    if (index_.contains(key)) {
      return index_[key];
    }
    return {};
  }

 private:
  std::map<std::string, caskdb::Entry> index_;
};

}  // namespace caskdb
