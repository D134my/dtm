#include "get_reply.hpp"

namespace dtm::msg {
void get_reply_msg::set_value(std::uint32_t value) noexcept { _value = value; }
std::uint32_t get_reply_msg::get_value() const noexcept { return _value; }
void get_reply_msg::set_key(std::uint32_t key) noexcept { _key = key; }
std::uint32_t get_reply_msg::get_key() const noexcept { return _key; }

} // namespace dtm::msg