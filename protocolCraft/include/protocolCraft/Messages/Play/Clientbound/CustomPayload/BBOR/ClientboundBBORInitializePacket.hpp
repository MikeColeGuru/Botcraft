#pragma once

// Bounding Box Outline Reloaded
// https://github.com/irtimaled/BoundingBoxOutlineReloaded
// https://www.curseforge.com/minecraft/mc-mods/bounding-box-outline-reloaded

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBBORInitializePacket : public BaseMessage<ClientboundBBORInitializePacket>
    {
    public:
        static constexpr int packet_id = ProtocolCraft::ClientboundCustomPayloadPacket::packet_id;
        static constexpr std::string_view packet_name = "BBOR Initialize";

        static constexpr std::string_view identifier = "bbor:initialize";

        virtual ~ClientboundBBORInitializePacket() override
        {

        }

        void SetSeed(long long int _seed) {
            seed = _seed;
        }

        void SetSpawnX(int _spawnX) {
            spawnX = _spawnX;
        }

        void SetSpawnZ(int _spawnZ) {
            spawnZ = _spawnZ;
        }

        long long int GetSeed() {
            return seed;
        }

        int GetSpawnX() {
            return spawnX;
        }

        int GetSpawnZ() {
            return spawnZ;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ReadData<std::string>(iter, length); // identifier
            seed = ReadData<long long int>(iter, length);
            spawnX = ReadData<int>(iter, length);
            spawnZ = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(std::string{identifier}, container);
            WriteData<long long int>(seed, container);
            WriteData<int>(spawnX, container);
            WriteData<int>(spawnZ, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            output["seed"] = seed;
            output["spawn_x"] = spawnX;
            output["spawn_z"] = spawnZ;

            return output;
        }

    private:
        long long int seed;
        int spawnX;
        int spawnZ;
    };
} //ProtocolCraft
