#include "tcp_client.hpp"
#include "../misc/misc.hpp"
#include <stdexcept>

namespace dtm::sock {
    tcp_client::tcp_client(struct sockaddr_in &server_addr) : _server_info(server_addr) {}
    void tcp_client::create_socket() {
        if ((_tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            auto error = dtm::misc::log("tcp socket creation failed");
            throw std::runtime_error(error);
        }
        tcp_connect();
    }
    void tcp_client::send_msg(const std::string &message) {
        if ((send(_tcp_socket, message.c_str(), message.length(), 0) == 1)) {
            auto error = dtm::misc::log("tcp socket can't send the message");
            throw std::runtime_error(error);
        }
    }
    std::pair<std::string, int> tcp_client::recv_msg() {
        char buffer[1204];
        int recv_bytes{};

        if ((recv_bytes = recv(_tcp_socket, buffer, 1024, 0) == -1)) {
            auto error = dtm::misc::log("tcp socket can't recv the message");
            throw std::runtime_error(error);
        }

        return {std::string{buffer}, recv_bytes};
    }

    int tcp_client::get_socket() noexcept {
        return _tcp_socket;
    }
    void tcp_client::tcp_connect() {
        if ((connect(_tcp_socket, (struct sockaddr *) &_server_info, sizeof(struct sockaddr))) == -1) {
            auto error = dtm::misc::log("tcp socket can't connect ");
            throw std::runtime_error(error);
        }
    }
    tcp_client::~tcp_client() {
        close(_tcp_socket);
    }


}// namespace dtm::sock