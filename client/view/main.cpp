#include "GameLauncher.h"
#include "Resource.h"

int main(const int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "hr:")) != -1) {
        switch (opt) {
            case 'h':
                std::cout << "Usage: " << argv[0] << " [-h] [-r resources_directory] hostname port"
                          << std::endl;
                return EXIT_SUCCESS;
            case 'r': {
                std::string resourcesPath(optarg);
                if (resourcesPath.back() != '/')
                    resourcesPath += '/';
                Resource::get().setSearchPath(std::move(resourcesPath));
            } break;
            default:
                std::cerr << "Usage: " << argv[0] << " [-h] [-r resources_directory] hostname port"
                          << std::endl;
                return EXIT_FAILURE;
        }
    }

    std::string hostname;
    std::string port;

    if (optind + 1 < argc) {
        hostname = argv[optind];
        port = argv[optind + 1];
    } else {
        std::cerr << "Usage: " << argv[0] << " [-h] [-r resources_directory] hostname port"
                  << std::endl;
        return EXIT_FAILURE;
    }

    try {
        GameLauncher launcher(argc, argv, hostname.c_str(), port.c_str());
        launcher.exec();
    } catch (const LibError& libError) {
        std::cerr << libError.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
