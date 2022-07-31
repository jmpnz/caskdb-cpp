#include "file_manager.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace caskdb {

/**
 * @brief Construct a new File Manager object.
 *
 * @param file_name
 */
FileManager::FileManager(const std::string& file_name) {
  file_name_ = file_name + ".log";
  file_.open(file_name_,
             std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
  if (!file_.is_open()) {
    // if the file doesn't exist, create a new one.
    file_.clear();
    file_.open(file_name_, std::ios::binary | std::ios::trunc | std::ios::app |
                               std::ios::out);
    file_.close();
    // re-open the file with the original mode.
    file_.open(file_name_,
               std::ios::binary | std::ios::in | std::ios::app | std::ios::out);
    if (!file_.is_open()) {
      throw std::runtime_error("Invalid operation, file could not be opened.");
    }
  }
}

std::string FileManager::FileName() { return file_name_; }

void FileManager::Close() { file_.close(); }

}  // namespace caskdb