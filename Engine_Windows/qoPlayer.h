#pragma once
#include "qoGameObject.h"

namespace qo
{
    class Gun;
    class Player : public GameObject
    {
    public:
        Player();
        virtual ~Player();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void AddGun();

    private:
        Gun*                mActiveGun; // 현재 활성화된 총
        std::vector<Gun*>   mGuns;      // 플레이어가 보유하고있는 총
    };
}

