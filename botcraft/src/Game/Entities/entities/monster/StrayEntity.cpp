#include "botcraft/Game/Entities/entities/monster/StrayEntity.hpp"

namespace Botcraft
{
    StrayEntity::StrayEntity()
    {

    }

    StrayEntity::~StrayEntity()
    {

    }


    std::string StrayEntity::GetName() const
    {
        return "stray";
    }

    EntityType StrayEntity::GetType() const
    {
        return EntityType::Stray;
    }

    double StrayEntity::GetWidth() const
    {
        return 0.6;
    }

    double StrayEntity::GetHeight() const
    {
        return 1.99;
    }


    std::string StrayEntity::GetClassName()
    {
        return "stray";
    }

    EntityType StrayEntity::GetClassType()
    {
        return EntityType::Stray;
    }

}
