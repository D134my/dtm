#ifndef __dtm_mix__
#define __dtm_mix__

#include "../hashing/pre_info.hpp"
#include <array>
#include <cstdint>
#include <string>

namespace dtm::net {
    class network {
    public:
        void forward_udp(std::uint32_t dest_node, std::string const &msg);
        std::string forward_data(std::string const &input_buffer);
        void set_node(std::uint16_t index, std::uint16_t tcp_port, std::uint16_t udp_port) noexcept;
        std::pair<std::uint16_t, std::uint16_t> get_node(std::uint8_t index) const noexcept;

    private://tcp       udp
        std::array<std::pair<std::uint16_t, std::uint16_t>, 20> _node;
    };
}// namespace dtm::net

#endif