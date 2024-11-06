#include "Server.h"
int main(int argc, char const* argv[]) {
    if (argc != 2) {
        return -1;
    }
    Server server(argv[1]);
    return server.run();
}
