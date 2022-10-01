#include "udp_server.hpp"
#include "../misc/misc.hpp"
#include <stdexcept>
#include <iostream>

namespace dtm::sock {
    udp_server::udp_server(struct sockaddr_in &server_addr) : _server_info(server_addr) {}


    void udp_server::create_socket() {
        if ((_udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            auto error = dtm::misc::log("udp socket creation failed");
            throw std::runtime_error(error);
        }

        udp_bind();
    }

    void udp_server::send_msg(std::string const &message) {
        if ((sendto(_udp_socket, message.c_str(), message.length(), 0, (struct sockaddr *) &_server_info, sizeof(struct sockaddr))) == 1) {
            auto error = dtm::misc::log("udp socket can't send the message");
            throw std::runtime_error(error);
        }
    }
    std::pair<std::string, int> udp_server::recv_msg() {
        char buffer[1204];
        socklen_t addr_len = sizeof(struct sockaddr);
        int recv_bytes{};

        if ((recv_bytes = recvfrom(_udp_socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &_server_info, &addr_len)) == -1) {
            auto error = dtm::misc::log("udp socket can't recv the message");
            throw std::runtime_error(error);
        }

        return {std::string{buffer}, recv_bytes};
    }

    void udp_server::udp_bind() {
        int opt = 1;
        if (setsockopt(_udp_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0) {
            auto error = dtm::misc::log("setsockopt so_reuseaddr failed");
            throw std::runtime_error(error);
        }


        if (setsockopt(_udp_socket, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(opt))<0)
        {
            auto error = dtm::misc::log("setsockopt so_reuseport failed");
            throw std::runtime_error(error);

        }

        if ((bind(_udp_socket,(struct sockaddr *)&_server_info, sizeof(struct sockaddr))) == -1)
        {
            auto error = dtm::misc::log("bind failed");
            throw std::runtime_error(error);
        }

    }

}// namespace dtm::sock