#ifndef SERDE_TEST_HPP
#define SERDE_TEST_HPP

#include <iostream>

#include "serde.hpp"

void TestSerde() {
  std::cout << "[+] TestSerde: \n";

  const int32_t a = 73095146;
  const int32_t _a = serde::deserialize_int32(serde::serialize_int32(a));
  assert(a == _a);

  std::cout << "    Successful !!!" << std::endl;
}
#endif