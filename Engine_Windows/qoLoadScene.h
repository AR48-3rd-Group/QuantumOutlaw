#pragma once
#include "..\\Engine_SOURCE\\qoSceneManager.h"
#include "qoPlayScene.h"

namespace qo
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}