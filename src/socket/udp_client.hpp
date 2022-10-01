#ifndef __dtm_udp_client__
#define __dtm_udp_client__

#include "dtm_socket.hpp"
#include "net_headers.hpp"
#include <string>

namespace dtm::sock {
    class udp_client : public dtm_socket {
    public:
        udp_client(struct sockaddr_in &client_addr);
        void create_socket() override;
        void send_msg(std::string const &message) override;
        [[nodiscard]] std::pair<std::string, int> recv_msg()  override;

        virtual ~udp_client() = default;

    private:
        struct sockaddr_in _client_info;
        int _udp_socket;
    };
}// namespace dtm::sock

#endif
