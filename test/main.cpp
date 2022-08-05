#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <stdexcept>

#include "doctest.h"
#include "entry.hpp"
#include "file_manager.hpp"
#include "header.hpp"
#include "index_mem.hpp"
#include "serde.hpp"
#include "utils.hpp"

using caskdb::Buffer, caskdb::FileManager, caskdb::Header;

namespace serde = caskdb::serde;
namespace utils = caskdb::utilities;

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
  auto index = caskdb::MemIndexMap();
  auto entry = caskdb::Entry(123456, 999, 64);
  auto [k, v] = std::tie("Alice", entry);
  index.Put(k, v);
  CHECK(index.Get(k).Timestamp() == v.Timestamp());
  CHECK(index.Get(k).Position() == v.Position());
  CHECK(index.Get(k).Size() == v.Size());
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

TEST_CASE("tesing file manager IO") {
  auto fm = FileManager("test");
  // Write 128 bytes of 0xff
  std::vector<uint8_t> bytes(128, 0xff);
  fm.Write(bytes, 0);
  // Write 128 bytes of 0x41
  std::vector<uint8_t> abytes(128, 0x41);
  fm.Write(abytes, 128);
  // Read from offset 0 should be 64,0xff.
  auto expected_one = fm.Read(64, 0);
  // Read from offset 128 + 64 should be 64, 0x41.
  auto expected_two = fm.Read(64, 128 + 64);
  // actually expected values.
  auto actual_one = std::vector(bytes.begin(), bytes.begin() + 64);
  auto actual_two = std::vector(abytes.begin(), abytes.begin() + 64);

  CHECK(expected_one == actual_one);
  CHECK(expected_two == actual_two);

  fm.Close();
}

TEST_CASE("testing current timestamp") { CHECK(utils::TimestampNow() > 0); }