#pragma once

// Bounding Box Outline Reloaded
// https://github.com/irtimaled/BoundingBoxOutlineReloaded
// https://www.curseforge.com/minecraft/mc-mods/bounding-box-outline-reloaded

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBBORStructureListSyncPacket : public BaseMessage<ClientboundBBORStructureListSyncPacket>
    {
    public:
        static constexpr int packet_id = ProtocolCraft::ClientboundCustomPayloadPacket::packet_id;
        static constexpr std::string_view packet_name = "BBOR Structure List Sync";

        static constexpr std::string_view identifier = "bbor:structure_list_sync_v1";

        virtual ~ClientboundBBORStructureListSyncPacket() override
        {

        }

        void SetStructureIds(const std::vector<std::string>& structure_ids_)
        {
            structure_ids = structure_ids_;
        }


        const std::vector<std::string>& GetStructureIds() const
        {
            return structure_ids;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ReadData<std::string>(iter, length); // identifier
            structure_ids = ReadVector<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(std::string{identifier}, container);
            WriteVector<std::string>(structure_ids, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            output["structure_ids"] = structure_ids;

            return output;
        }

    private:
        std::vector<std::string> structure_ids;
    };
} //ProtocolCraft
