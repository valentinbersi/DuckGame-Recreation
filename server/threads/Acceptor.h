
#include "Thread.h"

class Acceptor: public Thread{
private:
    //Por ahora vamos sin atributos, pero posiblemente requerimos de mapa y la lista de clientes.
public:
    Acceptor();

    virtual void run() override;

    void stop() override; 

    ~Acceptor();
};
