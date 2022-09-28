#include "put_reply.hpp"

namespace dtm::msg {
void put_reply_msg::set_value(std::uint32_t value) noexcept { _value = value; }
std::uint32_t put_reply_msg::get_value() const noexcept { return _value; }
void put_reply_msg::set_key(std::uint32_t key) noexcept { _key = key; }
std::uint32_t put_reply_msg::get_key() const noexcept { return _key; }

} // namespace dtm::msg