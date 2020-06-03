//
// Game.cpp
//


#include "Game.h"

#include "Game\Common\MyKeyBoard.h"
#include "Game\Common\ResourcesManager.h"

#include "Game\GameScene\Scenes.h"
#include "Game\GameScene\Manager\SceneManager.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;


const wchar_t* Game::WINDOW_TITLE  = L"Game";
const int      Game::WINDOW_WIDTH  = 1280;
const int      Game::WINDOW_HEIGHT = 720;


Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceResources->GetD3DDeviceContext());
	ResourceManager::GetInstance()->SetSpriteBatch(m_spriteBatch.get());

	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pMouse->SetWindow(window);
	m_pMouse->SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);

	//シーンを追加
	AddScene();

	//開始シーンの設定
	SceneManager::GetInstance()->SetStartScene(SCENE_PLAY);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(const DX::StepTimer& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	//キーボードの更新(最新)
	MyKeyBoard::GetInstance()->UpdateCurrentKey();

	//シーンの更新
	SceneManager::GetInstance()->UpdateActiveScene();

	//キーボードの更新(前情報)
	MyKeyBoard::GetInstance()->UpdatePreviousKey();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	m_spriteBatch->Begin();

	//シーンの描画
	SceneManager::GetInstance()->RenderActiveScene();

	m_spriteBatch->End();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width  = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
}

void Game::SetModelToManager()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルのセット
	resourceManager->SetModelData("Player",  L"Game\\Resources\\Models\\Player.cmo");
	resourceManager->SetModelData("ArmR",    L"Game\\Resources\\Models\\ArmR.cmo");
	resourceManager->SetModelData("Sword",   L"Game\\Resources\\Models\\Sword.cmo");
	resourceManager->SetModelData("Floor",   L"Game\\Resources\\Models\\Floor.cmo");
	resourceManager->SetModelData("Core",    L"Game\\Resources\\Models\\Core.cmo");
	resourceManager->SetModelData("Gear1",   L"Game\\Resources\\Models\\Gear1.cmo");
	resourceManager->SetModelData("Gear2",   L"Game\\Resources\\Models\\Gear2.cmo");
	resourceManager->SetModelData("Gear3",   L"Game\\Resources\\Models\\Gear3.cmo");
	resourceManager->SetModelData("Gear4",   L"Game\\Resources\\Models\\Gear4.cmo");
	resourceManager->SetModelData("Gear5",   L"Game\\Resources\\Models\\Gear5.cmo");
	resourceManager->SetModelData("Gear6",   L"Game\\Resources\\Models\\Gear6.cmo");
	resourceManager->SetModelData("Enemy",   L"Game\\Resources\\Models\\Enemy.cmo");
	resourceManager->SetModelData("Skydome", L"Game\\Resources\\Models\\Skydoom.cmo");

	//テクスチャのセット
	resourceManager->SetTextureData("Life", L"Game\\Resources\\Textures\\Life.png");

}

void Game::AddScene()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->AddScene(SCENE_TITLE, SceneTitle::Create);
	sceneManager->AddScene(SCENE_PLAY, ScenePlay::Create);
	sceneManager->AddScene(SCENE_PAUSE, ScenePause::Create);
	sceneManager->AddScene(SCENE_RESULT, SceneResult::Create);
	sceneManager->AddScene(SCENE_FAILURE, SceneFailure::Create);
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	//生成
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();
	m_commonStates = std::make_unique<DirectX::CommonStates>(m_deviceResources->GetD3DDevice());

	//マネージャーに各情報を渡す
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	resourceManager->SetDeviceResources(m_deviceResources.get());
	resourceManager->SetCommonStates(m_commonStates.get());
	resourceManager->SetModelPath(L"Game\\Resources\\Models");

	//モデルデータのセット
	SetModelToManager();

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	//画角を設定
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	//射影行列に反映させる
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY, aspectRatio, 0.01f, 10000.0f);

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
