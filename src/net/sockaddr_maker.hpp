#ifndef __dtm_sockaddr_maker__
#define __dtm_sockaddr_maker__

#include "../socket/net_headers.hpp"
#include <cstdint>
#include <string>

namespace dtm::net {
    struct sockaddr_in make_addr(std::uint16_t port, std::string const &address = "127.0.0.1");
}


#endif