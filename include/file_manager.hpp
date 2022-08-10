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
 * @brief kDefaultLogFileName is the default log file name if no filename is
 * passed.
 *
 */
static const std::string kDefaultLogFileName = "caskette";

/**
 * @brief kDefaultFileMode is the mode used to open the log file.
 *
 */
static constexpr uint kDefaultFileMode =
    std::ios::in | std::ios::out | std::ios::app | std::ios::binary;

/**
 * @brief kDefaultNewFileMode is the mode used to create a new log file.
 *
 */
static constexpr uint kDefaultNewFileMode =
    std::ios::binary | std::ios::trunc | std::ios::app | std::ios::out;

/**
 * @brief kLogFileMagic is a 4 bytes fixed size header used to identify
 * log files.
 */
static constexpr uint8_t kLogFileMagic[4] = {0x4c, 0x64, 74, 69};

/**
 * @brief FileManager takes care of reading and writing from and to the
 * underlying log file. Reads and writes are currently implemented with no
 * optimizations, various strategies can be implemented such as buffering
 * and using fixed sized pages for reads and writes.
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

  explicit FileManager();

  /**
   * @brief Prevent FileManager from being copied
   *
   * @param other
   */
  FileManager(const FileManager& other) = delete;
  FileManager& operator=(const FileManager& other) = delete;

  /**
   * @brief Enforce default move constructor for the FileManager.
   * Since both members are default types that implement the move constructor
   * we don't need to be explicit.
   * @param other
   */
  FileManager(FileManager&& other) = default;
  FileManager& operator=(FileManager&& other) = default;

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
