/**
 * @file buffer.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Buffer extends std::vector with more ergonomic operations.
 * @version 0.1
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>

namespace caskdb {

/**
 * @brief Buffer extends std::vector with Append operations.
 */
class Buffer {
 public:
  /**
   * @brief Construct a new empty Buffer object.
   *
   */
  Buffer() : data_() {}

  /**
   * @brief Construct a new Buffer object from std::vector<uint8_t>
   *
   * @param data
   */
  Buffer(std::vector<uint8_t> data) : data_(data) {}

  /**
   * @brief Construct a new Buffer object from const char*
   *
   * @param data
   */
  Buffer(const char* data, size_t length) : data_(data, data + length) {}

  /**
   * @brief Construct a new Buffer object with a pre-defined
   * capacity.
   * @param cap
   */
  Buffer(size_t cap) { data_.reserve(cap); }

  /**
   * @brief Append an std::vector to the underlying.
   * @param v
   */
  inline void Append(const std::vector<uint8_t>& v) {
    data_.insert(data_.end(), v.begin(), v.end());
  }

  /**
   * @brief Append a const char* to the underlying.
   *
   * @param v
   * @param length
   */
  inline void Append(const char* v, size_t length) {
    data_.insert(data_.end(), v, v + length);
  }

  inline void InsertFront(const std::vector<uint8_t>& v) {
    data_.insert(data_.begin(), v.begin(), v.end());
  }

  /**
   * @brief Clear the underlying the vector by zeroing its values.
   */
  inline void Clear() { data_.clear(); }

  /**
   * @brief Data returns the underlying vector.
   *
   * @return std::vector<uint8_t>
   */
  inline std::vector<uint8_t> Data() { return data_; }

  /**
   * @brief Return the underlying data contained in the vector.
   *
   * @return uint8_t*
   */
  inline const uint8_t* data() { return data_.data(); }

 private:
  std::vector<uint8_t> data_;
};

}  // namespace caskdb
