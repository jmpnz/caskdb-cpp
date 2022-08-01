#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <stdexcept>

#include "doctest.h"
#include "file_manager.hpp"
#include "header.hpp"
#include "index_mem.hpp"
#include "serde.hpp"

using caskdb::Buffer, caskdb::FileManager, caskdb::Header;

TEST_CASE("testing int32/int64 serialization") {
  const int32_t expected_32 = 73095146;
  const int32_t actual_32 =
      serde::DeserializeInt32(serde::SerializeInt32(expected_32));

  const int64_t expected_64 = 390534043073095146;
  const int64_t actual_64 =
      serde::DeserializeInt64(serde::SerializeInt64(expected_64));
  CHECK(expected_32 == actual_32);
  CHECK(expected_64 == actual_64);
}

TEST_CASE("testing header serialization") {
  auto header = Header(1111, 10, 245);

  auto bytes = header.Serialize();
  CHECK(bytes.size() == 12);
  auto header_actual = Header().Deserialize(bytes);

  CHECK(header.ts == header_actual.ts);
  CHECK(header.keySize == header_actual.keySize);
  CHECK(header.valSize == header_actual.valSize);
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
    auto fm = FileManager("test");
    /* code */
  } catch (const std::exception& e) {
    fm.Close();
    std::cerr << e.what() << '\n';
  }
  CHECK(fm.IsOpen() == true);
  fm.Close();
}