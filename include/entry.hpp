/**
 * @file entry.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Entry represents metadata about a key bound to an on-disk value.
 * @version 0.1
 * @date 2022-08-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <cstdint>

namespace caskdb {

struct Entry {
  Entry() : timestamp_(0), position_(0), size_(0) {}
  Entry(int64_t ts, int64_t pos, int64_t sz) : timestamp_(ts), position_(pos), size_(sz) {}

  auto Timestamp() -> int64_t { return timestamp_; }
  auto Position() -> int64_t { return position_; }
  auto Size() -> int64_t { return size_; }

 private:
  int64_t timestamp_;
  int64_t position_;
  int64_t size_;
};

}  // namespace caskdb
