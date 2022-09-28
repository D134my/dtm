#include "put_forward.hpp"

namespace dtm::msg {
void put_forward_msg::set_key(std::uint32_t key) noexcept { _key = key; }

std::uint32_t put_forward_msg::get_key() const noexcept { return _key; }

void put_forward_msg::set_address(std::int32_t address) noexcept {
  _address = address;
}
std::uint32_t put_forward_msg::get_address() const noexcept { return _address; }
void put_forward_msg::set_tcp_port(std::int32_t tcp_port) noexcept {
  _tcp_port = tcp_port;
}
std::uint32_t put_forward_msg::get_tcp_port() const noexcept {
  return _tcp_port;
}


} // namespace dtm::msg
