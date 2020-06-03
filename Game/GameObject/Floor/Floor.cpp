#include "Floor.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\Camera\FollowCameraClass.h"


Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Initialize()
{
	//���f���̍쐬
	CreateModel();

	//�ʒu�̒���
	m_pos.y = -0.1f;
}

void Floor::Update()
{
}

void Floor::Render()
{
	//�ϐ��̏���
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//ID3D11DeviceContext* deviceContext = resourceManager->GetContext();
	const DirectX::CommonStates* commonState = resourceManager->GetCommonStates();
	//���_
	DirectX::SimpleMath::Matrix view = FollowCamera::GetInstance()->GetViewMatrix();
	//�v���W�F�N�V����
	DirectX::SimpleMath::Matrix proj = FollowCamera::GetInstance()->GetProjMatrix();
	// �ʒu
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;
	// �ړ��s��
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	//for (int row = 0; row < MAP_ROW; row++)
	//{
	//	for (int column = 0; column < MAP_COLUMN; column++)
	//	{
	//		// �ʒu���v�Z����
	//		position = DirectX::SimpleMath::Vector3(float(column - MAP_COLUMN / 2) * FLOOR_SIZE,
	//												0.0f, float(row - MAP_ROW / 2) * FLOOR_SIZE);
	//		// �ړ��s����쐬����
	//		translation = DirectX::SimpleMath::Matrix::CreateTranslation(position);
	//		//���f���̕`��
	//		m_model->Draw(deviceContext,
	//			*commonState,
	//			translation,
	//			view, 
	//			proj);
	//	}
	//}
	//���f���̕`��
	m_model->Draw(resourceManager->GetContext(),
		*commonState, translation,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void Floor::Finalize()
{

}

void Floor::ReadFile()
{

}

void Floor::OnCollision(GameObject* gameObject, Collider* designation)
{
	gameObject;
	designation;
}

void Floor::CreateModel()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Floor"),
		*resourceManager->GetModelPath());
}