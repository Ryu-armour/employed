#include "ScenePause.h"

#include "Game\Common\ResourcesManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\GameScene\Manager\SceneManager.h"


Scene * ScenePause::Create()
{
	ScenePause* scene = new ScenePause();

	return scene;
}

ScenePause::ScenePause()
{
	//���݂̃V�[����������
	SetSceneName(L"ScenePause");

	//�ϐ��̏�����
	m_choice = OPTION::BACK;
}


ScenePause::~ScenePause()
{
}

void ScenePause::Init()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	
	//�ϐ��̏�����
	DirectX::CreateWICTextureFromFile(rm->GetDevice(), L"Game\\Resources\\Textures\\FinishGame.png", nullptr, m_finish.GetAddressOf());
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(rm->GetDeviceResources()->GetD3DDeviceContext());
	//m_manipulation_mediator[BACK] = RequestScene;
	//m_manipulation_mediator[FINISH] = FinishGame;
}

void ScenePause::Update()
{
	MyKeyBoard* key = MyKeyBoard::GetInstance();


	//�X�y�[�X�L�[�������ꂽ
	if (key->IsKeyMomentDown(DirectX::Keyboard::Space))
	{
		m_manipulation_mediator.at(m_choice);
	}

	//Esc�L�[�ŃQ�[���ɖ߂�
	if (key->IsKeyMomentDown(DirectX::Keyboard::Escape))
	{
		SceneManager::GetInstance()->RequestScene(SceneID::SCENE_PLAY);
	}
}

void ScenePause::Render()
{
	//�摜�̕`��
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_back.Get(), DirectX::SimpleMath::Vector2((float)OPTIN_POS_X,(float)OPTIN_POS_Y + (float)SPACING * m_choice));
	m_spriteBatch->Draw(m_finish.Get(), DirectX::SimpleMath::Vector2((float)OPTIN_POS_X,(float)OPTIN_POS_Y + (float)SPACING * m_choice));
	m_spriteBatch->End();
}

void ScenePause::Final()
{
	//�|�C���^�̉��
	m_back.Reset();
	m_finish.Reset();
	m_spriteBatch.reset();
}

void ScenePause::RequestScene()
{
	SceneManager::GetInstance()->RequestScene(m_scene_id_mediator.at(m_choice));
}

void ScenePause::FinishGame()
{
	exit(1);
}