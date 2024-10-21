
#include "MessageType.h"


//Sketch muy basico para prueba del protocolo.
struct ClientMessage{
    ClientMessage(MessageType type, unsigned char action): type(type), action(action) {}
    MessageType type; //deberia ser siempre INPUT= 0x0
    unsigned char action;
};
