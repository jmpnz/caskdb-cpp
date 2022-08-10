/**
 * @file file_manager.cpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief This file contains the implementation of FileManager class for
 * managing log files.
 * @version 0.1
 * @date 2022-08-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "file_manager.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace caskdb {

/**
 * @brief Construct a new File Manager object.
 *
 * @param file_name
 */
FileManager::FileManager(const std::string& file_name) {
  file_name_ = file_name + ".log";
  file_.open(file_name_, kDefaultFileMode);
  if (!file_.is_open()) {
    // if the file doesn't exist, create a new one.
    file_.clear();
    file_.open(file_name_, kDefaultNewFileMode);
    file_.close();
    // re-open the file with the original mode.
    file_.open(file_name_, kDefaultFileMode);
    if (!file_.is_open()) {
      throw std::runtime_error("Invalid operation, file could not be opened.");
    }
  }
}

/**
 * @brief Implement the default constructor for a new File Manager:: File
 * Manager object
 *
 */
FileManager::FileManager() : FileManager(kDefaultLogFileName) {}

/**
 * @brief Write a sequence of bytes to the log file.
 *
 * @param bytes
 */
void FileManager::Write(const std::vector<uint8_t>& bytes) {
  // Seek, write and flush.
  file_.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
  file_.flush();
}

/**
 * @brief Read a sequence of bytes from the log file, starting at offset.
 *
 * @param offset
 * @return std::vector
 */
std::vector<uint8_t> FileManager::Read(size_t offset, size_t length) {
  std::vector<uint8_t> buf(length);
  file_.seekg(offset);
  file_.read(reinterpret_cast<char*>(buf.data()), length);
  return buf;
}

/**
 * @brief Close the underlying log file.
 *
 */
void FileManager::Close() {
  file_.flush();
  file_.close();
}

/**
 * @brief Returns true if the underlying log file is open false otherwise.
 *
 * @return true
 * @return false
 */
auto FileManager::IsOpen() -> bool { return file_.is_open(); }

/**
 * @brief Return the current offset of the read cursor (i.e position after last
 * read).
 *
 * @return size_t
 */
auto FileManager::ReadCursorOffset() -> size_t { return file_.tellg(); }

/**
 * @brief Return the current offset of the write cursor (i.e position after last
 * write).
 *
 * @return size_t
 */
auto FileManager::WriteCursorOffset() -> size_t { return file_.tellp(); }

/**
 * @brief Return the underlying log file name.
 *
 * @return std::string
 */
std::string FileManager::LogFile() { return file_name_; }

}  // namespace caskdb