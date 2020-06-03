#include "WaitSword.h"

#include "Game\GameObject\Weapon\Sword\Sword.h"


WaitSword::WaitSword(Sword* sword) : m_sword(sword)
{
	//�X�e�[�g�̖��O���Z�b�g
	m_stateName = L"WaitSword";
	m_sword = sword;

}

WaitSword::~WaitSword()
{
	Finalize();
}

void WaitSword::Initialize()
{
}

void WaitSword::Update()
{
}

void WaitSword::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//���f���̕`��
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), m_sword->GetWorld(),
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void WaitSword::Finalize()
{
}
