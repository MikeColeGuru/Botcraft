#pragma once

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/enums.hpp"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#if PROTOCOL_VERSION > 759
#include "botcraft/Network/LastSeenMessagesTracker.hpp"
#endif
#if PROTOCOL_VERSION > 760
#include <atomic>
#endif

namespace Botcraft
{
    class TCP_Com;
    class Authentifier;

    class NetworkManager : public ProtocolCraft::Handler
    {
    public:
        NetworkManager(const std::string& address, const std::string& login, const bool force_microsoft_auth);
        // Used to create a dummy network manager that does not fire any message
        // but is always in constant_connection_state
        NetworkManager(const ProtocolCraft::ConnectionState constant_connection_state);
        ~NetworkManager();

        void Close();

        void AddHandler(ProtocolCraft::Handler* h);
        void Send(const std::shared_ptr<ProtocolCraft::Message> msg);
        const ProtocolCraft::ConnectionState GetConnectionState() const;
        const std::string& GetMyName() const;

        void SendChatMessage(const std::string& message);
        void SendChatCommand(const std::string& command);

    private:
        void WaitForNewPackets();
        void ProcessPacket(const std::vector<unsigned char>& packet);
        void OnNewRawData(const std::vector<unsigned char>& packet);


        virtual void Handle(ProtocolCraft::Message& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginCompressionPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundHelloPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundKeepAlivePacket& msg) override;
#if PROTOCOL_VERSION > 340
        virtual void Handle(ProtocolCraft::ClientboundCustomQueryPacket& msg) override;
#endif
#if PROTOCOL_VERSION > 759
        virtual void Handle(ProtocolCraft::ClientboundPlayerChatPacket& msg) override;
#if PROTOCOL_VERSION < 761
        virtual void Handle(ProtocolCraft::ClientboundPlayerChatHeaderPacket& msg) override;
#endif
#endif
#if PROTOCOL_VERSION > 760
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
#endif

    private:
        std::vector<ProtocolCraft::Handler*> subscribed;

        std::shared_ptr<TCP_Com> com;
        std::shared_ptr<Authentifier> authentifier;
        ProtocolCraft::ConnectionState state;

        std::thread m_thread_process;//Thread running to process incoming packets without blocking com

        std::queue<std::vector<unsigned char> > packets_to_process;
        std::mutex mutex_process;
        std::condition_variable process_condition;
        int compression;

        std::mutex mutex_send;

        std::string name;

#if PROTOCOL_VERSION > 759
        LastSeenMessagesTracker chat_context;
#endif
#if PROTOCOL_VERSION > 760
        ProtocolCraft::UUID chat_session_uuid;
        std::atomic<int> message_sent_index;
#endif

    };
}
