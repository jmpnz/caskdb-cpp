#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <fstream>
#include <memory>
#include <string>

namespace caskdb {

// File Manager abstracts all file operations.
class FileManager {
  std::string file_name_;
  std::fstream file_;

 public:
  FileManager(std::string file_name);
  void Read();
  void Write();
  void Close();
  std::string FileName();
};

}  // namespace caskdb

#endif