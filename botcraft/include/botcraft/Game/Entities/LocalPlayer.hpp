#pragma once

#include <mutex>

#include "botcraft/Game/Entities/entities/player/PlayerEntity.hpp"

namespace Botcraft 
{
    class LocalPlayer : public PlayerEntity
    {
    public:
        LocalPlayer();
        virtual ~LocalPlayer();

        std::mutex& GetMutex();

        const Vector3<double>& GetFrontVector() const;
        const Vector3<double>& GetXZVector() const;
        const Vector3<double>& GetRightVector() const;

        const Vector3<double>& GetPlayerInputs() const;
        const double GetPlayerInputsX() const;
        const double GetPlayerInputsY() const;
        const double GetPlayerInputsZ() const;
        
        float GetFlyingSpeed() const;
        float GetWalkingSpeed() const;
        bool GetIsFlying() const;
        bool GetIsRunning() const;
        bool GetIsClimbing() const;
        bool GetIsInvulnerable() const;
        float GetHealth() const;
        int GetFood() const;
        float GetFoodSaturation() const;
        bool GetHasMoved() const;

        void SetFlyingSpeed(const float flying_speed_);
        void SetWalkingSpeed(const float walking_speed_);
        void SetIsFlying(const bool b);
        void SetIsRunning(const bool b);
        void SetIsClimbing(const bool b);
        void SetIsInvulnerable(const bool b);
        void SetHealth(const float health_);
        void SetFood(const int food_);
        void SetFoodSaturation(const float food_saturation_);
        void SetHasMoved(const bool has_moved_);

        virtual void SetPosition(const Vector3<double>& pos) override;
        virtual void SetX(const double x) override;
        virtual void SetY(const double y) override;
        virtual void SetZ(const double z) override;
        virtual void SetYaw(const float yaw_) override;
        virtual void SetPitch(const float pitch_) override;

        void SetPlayerInputs(const Vector3<double>& p);
        void SetPlayerInputsX(const double x);
        void SetPlayerInputsY(const double y);
        void SetPlayerInputsZ(const double z);
        void AddPlayerInputs(const Vector3<double>& p);
        void AddPlayerInputsX(const double x);
        void AddPlayerInputsY(const double y);
        void AddPlayerInputsZ(const double z);

        virtual bool IsLocalPlayer() const override;
        virtual bool IsRemotePlayer() const override;

        void LookAt(const Vector3<double>& pos, const bool set_pitch = false);
        void Jump();

    private:
        void UpdateVectors();

    private:
        std::mutex player_mutex;

        Vector3<double> frontVector;
        Vector3<double> xzVector;
        Vector3<double> rightVector;

        Vector3<double> player_inputs;

        float flying_speed;
        float walking_speed;
        bool is_flying;
        bool is_running;
        bool is_climbing;

        bool is_invulnerable;
        float health;
        int food;
        float food_saturation;

        bool has_moved;
    };
} // Botcraft
