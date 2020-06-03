#include "Core.h"

#include "Game\Common\MyKeyBoard.h"
#include "Game\Common\ResourcesManager.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameScene\Manager\SceneManager.h"


Core::Core() : m_life(7), m_invincibleTime(INVINCIBLE_TIME), is_invincibility(false), isAlive(true),is_drawPrimitive(false)
{
}

Core::~Core()
{
}

void Core::Initialize()
{
	//�ϐ��̏�����
	SetPos(DirectX::SimpleMath::Vector3(10.0f, 2.0f, -40.0f));
	ApplyWorld();
	
	//�����蔻��̍쐬
	m_collider[0] = std::make_unique<Sphere>(this, 0.0f);
	m_collider[1] = std::make_unique<Sphere>(this, 1.0f);
	m_collider[2] = std::make_unique<Sphere>(this, 2.0f);
	m_collider[3] = std::make_unique<Sphere>(this, 3.0f);
	m_collider[4] = std::make_unique<Sphere>(this, 5.0f);
	m_collider[5] = std::make_unique<Sphere>(this, 7.0f);
	m_collider[6] = std::make_unique<Sphere>(this, 10.0f);
	m_collider[7] = std::make_unique<Sphere>(this, 13.0f);

	for (int i = 0; i <= m_life; i++)
	{
		m_collider[i]->SetPos(this->GetPos());
		m_collider[i]->SetTag(Collider::COLLIDER_TAG::CORE);
		m_collider[i]->SetCollide(true);
	}
	m_color = DirectX::Colors::Aqua;

	//���f���쐬
	CreateModel();

	//�^�O�̐ݒ�
	SetTag(GAMEOBJECT_TAG::CORE);
}

void Core::Update()
{
	//�F�̃��Z�b�g
	m_color = DirectX::Colors::Aqua;

	//E�L�[�Ńv���~�e�B�u�`��t���O�𔽓]
	if (MyKeyBoard::GetInstance()->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawPrimitive = !is_drawPrimitive;
	}

	//�����蔻��̃}�l�[�W���[�ɓo�^
	CollisionManager::GetInstance()->Add("CORE", m_collider[m_life].get());

	//���G���Ԃ̃J�E���g
	if (is_invincibility)
	{
		m_color = DirectX::Colors::Silver;
		m_invincibleTime--;
		//��莞�Ԍo�ߌ�ɖ��G����
		if (m_invincibleTime == 0)
		{
			m_invincibleTime = INVINCIBLE_TIME;
			is_invincibility = false;
		}
	}

	//���C�t��0�ȉ��ɂȂ����玩��
	if (m_life <= 0)
	{
		//�s�v��Ԃɂ���
		ToParaphernalia();
		//�V�[���J��
		SceneManager::GetInstance()->RequestScene(SCENE_RESULT);
	}
}

void Core::Render()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	FollowCamera* followCamera = FollowCamera::GetInstance();

	//���f���̕`��
	if (isAlive)
	{
		for (int i = 0; i < m_life; i++)
		{
			m_gears[i]->Draw(resourceManager->GetContext(), *resourceManager->GetCommonStates(),
				m_world, followCamera->GetViewMatrix(), followCamera->GetProjMatrix());
		}

		if (is_drawPrimitive)
		{
			for(int i = 1; i <= m_life; i++)
			m_collider[i]->Draw(m_world, followCamera->GetViewMatrix(), followCamera->GetProjMatrix(), m_color);
		}
	}
}

void Core::Finalize()
{
}

void Core::ReadFile()
{

}

void Core::OnCollision(GameObject* gameObject, Collider* designation)
{
	if (!designation)
	{
		//����Ɠ��������ۂ̏���(���G��ԂłȂ��Ƃ�)
		if (gameObject->GetTag() == GameObject::WEAPON && !is_invincibility)
		{
			m_color = DirectX::Colors::Red;
			m_life--;
			//���G��Ԃɂ���
			is_invincibility = true;
		}
	}
}

void Core::CreateModel()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_gears[0] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Core"),
		*resourceManager->GetModelPath());
	m_gears[1] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear1"),
		*resourceManager->GetModelPath());
	m_gears[2] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear2"),
		*resourceManager->GetModelPath());
	m_gears[3] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear3"),
		*resourceManager->GetModelPath());
	m_gears[4] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear4"),
		*resourceManager->GetModelPath());
	m_gears[5] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear5"),
		*resourceManager->GetModelPath());
	m_gears[6] = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Gear6"),
		*resourceManager->GetModelPath());

	//for (std::unique_ptr<DirectX::Model>& e : m_gears)
	//{
	//	e = DirectX::Model::CreateFromCMO(
	//		resourceManager->GetDevice(),
	//		resourceManager->GetModelData("Gear1"),
	//		*resourceManager->GetModelPath());
	//}
}

bool Core::OnCollisionToPlayer()
{
	return false;
}

void Core::Brake()
{
	isAlive = false;
}