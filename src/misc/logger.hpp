#ifndef __dtm_logger__
#define __dtm__logger__

#include <source_location>
#include <string_view>
namespace dtm::misc {

    std::string log(std::string const &msg,
                    const std::source_location location =
                            std::source_location::current()) noexcept;


}// namespace dtm::misc

#endif
