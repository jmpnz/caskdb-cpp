#ifndef INDEX_MEM_HPP
#define INDEX_MEM_HPP
#include <string>
#include <unordered_map>

struct MemIndexMap {
  void Set(std::string key, std::string value) { index_[key] = value; }
  std::string Get(std::string key) { return index_[key]; }

 private:
  std::unordered_map<std::string, std::string> index_;
};

#endif