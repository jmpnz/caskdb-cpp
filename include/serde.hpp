#ifndef SERDE_HPP
#define SERDE_HPP
#include <cassert>
#include <vector>

namespace serde {

// serialize int32_t (4 bytes) by linearly slicing it to 4 octets.
std::vector<uint8_t> serialize_int32(int32_t x) {
  auto bytes = std::vector<uint8_t>(4);

  bytes[0] = (uint8_t)(x >> 24 & 0xFF);
  bytes[1] = (uint8_t)(x >> 16 & 0xFF);
  bytes[2] = (uint8_t)(x >> 8 & 0xFF);
  bytes[3] = (uint8_t)(x & 0xFF);

  return bytes;
}
// deserialize int32 by concatenating the octets.
static inline int32_t deserialize_int32(std::vector<uint8_t> bytes) {
  assert(bytes.size() == 4);
  return int32_t(bytes.at(0) << 24 | bytes.at(1) << 16 | bytes.at(2) << 8 |
                 bytes.at(3));
}
}  // namespace serde

#endif