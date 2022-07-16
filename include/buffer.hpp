// @file buffer.hpp
// @author jmpnz
// @desc In-memory buffer of bytes.
#include <cstdint>
#include <vector>

struct Buffer {
  // Current offset for read/write ops.
  int offset_;
  // Underlying buffer.
  std::vector<uint8_t> buf_;

  // Constructors
  Buffer(const std::vector<uint8_t>& buf) {
    offset_ = 0;
    buf_ = buf;
  }
  Buffer(int cap) {
    offset_ = 0;
    buf_ = std::vector<uint8_t>(cap);
  }
  // Append buffer.
  void Append(const std::vector<uint8_t>& buf) {
    int sz = buf.size();
    buf_.resize(sz);
    buf_.insert(buf_.end(), buf.begin(), buf.end());
  }
  // Read total bytes from buffer.
  std::vector<uint8_t> Read(int off,int total) {
    std::vector<uint8_t> buf(buf_.begin() + off,buf.end());
    return buf;
  }
  // Slice buffer.
  Buffer Slice(int start, int end) {
    auto buf = std::vector<uint8_t>(buf_.begin() + start, buf_.begin() + end - 1);
    return Buffer(buf);
  }

  // Data returns the raw underlying vector.
  std::vector<uint8_t> Data() { return buf_; }
  // Clear buffer.
  void Clear() { buf_.clear(); }
};
