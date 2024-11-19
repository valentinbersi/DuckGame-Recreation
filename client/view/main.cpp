#include "GameLauncher.h"

int main(int argc, char* argv[]) {
    cppstring hostname = argv[1];
    cppstring servname = argv[2];

    GameLauncher launcher(argc, argv, hostname, servname);
    launcher.exec();

    return 0;
}
