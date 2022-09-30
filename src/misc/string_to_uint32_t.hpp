#ifndef __dtm_string_to_uint32_t__
#define __dtm_string_to_uint32_t__

#include <cstdint>
#include <string>

namespace dtm::misc {
    std::uint32_t str_to_u32_t(std::string const& str) noexcept;
}

#endif