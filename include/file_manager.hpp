#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace caskdb {

/**
 * @brief FileManager takes care of reading and writing from and to the
 * underlying log file. Reads and writes are currently implemented with no
 * optimizations, various strategies can be implemented such as buffering and
 * using fixed sized pages for reads and writes.
 */
class FileManager {
  std::string file_name_;
  std::fstream file_;

 public:
  explicit FileManager(const std::string& file_name);
  void Read();
  std::vector<uint8_t> Write();
  void Close();
  auto IsOpen() -> bool;
  std::string LogFile();
};

}  // namespace caskdb
