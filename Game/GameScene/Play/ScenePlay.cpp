#include "ScenePlay.h"

#include "Game\Common\CSVLoader.h"
#include "Game\Common\TextManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "game\GameObject\GameObjects.h"
#include "Game\GameObject\Manager\GameObjectManager.h"
#include "Game\GameObject\Enemy\Factory\EnemyFactory.h"

#include "Game\GameScene\Manager\SceneManager.h"


Scene * ScenePlay::Create()
{
	ScenePlay* scene = new ScenePlay();

	return scene;
}

ScenePlay::ScenePlay(): Scene()
{
	SetSceneName(L"ScenePlay");

	//�����o�ϐ��̏�����
	is_drawDebugValue = false;
}

ScenePlay::~ScenePlay()
{
	Final();
}

void ScenePlay::Init()
{
	//�I�u�W�F�N�g�̐���
	CreateObject();

	//�����蔻��̃O���[�v��ݒ�
	SetCollisionGroup();
}

void ScenePlay::Update()
{
	//�J�����̍X�V
	FollowCamera* camera = FollowCamera::GetInstance();
	camera->Update();

	//�}�l�[�W���[�̍X�V
	GameObjectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->DetectCollision();

	//�L�[�{�[�h
	MyKeyBoard* keyboard = MyKeyBoard::GetInstance();
	
	//E�L�[�������ꂽ��f�o�b�O�p�̒l�̕`��t���O�𔽓]
	if (keyboard->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawDebugValue = !is_drawDebugValue;
	}

	//Esc�L�[�������ꂽ��Q�[�����I��
	if (keyboard->IsKeyMomentDown(DirectX::Keyboard::Escape))
	{
		exit(1);
	}
}

void ScenePlay::Render()
{
	//���f���̕`��
	GameObjectManager::GetInstance()->Render();
}

void ScenePlay::Final()
{
	//�Ǘ����Ă���I�u�W�F�N�g�̍폜
	GameObjectManager::GetInstance()->DeleteAllObject();
}

void ScenePlay::SetCollisionGroup()
{
	//�}�l�[�W���[�ɓ����蔻��̃O���[�v��o�^
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "HITENEMY");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "CORE");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "DEFAULT");
	CollisionManager::GetInstance()->AllowCollision("WEAPON", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("WEAPON", "CORE");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "CORE");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "DEFAULT");
}

void ScenePlay::CreateObject()
{
	//���f���쐬
	//�v���C���[
	std::unique_ptr<Player> player = std::make_unique<Player>();
	player->Initialize();
	//�p�[�c
	std::unique_ptr<ArmR> armR = std::make_unique<ArmR>();
	armR->Initialize();
	player->SetArmR(armR.get());
	//���C�t�̍쐬	
	std::unique_ptr<Life> life = std::make_unique<Life>(player.get());
	life->Initialize();
	//����
	std::unique_ptr<Sword> sword = std::make_unique<Sword>(player.get());
	sword->Initialize();
	player->SetWeapon(sword.get());
	//��
	std::unique_ptr<Floor> floor = std::make_unique<Floor>();
	floor->Initialize();
	//�R�A
	std::unique_ptr<Core> core = std::make_unique<Core>();
	core->Initialize();
	//�G
	CSVLoader::GetInstance()->LoadEnemyData(L"Game\\Resources\\MapData\\EnemyData2.csv");
	EnemyFactory::GetInstance()->Create(player.get(),CSVLoader::GetInstance()->GetEnemyData());
	//�V��
	std::unique_ptr<Skydome> skydome = std::make_unique<Skydome>();
	skydome->Initialize();


	//�J�����̏�����
	//�E�B���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = ResourceManager::GetInstance()->GetDeviceResources()->GetOutputSize();

	//�r���[�s��쐬
	DirectX::SimpleMath::Vector3 eye(player->GetPos() + FollowCamera::GetInstance()->TARGET_TO_EYE_VEC * 4);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//�J�����̍쐬
	//��p
	float angle = 45.0f;
	FollowCamera::GetInstance()->Init(player.get(), angle, up);

	//�}�l�[�W���[�ɒǉ�
	GameObjectManager* gameObjectManager = GameObjectManager::GetInstance();
	gameObjectManager->Add(std::move(player));
	gameObjectManager->Add(std::move(life));
	gameObjectManager->Add(std::move(armR));
	gameObjectManager->Add(std::move(sword));
	gameObjectManager->Add(std::move(floor));
	gameObjectManager->Add(std::move(core));
	gameObjectManager->Add(std::move(skydome));
}