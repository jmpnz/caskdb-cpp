// @file store.cc
// @desc Implements a storage interface used to initate various low-level hashtables.
// @author jmpnz
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<vector>

// C headers.
#include<cassert>
#include<cstdint>

// Include headers
#include "store.hpp"

int main(int argc, char* argv[]){
  auto db = DiskStorage<std::string, std::string>();
  // Timing 1,000,000 KV writes.
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0;i < 1000000;i++) {
    std::string key = "Alice" + std::to_string(i);
    std::string val = "Bob" + std::to_string(i*2);
    db.Set(key,val);
  }
  db.Close();
  auto end = std::chrono::high_resolution_clock::now();
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "[+] Benchmarking CaskDB :" << std::endl;
  std::cout << "[+] Insert 1,000,000 Key/Values :" << diff.count() << " ms" << std::endl;

}
