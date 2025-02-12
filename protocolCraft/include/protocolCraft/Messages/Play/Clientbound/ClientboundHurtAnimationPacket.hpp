#if PROTOCOL_VERSION > 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHurtAnimationPacket : public BaseMessage<ClientboundHurtAnimationPacket>
    {
    public:
#if PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x21;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Hurt Animation";

        virtual ~ClientboundHurtAnimationPacket() override
        {

        }


        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetYaw(const float yaw_)
        {
            yaw = yaw_;
        }


        int GetId_() const
        {
            return id_;
        }

        float GetYaw() const
        {
            return yaw;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            yaw = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<float>(yaw, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["yaw"] = yaw;


            return output;
        }

    private:
        int id_;
        float yaw;
    };
} //ProtocolCraft
#endif
