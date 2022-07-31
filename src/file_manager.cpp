#include "file_manager.hpp"

#include <fstream>
#include <memory>
#include <string>

namespace caskdb {

FileManager::FileManager(std::string file_name) {
  file_name_ = file_name;
  file_.open(file_name_, std::ios::out | std::ios::app | std::ios::binary);
}

std::string FileManager::FileName() { return file_name_; }

void FileManager::Close() { file_.close(); }

}  // namespace caskdb