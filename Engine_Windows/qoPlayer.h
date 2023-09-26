#pragma once
#include "qoGameObject.h"

namespace qo
{
    class Player : public GameObject
    {
    public:
        Player();
        virtual ~Player();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:

    };
}

