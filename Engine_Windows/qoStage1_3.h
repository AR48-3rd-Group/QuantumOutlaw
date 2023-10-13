#pragma once
#include "qoScene.h"

namespace qo
{
	class Player;
	class Stage1_3 : public Scene
	{
	public:
		Stage1_3();
		virtual ~Stage1_3();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Enter() override;
		void Exit() override;

	private:
		Player* mPlayer;
	};
}


