#include "ArmR.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Weapon\Sword\Sword.h"


//�R���X�g���N�^
ArmR::ArmR()
{
}

//�f�X�g���N�^
ArmR::~ArmR()
{
}

//������
void ArmR::Initialize()
{
	//���f���̍쐬
	CreateModel();
}

//�X�V
void ArmR::Update()
{
	//����̍��W�̍X�V
	if (m_weapon)
	{
		m_weapon->SetPos(m_pos);
		m_weapon->SetWorld(m_world);
	}
}

//�`��
void ArmR::Render()
{
	//�ϐ��̏���
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	FollowCamera* camera = FollowCamera::GetInstance();

	//�`��
	m_model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(),
		m_world,
		camera->GetViewMatrix(), 
		camera->GetProjMatrix());
}

//�I������
void ArmR::Finalize()
{
}

//Json�t�@�C�����J��
void ArmR::ReadFile()
{
}

//�Փ˔���
void ArmR::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//���f���̍쐬
void ArmR::CreateModel()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//�쐬
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("ArmR"),
		*resourceManager->GetModelPath());
}
