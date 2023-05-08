#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include <vector>
#include <string>

namespace ProtocolCraft
{
    class ClientboundMinecraftRegisterPacket : public BaseMessage<ClientboundMinecraftRegisterPacket>
    {
    public:
        static constexpr int packet_id = ProtocolCraft::ClientboundCustomPayloadPacket::packet_id;
        static constexpr std::string_view packet_name = "Register Channels";

#if PROTOCOL_VERSION < 390 // 1.13-pre8
        static constexpr std::string_view identifier = "REGISTER";
#else 
        static constexpr std::string_view identifier = "minecraft:register";
#endif

        virtual ~ClientboundMinecraftRegisterPacket() override
        {

        }

        void SetChannels(const std::vector<std::string>& channels_)
        {
            channels = channels_;
        }

        const std::vector<std::string>& GetChannels() const
        {
            return channels;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ReadData<std::string>(iter, length); // identifier

            std::vector<unsigned char> data = ReadByteArray(iter, length, length);

            auto begin = data.begin();
            auto end = data.begin();
            while(end < data.end()) {
                if (*end == '\0') {
                    channels.push_back(std::string(begin, end));
                    end++;
                    begin = end;
                }
                else {
                    end++;
                }
            }            
            if (end > begin) {
                channels.push_back(std::string(begin, end));
            }
            
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(std::string{identifier}, container);

            std::vector<unsigned char> data;

            for(std::string channel : channels) {
                for(unsigned char ch : channel) {
                    data.push_back(ch);
                }
                data.push_back('\0');
            }

            WriteByteArray(data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            output["channels"] = channels;

            return output;
        }

    private:
        std::vector<std::string> channels;

    };
} //ProtocolCraft
