#include "tcp_server.hpp"
#include "../misc/misc.hpp"
#include <iostream>
#include <stdexcept>

namespace dtm::sock {

    tcp_server::tcp_server(struct sockaddr_in &server_addr) : _server_info(server_addr) {}

    void tcp_server::create_socket() {
        if ((_tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            auto error = dtm::misc::log("tcp socket creation failed");
            throw std::runtime_error(error);
        }

        tcp_bind();
        tcp_listen();
    }

    int tcp_server::get_socket() noexcept {
        return _tcp_socket;
    }

    void tcp_server::tcp_bind() {
        int opt = 1;
        if ((setsockopt(_tcp_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt))) == -1) {
            auto error = dtm::misc::log("setsockopt so_reuseaddr failed");
            throw std::runtime_error(error);
        }


        if ((setsockopt(_tcp_socket, SOL_SOCKET, SO_REUSEPORT, (char *) &opt, sizeof(opt))) == -1) {
            auto error = dtm::misc::log("setsockopt so_reuseport failed");
            throw std::runtime_error(error);
        }

        if ((bind(_tcp_socket, (struct sockaddr *) &_server_info, sizeof(struct sockaddr))) == -1) {
            auto error = dtm::misc::log("bind failed");
            throw std::runtime_error(error);
        }
    }
    void tcp_server::tcp_listen() {
        if (listen(_tcp_socket, 5) < 0) {
            auto error = dtm::misc::log("listen failed");
            throw std::runtime_error(error);
        }
    }
    void tcp_server::tcp_select(int max_fd, fd_set &readfds) {
        if ((select(max_fd + 1, &readfds, NULL, NULL, NULL)) == -1) {
            auto error = dtm::misc::log("select failed");
            throw std::runtime_error(error);
        }
    }

    int &tcp_server::tcp_accept() {

        socklen_t addrlen = sizeof(struct sockaddr);

        if ((_new_tcp_socket = accept(_tcp_socket, (struct sockaddr *) &_server_info, &addrlen)) < 0) {
            auto error = dtm::misc::log("accept failed");
            throw std::runtime_error(error);
        }


        return _new_tcp_socket;
    }


    void tcp_server::send_msg(std::string const &message) {
        if ((send(_new_tcp_socket, message.c_str(), message.length(), 0) == 1)) {
            auto error = dtm::misc::log("udp socket can't send the message");
            throw std::runtime_error(error);
        }
    }
    std::pair<std::string, int> tcp_server::recv_msg() {
        char buffer[1204];
        memset(buffer, '\0', sizeof(buffer));
        int recv_bytes{};

        if ((recv_bytes = recv(_new_tcp_socket, buffer, 1024, 0) == -1)) {
            auto error = dtm::misc::log("udp socket can't recv the message");
            throw std::runtime_error(error);
        }

        return {std::string{buffer}, recv_bytes};
    }
    tcp_server::~tcp_server() {
        close(_tcp_socket);
        close(_new_tcp_socket);
    }
    void tcp_server::del_sock() noexcept {
        close(_tcp_socket);
    }
    void tcp_server::del_new_sock() noexcept {
        close(_new_tcp_socket);
    }

}// namespace dtm::sock