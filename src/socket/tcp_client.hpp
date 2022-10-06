#ifndef __dtm_tcp_client__
#define __dtm_tcp_client__

#include "net_headers.hpp"
#include "dtm_socket.hpp"

namespace dtm::sock {
    class tcp_client : public dtm_socket {
    public:
        tcp_client(struct sockaddr_in &server_addr);
        void create_socket() override;
        void send_msg(std::string const &message) override;
        [[nodiscard]] std::pair<std::string, int> recv_msg()  override;
        [[nodiscard]] int get_socket ()  noexcept override;
        virtual ~tcp_client();

    private:
        void tcp_connect();
    private:
        int _tcp_socket;
        struct sockaddr_in _server_info;
    };
}// namespace dtm::sock


#endif