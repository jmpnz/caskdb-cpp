#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <stdexcept>

#include "doctest.h"
#include "file_manager.hpp"
#include "header.hpp"
#include "index_mem.hpp"
#include "serde.hpp"

using namespace caskdb;

TEST_CASE("testing int32/int64 serialization") {
  const int32_t a = 73095146;
  const int32_t _a = serde::DeserializeInt32(serde::SerializeInt32(a));

  const int64_t b = 390534043073095146;
  const int64_t _b = serde::DeserializeInt64(serde::SerializeInt64(b));
  CHECK(a == _a);
  CHECK(b == _b);
}

TEST_CASE("testing header serialization") {
  auto header = Header(1111, 10, 245);

  auto bytes = header.Serialize();
  CHECK(bytes.size() == 12);
  auto _header = Header().Deserialize(bytes);

  CHECK(header.ts == _header.ts);
  CHECK(header.keySize == _header.keySize);
  CHECK(header.valSize == _header.valSize);
}

TEST_CASE("testing in-memory index") {
  auto index = MemIndexMap();
  auto [k, v] = std::tie("Alice", "Hello !");
  index.Set(k, v);
  CHECK(index.Get(k) == v);
}

TEST_CASE("testing file manager") {
  auto fm = FileManager("test");

  try {
    fm = FileManager("test");
    /* code */
  } catch (const std::exception& e) {
    fm.Close();
    std::cerr << e.what() << '\n';
  }
  CHECK(fm.IsOpen() == true);
  fm.Close();
}