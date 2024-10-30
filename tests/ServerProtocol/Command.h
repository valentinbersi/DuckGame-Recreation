
#include "GameLoop.h"  //ver despues porque voy a importar es gamecontroler.

class Command {
    virtual void execute(GameController&) = 0;
};
