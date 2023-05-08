#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMinecraftBrandPacket : public BaseMessage<ClientboundMinecraftBrandPacket>
    {
    public:
        static constexpr int packet_id = ProtocolCraft::ClientboundCustomPayloadPacket::packet_id;
        static constexpr std::string_view packet_name = "Brand";

#if PROTOCOL_VERSION <= 340 // 1.12.2
        static constexpr std::string_view identifier = "MC|Brand";
#else 
        static constexpr std::string_view identifier = "minecraft:brand";
#endif

        virtual ~ClientboundMinecraftBrandPacket() override
        {

        }

        const void SetBrand(std::string& brand_)
        {
            brand = brand_;
        }

        const std::string& GetBrand() const
        {
            return brand;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ReadData<std::string>(iter, length); // identifier
            brand = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(std::string{identifier}, container);
            WriteData<std::string>(brand, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            output["brand"] = brand;

            return output;
        }

    private:
        std::string brand;

    };
} //ProtocolCraft
