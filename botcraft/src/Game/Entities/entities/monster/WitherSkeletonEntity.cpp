#include "botcraft/Game/Entities/entities/monster/WitherSkeletonEntity.hpp"

namespace Botcraft
{
    WitherSkeletonEntity::WitherSkeletonEntity()
    {

    }

    WitherSkeletonEntity::~WitherSkeletonEntity()
    {

    }


    std::string WitherSkeletonEntity::GetName() const
    {
        return "wither_skeleton";
    }

    EntityType WitherSkeletonEntity::GetType() const
    {
        return EntityType::WitherSkeleton;
    }

    double WitherSkeletonEntity::GetWidth() const
    {
        return 0.7;
    }

    double WitherSkeletonEntity::GetHeight() const
    {
        return 2.4;
    }


    std::string WitherSkeletonEntity::GetClassName()
    {
        return "wither_skeleton";
    }

    EntityType WitherSkeletonEntity::GetClassType()
    {
        return EntityType::WitherSkeleton;
    }

}
