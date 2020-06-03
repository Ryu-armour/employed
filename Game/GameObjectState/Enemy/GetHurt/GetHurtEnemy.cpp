#include "GetHurtEnemy.h"

#include "Game\GameObject\Enemy\Enemy.h"


GetHurtEnemy::GetHurtEnemy(Enemy* enemy) : m_enemy(enemy)
{
	//変数の初期化
	m_stateName = L"GetHurtEnemyState";
}

GetHurtEnemy::~GetHurtEnemy()
{
	Finalize();
}

void GetHurtEnemy::Initialize()
{
	//カウントのリセット
	m_count = 0;
	//無敵状態
	m_enemy->ToInvincible();
}

void GetHurtEnemy::Update()
{
	//カウントを進める
	m_count++;

	//ステート遷移
	if (m_count >= WINCE_TIME)
	{
		m_enemy->UnlockInvicinble();
		m_enemy->ChangeState(m_enemy->GetWalkState());
	}
}

void GetHurtEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
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
	//プレイヤーとの距離
	DirectX::SimpleMath::Vector3 distance = m_enemy->GetPlayer()->GetPos() - m_enemy->GetPos();
	//向いている方向
	DirectX::SimpleMath::Vector3 direction = { 0.0f, 0.0f, -1.0f };

	if (distance.Length() != 0.0f || direction.Length() != 0.0f)
	{
		//内積とベクトルの長さを使ってcosθを求める
		float cosSita = distance.Dot(direction) / (distance.Length() * direction.Length());

		//cosθからθを算出(デグリー角)
		float sita = DirectX::XMConvertToDegrees(acos(cosSita));

		//向きをセット
		m_enemy->SetAngle(sita);
	}
}
