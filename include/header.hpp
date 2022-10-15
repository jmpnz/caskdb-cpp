/**
 * @file header.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Header is defined as part of the caskdb file format.
 * @version 0.1
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>

#include "buffer.hpp"
#include "serde.hpp"

namespace caskdb {

/**
 * @brief kHeaderSize constant stores the size of the header.
 *
 */
const size_t HEADER_SIZE = 12;

struct Header {
  int32_t ts_;
  int32_t key_size_;
  int32_t val_size_;

  /**
   * @brief Construct a new Header object.
   *
   */
  explicit Header() : ts_(0), key_size_(0), val_size_(0){};

  /**
   * @brief Construct a new Header object
   *
   * @param _ts
   * @param szKeySize
   * @param szValSize
   */
  explicit Header(int32_t _ts, int32_t szKeySize, int32_t szValSize)
      : ts_(_ts), key_size_(szKeySize), val_size_(szValSize){};

  /**
   * @brief Serialize a header.
   *
   * @return std::vector<uint8_t>
   */
  std::vector<uint8_t> Serialize() {
    auto bytes = Buffer(HEADER_SIZE);
    // serialize all the struct members.
    auto ts_bytes = serde::SerializeInt32(ts_);
    auto sz_key_bytes = serde::SerializeInt32(key_size_);
    auto sz_val_bytes = serde::SerializeInt32(val_size_);
    // append the individual serialized members linearly.
    // this could be improved.
    bytes.Append(ts_bytes);
    bytes.Append(sz_key_bytes);
    bytes.Append(sz_val_bytes);

    return bytes.Data();
  }

  /**
   * @brief Deserialize a header.
   *
   * @param bytes
   * @return Header
   */
  Header Deserialize(const std::vector<uint8_t>& bytes) {
    auto ts =
        serde::DeserializeInt32(std::vector(bytes.begin(), bytes.begin() + 4));
    auto sz_key_size = serde::DeserializeInt32(
        std::vector(bytes.begin() + 4, bytes.begin() + 8));
    auto sz_val_size =
        serde::DeserializeInt32(std::vector(bytes.begin() + 8, bytes.end()));

    return Header(ts, sz_key_size, sz_val_size);
  }
};

}  // namespace caskdb
