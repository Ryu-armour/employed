#include "SceneResult.h"

#include "Game\Common\ResourcesManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\GameScene\Manager\SceneManager.h"


Scene * SceneResult::Create()
{
	SceneResult* scene = new SceneResult();

	return scene;
}

SceneResult::SceneResult()
{
	SetSceneName(L"SceneResult");
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//�ϐ��̏�����
	DirectX::CreateWICTextureFromFile(rm->GetDeviceResources()->GetD3DDevice(), L"Game\\Resources\\Textures\\Clear.png", nullptr, m_clear.GetAddressOf());
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(rm->GetDeviceResources()->GetD3DDeviceContext());

}

void SceneResult::Update()
{
	MyKeyBoard* key = MyKeyBoard::GetInstance();

	//�X�y�[�X�L�[�������ꂽ��V�[���J��
	if (key->IsKeyMomentDown(DirectX::Keyboard::Space))
	{
		SceneManager::GetInstance()->RequestScene(SceneID::SCENE_PLAY);
	}

	//Esc�L�[�ŏI��
	if (key->IsKeyMomentDown(DirectX::Keyboard::Escape))
	{
		exit(1);
	}
}

void SceneResult::Render()
{
	//�摜�̕`��
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_clear.Get(), DirectX::SimpleMath::Vector2::Zero);
	m_spriteBatch->End();
}

void SceneResult::Final()
{
	//�I������
	m_clear.Reset();
	m_spriteBatch.reset();
}

void SceneResult::SetCollisionGroup()
{
}

void SceneResult::CreateObject()
{
}
