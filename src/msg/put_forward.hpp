#ifndef __dtm_put_forward__
#define __dtm_put_forward__

#include <cstdint>
#include <memory>

namespace dtm::msg {
class put_forward_msg {
public:
  void set_key(std::uint32_t key) noexcept;
  std::uint32_t get_key() const noexcept;
  void set_address(std::int32_t address) noexcept;
  std::uint32_t get_address() const noexcept;
  void set_tcp_port(std::int32_t tcp_port) noexcept;
  std::uint32_t get_tcp_port() const noexcept;

private:
  std::uint32_t _key;
  std::int32_t _address;
  std::int32_t _tcp_port;
};




} // namespace dtm::msg
#endif
