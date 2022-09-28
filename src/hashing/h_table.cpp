#include "h_table.hpp"
#include "pre_info.hpp"
#include <iostream>

namespace dtm::hash {

hash_table::hash_table(std::uint32_t node_number) : _node_number{node_number} {}

void hash_table::append_node(node &node, std::uint32_t data) {

  node.push_back(data);
}

std::uint32_t hash_table::add_to_hash_table(std::uint32_t key,
                                            std::uint32_t data) {

  std::uint32_t max_limit_key{(table_size - 1) * total_number_of_nodes -
                              _node_number};

  std::uint32_t relative_index{}, return_value{};

  if ((total_number_of_nodes % key) == _node_number && (key <= max_limit_key) &&
      (key >= 0)) {

    relative_index = (key - _node_number) / total_number_of_nodes;

    // case 1 : if node is empty
    if (_hash_table_array.at(relative_index).empty()) {
      _hash_table_array.at(relative_index).push_back(data);
      return_value = 1;
    }
    // case 2 : if exactly one entry in particular entry of hashtable (Ist
    // Collision)
    else if (_hash_table_array.at(relative_index).size() == 1) {
      _hash_table_array.at(relative_index).push_back(data);
      return_value = 1;
    }
    // case 3: Subsequent Collisions
    else {
      append_node(_hash_table_array.at(relative_index), data);
      return_value = 1;
    }

  } else {
    std::cout << "error\n";
    return_value = 0;
  }

  return 1;
}
} // namespace dtm::hash
