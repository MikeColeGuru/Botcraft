#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Coords : public NetworkType
    {
    public:
        virtual ~Coords() override
        {

        }

        void SetX(const VarInt& x_) {
            x = x_;
        }

        void SetY(const VarInt& y_) {
            y = y_;
        }

        void SetZ(const VarInt& z_) {
            z = z_;
        }

        const VarInt& GetX() {
            return x;
        }

        const VarInt& GetY() {
            return y;
        }

        const VarInt& GetZ() {
            return z;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<VarInt>(iter, length);
            y = ReadData<VarInt>(iter, length);
            z = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(x, container);
            WriteData<VarInt>(y, container);
            WriteData<VarInt>(z, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;

            return output;
        }

    private:
        int x, y, z;
    };
}