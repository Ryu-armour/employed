#include "SceneFailure.h"

#include "Game\Common\MyKeyBoard.h"
#include "Game\Common\ResourcesManager.h"

#include "Game\GameScene\Manager\SceneManager.h"



Scene * SceneFailure::Create()
{
	SceneFailure* scene = new SceneFailure();

	return scene;
}

SceneFailure::~SceneFailure()
{
}

void SceneFailure::Init()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//変数の初期化
	DirectX::CreateWICTextureFromFile(rm->GetDeviceResources()->GetD3DDevice(), L"Game\\Resources\\Textures\\Failure.png", nullptr, m_failure.GetAddressOf());
	DirectX::CreateWICTextureFromFile(rm->GetDeviceResources()->GetD3DDevice(), L"Game\\Resources\\Textures\\Continue.png", nullptr, m_continue.GetAddressOf());
	DirectX::CreateWICTextureFromFile(rm->GetDeviceResources()->GetD3DDevice(), L"Game\\Resources\\Textures\\Close.png", nullptr, m_close.GetAddressOf());
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(rm->GetDeviceResources()->GetD3DDeviceContext());

}

void SceneFailure::Update()
{
	MyKeyBoard* key = MyKeyBoard::GetInstance();

	//スペースキーが押されたらシーン遷移
	if (key->IsKeyMomentDown(DirectX::Keyboard::Space))
	{
		SceneManager::GetInstance()->RequestScene(SceneID::SCENE_PLAY);
	}

	//Escキーで終了
	if (key->IsKeyMomentDown(DirectX::Keyboard::Escape))
	{
		exit(1);
	}
}

void SceneFailure::Render()
{
	//画像の描画
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_failure.Get(), DirectX::SimpleMath::Vector2::Zero);
	m_spriteBatch->End();
}

void SceneFailure::Final()
{
	//終了処理
	m_failure.Reset();
	m_continue.Reset();
	m_close.Reset();
	m_spriteBatch.reset();
}
