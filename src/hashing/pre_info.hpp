#ifndef __dtm_pre_info__
#define __dtm_pre_info__

#include <cstdint>
namespace dtm::hash {
constexpr std::uint32_t total_number_of_nodes{3};
constexpr auto nodes_ip{"127.0.0.1"};

struct machine_id{
    std::string ip_address;
    std::uint32_t tcp_port_number;
    std::uint32_t udp_port_number;

};
} // namespace dtm::hash
#endif
