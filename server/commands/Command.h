#include "GameLoop.h" //despues porque voy a importar es gamecontroler.

class Command {
    virtual void execute(GameController&) = 0;
};
