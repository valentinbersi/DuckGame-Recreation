#include "LobbyResolver.h"

#include <string>

#include <syslog.h>
#define CREATE_ERROR "Error creating game. Uknonwn cause."
#define JOIN_ERROR "Error joining game. Unknown cause."
#define START_ERROR "Error starting game. Unknown cause."
#define NO_MATCH "Match Requested does not exist."

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


std::optional<BlockingQueue<std::unique_ptr<Command>>*> LobbyResolver::resolveNewMatch(
        const LobbyMessage& message) {
    try {
        gameMap.createGameAndJoinSafe(senderQueue, clientID, message.playerCount);
    } catch (...) {
        senderQueue->push(std::make_unique<ReplyMessage>(CREATE_ERROR));
        syslog(LOG_CRIT, CREATE_ERROR);
    }
    return std::nullopt;
}

std::optional<BlockingQueue<std::unique_ptr<Command>>*> LobbyResolver::resolveJoinMatch(
        const LobbyMessage& message) {
    std::string error;
    try {
        return gameMap.joinGameSafe(message.matchId, senderQueue, clientID, message.playerCount);
    } catch (const std::out_of_range& err) {
        error = NO_MATCH;
    } catch (const std::logic_error& err) {
        error = err.what();
    } catch (...) {
        syslog(LOG_CRIT, JOIN_ERROR);
    }
    senderQueue->push(std::make_unique<ReplyMessage>(error));
    return std::nullopt;
}

std::optional<BlockingQueue<std::unique_ptr<Command>>*> LobbyResolver::resolveStartMatch(
        const LobbyMessage& message) {
    std::string error;
    try {
        return gameMap.startGameSafe(message.matchId);
    } catch (const std::out_of_range& err) {
        error = NO_MATCH;
    } catch (const std::logic_error& err) {
        error = err.what();
    } catch (...) {
        syslog(LOG_CRIT, START_ERROR);
    }
    senderQueue->push(std::make_unique<ReplyMessage>(error));
    return std::nullopt;
}

std::optional<BlockingQueue<std::unique_ptr<Command>>*> LobbyResolver::resolveRequest(
        const LobbyMessage& message) {
    return resolveMap.at(message.request)(message);
}

LobbyResolver::~LobbyResolver() = default;
