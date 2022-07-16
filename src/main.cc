// @file store.cc
// @desc Implements a storage interface used to initate various low-level
// hashtables.
// @author jmpnz
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// C headers.
#include <cassert>
#include <cstdint>

// Include headers
#include "helpers.hpp"
#include "store.hpp"

int main() {
  auto db = DiskStorage<std::string, std::string>();
  auto cache = NaiveMapStorage<std::string, std::string>();
  // Timing 1,000,000 KV writes (on-disk).
  std::cout << "[+] Benchmarking CaskDB (On Disk):" << std::endl;
  auto start = helpers::now();
  for (int i = 0; i < 1000000; i++) {
    std::string key = "Alice" + std::to_string(i);
    std::string val = "Bob" + std::to_string(i * 2);
    db.Set(key, val);
  }
  auto end = helpers::now();
  auto diff = helpers::chrono_diff(start, end);
  std::cout << "[+] Insert 1,000,000 Key/Values :" << diff.count() << " ms"
            << std::endl;

  // Timing 1,000,000 KV reads.
  start = helpers::now();
  for (int i = 0; i < 1000000; i++) {
    std::string key = "Alice" + std::to_string(i);
    db.Get(key);
  }
  db.Close();
  end = helpers::now();

  diff = helpers::chrono_diff(start, end);
  std::cout << "[+] Read 1,000,000 Key/Values :" << diff.count() << " ms"
            << std::endl;
  // Timing 1,000,000 KV writes (in-mem) no-opt.
  std::cout << "[+] Benchmarking CaskDB (On Memory):" << std::endl;
  start = helpers::now();
  for (int i = 0; i < 1000000; i++) {
    std::string key = "Alice" + std::to_string(i);
    std::string val = "Bob" + std::to_string(i * 2);
    cache.Set(key, val);
  }
  end = helpers::now();
  diff = helpers::chrono_diff(start, end);
  std::cout << "[+] Insert 1,000,000 Key/Values :" << diff.count() << " ms"
            << std::endl;

  // Timing 1,000,000 KV reads.
  start = helpers::now();
  for (int i = 0; i < 1000000; i++) {
    std::string key = "Alice" + std::to_string(i);
    cache.Get(key);
  }
  end = helpers::now();

  diff = helpers::chrono_diff(start, end);
  std::cout << "[+] Read 1,000,000 Key/Values :" << diff.count() << " ms"
            << std::endl;
}
