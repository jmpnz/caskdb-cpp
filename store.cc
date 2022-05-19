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
  auto cache = NaiveMapStorage<std::string,std::string>();
  cache.set("hello","world");
  
  auto db = DiskStorage<std::string, std::string>();

  std::cout << "Hello " << cache.get("hello") << std::endl;
  std::cout << "Hello World !" << std::endl;
  
  auto header= Header(1652659839,32,32);
  header.Debug();
  auto bytes = header.Serialize();
  std::cout << std::endl;
  auto header_copy = Header();
  header_copy.Deserialize(bytes);
  header_copy.Debug();


  header= Header(1652659839,32,32);
  header.Debug();
  bytes = header.Serialize();
  db.write(bytes);
  db.Set("Marco", "Polo");
  db.Close();
}
