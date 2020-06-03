//
// Game.h
//

#pragma once

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"
#include <Effects.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:
	static const wchar_t* WINDOW_TITLE;
	static const int      WINDOW_WIDTH;
	static const int      WINDOW_HEIGHT;

public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize(int& width, int& height) const;

	//モデルデータをマネージャーにセット
	void SetModelToManager();

	//シーンを追加
	void AddScene();
private:

    void Update(const DX::StepTimer& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	//Common States
	std::unique_ptr<DirectX::CommonStates> m_commonStates;

	//SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;

	//マウス
	std::unique_ptr<DirectX::Mouse> m_pMouse;

	//射影行列
	DirectX::SimpleMath::Matrix m_projection;
};