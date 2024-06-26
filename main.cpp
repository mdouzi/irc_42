#include "server.hpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
        return 1;
    }
     wint_t port;
    try {
        port = static_cast<wint_t>(atoi(argv[1]));
    } catch (const std::invalid_argument&) {
        std::cerr << "Invalid argument: " << argv[1] << ". Please enter a valid port number.\n";
        return 1;
    } catch (const std::out_of_range&) {
        std::cerr << "Port number out of range. Please enter a valid port number between 0 and 65535.\n";
        return 1;
    }
    my_server a;

    a.setPassword(argv[2]);
    a.runServer(port);
    return 0;
}
