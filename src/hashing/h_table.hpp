#ifndef __dtm_hash_table__
#define __dtm_hash_table__

#include <array>
#include <cstdint>
#include <list>
#include <map>
#include <string>

namespace dtm::hash {

constexpr std::uint16_t table_size = 100;

using node = std::list<std::uint32_t>;
using h_t_array = std::array<node, table_size>;

class hash_table {
public:
  //explicit hash_table(std::uint32_t node_number = 3);
  void append_node(node &node, std::uint32_t data);
  void add_to_hash_table(std::uint32_t key, std::uint32_t data);
  std::uint32_t fetch_value_from_hash_table(std::uint32_t key);
  void display_hash_table();
  static bool check_current_node(std::uint32_t node_number, std::string const& request) noexcept;
  static std::uint32_t get_or_put_(std::string const& request);
  static std::uint32_t extract_key_from_get_request(std::string const& request) noexcept;
  static std::uint32_t extract_key_from_put_request(std::string const& request) noexcept;
  static std::uint32_t extract_value_from_put_request(std::string const& request) noexcept;
  static std::uint32_t extract_port(std::string const& request) noexcept;
  static std::uint32_t extract_node(std::string const& request) noexcept;
private:
  h_t_array _hash_table_array{};

};

} // namespace dtm::hash

#endif
