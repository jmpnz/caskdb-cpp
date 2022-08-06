/**
 * @file utils.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Utilities for timestamps and other miscellaneous functions.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <chrono>
#include <cstdint>

namespace caskdb {

using std::chrono::duration_cast, std::chrono::seconds, std::chrono::system_clock;

int64_t TimestampNow() {
  return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

}  // namespace caskdb
