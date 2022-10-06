#include "h_table.hpp"
#include "../misc/misc.hpp"
#include "pre_info.hpp"
#include <algorithm>
#include <iostream>

namespace dtm::hash {

    // hash_table::hash_table(std::uint32_t node_number) : _node_number{node_number}
    // {}

    void hash_table::append_node(node &node, std::uint32_t data) {

        node.push_back(data);
    }

    void hash_table::add_to_hash_table(std::uint32_t key, std::uint32_t data) {

        std::uint32_t max_limit_key{(table_size - 1) * total_number_of_nodes +
                                    _node_number};

        std::uint32_t relative_index{};

        if ((key % dtm::total_number_of_nodes) == _node_number &&
            (key <= max_limit_key)) {

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
            auto error = dtm::misc::log("error : bad argument passed");
            throw std::invalid_argument(error);
        }
    }

    std::uint32_t hash_table::fetch_value_from_hash_table(std::uint32_t key) {
        // calculate index of key in hash table
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
        auto to_key =
                std::uint32_t{(table_size - 1) * total_number_of_nodes + _node_number};

        if (from_key > to_key) {
            std::uint32_t temp = from_key;
            from_key = to_key;
            to_key = temp;
        }

        std::cout << "Hash table contents " << from_key << " , " << to_key << '\n';

        if (from_key % total_number_of_nodes == _node_number &&
            to_key % total_number_of_nodes == _node_number) {
            auto from =
                    std::uint32_t{(from_key - _node_number) / total_number_of_nodes};
            auto to = std::uint32_t{(to_key - _node_number) / total_number_of_nodes};
            std::uint32_t key, fetch_value;

            for (std::uint32_t i = from; i < to; i++) {
                key = i * total_number_of_nodes + _node_number;
                fetch_value = fetch_value_from_hash_table(key);

                if (fetch_value != 0)
                    std::cout << "display -> key : " << key
                              << " value : " << fetch_value_from_hash_table(key) << '\n';
            }
        }
    }
    bool hash_table::check_current_node(std::uint32_t node_number,
                                        std::string const &request) noexcept {
        std::uint32_t key;
        if (get_or_put_(request) == 1)
            key = extract_key_from_get_request(request);
        else
            key = extract_key_from_get_request(request);

        if (key % total_number_of_nodes == node_number)
            return true;
        else
            return false;
    }

    std::uint32_t hash_table::get_or_put_(const std::string &request) {
        if (char ch = std::toupper(request.at(0)); ch == 'G')
            return 1;// 1 means get method, 0 means put
        else
            return 0;
    }

    std::uint32_t
    hash_table::extract_key_from_get_request(const std::string &request) noexcept {

        try {
            auto str = request;
            auto left_parenthes = std::ranges::find(str, '(');

            if (left_parenthes == str.end()) {
                auto error = dtm::misc::log(" '(' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin(), left_parenthes + 1);
            auto right_parenthes = std::ranges::find(str, ')');

            if (right_parenthes == str.end()) {
                auto error = dtm::misc::log(" ')' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin() + 1, right_parenthes + 1);

            return dtm::misc::str_to_u32_t(str);

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }

    std::uint32_t
    hash_table::extract_key_from_put_request(std::string const &request) noexcept {
        try {
            auto str = request;
            auto left_parenthes = std::ranges::find(str, '(');

            if (left_parenthes == str.end()) {
                auto error = dtm::misc::log(" '(' not found !");
                throw std::invalid_argument(error);
            }
            str.erase(str.begin(), left_parenthes + 1);

            auto comma = std::ranges::find(str, ',');

            if (comma == str.end()) {
                auto error = dtm::misc::log(" ',' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin() + 1, comma + 1);

            auto right_parenthes = std::ranges::find(str, ')');

            if (right_parenthes == str.end()) {
                auto error = dtm::misc::log(" ')' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin() + 1, right_parenthes + 1);
            return dtm::misc::str_to_u32_t(str);

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }

    std::uint32_t hash_table::extract_value_from_put_request(
            const std::string &request) noexcept {
        try {
            auto str = request;

            auto comma = std::ranges::find(str, ',');

            if (comma == str.end()) {
                auto error = dtm::misc::log(" ',' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin(), comma + 1);

            auto right_parenthes = std::ranges::find(str, ')');

            if (right_parenthes == str.end()) {
                auto error = dtm::misc::log(" ')' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(comma + 1, right_parenthes + 1);
            return dtm::misc::str_to_u32_t(str);

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }
    std::uint32_t hash_table::extract_port(const std::string &request) noexcept {
        try {
            auto str = request;
            auto left_bracket = std::ranges::find(str, '[');

            if (left_bracket == str.end()) {
                auto error = dtm::misc::log(" '[' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin(), left_bracket + 1);
            auto right_bracket = std::ranges::find(str, ']');

            if (right_bracket == str.end()) {
                auto error = dtm::misc::log(" ']' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(right_bracket);

            return dtm::misc::str_to_u32_t(str);

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }
    std::uint32_t hash_table::extract_node(const std::string &request) noexcept {
        try {
            auto str = request;
            auto left_cuerly = std::ranges::find(str, '{');

            if (left_cuerly == str.end()) {
                auto error = dtm::misc::log(" '{' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin(), left_cuerly + 1);
            auto right_cuerly = std::ranges::find(str, '}');

            if (right_cuerly == str.end()) {
                auto error = dtm::misc::log(" '}' not found !");
                throw std::invalid_argument(error);
            }

            str.erase(str.begin() + 1, right_cuerly + 1);

            return dtm::misc::str_to_u32_t(str);

        } catch (std::exception &e) {
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }

}// namespace dtm::hash
