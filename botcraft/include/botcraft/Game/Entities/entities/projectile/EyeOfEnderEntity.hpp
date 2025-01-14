#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#if PROTOCOL_VERSION > 404
#include "protocolCraft/Types/Slot.hpp"
#endif

namespace Botcraft
{
    class EyeOfEnderEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        EyeOfEnderEntity();
        virtual ~EyeOfEnderEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 404
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        const ProtocolCraft::Slot& GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    };
}
