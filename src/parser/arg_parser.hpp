#ifndef __dtm_arg_parser__
#define __dtm_arg_parser__

#include <array>
#include <optional>
#include <string>

namespace dtm::parsing {
class parser {
public:
  parser() = delete;
  ~parser() = delete;

  static bool validation_args(int argc, char *argv[]);

  [[nodiscard]] static std::optional<std::array<std::string, 3>>
  get_args() noexcept;

private:
  static bool check_args_type();

private:
  static inline std::array<std::string, 3> args;
};

} // namespace dtm::parsing

#endif
