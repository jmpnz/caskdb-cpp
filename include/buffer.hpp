#pragma once

#include <vector>

namespace caskdb {

/**
 * @brief Buffer extends std::vector with Append operations.
 */
class Buffer {
 public:
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
   * @brief Clear the underlying the vector by zeroing its values.
   */
  inline void Clear() { data_.clear(); }
  /**
   * @brief Data returns the underlying vector.
   *
   * @return std::vector<uint8_t>
   */
  inline std::vector<uint8_t> Data() { return data_; }

 private:
  std::vector<uint8_t> data_;
};

}  // namespace caskdb
