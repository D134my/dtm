#include "dtm.hpp"
#include <iostream>


int main(int argc, char *argv[]) {

    dtm::parsing::parser::validation_args(argc, argv);
    auto args = dtm::parsing::parser::get_args();


    std::uint32_t node_number = dtm::misc::str_to_u32_t(args->at(2));

//
//    dtm::hash::hash_table h{node_number};
//    h.add_to_hash_table(3, 2);
//
//    //h.display_hash_table();
//
//
//    std::cout << "key : " << h.extract_key_from_put_request("put (1,2)");
//    std::cout << "value : " << h.extract_value_from_put_request("put (1,2)");

    sockaddr_in client_info;
    client_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_info.sin_port = htons(2000);
    client_info.sin_family = AF_INET;
    memset(client_info.sin_zero, 0, sizeof(client_info.sin_zero));

//    dtm::sock::udp_client client(client_info);
//    client.create_socket();
//    client.send_msg("hello ");

    dtm::sock::udp_server server(client_info);
    server.create_socket();
    auto result = server.recv_msg();

    std::cout << "msg " << result.first <<  " size " << result.second << std::endl;
    return 0;
}
