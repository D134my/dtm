#ifndef __dtm_msg_helper__
#define __dtm_msg_helper__

#include "get_forward.hpp"
#include "get_reply.hpp"
#include "put_forward.hpp"
#include "put_reply.hpp"
#include "what_value.hpp"
#include <memory>

// function helpers

namespace dtm::msg {
std::unique_ptr<put_forward_msg> make_put_forward();
std::unique_ptr<get_forward_msg> make_get_forward();
std::unique_ptr<what_value_msg> make_what_value();
std::unique_ptr<put_reply_msg> make_put_reply();
std::unique_ptr<get_reply_msg> make_get_reply();
} // namespace dtm::msg

#endif