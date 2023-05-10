#include "protocolCraft/MessageFactory.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "protocolCraft/Messages/Play/Clientbound/ClientboundCustomPayloadPacket.hpp"

enum DIRECTION {
    CLIENT_BOUND,
    SERVER_BOUND
};

// Template black magic to loop at compile time
template<std::size_t... indices, class LoopBody>
void loop_impl(std::index_sequence<indices...>, LoopBody&& loop_body) {
    (loop_body(std::integral_constant<std::size_t, indices>{}), ...);
}

template<std::size_t N, class LoopBody>
void loop(LoopBody&& loop_body) {
    loop_impl(std::make_index_sequence<N>{}, std::forward<LoopBody>(loop_body));
}

template<typename TypesTuple>
std::shared_ptr<ProtocolCraft::Message> AutomaticMessageFactory(const int id)
{
    std::shared_ptr<ProtocolCraft::Message> output = nullptr;

    loop < std::tuple_size<TypesTuple>{} > (
        [&](auto i)
        {
            using TupleElement = std::tuple_element_t<i, TypesTuple>;
            if (id == TupleElement::packet_id)
            {
                output = std::make_shared<TupleElement>();
            }
        }
    );

    return output;
}

template<typename TypesTuple>
std::shared_ptr<ProtocolCraft::Message> AutomaticCustomMessageFactory(const std::string identifier, enum DIRECTION direction)
{
    std::shared_ptr<ProtocolCraft::Message> output = nullptr;

    loop < std::tuple_size<TypesTuple>{} > (
        [&](auto i)
        {
            using TupleElement = std::tuple_element_t<i, TypesTuple>;
            if (identifier == TupleElement::identifier)
            {
                output = std::make_shared<TupleElement>();
            }
        }
    );

    // If not found then fall back to generic custom payload packet handler
    if (output == nullptr) {
        if (direction == CLIENT_BOUND)
        {
            output = std::make_shared<ProtocolCraft::ClientboundCustomPayloadPacket>();
        }
        else
        {
            output = std::make_shared<ProtocolCraft::ServerboundCustomPayloadPacket>();
        }
    }

    return output;
}

namespace ProtocolCraft
{
    std::shared_ptr<Message> CreateClientboundMessage(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Login:
            return AutomaticMessageFactory<AllClientboundLoginPacket>(id);
        case ConnectionState::Status:
            return AutomaticMessageFactory<AllClientboundStatusPacket>(id);
        case ConnectionState::Play:
            return AutomaticMessageFactory<AllClientboundPlayPacket>(id);
        default:
            return nullptr;
        }
    }

    std::shared_ptr<Message> CreateCustomClientboundMessage(const ConnectionState state, const std::string identifer)
    {
        switch (state)
        {
        case ConnectionState::Login:
            return AutomaticCustomMessageFactory<AllClientboundCustomLoginPacket>(identifer, CLIENT_BOUND);
        case ConnectionState::Status:
            return AutomaticCustomMessageFactory<AllClientboundCustomStatusPacket>(identifer, CLIENT_BOUND);
        case ConnectionState::Play:
            return AutomaticCustomMessageFactory<AllClientboundCustomPlayPacket>(identifer, CLIENT_BOUND);
        default:
            return nullptr;
        }
    }

    std::shared_ptr<Message> CreateServerboundMessage(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Handshake:
            return AutomaticMessageFactory<AllServerboundHandshakeMessages>(id);
        case ConnectionState::Login:
            return AutomaticMessageFactory<AllServerboundLoginMessages>(id);
        case ConnectionState::Status:
            return AutomaticMessageFactory<AllServerboundStatusMessages>(id);
        case ConnectionState::Play:
            return AutomaticMessageFactory<AllServerboundPlayMessages>(id);
        default:
            return nullptr;
        }
    }

    std::shared_ptr<Message> CreateCustomServerboundMessage(const ConnectionState state, const std::string identifer)
    {
        switch (state)
        {
        case ConnectionState::Handshake:
            return AutomaticCustomMessageFactory<AllServerboundCustomHandshakeMessages>(identifer, SERVER_BOUND);
        case ConnectionState::Login:
            return AutomaticCustomMessageFactory<AllServerboundCustomLoginMessages>(identifer, SERVER_BOUND);
        case ConnectionState::Status:
            return AutomaticCustomMessageFactory<AllServerboundCustomStatusMessages>(identifer, SERVER_BOUND);
        case ConnectionState::Play:
            return AutomaticCustomMessageFactory<AllServerboundCustomPlayMessages>(identifer, SERVER_BOUND);
        default:
            return nullptr;
        }
    }
}
