#include "GetHurtEnemy.h"

#include "Game\GameObject\Enemy\Enemy.h"


GetHurtEnemy::GetHurtEnemy(Enemy* enemy) : m_enemy(enemy)
{
	//�ϐ��̏�����
	m_stateName = L"GetHurtEnemyState";
}

GetHurtEnemy::~GetHurtEnemy()
{
	Finalize();
}

void GetHurtEnemy::Initialize()
{
	//�J�E���g�̃��Z�b�g
	m_count = 0;
	//���G���
	m_enemy->ToInvincible();
}

void GetHurtEnemy::Update()
{
	//�J�E���g��i�߂�
	m_count++;

	//�X�e�[�g�J��
	if (m_count >= WINCE_TIME)
	{
		m_enemy->UnlockInvicinble();
		m_enemy->ChangeState(m_enemy->GetWalkState());
	}
}

void GetHurtEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	DirectX::SimpleMath::Matrix world = m_enemy->GetWorld();

	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void GetHurtEnemy::Finalize()
{
}

void GetHurtEnemy::LookToThePlayer()
{
	//�v���C���[�Ƃ̋���
	DirectX::SimpleMath::Vector3 distance = m_enemy->GetPlayer()->GetPos() - m_enemy->GetPos();
	//�����Ă������
	DirectX::SimpleMath::Vector3 direction = { 0.0f, 0.0f, -1.0f };

	if (distance.Length() != 0.0f || direction.Length() != 0.0f)
	{
		//���ςƃx�N�g���̒������g����cos�Ƃ����߂�
		float cosSita = distance.Dot(direction) / (distance.Length() * direction.Length());

		//cos�Ƃ���Ƃ��Z�o(�f�O���[�p)
		float sita = DirectX::XMConvertToDegrees(acos(cosSita));

		//�������Z�b�g
		m_enemy->SetAngle(sita);
	}
}
