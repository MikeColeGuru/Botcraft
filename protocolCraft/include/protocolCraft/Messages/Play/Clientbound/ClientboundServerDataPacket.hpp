#if PROTOCOL_VERSION > 758
#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundServerDataPacket : public BaseMessage<ClientboundServerDataPacket>
    {
    public:
#if PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x45;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Server Data";

        virtual ~ClientboundServerDataPacket() override
        {

        }


#if PROTOCOL_VERSION < 762
        void SetMotd(const std::optional<Chat>& motd_)
        {
            motd = motd_;
        }

        void SetIconBase64(const std::optional<std::string>& icon_base_64_)
        {
            icon_base_64 = icon_base_64_;
        }
#else
        void SetMotd(const Chat& motd_)
        {
            motd = motd_;
        }

        void SetIconBytes(const std::optional<std::vector<unsigned char>>& icon_bytes_)
        {
            icon_bytes = icon_bytes_;
        }
#endif

#if PROTOCOL_VERSION < 761
        void SetPreviewsChat(const bool previews_chat_)
        {
            previews_chat = previews_chat_;
        }
#endif

#if PROTOCOL_VERSION > 759
        void SetEnforcesSecureChat(const bool enforces_secure_chat_)
        {
            enforces_secure_chat = enforces_secure_chat_;
        }
#endif


#if PROTOCOL_VERSION < 762
        const std::optional<Chat>& GetMotd() const
        {
            return motd;
        }

        const std::optional<std::string>& GetIconBase64() const
        {
            return icon_base_64;
        }
#else
        const Chat& GetMotd() const
        {
            return motd;
        }

        const std::optional<std::vector<unsigned char>>& GetIconBytes() const
        {
            return icon_bytes;
        }
#endif

#if PROTOCOL_VERSION < 761
        bool GetPreviewsChat() const
        {
            return previews_chat;
        }
#endif

#if PROTOCOL_VERSION > 759
        bool GetEnforcesSecureChat() const
        {
            return enforces_secure_chat;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 762
            motd = ReadOptional<Chat>(iter, length);
            icon_base_64 = ReadOptional<std::string>(iter, length);
#else
            motd = ReadData<Chat>(iter, length);
            icon_bytes = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<unsigned char>(i, l);
                }
            );
#endif
#if PROTOCOL_VERSION < 761
            previews_chat = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 759
            enforces_secure_chat = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 762
            WriteOptional<Chat>(motd, container);
            WriteOptional<std::string>(icon_base_64, container);
#else
            WriteData<Chat>(motd, container);
            WriteOptional<std::vector<unsigned char>>(icon_bytes, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteVector<unsigned char>(v, c);
                }
            );
#endif
#if PROTOCOL_VERSION < 761
            WriteData<bool>(previews_chat, container);
#endif
#if PROTOCOL_VERSION > 759
            WriteData<bool>(enforces_secure_chat, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 762
            if (motd.has_value())
            {
                output["motd"] = motd.value();
            }
            if (icon_base_64.has_value())
            {
                output["icon_base_64"] = icon_base_64.value();
            }
#else
            output["motd"] = motd;
            if (icon_bytes.has_value())
            {
                output["icon_base_64"] = "Vector of " + std::to_string(icon_bytes.value().size()) + " unsigned char";
            }
#endif
#if PROTOCOL_VERSION < 761
            output["previews_chat"] = previews_chat;
#endif
#if PROTOCOL_VERSION > 759
            output["enforces_secure_chat"] = enforces_secure_chat;
#endif


            return output;
        }

    private:
#if PROTOCOL_VERSION < 762
        std::optional<Chat> motd;
        std::optional<std::string> icon_base_64;
#else
        Chat motd;
        std::optional<std::vector<unsigned char>> icon_bytes;
#endif
#if PROTOCOL_VERSION < 761
        bool previews_chat;
#endif
#if PROTOCOL_VERSION > 759
        bool enforces_secure_chat;
#endif

    };
} //ProtocolCraft
#endif
