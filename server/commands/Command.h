#pragma once
#include "GameController.h"  //despues porque voy a importar es gamecontroler.

class Command {
public:
    virtual void execute(GameController&) = 0;
    virtual ~Command() = default;
};
