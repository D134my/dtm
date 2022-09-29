#include "dtm.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  std::cout << "project is working \n";
  dtm::parsing::parser::validation_args(argc, argv);
  auto args = dtm::parsing::parser::get_args();

  std::stringstream ss;
  ss << args->at(2);
  std::uint32_t node_number;
  ss >> node_number;
  dtm::hash::hash_table h{node_number};
  h.add_to_hash_table(4, 3);

  h.display_hash_table();
  return 0;
}
