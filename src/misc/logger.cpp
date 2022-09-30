#include "logger.hpp"
#include <string>

namespace dtm::misc {
    std::string log(std::string const &msg, std::source_location location)  noexcept {
        return msg + ", line : " + std::string{std::to_string(location.line()) + " function :" + std::string(location.function_name())};
    }
}// namespace dtm::misc