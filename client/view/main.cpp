#include "GameLauncher.h"

int main(int argc, char* argv[]) {
    cppstring hostname = argv[1];
    cppstring servname = argv[2];

    try {
        GameLauncher launcher(argc, argv, hostname, servname);
        launcher.exec();
    } catch (const LibError& libError) {
        syslog(LOG_CRIT, "%s", libError.what());
        return -1;
    }
    return 0;
}
