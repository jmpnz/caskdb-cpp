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

/**
 * @brief MemIndexMap implements an in-memory index using std::unordered_map.
 *
 */
class MemIndexMap {
 public:
  /**
   * @brief Store a key and value.
   *
   * @param key
   * @param value
   */
  void Set(std::string key, std::string value) { index_[key] = value; }
  /**
   * @brief Get a value by its key.
   *
   * @param key
   * @return std::string
   */
  std::string Get(std::string key) { return index_[key]; }

 private:
  std::unordered_map<std::string, std::string> index_;
};
