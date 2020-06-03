#include "AttackSword.h"

#include "Game\GameObject\Weapon\Sword\Sword.h"

#include "Game\GameObjectState\Sword\SwordState.h"


AttackSword::AttackSword(Sword* sword) : m_sword(sword)
{
	//ステートの名前をセット
	m_stateName = L"AttackSword";
	m_sword = sword;
}

AttackSword::~AttackSword()
{
	Finalize();
}

void AttackSword::Initialize()
{
	//カウントのリセット
	m_attackCount = 0;
}

void AttackSword::Update()
{
	//カウントの更新
	m_attackCount++;
}

void AttackSword::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), m_sword->GetWorld(),
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void AttackSword::Finalize()
{
}