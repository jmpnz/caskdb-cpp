/**
 * @file storage.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Header file for the storage engine.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "file_manager.hpp"
#include "index_mem.hpp"
#include "utils.hpp"

namespace caskdb {
/**
 * @brief DiskStorage implements the caskdb storage engine using FileManager as
 * an I/O backend and MemIndexMap as an in-memory index.
 *
 */
class DiskStorage {
  // Filename
  std::string file_name_;
  // File manager
  FileManager fm_;
  // In-memory index
  MemIndexMap index_;

 public:
  /**
   * @brief Construct a new Disk Storage object
   *
   * @param file
   */
  explicit DiskStorage(const std::string& file);

  ~DiskStorage() = default;

  void Put(const std::string& key, const std::string& value);
};

}  // namespace caskdb
