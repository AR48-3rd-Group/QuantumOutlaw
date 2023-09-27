#pragma once
#include "qoGameObject.h"

namespace qo
{
	class Guard : public GameObject
	{
	public:
		enum class eState
		{
			Serch,	// 좌우로 움직이면서 플레이어 찾기
			Follow,	// 플레이어 찾으면 따라가기
			Attack,
			Hit,
			Death,
			End,
		};

		Guard();
		virtual ~Guard();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		//virtual int Hp override;
	private:
		eState mState;
	};
}