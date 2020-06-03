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
	//ターゲットの位置を入れる
	m_targetPos = &m_enemy->GetPlayer()->GetPos();
}

void WalkingEnemy::Update()
{
	//ターゲットの方向に向く
	LookAtThePlayer();

	//ターゲットと現在の座標の距離
	DirectX::SimpleMath::Vector3 length =  *m_targetPos - m_enemy->GetPos();
	float llength = length.Length();

	//ターゲットから一定距離離れるまで移動
	if (1.0f < llength && llength < m_enemy->SIGHT)
	{
		//目的地に進む
		DirectX::SimpleMath::Vector3 n = length;
		n.Normalize();
		m_enemy->SetVel(n * MOVEMENT);
		m_enemy->Move();
	}
	else
	{
		//目的地に着いたら次の目的地を探す
		m_enemy->ChangeState(m_enemy->GetSearchState());
	}
}

void WalkingEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), m_enemy->GetWorld(),
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void WalkingEnemy::Finalize()
{
}

void WalkingEnemy::LookAtThePlayer()
{
	//プレイヤーとの距離
	DirectX::SimpleMath::Vector3 relativePos = m_enemy->GetPlayer()->GetPos() - m_enemy->GetPos();
	//向いている方向
	DirectX::SimpleMath::Vector3 direction = { 0.0f, 0.0f, 1.0f };
	
	float angle1 = atan2(relativePos.z, relativePos.x);
	float angle2 = atan2(direction.z, direction.x);

	//cosθからθを算出(デグリー角)
	float theta = DirectX::XMConvertToDegrees(angle1 - angle2);

	//向きをセット
	m_enemy->SetAngle(-theta);


	//if (distance.Length() != 0.0f || direction.Length() != 0.0f)
	//{
	//	//内積とベクトルの長さを使ってcosθを求める
	//	float cosTheta = distance.Dot(direction) / (distance.Length() * direction.Length());

	//	//cosθからθを算出(デグリー角)
	//	float sita = DirectX::XMConvertToDegrees(acos(cosTheta));

	//	//向きをセット
	//	m_enemy->SetAngle(sita);
	//}
}
