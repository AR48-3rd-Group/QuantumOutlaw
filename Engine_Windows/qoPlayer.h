#pragma once
#include "qoGameObject.h"

namespace qo
{
    // FSM State Script 에서 적용함
    enum class ePlayerState
    {
        Idle,
        Walk,
        Jump,
        Dead,
    };

    enum class eGunType
    {
        Superposition,
        Entanglement,
        Teleportation,
    };

    class Gun;
    class Player : public GameObject
    {
        friend class PlayerScript;
    public:
        Player();
        virtual ~Player();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void AddGun(eGunType type);
        virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero);

    private:
        Gun*                mActiveGun; // 현재 활성화된 총
        std::vector<Gun*>   mGuns;      // 플레이어가 보유하고있는 총

        ePlayerState        mState;

        int                 mHp;
        float               mSpeed;
    };
}

