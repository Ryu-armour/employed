#include "SearChingEnemy.h"

#include <time.h>

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Enemy\Enemy.h"


SearchingEnemy::SearchingEnemy(Enemy* enemy) : m_enemy(enemy)
{
	//�ϐ��̏�����
	m_stateName = L"SearchingEnemyState";
	m_color		= DirectX::Colors::Blue;
}

SearchingEnemy::~SearchingEnemy()
{
	Finalize();
}

void SearchingEnemy::Initialize()
{
	//���E�̍쐬
	m_sight = std::make_unique<Sphere>(m_enemy, m_enemy->SIGHT);
	m_sight->SetPos(m_enemy->GetPos());
	m_sight->SetCollide(true);

}

void SearchingEnemy::Update()
{
	//�V�[���̐؂�ւ�
	if (CommingIntoSight())
	{
		m_enemy->ChangeState(m_enemy->GetWalkState());
	}
}

void SearchingEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	DirectX::SimpleMath::Matrix world = m_enemy->GetWorld();

	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void SearchingEnemy::Finalize()
{
}

bool SearchingEnemy::CommingIntoSight()
{
	//�v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3 pPos = m_enemy->GetPlayer()->GetPos();
	//�v���C���[�Ƃ̋���
	DirectX::SimpleMath::Vector3 distance = pPos - m_enemy->GetPos();

	//�v���C���[�Ƃ̋����̒���
	float pLength = distance.Length();

	//�x�N�g���̐��K��
	pPos.Normalize();
	distance.Normalize();

	//�v���C���[�̈ʒu�Ƌ����Ƃ̂Ȃ��p�����߂�
	float sita = distance.Dot(pPos);
	sita = DirectX::XMConvertToDegrees(sita);

	//�v���C���[������p����O��Ă��邩����������
	if(sita > ANGLE || pLength > m_enemy->SIGHT)
		return false;

	return true;
}
