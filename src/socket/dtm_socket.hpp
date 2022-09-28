#ifndef __dtm_socket__
#define __dtm_socket__

namespace dtm::socket {
class dtm_socket {
public:
  virtual void create_socket() = 0;
  virtual void send_msg() = 0;
  virtual void recv_msg() = 0;
  virtual void print_msg() = 0;

  virtual ~dtm_socket() = default;
};

} // namespace dtm::socket

#endif