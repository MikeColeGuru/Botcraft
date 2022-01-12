#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class ZombieHorseEntity : public AbstractHorseEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        ZombieHorseEntity();
        virtual ~ZombieHorseEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}