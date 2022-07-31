#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <vector>

namespace buffer {

// Buffer wraps an std::vector with buffered operations including appends.
struct Buffer {
  // Constructor with capacity
  Buffer(size_t cap) { data_.reserve(cap); }

  // Append a vector to the buffer.
  inline void Append(const std::vector<uint8_t>& v) {
    data_.insert(data_.end(), v.begin(), v.end());
  }
  // Clear zeroes out a vector for re-use keeping it allocated.
  inline void Clear() { data_.clear(); }
  // Data returns the underlying vector.
  inline std::vector<uint8_t> Data() { return data_; }

 private:
  std::vector<uint8_t> data_;
};

}  // namespace buffer

#endif