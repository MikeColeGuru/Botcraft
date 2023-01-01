#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundExplodePacket : public BaseMessage<ClientboundExplodePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x1C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1C;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x1C;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x19;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x1B;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x1A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Explode";
        }

        virtual ~ClientboundExplodePacket() override
        {

        }

#if PROTOCOL_VERSION < 761
        void SetX(const float x_)
        {
            x = x_;
        }

        void SetY(const float y_)
        {
            y = y_;
        }

        void SetZ(const float z_)
        {
            z = z_;
        }
#else
        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }
#endif

        void SetPower(const float power_)
        {
            power = power_;
        }

        void SetToBlow(const std::vector<NetworkPosition>& to_blow_)
        {
            to_blow = to_blow_;
        }

        void SetKnockbackX(const float knockback_x_)
        {
            knockback_x = knockback_x_;
        }

        void SetKnockbackY(const float knockback_y_)
        {
            knockback_y = knockback_y_;
        }

        void SetKnockbackZ(const float knockback_z_)
        {
            knockback_z = knockback_z_;
        }

#if PROTOCOL_VERSION < 761
        const float GetX() const
        {
            return x;
        }

        const float GetY() const
        {
            return y;
        }

        const float GetZ() const
        {
            return z;
        }
#else

        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }
#endif

        const float GetPower() const
        {
            return power;
        }

        const std::vector<NetworkPosition>& GetToBlow() const
        {
            return to_blow;
        }

        const float GetKnockbackX() const
        {
            return knockback_x;
        }

        const float GetKnockbackY() const
        {
            return knockback_y;
        }

        const float GetKnockbackZ() const
        {
            return knockback_z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
#else
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
#endif
            power = ReadData<float>(iter, length);
#if PROTOCOL_VERSION < 755
            const int to_blow_size = ReadData<int>(iter, length);
#else
            const int to_blow_size = ReadData<VarInt>(iter, length);
#endif
            to_blow = std::vector<NetworkPosition>(to_blow_size);
            for (int i = 0; i < to_blow_size; ++i)
            {
                to_blow[i].SetX(static_cast<int>(ReadData<char>(iter, length)));
                to_blow[i].SetY(static_cast<int>(ReadData<char>(iter, length)));
                to_blow[i].SetZ(static_cast<int>(ReadData<char>(iter, length)));
            }
            knockback_x = ReadData<float>(iter, length);
            knockback_y = ReadData<float>(iter, length);
            knockback_z = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
#else
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
#endif
            WriteData<float>(power, container);
#if PROTOCOL_VERSION < 755
            WriteData<int>(static_cast<int>(to_blow.size()), container);
#else
            WriteData<VarInt>(static_cast<int>(to_blow.size()), container);
#endif
            for (int i = 0; i < to_blow.size(); ++i)
            {
                WriteData<char>(to_blow[i].GetX(), container);
                WriteData<char>(to_blow[i].GetY(), container);
                WriteData<char>(to_blow[i].GetZ(), container);
            }
            WriteData<float>(knockback_x, container);
            WriteData<float>(knockback_y, container);
            WriteData<float>(knockback_z, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["power"] = power;
            output["to_blow"] = nlohmann::json::array();
            for (int i = 0; i < to_blow.size(); ++i)
            {
                output["to_blow"].push_back(to_blow[i].Serialize());
            }
            output["knockback_x"] = knockback_x;
            output["knockback_y"] = knockback_y;
            output["knockback_z"] = knockback_z;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761
        float x;
        float y;
        float z;
#else
        double x;
        double y;
        double z;
#endif
        float power;
        std::vector<NetworkPosition> to_blow;
        float knockback_x;
        float knockback_y;
        float knockback_z;

    };
} //ProtocolCraft
