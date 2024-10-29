#include "VClient.h"

VirtualClient::VirtualClient(ActiveSocket&& socket) : skt(std::move(socket)), 
                                                      gameQueue(nullptr),
                                                      sendQueue(),
                                                      receiver(skt, gameQueue),
                                                      sender(skt, sendQueue) 
{
    receiver.start();
    sender.start();
}



                        