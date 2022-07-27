#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <vector>

namespace buffer {

// Buffer wraps an std::vector with buffered operations including appends.
struct Buffer {
  // Constructor with capacity
  Buffer(size_t cap) { data_.reserve(cap); }

  // append a vector to the buffer.
  inline void append(std::vector<uint8_t> v) {
    data_.insert(data_.end(), v.begin(), v.end());
  }
  // clear zeroes out a vector for re-use keeping it allocated.
  inline void clear() { data_.clear(); }
  // data returns the underlying vector.
  inline std::vector<uint8_t> data() { return data_; }

 private:
  std::vector<uint8_t> data_;
};

}  // namespace buffer

#endif