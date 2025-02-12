#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetDataPacket : public BaseMessage<ClientboundContainerSetDataPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x13;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Container Set Data";

        virtual ~ClientboundContainerSetDataPacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetId_(const short id__)
        {
            id_ = id__;
        }

        void SetValue(const short value_)
        {
            value = value_;
        }


        unsigned char GetWindowId() const
        {
            return container_id;
        }

        short GetId_() const
        {
            return id_;
        }

        short GetValue() const
        {
            return value;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
            id_ = ReadData<short>(iter, length);
            value = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(container_id, container);
            WriteData<short>(id_, container);
            WriteData<short>(value, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["id_"] = id_;
            output["value"] = value;

            return output;
        }

    private:
        unsigned char container_id;
        short id_;
        short value;

    };
} //ProtocolCraft
