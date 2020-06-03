#include "AttackSword.h"

#include "Game\GameObject\Weapon\Sword\Sword.h"

#include "Game\GameObjectState\Sword\SwordState.h"


AttackSword::AttackSword(Sword* sword) : m_sword(sword)
{
	//�X�e�[�g�̖��O���Z�b�g
	m_stateName = L"AttackSword";
	m_sword = sword;
}

AttackSword::~AttackSword()
{
	Finalize();
}

void AttackSword::Initialize()
{
	//�J�E���g�̃��Z�b�g
	m_attackCount = 0;
}

void AttackSword::Update()
{
	//�J�E���g�̍X�V
	m_attackCount++;
}

void AttackSword::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), m_sword->GetWorld(),
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void AttackSword::Finalize()
{
}