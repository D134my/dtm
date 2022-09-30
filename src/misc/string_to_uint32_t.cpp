#include "string_to_uint32_t.hpp"
#include <iostream>
#include <sstream>


namespace dtm::misc {
    std::uint32_t str_to_u32_t(std::string const &str) noexcept {
        try {
            std::stringstream ss;
            ss << str;
            std::uint32_t converted_value;
            ss >> converted_value;

            return converted_value;

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(-1);
        }
    }
}// namespace dtm::misc