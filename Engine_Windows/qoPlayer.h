#pragma once
#include "qoGameObject.h"

namespace qo
{
    // FSM State Script 에서 적용함
    enum class ePlayerState
    {
        Idle,
        Walk,
        Fall,
        Jump,
        Dash,
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

        virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero);
        
        void AddGun(eGunType type);
        bool ChangeActiveGun(eGunType type);

        eDirection GetDirection() const { return mDir; }

    private:
        Gun*                mActiveGun; // 현재 활성화된 총
        std::vector<Gun*>   mGuns;      // 플레이어가 보유하고있는 총

        ePlayerState        mState;
        eDirection          mDir;

        int                 mHp;
        float               mSpeed;
    };
}

