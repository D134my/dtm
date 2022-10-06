#ifndef __dtm_udp_server__
#define __dtm_udp_server__

#include "dtm_socket.hpp"
#include "net_headers.hpp"
#include <string>
#include <tuple>
namespace dtm::sock {
    class udp_server : public dtm_socket {
    public:
        udp_server(struct sockaddr_in &server_addr);

        void create_socket() override;
        void send_msg(std::string const &message) override;
        [[nodiscard]] std::pair<std::string, int> recv_msg() override;
        [[nodiscard]] std::tuple<std::string, int, sockaddr_in> recvfrom_msg();
        [[nodiscard]] int get_socket ()  noexcept override;
        virtual ~udp_server();

    private:
        void udp_bind();

    private:
        struct sockaddr_in _server_info;
        int _udp_socket;
    };
}// namespace dtm::sock

#endif
