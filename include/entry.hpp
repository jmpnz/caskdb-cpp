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
  /**
   * @brief Construct a new Entry object
   *
   */
  Entry() : timestamp_(0), position_(0), size_(0) {}

  /**
   * @brief Construct a new Entry object
   *
   * @param ts
   * @param pos
   * @param sz
   */
  Entry(int64_t ts, int64_t pos, int64_t sz)
      : timestamp_(ts), position_(pos), size_(sz) {}

  /**
   * @brief Return entry timestamp.
   *
   * @return int64_t
   */
  auto Timestamp() -> int64_t { return timestamp_; }

  /**
   * @brief  Return entry position in the file.
   *
   * @return int64_t
   */
  auto Position() -> int64_t { return position_; }

  /**
   * @brief Return entry data size in bytes.
   *
   * @return int64_t
   */
  auto Size() -> int64_t { return size_; }

  /**
   * @brief Return true if the entry is Null.
   *
   * @return true
   * @return false
   */
  auto IsNull() -> bool { return (size_ == -1 && position_ == -1); }

 private:
  int64_t timestamp_;
  int64_t position_;
  int64_t size_;
};

/**
 * @brief kNullEntry is used to represent a null entry in the map.
 * A null entry is one that doesn't have a key, this is preferred to
 * using pointers and dealing with null down the line.
 * The null entry has size and position set to -1.
 */
static const Entry kNullEntry = Entry(0, -1, -1);

}  // namespace caskdb
