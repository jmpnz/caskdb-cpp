/**
 * @file serde.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief This file implements linear binary encoding for int32_t and int64_t
 * types.
 * @version 0.1
 * @date 2022-08-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cassert>
#include <vector>

namespace caskdb::serde {

/**
 * @brief Serialize int32_t (4 bytes) by linearly slicing it to 4 octets.
 *
 * @param x
 * @return std::vector<uint8_t>
 */
inline std::vector<uint8_t> SerializeInt32(int32_t x) {
  auto bytes = std::vector<uint8_t>(4);

  bytes[0] = static_cast<uint8_t>(x >> 24 & 0xFF);
  bytes[1] = static_cast<uint8_t>(x >> 16 & 0xFF);
  bytes[2] = static_cast<uint8_t>(x >> 8 & 0xFF);
  bytes[3] = static_cast<uint8_t>(x & 0xFF);

  return bytes;
}

/**
 * @brief Deserialize int32 by concatenating the octets.
 *
 * @param bytes
 * @return int32_t
 */
inline int32_t DeserializeInt32(std::vector<uint8_t> const& bytes) {
  assert(bytes.size() == 4);
  return (bytes.at(0) << 24 | bytes.at(1) << 16 | bytes.at(2) << 8 |
          bytes.at(3));
}

/**
 * @brief Serialize int64 by splitting the 64-bit integer to two equal 32-bit
 * parts.
 *
 * @param x
 * @return std::vector<uint8_t>
 */
inline std::vector<uint8_t> SerializeInt64(int64_t x) {
  auto bytes = std::vector<uint8_t>(8);

  bytes[0] = static_cast<uint8_t>(x >> 56 & 0xff);
  bytes[1] = static_cast<uint8_t>(x >> 48 & 0xff);
  bytes[2] = static_cast<uint8_t>(x >> 40 & 0xff);
  bytes[3] = static_cast<uint8_t>(x >> 32 & 0xff);
  bytes[4] = static_cast<uint8_t>(x >> 24 & 0xff);
  bytes[5] = static_cast<uint8_t>(x >> 16 & 0xff);
  bytes[6] = static_cast<uint8_t>(x >> 8 & 0xff);
  bytes[7] = static_cast<uint8_t>(x & 0xff);

  return bytes;
}

/**
 * @brief Deserialize int32 by concatenating the 2 words.
 *
 * @param bytes
 * @return int64_t
 */
inline int64_t DeserializeInt64(std::vector<uint8_t> const& bytes) {
  uint64_t value = static_cast<uint64_t>(bytes[0]) << 56 |
                   static_cast<uint64_t>(bytes[1]) << 48 |
                   static_cast<uint64_t>(bytes[2]) << 40 |
                   static_cast<uint64_t>(bytes[3]) << 32 |
                   static_cast<uint64_t>(bytes[4]) << 24 |
                   static_cast<uint64_t>(bytes[5]) << 16 |
                   static_cast<uint64_t>(bytes[6]) << 8 |
                   static_cast<uint64_t>(bytes[7]);

  return value;
}

}  // namespace caskdb::serde
