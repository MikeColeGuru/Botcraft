#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/LlamaEntity.hpp"

namespace Botcraft
{
    class TraderLlamaEntity : public LlamaEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = LlamaEntity::metadata_count + LlamaEntity::hierarchy_metadata_count;

    public:
        TraderLlamaEntity();
        virtual ~TraderLlamaEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
#endif
