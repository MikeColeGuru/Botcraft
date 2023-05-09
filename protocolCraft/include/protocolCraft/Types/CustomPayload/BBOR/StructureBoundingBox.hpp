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
            { -1344621490, "World_Spawn" },
            { -624909014, "Spawn_Chunks" },
            { -1619452207, "Lazy_Chunks" },
            { -290022679, "Mob_Spawner" },
            { -1209894595, "Slime_Chunks" },
            { 823719047, "AFK Sphere" },
            { 707051500, "Biome Border" },
            { 2029746065, "Custom" },
            { 1985788004, "Beacon" },
            { -1679244834, "Conduit" },
            { -1080583951, "Spawnable Blocks" },
            { 1877252482, "Flower Forest" },
            { 1715580355, "Bedrock Ceiling" }
        };
    };
}