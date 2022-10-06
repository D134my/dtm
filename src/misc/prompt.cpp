#include "prompt.hpp"
#include "../hashing/pre_info.hpp"
#include <iostream>
namespace dtm::misc {
    void prompt() noexcept {
        std::cout << "=================[NODE: "
                  << dtm::_node_number << "]=======================\n";

        std::cout << "   1.'put' request format : PUT(<integer>,<integer>)\n";
        std::cout << "   2.'get' request format : GET(<integer>)\n";
        std::cout << "   3.To print Hash Table : 'r'\n";
        std::cout << "=======================\n\nenter put/get request: " << std::endl;
    }
}// namespace dtm::misc