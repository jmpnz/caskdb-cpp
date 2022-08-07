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
size_t const kHeaderSize = 12;

struct Header {
  int32_t ts;
  int32_t keySize;
  int32_t valSize;

  /**
   * @brief Construct a new Header object.
   *
   */
  explicit Header() : ts(0), keySize(0), valSize(0){};

  /**
   * @brief Construct a new Header object
   *
   * @param _ts
   * @param szKeySize
   * @param szValSize
   */
  explicit Header(int32_t _ts, int32_t szKeySize, int32_t szValSize)
      : ts(_ts), keySize(szKeySize), valSize(szValSize){};

  /**
   * @brief Serialize a header.
   *
   * @return std::vector<uint8_t>
   */
  std::vector<uint8_t> Serialize() {
    auto bytes = Buffer(kHeaderSize);
    // serialize all the struct members.
    auto tsBytes = serde::SerializeInt32(ts);
    auto szKeyBytes = serde::SerializeInt32(keySize);
    auto szValBytes = serde::SerializeInt32(valSize);
    // append the individual serialized members linearly.
    // this could be improved.
    bytes.Append(tsBytes);
    bytes.Append(szKeyBytes);
    bytes.Append(szValBytes);

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
    auto szKeySize = serde::DeserializeInt32(
        std::vector(bytes.begin() + 4, bytes.begin() + 8));
    auto szValSize =
        serde::DeserializeInt32(std::vector(bytes.begin() + 8, bytes.end()));

    return Header(ts, szKeySize, szValSize);
  }
};

}  // namespace caskdb