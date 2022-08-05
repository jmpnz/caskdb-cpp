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
std::vector<uint8_t> SerializeInt32(int32_t x);

/**
 * @brief Deserialize int32 by concatenating the octets.
 *
 * @param bytes
 * @return int32_t
 */
int32_t DeserializeInt32(std::vector<uint8_t> const& bytes);

/**
 * @brief Serialize int64 by splitting the 64-bit integer to two equal 32-bit
 * parts.
 *
 * @param x
 * @return std::vector<uint8_t>
 */
std::vector<uint8_t> SerializeInt64(int64_t x);

/**
 * @brief Deserialize int32 by concatenating the 2 words.
 *
 * @param bytes
 * @return int64_t
 */
int64_t DeserializeInt64(std::vector<uint8_t> const& bytes);

}  // namespace caskdb::serde
