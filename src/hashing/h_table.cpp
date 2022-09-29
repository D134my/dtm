#include "h_table.hpp"
#include "pre_info.hpp"
#include <iostream>

namespace dtm::hash {

    hash_table::hash_table(std::uint32_t node_number) : _node_number{node_number} {}

    void hash_table::append_node(node &node, std::uint32_t data) {

        node.push_back(data);
    }

    void hash_table::add_to_hash_table(std::uint32_t key,
                                       std::uint32_t data) {

        std::uint32_t max_limit_key{(table_size - 1) * total_number_of_nodes +
                                    _node_number};

        std::uint32_t relative_index{};

        if ((_node_number % key) == _node_number && (key <= max_limit_key)) {

            relative_index = (key - _node_number) / total_number_of_nodes;

            // case 1 : if node is empty
            if (_hash_table_array.at(relative_index).empty()) {
                _hash_table_array.at(relative_index).push_back(data);
            }
            // case 2 : if exactly one entry in particular entry of hashtable (Ist
            // Collision)
            else if (_hash_table_array.at(relative_index).size() == 1) {
                _hash_table_array.at(relative_index).push_back(data);
            }
            // case 3: Subsequent Collisions
            else {
                append_node(_hash_table_array.at(relative_index), data);
            }

        } else {
            throw std::invalid_argument("error : bad argument passed \n");
        }
    }

    std::uint32_t hash_table::fetch_value_from_ht(std::uint32_t key) {
        //calculate index of key in hash table
        std::uint32_t relative_index = (key - _node_number) / total_number_of_nodes;
        std::uint32_t return_value;

        if (_hash_table_array.at(relative_index).size() == 1)
            return_value = _hash_table_array.at(relative_index).front();
        else
            return_value = _hash_table_array.at(relative_index).back();

        return return_value;
    }

    void hash_table::display_hash_table() {
        auto from_key = std::uint32_t{_node_number};
        auto to_key = std::uint32_t{(table_size - 1) * total_number_of_nodes + _node_number};

        if (from_key > to_key) {
            std::uint32_t temp = from_key;
            from_key = to_key;
            to_key = temp;
        }

        std::cout << "Hash table contents " << from_key << " , " << to_key << '\n';

        if (from_key % total_number_of_nodes == _node_number && to_key % total_number_of_nodes == _node_number) {
            auto from = std::uint32_t{(from_key - _node_number) / total_number_of_nodes};
            auto to = std::uint32_t{(to_key - _node_number) / total_number_of_nodes};
            std::uint32_t key, fetch_value;

            for (std::uint32_t i = from; i < to; i++) {
                key = i * total_number_of_nodes + _node_number;
                fetch_value = fetch_value_from_ht(key);

                if (fetch_value != 0)
                    std::cout << "key : " << key << " value : " << fetch_value_from_ht(key) << '\n';
                else
                    std::cout << "invalid keys , hash table cannot be displayed\n";
            }
        }
    }
    bool hash_table::check_current_node(std::uint32_t node_number, std::string const &request) noexcept {
        std::uint32_t key{};
    }

    std::uint32_t hash_table::get_or_put_(const std::string &request) {
        if (char ch = std::toupper(request.at(0)); ch == 'G')
            return 1;//1 means get method, 0 means put
        else
            return 0;
    }

}// namespace dtm::hash
