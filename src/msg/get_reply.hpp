#ifndef __dtm_get_reply__
#define __dtm_get_reply__

#include <cstdint>

namespace dtm::msg {
class get_reply_msg {
public:
  void set_value(std::uint32_t value) noexcept;
  std::uint32_t get_value() const noexcept;
  void set_key(std::uint32_t key) noexcept;
  std::uint32_t get_key() const noexcept;

private:
  std::uint32_t _value;
  std::uint32_t _key;
};
} // namespace dtm::msg

#endif