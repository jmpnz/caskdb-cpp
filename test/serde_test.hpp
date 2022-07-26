#ifndef SERDE_TEST_HPP
#define SERDE_TEST_HPP

#include <iostream>

#include "serde.hpp"

void TestSerde() {
  std::cout << "[+] TestSerde: \n";

  const int32_t a = 73095146;
  const int32_t _a = serde::deserialize_int32(serde::serialize_int32(a));
  assert(a == _a);

  const int64_t b = 390534043073095146;
  const int64_t _b = serde::deserialize_int64(serde::serialize_int64(b));
  assert(b == _b);
  std::cout << "    Successful !!!" << std::endl;
}
#endif