#pragma once

#if PROTOCOL_VERSION < 755
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacket : public BaseMessage<ServerboundMovePlayerPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x15;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Move Player";

        virtual ~ServerboundMovePlayerPacket() override
        {

        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(on_ground, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["on_ground"] = on_ground;

            return output;
        }

    private:
        bool on_ground;

    };
} //ProtocolCraft
#endif
