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
