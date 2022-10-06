#include "udp_client.hpp"
#include "../misc/misc.hpp"
#include <stdexcept>


namespace dtm::sock {
    udp_client::udp_client(struct sockaddr_in &client_addr) : _client_info(client_addr) {}


    void udp_client::create_socket() {
        if ((_udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            auto error = dtm::misc::log("udp socket creation failed");
            throw std::runtime_error(error);
        }
    }

    void udp_client::send_msg(std::string const &message) {
        if (sendto(_udp_socket, message.c_str(), message.length(), 0, (struct sockaddr *) &_client_info, sizeof(struct sockaddr)) == -1) {
            auto error = dtm::misc::log("udp socket can't send the message");
            throw std::runtime_error(error);
        }
    }
    std::pair<std::string, int> udp_client::recv_msg() {
        char buffer[1204];
        socklen_t addr_len = sizeof(struct sockaddr);
        int recv_bytes{};

        if ((recv_bytes = recvfrom(_udp_socket, buffer, 1024, 0, (struct sockaddr *) &_client_info, &addr_len)) == -1) {
            auto error = dtm::misc::log("udp socket can't recv the message");
            throw std::runtime_error(error);
        }

        return {std::string{buffer}, recv_bytes};
    }
    int udp_client::get_socket() noexcept {
        return _udp_socket;
    }
    udp_client::~udp_client() {
        close(_udp_socket);
    }
    void udp_client::del_sock() noexcept {
        close(_udp_socket);
    }

}// namespace dtm::sock
