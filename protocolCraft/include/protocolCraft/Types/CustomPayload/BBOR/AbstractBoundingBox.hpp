#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class AbstractBoundingBox : public NetworkType
    {
        public:

        virtual const unsigned char GetBoundingBoxType() {
            return '\0';
        }

        protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            return output;
        }

    };
}