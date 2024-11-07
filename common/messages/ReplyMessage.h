
#include "ServerMessage.h"

struct ReplyMessage: public ServerMessage {
public:
    u16 matchID;

    u8 startGame;

    ReplyMessage();

    ReplyMessage(u16 id, u8 startGame);

    void send(ServerSendProtocol& serverProtocol) override;

    bool operator==(const ReplyMessage& other) const;

    ~ReplyMessage();
};
