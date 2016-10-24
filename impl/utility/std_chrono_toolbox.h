#include <chrono>
#include <ostream>

namespace vita {

namespace impl {
template<typename CharType, typename Traits,
         typename RepType, typename PeriodType>
std::basic_ostream<CharType,Traits>& operator<<(
    std::basic_ostream<CharType,Traits>& os,
    const std::chrono::duration<RepType, PeriodType>& some_duration) {
  os << some_duration.count() <<
      " [" << PeriodType::num << "/" << PeriodType::den << "]s" << std::endl;
  return os;
}
}  // impl

}  // vita
