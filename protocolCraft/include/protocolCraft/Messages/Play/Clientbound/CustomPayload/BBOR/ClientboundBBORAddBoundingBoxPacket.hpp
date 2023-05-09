#pragma once

// Bounding Box Outline Reloaded
// https://github.com/irtimaled/BoundingBoxOutlineReloaded
// https://www.curseforge.com/minecraft/mc-mods/bounding-box-outline-reloaded

#include <vector>
#include <variant>
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/CustomPayload/BBOR/AbstractBoundingBox.hpp"
#include "protocolCraft/Types/CustomPayload/BBOR/StructureBoundingBox.hpp"

namespace ProtocolCraft
{

    typedef std::variant<StructureBoundingBox> bounding_box_t;

    class ClientboundBBORAddBoundingBoxPacket : public BaseMessage<ClientboundBBORAddBoundingBoxPacket>
    {
    public:
        static constexpr int packet_id = ProtocolCraft::ClientboundCustomPayloadPacket::packet_id;
        static constexpr std::string_view packet_name = "BBOR Add Bounding Box";

        static constexpr std::string_view identifier = "bbor:add_bounding_box_v2";

        virtual ~ClientboundBBORAddBoundingBoxPacket() override
        {

        }

    protected:
        bounding_box_t ReadBoundingBox(ReadIterator& iter, size_t& length) {
            ReadData<unsigned char>(iter, length); // 0
            unsigned char type = ReadData<unsigned char>(iter, length);

            // if (type == StructureBoundingBox::bounding_box_type) {
                return ReadData<StructureBoundingBox>(iter, length);
            // }
        }
        
        void WriteBoundingBox(bounding_box_t bounding_box, WriteContainer& container) const {
            if (std::holds_alternative<StructureBoundingBox>(bounding_box)) {
                WriteData<unsigned char>('\0', container);
                WriteData<unsigned char>(StructureBoundingBox::bounding_box_type, container);
                WriteData<StructureBoundingBox>(std::get<StructureBoundingBox>(bounding_box), container);
            }
        }

        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ReadData<std::string>(iter, length); // identifier

            data = ReadByteArray(iter, length, length);

            // dimension = ReadData<Identifier>(iter, length);

            // key.push_back(ReadBoundingBox(iter, length));

            // while(length > 0) {
            //     bounding_boxes.push_back(ReadBoundingBox(iter, length));
            // }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(std::string{identifier}, container);
            WriteByteArray(data, container);
            // WriteData<Identifier>(dimension, container);
            // WriteBoundingBox(key.at(0), container);
            // for(auto bounding_box : bounding_boxes) {
            //     WriteBoundingBox(bounding_box, container);
            // }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;

            output["bytes"] = data;

            // output["dimension"] = dimension;

            // if (std::holds_alternative<StructureBoundingBox>(key.at(0))) {
            //     output["key"] = std::get<StructureBoundingBox>(key.at(0)).Serialize();
            // }
            // else {
            //     output["key"] = nullptr;
            // }

            // Json::Value boxes;
            // for(auto bounding_box : bounding_boxes) {
            //     if (std::holds_alternative<StructureBoundingBox>(bounding_box)) {
            //         boxes.push_back(std::get<StructureBoundingBox>(bounding_box).Serialize());
            //     }
            // }
            // output["bounding_boxes"] = boxes;

            return output;
        }

    private:
        // Identifier dimension;
        // std::vector<bounding_box_t> key = std::vector<bounding_box_t>(0);
        // std::vector<bounding_box_t> bounding_boxes = std::vector<bounding_box_t>(0);
        std::vector<unsigned char> data;
    };
} //ProtocolCraft
