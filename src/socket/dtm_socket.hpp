#ifndef __dtm_dtm_socket__
#define __dtm_dtm_socket__

#include <string>

namespace dtm::sock {
    class dtm_socket {
    public:
        virtual void create_socket() = 0;
        virtual void send_msg(std::string const &) = 0;
        [[nodiscard]] virtual std::pair<std::string, int> recv_msg() { return {"don't use me ", 0}; };
        [[nodiscard]] virtual int get_socket() noexcept { return _val; }

        virtual ~dtm_socket() = default;

    private:
        int _val{-1};
    };

}// namespace dtm::sock

#endif