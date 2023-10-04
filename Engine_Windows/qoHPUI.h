#pragma once
#include "qoUI.h"
#include "qoPlayer.h"

namespace qo
{
	class HPUI : public UI
	{
	public:
		HPUI(Player* player);
		virtual ~HPUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetFixedPosition(Vector3 fixedposition) { mFixedPosition = fixedposition; }
		void SetFixedScale(Vector3 fixedScale) { mFixedScale = fixedScale; }

		Vector3 GetFixedPosition() { return mFixedPosition; }
		Vector3 GetFixedScale() { return mFixedScale; }

	private:
		Vector3 mFixedScale;
		Vector3 mFixedPosition;
		Player* mPlayer;
	};
}


