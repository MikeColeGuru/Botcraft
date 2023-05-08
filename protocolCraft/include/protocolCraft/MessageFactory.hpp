#pragma once

#include <memory>
#include <string>

#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    class Message;

    std::shared_ptr<Message> CreateClientboundMessage(const ConnectionState state, const int id);
    std::shared_ptr<Message> CreateServerboundMessage(const ConnectionState state, const int id);
    std::shared_ptr<Message> CreateCustomClientboundMessage(const ConnectionState state, const std::string identifer);
    std::shared_ptr<Message> CreateCustomServerboundMessage(const ConnectionState state, const std::string identifer);
} //ProtocolCraft
