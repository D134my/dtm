#ifndef __dtm_what_value__
#define __dtm_what_value__

#include <cstdint>

namespace dtm::msg {
class what_value_msg {
public:
  void set_value(std::uint32_t value) noexcept;
  std::uint32_t get_value() const noexcept;

private:
  std::uint32_t _value;
};
} // namespace dtm::msg

#endif