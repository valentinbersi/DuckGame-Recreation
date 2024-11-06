#include "LobbyResolver.h"

LobbyResolver::LobbyResolver(
        GameMapMonitor& gameMap,
        std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
        const u16& clientID):

        gameMap(gameMap), senderQueue(senderQueue), clientID(clientID), resolveMap() {

    resolveMap.insert({LobbyRequest::NEWMATCH,
                       [this](const LobbyMessage& message) { return resolveNewMatch(message); }});
    resolveMap.insert({LobbyRequest::JOINMATCH,
                       [this](const LobbyMessage& message) { return resolveJoinMatch(message); }});
    resolveMap.insert({LobbyRequest::STARTMATCH,
                       [this](const LobbyMessage& message) { return resolveStartMatch(message); }});
}


BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveNewMatch(
        const LobbyMessage& message) {
    (void) message;
    u16 matchID = gameMap.creatGameSafe();
    senderQueue->push(std::make_shared<ReplyMessage>(matchID, 0));
    gameMap.joinGameIfCreated(matchID, senderQueue, clientID);
    return nullptr;
}

BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveJoinMatch(
        const LobbyMessage& message) {
            
    auto* queue = gameMap.joinGameIfCreated(message.matchId, senderQueue, clientID);
    if (gameMap.joinGameIfCreated(message.matchId, senderQueue, clientID)){
        senderQueue->push(std::make_shared<ReplyMessage>(message.matchId, 0));
    } else {
        senderQueue->push(std::make_shared<ReplyMessage>(0, 0));
    }
    return queue;
}

BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveStartMatch(
        const LobbyMessage& message) {
    return gameMap.startGameIfCreated(message.matchId);
}

BlockingQueue<std::unique_ptr<Command>>* LobbyResolver::resolveRequest(
        const LobbyMessage& message) {
    return resolveMap.at(message.request)(message);
}