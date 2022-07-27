#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "header.hpp"
#include "serde.hpp"

using namespace caskdb;

TEST_CASE("testing int32/int64 serialization") {
  const int32_t a = 73095146;
  const int32_t _a = serde::deserializeInt32(serde::serializeInt32(a));

  const int64_t b = 390534043073095146;
  const int64_t _b = serde::deserializeInt64(serde::serializeInt64(b));
  CHECK(a == _a);
  CHECK(b == _b);
}

TEST_CASE("testing header serialization") {
  auto header = Header(1111, 10, 245);

  auto bytes = header.serialize();
  CHECK(bytes.size() == 12);
  auto _header = Header().deserialize(bytes);

  CHECK(header.ts == _header.ts);
  CHECK(header.keySize == _header.keySize);
  CHECK(header.valSize == _header.valSize);
}