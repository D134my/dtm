#include "arg_parser.hpp"
#include <algorithm>
#include <iostream>

namespace dtm::parsing {

bool parser::validation_args(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "./dtmapp udp port, tcp port, node number \n";
    return false;
  }

  args = {argv[1], argv[2], argv[3]};

  return check_args_type();
}

bool parser::check_args_type() {

  for (auto const &arg : args)
    if (auto result = std::ranges::find_if(
            arg, [](unsigned char c) { return !std::isdigit(c); });
        result != arg.end()) {
      return false;
    }

  return true;
}

std::optional<std::array<std::string, 3>> parser::get_args() noexcept {
  return args;
}

} // namespace dtm::parsing
