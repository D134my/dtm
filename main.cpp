#include "dtm.hpp"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    try {
        dtm::parsing::parser::validation_args(argc, argv);
        auto args = dtm::parsing::parser::get_args();
        dtm::_node_number = dtm::misc::str_to_u32_t(args->at(2));
        fd_set readfds;
        std::string message;
        int max_fd{};
        dtm::hash::hash_table ht;
        dtm::net::network n;

        std::uint16_t tcp_port = dtm::misc::str_to_u32_t(args->at(0));
        std::uint32_t udp_port = dtm::misc::str_to_u32_t(args->at(1));
        n.set_node(dtm::_node_number, tcp_port, udp_port);              //2000 //2004
        n.set_node((dtm::_node_number + 1), tcp_port + 1, udp_port + 1);//2001  //2005
        n.set_node(dtm::_node_number + 2, tcp_port + 2, udp_port + 2);  //2003 //2006

        dtm::misc::prompt();

        auto server_udp_port = n.get_node(dtm::_node_number).second;
        auto udp_server_info = dtm::net::make_addr(server_udp_port);
        auto u_server = std::make_unique<dtm::sock::udp_server>(udp_server_info);
        u_server->create_socket();

        auto server_tcp_port = n.get_node(dtm::_node_number).first;
        auto tcp_server_info = dtm::net::make_addr(server_tcp_port);
        auto t_server = std::make_unique<dtm::sock::tcp_server>(tcp_server_info);
        t_server->create_socket();


        while (true) {
            FD_ZERO(&readfds);
            FD_SET(0, &readfds);// to read from standard input
            FD_SET(u_server->get_socket(), &readfds);
            FD_SET(t_server->get_socket(), &readfds);

            if (t_server->get_socket() > u_server->get_socket())
                max_fd = t_server->get_socket();
            else
                max_fd = u_server->get_socket();

            t_server->tcp_select(max_fd, readfds);

            if (FD_ISSET(t_server->get_socket(), &readfds)) {
                t_server->tcp_accept();
                auto [msg, recv_size] = t_server->recv_msg();
                std::cout << msg << std::endl;

            } else if (FD_ISSET(u_server->get_socket(), &readfds)) {
                auto [msg, recv_size, u_server_info] = u_server->recvfrom_msg();
                message = msg;
                // std::cout << "msg: " << message << " recv_size: " << recv_size << std::endl;

                if (!(dtm::hash::hash_table::check_current_node(dtm::_node_number, message))) {
                    n.forward_udp(dtm::_node_number + 1, message);
                    std::cout << "enter get/put request:" << std::endl;
                }

                else {
                    std::string response;
                    if ((dtm::hash::hash_table::get_or_put_(message))) {
                        auto key = dtm::hash::hash_table::extract_key_from_get_request(message);
                        auto value = ht.fetch_value_from_hash_table(key);
                        if (value != 0)
                            response = "[node:" + std::to_string(dtm::_node_number) + "] value: " + std::to_string(value);
                        else
                            response = "[node:" + std::to_string(dtm::_node_number) + "] no hash entry to this key on this node";

                    } else {
                        ht.add_to_hash_table(dtm::hash::hash_table::extract_key_from_put_request(message),
                                             dtm::hash::hash_table::extract_value_from_put_request(message));
                        response = "[node:" + std::to_string(dtm::_node_number) + "] value: " +
                                   std::to_string(dtm::hash::hash_table::extract_value_from_put_request(message)) +
                                   " added to hash table";
                    }

                    auto port = dtm::hash::hash_table::extract_port(message);
                    auto tcp_client_info = dtm::net::make_addr(port);
                    auto t_client = std::make_unique<dtm::sock::tcp_client>(tcp_client_info);
                    response += "\nenter get/put request:";
                    std::cout << response << std::endl;
                    t_client->create_socket();
                    t_client->send_msg(response);
                }
            }// end of else if

            if (FD_ISSET(0, &readfds)) {
                std::string rec_buffer;
                std::cin >> rec_buffer;

                if (char first_ch = std::toupper(rec_buffer.at(0)); first_ch == 'R') {
                    ht.display_hash_table();
                    std::cout << "enter get/put request: ";
                } else if ((dtm::hash::hash_table::check_current_node(dtm::_node_number, rec_buffer))) {
                    if (dtm::hash::hash_table::get_or_put_(rec_buffer)) {// get request
                        auto key = dtm::hash::hash_table::extract_key_from_get_request(rec_buffer);
                        auto max_key_limit = (dtm::hash::table_size - 1) * dtm::total_number_of_nodes + dtm::_node_number;
                        if (key <= max_key_limit) {
                            auto value = ht.fetch_value_from_hash_table(key);

                            if (!value) {
                                std::cout << "error: no value in hash table for this key on this node." << std::endl
                                          << "enter get/put request:" << std::endl;
                                continue;
                            } else {
                                std::cout << "key : " << key << " value: " << value << std::endl
                                          << "enter get/put request:" << std::endl;
                                continue;
                            }
                        } else {
                            std::cout << "error: max limit key:" << max_key_limit << std::endl
                                      << "enter get/put request:" << std::endl;
                            continue;
                        }

                    } else// put request
                        std::cout << "[node:" << dtm::_node_number << "] "
                                  << "value: " << dtm::hash::hash_table::extract_value_from_put_request(rec_buffer) << std::endl
                                  << "added to hash table" << std::endl
                                  << "enter get/put request: ";
                    ht.add_to_hash_table(dtm::hash::hash_table::extract_key_from_put_request(rec_buffer),
                                         dtm::hash::hash_table::extract_value_from_put_request(rec_buffer));

                } else {
                    std::string out_buffer = n.forward_data(rec_buffer);
                    n.forward_udp(dtm::_node_number + 1, out_buffer);
                }
                std::endl(std::cout);
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
