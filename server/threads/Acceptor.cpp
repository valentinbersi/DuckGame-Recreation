
#include "Acceptor.h"
#include "LibError.h"

Acceptor::Acceptor(std::string& hostname, GameMapMonitor& monitor): acceptorSocket(hostname.c_str()), gamesMonitor(monitor), clientes() {}

bool Acceptor::removeIfNotConnected(VirtualClient& client){
    return !client.isConnected();
}

void Acceptor::reapDead(){
    clientes.remove_if(removeIfNotConnected);
}

void Acceptor::run() {
    try{
        while(_keep_running){
            ActiveSocket peer = acceptorSocket.accept();
            clientes.emplace_back(std::move(peer), gamesMonitor);
            reapDead();
        }
    }catch(const LibError& err){
        if(is_alive()){
            //syslog
        }
        //esperado
    }catch(...){
        //syslog
    }
    _is_alive = false;  
}

void Acceptor::stop(){
    acceptorSocket.shutdown(Socket::ShutdownOptions::READ_WRITE);
    acceptorSocket.close();
    _keep_running = false;
    _is_alive = false;
}

Acceptor::~Acceptor() = default;
