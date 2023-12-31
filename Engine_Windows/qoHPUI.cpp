#include "qoHPUI.h"

namespace qo
{
	HPUI::HPUI(Player* player)
		: mPlayer(player)
	{
	}

	HPUI::~HPUI()
	{
	}

	void HPUI::Initialize()
	{
		UI::Initialize();
	}

	void HPUI::Update()
	{
		UI::Update();
	}

	void HPUI::LateUpdate()
	{
		UI::LateUpdate();
	}

	void HPUI::Render()
	{
		UI::Render();
	}
}