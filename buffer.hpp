// @file buffer.hpp
// @author jmpnz
// @desc In-memory buffer of bytes.
#include <vector>
#include <cstdint>

struct Buffer {
    int len_;
    std::vector<uint8_t> buf_;

    // Constructors
    Buffer(const std::vector<uint8_t>& buf) {
        len_ = buf.size();
        buf_ = buf;
    }
    // Append buffer.
    void Append(const std::vector<uint8_t>& buf) {
        len_ += buf.size();
        buf_.resize(len_);
        buf_.insert(buf_.end(), buf.begin(), buf.end());
    }
    // Clear buffer.
    void Clear() {
        buf_.clear();
    }
};