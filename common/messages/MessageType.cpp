#include "MessageType.h"

MessageType::MessageType(Value value): _value(value) {}

MessageType::MessageType(unsigned char value): _value(static_cast<Value>(value)) {}

MessageType::operator Value() const { return _value; }


InputAction::InputAction(Value value): _value(value) {}

InputAction::InputAction(unsigned char value): _value(static_cast<Value>(value)) {}

InputAction::operator Value() const { return _value; }


LobbyRequest::LobbyRequest(Value value): _value(value) {}

LobbyRequest::LobbyRequest(unsigned char value): _value(static_cast<Value>(value)) {}

LobbyRequest::operator Value() const { return _value; }

LobbyRequest::LobbyRequest(): _value(NEWMATCH) {}
