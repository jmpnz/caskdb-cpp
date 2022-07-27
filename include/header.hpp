#ifndef HEADER_HPP
#define HEADER_HPP
#include <span>
#include <vector>

#include "buffer.hpp"
#include "serde.hpp"

namespace caskdb {

size_t const szHeaderSize = 12;

struct Header {
  int32_t ts;
  int32_t keySize;
  int32_t valSize;
  // Default constructor zeroes all members.
  Header() : ts(0), keySize(0), valSize(0){};
  // Full constructor.
  Header(int32_t _ts, int32_t szKeySize, int32_t szValSize)
      : ts(_ts), keySize(szKeySize), valSize(szValSize){};

  // Serialize a header.
  std::vector<uint8_t> serialize() {
    auto bytes = buffer::Buffer(szHeaderSize);
    // serialize all the struct members.
    auto tsBytes = serde::serializeInt32(ts);
    auto szKeyBytes = serde::serializeInt32(keySize);
    auto szValBytes = serde::serializeInt32(valSize);
    // append the individual serialized members linearly.
    // this could be improved.
    bytes.append(tsBytes);
    bytes.append(szKeyBytes);
    bytes.append(szValBytes);

    return bytes.data();
  }

  // Deserialize a header.
  Header deserialize(std::vector<uint8_t> bytes) {
    auto ts =
        serde::deserializeInt32(std::vector(bytes.begin(), bytes.begin() + 4));
    auto szKeySize = serde::deserializeInt32(
        std::vector(bytes.begin() + 4, bytes.begin() + 8));
    auto szValSize =
        serde::deserializeInt32(std::vector(bytes.begin() + 8, bytes.end()));

    return Header(ts, szKeySize, szValSize);
  }
};

}  // namespace caskdb
#endif