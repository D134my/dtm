#ifndef __dtm_tcp_server__
#define __dtm_tcp_server__

#include "dtm_socket.hpp"
#include "net_headers.hpp"

namespace dtm::sock {
    class tcp_server : public dtm_socket {
    public:
        tcp_server(struct sockaddr_in & server_addr);
        void create_socket() override;
        void send_msg(std::string const &message) override;
        [[nodiscard]] std::pair<std::string, int> recv_msg()  override;
        [[nodiscard]] int get_socket ()  noexcept override;
        void tcp_select(int max_fd, fd_set & readfds);
        int& tcp_accept();
        void del_sock() noexcept;
        void del_new_sock() noexcept;
        virtual ~tcp_server();

    private:
        void tcp_bind();
        void tcp_listen();

    private:
        struct sockaddr_in _server_info;
        int _tcp_socket{};
        int _new_tcp_socket{};

    };
}// namespace dtm::sock


#endif