#include "SearChingEnemy.h"

#include <time.h>

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Enemy\Enemy.h"


SearchingEnemy::SearchingEnemy(Enemy* enemy) : m_enemy(enemy)
{
	//変数の初期化
	m_stateName = L"SearchingEnemyState";
	m_color		= DirectX::Colors::Blue;
}

SearchingEnemy::~SearchingEnemy()
{
	Finalize();
}

void SearchingEnemy::Initialize()
{
	//視界の作成
	m_sight = std::make_unique<Sphere>(m_enemy, m_enemy->SIGHT);
	m_sight->SetPos(m_enemy->GetPos());
	m_sight->SetCollide(true);

}

void SearchingEnemy::Update()
{
	//シーンの切り替え
	if (CommingIntoSight())
	{
		m_enemy->ChangeState(m_enemy->GetWalkState());
	}
}

void SearchingEnemy::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
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
	//プレイヤーの位置
	DirectX::SimpleMath::Vector3 pPos = m_enemy->GetPlayer()->GetPos();
	//プレイヤーとの距離
	DirectX::SimpleMath::Vector3 distance = pPos - m_enemy->GetPos();

	//プレイヤーとの距離の長さ
	float pLength = distance.Length();

	//ベクトルの正規化
	pPos.Normalize();
	distance.Normalize();

	//プレイヤーの位置と距離とのなす角を求める
	float sita = distance.Dot(pPos);
	sita = DirectX::XMConvertToDegrees(sita);

	//プレイヤーが視野角から外れているか距離が遠い
	if(sita > ANGLE || pLength > m_enemy->SIGHT)
		return false;

	return true;
}
