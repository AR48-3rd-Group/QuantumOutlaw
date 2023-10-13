#pragma once
#include "..\\Engine_SOURCE\\qoSceneManager.h"
#include "qoPlayScene.h"
#include "qoStage1_1.h"
#include "qoStage1_2.h"
#include "qoStage1_3.h"

namespace qo
{
	void InitializeScenes()
	{
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<Stage1_1>(L"Stage1_1");
		SceneManager::CreateScene<Stage1_2>(L"Stage1_2");
		SceneManager::CreateScene<Stage1_3>(L"Stage1_3");

		SceneManager::LoadScene(L"Stage1_3");
	}
}