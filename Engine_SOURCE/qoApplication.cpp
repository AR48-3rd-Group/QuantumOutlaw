#include "qoApplication.h"
#include "qoGraphicsDevice_DX11.h"

#include "qoInput.h"
#include "qoTime.h"
#include "qoRenderer.h"
#include "qoSceneManager.h"
#include "qoCollisionManager.h"

using namespace qo::graphics;

namespace qo
{
	Application::~Application()
	{
		renderer::Release();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();

		renderer::Initialize();
		CollisionManager::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
		graphicsDevice->Clear();
		graphicsDevice->AdjustViewport();

		Time::Render();
		SceneManager::Render();

		//graphicsDevice->Render();
		graphicsDevice->Present();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicsDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicsDevice = std::make_unique<GraphicsDevice_DX11>();
			qo::graphics::GetDevice() = graphicsDevice.get();
			//qo::device = graphicsDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
