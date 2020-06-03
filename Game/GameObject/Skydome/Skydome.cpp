#include "Skydome.h"

#include "Game\Common\ResourcesManager.h"


//�R���X�g���N�^
Skydome::Skydome()
{
}

//�f�X�g���N�^
Skydome::~Skydome()
{
}

//������
void Skydome::Initialize()
{
	//���f���̍쐬
	CreateModel();
}

//�X�V
void Skydome::Update()
{
}

//�`��
void Skydome::Render()
{
	//�ϐ��̏���
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	FollowCamera* camera = FollowCamera::GetInstance();

	//���f���̕`��
	m_model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), DirectX::SimpleMath::Matrix::Identity,
		camera->GetViewMatrix(), camera->GetProjMatrix());
}

//�I������
void Skydome::Finalize()
{
}

//Json�t�@�C�����J��
void Skydome::ReadFile()
{
}

//�Փ˔���
void Skydome::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//���f���̍쐬
void Skydome::CreateModel()
{
	//�ϐ��̏���
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̍쐬
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Skydome"),
		*resourceManager->GetModelPath());
}