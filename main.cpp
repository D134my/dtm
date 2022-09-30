#include "dtm.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    std::cout << "project is working \n";
    dtm::parsing::parser::validation_args(argc, argv);
    auto args = dtm::parsing::parser::get_args();


    std::uint32_t node_number = dtm::misc::str_to_u32_t(args->at(2));
    std::cout << "node_number" << node_number;

    dtm::hash::hash_table h{node_number};
    h.add_to_hash_table(3, 2);

    //h.display_hash_table();


    std::cout << "key : " << h.extract_key_from_put_request("put (1,2)");
    std::cout << "value : " << h.extract_value_from_put_request("put (1,2)");
    return 0;
}
