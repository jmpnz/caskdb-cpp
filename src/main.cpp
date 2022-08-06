#include <iostream>
#include <tuple>
#include <chrono>
#include "utils.hpp"
#include "storage.hpp"

int main() {
  auto db = caskdb::DiskStorage("bench.test");
  std::cout << "Benchmark 1 million insert" << '\n';

  auto start = caskdb::TimestampNow();
  for (int i = 0;i < 1000000;i++) {
    auto [k,v] = std::make_tuple<std::string, std::string>(
      "Alice" + std::to_string(i), "Lorem Ipsum Something Something" + std::to_string(i * 2)
    );
    db.Put(k,v);
  }
  auto end = caskdb::TimestampNow();

  auto diff = end - start;

  std::cout << "Took " << diff << " seconds" << '\n';
}