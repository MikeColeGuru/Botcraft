#if PROTOCOL_VERSION > 761
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class DisplayEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 14;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        DisplayEntity();
        virtual ~DisplayEntity();

        virtual bool IsDisplay() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataInterpolationStartDeltaTicksId() const;
        int GetDataInterpolationDurationId() const;
        Vector3<float> GetDataTranslationId() const;
        Vector3<float> GetDataScaleId() const;
        std::array<float, 4> GetDataLeftRotationId() const;
        std::array<float, 4> GetDataRightRotationId() const;
        char GetDataBillboardRenderConstraintsId() const;
        int GetDataBrightnessOverrideId() const;
        float GetDataViewRangeId() const;
        float GetDataShadowRadiusId() const;
        float GetDataShadowStrengthId() const;
        float GetDataWidthId() const;
        float GetDataHeightId() const;
        int GetDataGlowColorOverrideId() const;
        
        void SetDataInterpolationStartDeltaTicksId(const int data_interpolation_start_delta_ticks_id);
        void SetDataInterpolationDurationId(const int data_interpolation_duration_id);
        void SetDataTranslationId(const Vector3<float> data_translation_id);
        void SetDataScaleId(const Vector3<float> data_scale_id);
        void SetDataLeftRotationId(const std::array<float, 4> data_left_rotation_id);
        void SetDataRightRotationId(const std::array<float, 4> data_right_rotation_id);
        void SetDataBillboardRenderConstraintsId(const char data_billboard_render_constraints_id);
        void SetDataBrightnessOverrideId(const int data_brightness_override_id);
        void SetDataViewRangeId(const float data_view_range_id);
        void SetDataShadowRadiusId(const float data_shadow_radius_id);
        void SetDataShadowStrengthId(const float data_shadow_strength_id);
        void SetDataWidthId(const float data_width_id);
        void SetDataHeightId(const float data_height_id);
        void SetDataGlowColorOverrideId(const int data_glow_color_override_id);
        
    };
}
#endif
