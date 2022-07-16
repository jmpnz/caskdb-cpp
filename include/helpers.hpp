#include <chrono>

using timepoint_ = std::chrono::steady_clock::time_point;

namespace helpers {

inline auto now() { return std::chrono::high_resolution_clock::now(); }

inline auto chrono_diff(timepoint_ start, timepoint_ end) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

}  // namespace helpers