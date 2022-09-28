#include "what_value.hpp"

namespace dtm::msg {
void what_value_msg::set_value(std::uint32_t value) noexcept { _value = value; }
std::uint32_t what_value_msg::get_value() const noexcept { return _value; }
} // namespace dtm::msg