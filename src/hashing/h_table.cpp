#include "h_table.hpp"
#include "pre_info.hpp"

namespace dtm::hash {
void hash_table::append_node(std::uint32_t data) { _node.push_back(data); }

std::uint32_t hash_table::add_to_hash_table(std::uint32_t key,
                                            std::uint32_t data) {

  const std::uint32_t max_limit_key{(table_size - 1) * total_number_of_nodes +
                                    node_number};

  std::uint32_t relative_index{}, return_value{};

  if (key % total_number_of_nodes == node_number && key <= max_limit_key,
      key > -1) {
    relative_index = (key - node_number) / total_number_of_nodes;

    // case 1 :  if hash table entry is empty
    if (_hash_table_array.at(relative_index).first == 0) {
      _hash_table_array.at(relative_index).first = data;
      return_value = 1;
    }

    // case 2 : if exactly one entry in particular entry of hashtable (Ist
    // Collision)

    if (_hash_table_array.at(relative_index).first != 0 &&
        _hash_table_array.at(relative_index).second.empty()) {
      _hash_table_array.at(relative_index).second.push_back(data);
      return_value = 1;
    }

    
  }
}

} // namespace dtm::hash