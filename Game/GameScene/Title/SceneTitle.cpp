#include "SceneTitle.h"

#include "Game\Common\ResourcesManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\GameScene\Manager\SceneManager.h"


Scene * SceneTitle::Create()
{
	SceneTitle* scene = new SceneTitle();

	return scene;
}

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//�ϐ��̏�����
	DirectX::CreateWICTextureFromFile(rm->GetDeviceResources()->GetD3DDevice(), L"Game\\Resources\\Textures\\Title.png", nullptr, m_title.GetAddressOf());
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(rm->GetDeviceResources()->GetD3DDeviceContext());

}

void SceneTitle::Update()
{
	MyKeyBoard* key = MyKeyBoard::GetInstance();

	//�X�y�[�X�L�[�������ꂽ��V�[���J��
	if (key->IsKeyMomentDown(DirectX::Keyboard::Space))
	{
		SceneManager::GetInstance()->RequestScene(SceneID::SCENE_PLAY);
	}
}

void SceneTitle::Render()
{
	//�摜�̕`��
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_title.Get(), DirectX::SimpleMath::Vector2::Zero);
	m_spriteBatch->End();
}

void SceneTitle::Final()
{
	//�I������
	m_title.Reset();
	m_spriteBatch.reset();
}

void SceneTitle::CreateObject()
{
}
