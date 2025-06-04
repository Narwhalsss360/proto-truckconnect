#include "communication.h"
#include <string>

namespace truckconnect {
    struct connection {
        SOCKET socket;
        sockaddr_in addr;
        socklen_t addr_len;

        connection(const std::string& ip);
    };

    namespace connection_results {
        enum connection_result {
            success,
            generic_socket_error,
            nonblocking_mode_error,
            not_connected_error,
            already_connected_error
        };
    }

    using connection_results::connection_result;

    connection_result connect(connection& connection);

    connection_result disconnect(connection& connection);
}
