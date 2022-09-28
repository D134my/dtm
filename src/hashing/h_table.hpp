#ifndef __dtm_hash_table__
#define __dtm_hash_table__

#include <array>
#include <cstdint>
#include <list>
#include <map>

namespace dtm::hash {

constexpr std::uint16_t table_size = 100;

using node = std::list<std::uint32_t>;
using h_t_array = std::array<node, table_size>;

class hash_table {
public:
  hash_table(std::uint32_t node_number = 0);
  void append_node(node &node, std::uint32_t data);
  std::uint32_t add_to_hash_table(std::uint32_t key, std::uint32_t data);

private:
  h_t_array _hash_table_array{};
  std::uint32_t _node_number;
};

} // namespace dtm::hash

#endif
