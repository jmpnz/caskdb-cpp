/**
 * @file file_manager.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief FileManager takes care of all on-diks I/O.
 * @version 0.1
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

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
  // Filename.
  std::string file_name_;
  // Stream to write the log file.
  std::fstream file_;
  // Last written position.

 public:
  /**
   * @brief Construct a new File Manager object
   *
   * @param file_name
   */
  explicit FileManager(const std::string& file_name);

  ~FileManager() = default;

  /**
   * @brief Read from offset.
   *
   * @param offset
   * @return std::vector<uint8_t>
   */
  std::vector<uint8_t> Read(size_t offset, size_t length);

  /**
   * @brief Write bytes to log file.
   *
   * @param bytes
   */
  void Write(const std::vector<uint8_t>& bytes);

  /**
   * @brief Close underlying log file.
   *
   */
  void Close();

  /**
   * @brief Check if log file is open.
   *
   * @return true
   * @return false
   */
  auto IsOpen() -> bool;

  /**
   * @brief Return read cursor offset.
   *
   * @return size_t
   */
  auto ReadCursorOffset() -> size_t;

  /**
   * @brief Return write cursor offset.
   *
   * @return size_t
   */
  auto WriteCursorOffset() -> size_t;

  /**
   * @brief Return log file name.
   *
   * @return std::string
   */
  std::string LogFile();
};

}  // namespace caskdb
