#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace caskdb {

/**
 * @brief FileManager takes care of reading and writing from and to the
 * underlying log file. Reads and wrties are currently implemented with no
 * optimizations, various strategies can be implemented such as buffering and
 * using fixed sized pages for reads and writes.
 */
class FileManager {
  std::string file_name_;
  std::fstream file_;

 public:
  FileManager(const std::string& file_name);
  void Read();
  void Write();
  void Close();
  std::string FileName();
};

}  // namespace caskdb
