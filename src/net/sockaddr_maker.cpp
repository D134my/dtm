#include "sockaddr_maker.hpp"

namespace dtm::net {
    struct sockaddr_in make_addr(std::uint16_t port, std::string const &address) {

        struct sockaddr_in addr;
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        memset(addr.sin_zero, 0, sizeof(addr.sin_addr));

        return addr;
    }
}// namespace dtm::net
