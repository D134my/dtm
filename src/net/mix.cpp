#include "mix.hpp"
#include "../hashing/hash.hpp"
#include "../socket/socket.hpp"
#include "sockaddr_maker.hpp"
#include <iostream>


namespace dtm::net {
    void network::forward_udp(std::uint32_t dest_node, std::string const &msg) {
        try {

            dest_node = dest_node % dtm::total_number_of_nodes;
            auto client_info = make_addr(_node.at(dest_node).second);
            dtm::sock::udp_client client(client_info);

            client.create_socket();
            client.send_msg(msg);

            std::cout << "forward request : " << msg << " has been forwarded to node : " << dest_node << " port : " << _node.at(dest_node).second << std::endl;
            client.del_sock();
        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }

    std::string network::forward_data(const std::string &input_buffer) {
        std::uint32_t tcp_port;
        tcp_port = _node.at(dtm::_node_number).first;
        std::string port_buffer = std::to_string(tcp_port);
        std::string result = input_buffer + '[' + port_buffer + ']' + '{' + std::to_string(dtm::_node_number) + '}';

        return result;
    }

    void network::set_node(std::uint16_t index, std::uint16_t tcp_port, std::uint16_t udp_port) noexcept {
        try {
            _node.at(index).first = tcp_port;
            _node.at(index).second = udp_port;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    std::pair<std::uint16_t, std::uint16_t> network::get_node(std::uint8_t index) const noexcept {
        return _node.at(index);
    }
}// namespace dtm::net