#include "msg_helper.hpp"

namespace dtm::msg {
std::unique_ptr<put_forward_msg> make_put_forward() {
  return std::make_unique<put_forward_msg>();
}

std::unique_ptr<get_forward_msg> make_get_forward() {
  return std::make_unique<get_forward_msg>();
}

std::unique_ptr<what_value_msg> make_what_value() {
  return std::make_unique<what_value_msg>();
}

std::unique_ptr<put_reply_msg> make_put_reply() {
  return std::make_unique<put_reply_msg>();
}

std::unique_ptr<get_reply_msg> make_get_reply() {
  return std::make_unique<get_reply_msg>();
}

} // namespace dtm::msg