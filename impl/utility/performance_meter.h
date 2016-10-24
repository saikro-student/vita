#include "impl/utility/std_chrono_toolbox.h"

namespace vita {

namespace impl {
template<typename CharType = char, typename Traits = std::char_traits<CharType>>
class ScopedPerformanceMeterBase {
 public:
   ScopedPerformanceMeterBase(std::basic_ostream<CharType,Traits>& os) :
      os_{os},
      start_{std::chrono::high_resolution_clock::now()} {
  }

  ~ScopedPerformanceMeterBase() {
    os_ << std::chrono::high_resolution_clock::now() - start_;
  }

 private:
  std::basic_ostream<CharType,Traits>& os_;
  std::chrono::high_resolution_clock::time_point start_;
};

using ScopedPerformanceMeter = ScopedPerformanceMeterBase<char>;
using WScopedPerformanceMeter = ScopedPerformanceMeterBase<wchar_t>;
}  // impl

}  // vita
