#include <iostream>

#include "Config.h"
#include "Server.h"

int main(const int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "hc:m:")) != -1) {
        switch (opt) {
            case 'h':
                std::cout << "Usage: " << argv[0]
                          << " [-h] [-c config_directory] [-m maps_directory] [port]" << std::endl;
                return 0;
            case 'c': {
                std::string configPath(optarg);
                if (configPath.back() != '/')
                    configPath += '/';
                Config::setConfigPath(std::move(configPath));
            } break;
            case 'm': {
                std::string mapsPath(optarg);
                if (mapsPath.back() != '/')
                    mapsPath += '/';
                Config::setMapsDirectory(std::move(mapsPath));
            } break;
            default:
                std::cerr << "Usage: " << argv[0]
                          << " [-h] [-c config_directory] [-m maps_directory] [port]" << std::endl;
                return -1;
        }
    }

    std::string port;

    if (optind < argc)
        port = argv[optind];
    else
        port = "8080";

    try {
        Config::load();
    } catch (const Config::BadConfigFile& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    try {
        Server server(port);
        return server.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
