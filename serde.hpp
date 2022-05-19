#include<vector>
#include<cstdint>
#include<cassert>

std::vector<uint8_t> serialize_int32(int32_t a) {
    auto bytes = std::vector<uint8_t>(4);

    bytes[0] = (uint8_t)(a >> 24) & 0xFF;
    bytes[1] = (uint8_t)(a >> 16) & 0xFF;
    bytes[2] = (uint8_t)(a >> 8) & 0xFF;
    bytes[3] = (uint8_t)a & 0xFF;

    return bytes;
}
static inline int32_t deserialize_int32(std::vector<uint8_t> bytes){
  assert(bytes.size() == 4);
  return (int32_t)(bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3]);

}
