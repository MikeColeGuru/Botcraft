#pragma once

#include "protocolCraft/Types/CustomPayload/BBOR/AbstractBoundingBox.hpp"
#include "protocolCraft/Types/CustomPayload/BBOR/Coords.hpp"

namespace ProtocolCraft
{
    class StructureBoundingBox : public AbstractBoundingBox
    {
    public:
        static constexpr unsigned char bounding_box_type = 'S';

        virtual ~StructureBoundingBox() override
        {

        }

        virtual const unsigned char GetBoundingBoxType() override {
            return bounding_box_type;
        }

        void SetHashCode(const int hash_code_) {
            hash_code = hash_code_;
            SetTypeFromHashCode();
        }

        int GetHashCode() {
            return hash_code;
        }

        std::string& GetType() {
            return type;
        }

        void SetMin(const Coords& coords_) {
            min = coords_;
        }

        void SetMax(const Coords& coords_) {
            max = coords_;
        }

        Coords& GetMin() {
            return min;
        }

        Coords& GetMax() {
            return max;
        }

    protected:
        void SetTypeFromHashCode() {
            std::map<int, std::string>::const_iterator mapping_iter =
                mapping.find(hash_code);
            if (mapping_iter != mapping.end())
            {
                type = std::string(mapping_iter->second);
            }
            else
            {
                type = "Unknown Type";
            }
        }

        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            hash_code = ReadData<int>(iter, length);
            min = ReadData<Coords>(iter, length);
            max = ReadData<Coords>(iter, length);

            SetTypeFromHashCode();
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(hash_code, container);
            WriteData<Coords>(min, container);
            WriteData<Coords>(max, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["type"] = type;
            output["hash_code"] = hash_code;
            output["min"] = min;
            output["max"] = max;

            return output;
        }

    private:

        long hash_code;
        std::string type;
        Coords min, max;

        const std::map<int, std::string> mapping = {
            { 663828647, "minecraft:ocean_ruin_warm" },
            { 500473178, "minecraft:igloo" },
            { -996376581, "minecraft:mansion" },
            { -1467874289, "minecraft:village_taiga" },
            { -1604172283, "minecraft:shipwreck_beached" },
            { -1468404241, "minecraft:village_snowy" },
            { 1860196202, "minecraft:stronghold" },
            { 1541388001, "minecraft:village_savanna" },
            { 1286461596, "minecraft:village_desert" },
            { -1353437812, "minecraft:ruined_portal_jungle" },
            { 1836783184, "minecraft:ruined_portal" },
            { 1547470632, "minecraft:bastion_remnant" },
            { -1642610609, "minecraft:pillager_outpost" },
            { -481824846, "minecraft:fortress" },
            { 1399332866, "minecraft:shipwreck" },
            { 137345714, "minecraft:mineshaft_mesa" },
            { 518889009, "minecraft:ruined_portal_swamp" },
            { -1253518041, "minecraft:ruined_portal_nether" },
            { -1280796581, "minecraft:monument" },
            { 831868828, "minecraft:ruined_portal_mountain" },
            { -1539841820, "minecraft:ruined_portal_desert" },
            { 762183395, "minecraft:end_city" },
            { 1635943536, "minecraft:village_plains" },
            { 1163648294, "minecraft:ancient_city" },
            { -2119164545, "minecraft:nether_fossil" },
            { -1065344207, "minecraft:buried_treasure" },
            { 925602803, "minecraft:mineshaft" },
            { -1702935198, "minecraft:jungle_pyramid" },
            { -846847814, "minecraft:desert_pyramid" },
            { 514602575, "minecraft:ruined_portal_ocean" },
            { 663246086, "minecraft:ocean_ruin_cold" },
            { -1126292716, "minecraft:swamp_hut" }
        };
    };
}