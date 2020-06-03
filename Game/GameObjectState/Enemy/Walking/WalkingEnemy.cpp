#include "WalkingEnemy.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Enemy\Enemy.h"


WalkingEnemy::WalkingEnemy(Enemy* enemy)
{
	m_enemy = enemy;
	m_stateName = L"WalkingEnemyState";
}

WalkingEnemy::~WalkingEnemy()
{
	Finalize();
}

void WalkingEnemy::Initialize()
{
	//�^�[�Q�b�g�̈ʒu������
	m_targetPos = &m_enemy->GetPlayer()->GetPos();
}

void WalkingEnemy::Update()
{
	//�^�[�Q�b�g�̕����Ɍ���
	LookAtThePlayer();

	//�^�[�Q�b�g�ƌ��݂̍��W�̋���
	DirectX::SimpleMath::Vector3 length =  *m_targetPos - m_enemy->GetPos();
	float llength = length.Length();

	//�^�[�Q�b�g�����苗�������܂ňړ�
	if (1.0f < llength && llength < m_enemy->SIGHT)
	{
		//�ړI�n�ɐi��
		DirectX::SimpleMath::Vector3 n = length;
		n.Normalize();
		m_enemy->SetVel(n * MOVEMENT);
		m_enemy->Move();
	}
	else
	{
		//�ړI�n�ɒ������玟�̖ړI�n��T��
		m_enemy->ChangeState(m_enemy->GetSearchState());
	}
}

void WalkingEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), m_enemy->GetWorld(),
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void WalkingEnemy::Finalize()
{
}

void WalkingEnemy::LookAtThePlayer()
{
	//�v���C���[�Ƃ̋���
	DirectX::SimpleMath::Vector3 relativePos = m_enemy->GetPlayer()->GetPos() - m_enemy->GetPos();
	//�����Ă������
	DirectX::SimpleMath::Vector3 direction = { 0.0f, 0.0f, 1.0f };
	
	float angle1 = atan2(relativePos.z, relativePos.x);
	float angle2 = atan2(direction.z, direction.x);

	//cos�Ƃ���Ƃ��Z�o(�f�O���[�p)
	float theta = DirectX::XMConvertToDegrees(angle1 - angle2);

	//�������Z�b�g
	m_enemy->SetAngle(-theta);


	//if (distance.Length() != 0.0f || direction.Length() != 0.0f)
	//{
	//	//���ςƃx�N�g���̒������g����cos�Ƃ����߂�
	//	float cosTheta = distance.Dot(direction) / (distance.Length() * direction.Length());

	//	//cos�Ƃ���Ƃ��Z�o(�f�O���[�p)
	//	float sita = DirectX::XMConvertToDegrees(acos(cosTheta));

	//	//�������Z�b�g
	//	m_enemy->SetAngle(sita);
	//}
}
