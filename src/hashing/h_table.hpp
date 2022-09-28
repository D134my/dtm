#ifndef __dtm_hash_table__
#define __dtm_hash_table__

#include <array>
#include <cstdint>
#include <list>
#include <map>

namespace dtm::hash {

constexpr std::uint16_t table_size = 100;

using node = std::list<std::uint32_t>;
using h_t_entry = std::pair<std::uint32_t, node>;
using h_t_array = std::array<h_t_entry, table_size>;

class hash_table {
public:
  void append_node(std::uint32_t data);
  std::uint32_t add_to_hash_table(std::uint32_t key, std::uint32_t data);

private:
  node _node;
  h_t_entry _hash_table_entry;
  h_t_array _hash_table_array{};
};

} // namespace dtm::hash

#endif