
#pragma once
#include <string>

#include "Message.h"
#include "Types.h"

struct LobbyMessage: public Message {
    LobbyRequest request;
    std::string usrName;
    u16 matchId;
    LobbyMessage(LobbyRequest request, std::string name, u16 id):
            Message(MessageType::Lobby), request(request), usrName(name), matchId(id) {}
    ~LobbyMessage() = default;
};
