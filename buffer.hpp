// @file buffer.hpp
// @author jmpnz
// @desc In-memory buffer of bytes.
#include <cstdint>
#include <vector>

struct Buffer {
  int len_;
  std::vector<uint8_t> buf_;

  // Constructors
  Buffer(const std::vector<uint8_t>& buf) {
    len_ = buf.size();
    buf_ = buf;
  }
  Buffer(int cap) {
    len_ = 0;
    buf_ = std::vector<uint8_t>(cap);
  }
  // Append buffer.
  void Append(const std::vector<uint8_t>& buf) {
    len_ += buf.size();
    buf_.resize(len_);
    buf_.insert(buf_.end(), buf.begin(), buf.end());
  }
  // Slice buffer.
  Buffer Slice(int start, int end) {
    auto buf = std::vector<uint8_t>(buf_.begin() + start, buf_.begin() + end - 1);
    return Buffer(buf);
  }
  // Clear buffer.
  void Clear() { buf_.clear(); }
};