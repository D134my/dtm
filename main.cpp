#include "dtm.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "project is working \n";
  dtm::parsing::parser::validation_args(argc, argv);
  auto args = dtm::parsing::parser::get_args();

  std::cout << "tcp port " << args->at(0) << " udp port " << args->at(1)
            << " node number " << args->at(2) << std::endl;

  return 0;
}
