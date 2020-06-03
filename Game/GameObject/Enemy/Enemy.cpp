#include "Enemy.h"

#include "Game\Common\MyKeyBoard.h"
#include "Game\Common\ResourcesManager.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\GameObjectState\Enemy\EnemyState.h"


//コンストラクタ
Enemy::Enemy(GameObject* player) : m_life(3),m_angle(0.0f),m_quaternion(DirectX::SimpleMath::Vector3::Zero, 0.0f),
is_invincibility(false), m_vel(DirectX::SimpleMath::Vector3::Zero),m_player(player)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	//メンバ変数の初期化
	ApplyWorld();

	//モデルの作成
	m_model = std::make_unique <DirectX::Model>();
	CreateModel();

	//各ステートの生成
	m_gethurt = std::make_unique<GetHurtEnemy>(this);
	m_walk = std::make_unique<WalkingEnemy>(this);
	m_search = std::make_unique<SearchingEnemy>(this);

	//Stateをセット
	EnemyState* enemyState = EnemyState::GetInstance();
	enemyState->Add(EnemyState::GetHurt, std::move(std::make_unique<GetHurtEnemy>(this)));
	enemyState->Add(EnemyState::Walking, std::move(std::make_unique<WalkingEnemy>(this)));
	enemyState->Add(EnemyState::Search, std::move(std::make_unique<SearchingEnemy>(this)));

	//初期Stateの設定
	ChangeState(m_search.get());

	//当たり判定の作成
	m_hurtBox = std::make_unique<Sphere>(this, HURT_SIZE);
	m_hurtBox->SetPos(this->GetPos());
	m_hurtBox->SetTag(Collider::COLLIDER_TAG::HURTENEMY);
	m_hurtBox->SetCollide(true);
	
	m_hitBox = std::make_unique<Sphere>(this, HIT_SIZE);
	m_hitBox->SetPos(this->GetPos());
	m_hitBox->SetTag(Collider::COLLIDER_TAG::HITENEMY);
	m_hitBox->SetCollide(true);
}

//更新
void Enemy::Update()
{
	//現在のStateの更新
	m_state->Update();

	//当たり判定の更新
	m_hitBox->SetPos(m_pos);
	m_hurtBox->SetPos(m_pos);

	//当たり判定のマネージャーに登録
	CollisionManager::GetInstance()->Add("HITENEMY", m_hitBox.get());
	CollisionManager::GetInstance()->Add("HURTENEMY", m_hurtBox.get());

	//HPが0になったら自壊
	if (!m_life)
	{
		ToParaphernalia();
	}

	//向き
	DirectX::SimpleMath::Vector3 axis = { 0.0f, 1.0f, 0.0f };
	m_quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(m_angle));

	//ワールド座標の更新
	m_world = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion);
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}

//描画
void Enemy::Render()
{
	//当たり判定の描画(デバッグ)
	m_state->Render(m_model.get());
}

//終了処理
void Enemy::Finalize()
{

}

//ファイル読み込み
void Enemy::ReadFile()
{

}

//衝突判定
void Enemy::OnCollision(GameObject* gameObject, Collider* designation)
{
	if (designation)
	{
		//武器と当たった際の処理(無敵状態でないとき)
		if (designation->GetTag() == Collider::COLLIDER_TAG::SWORD && !is_invincibility)
		{
			//ノックバック
			KickBack(gameObject->GetPos());
			//被ダメージ状態にする
			ChangeState(m_gethurt.get());
		}
		//エネミー同士で当たった際の処理
		else if (designation->GetTag() == Collider::COLLIDER_TAG::HURTENEMY)
		{
			//重ならないようにする
			OnColliderToFamiry(gameObject);
		}
	}
}

//無敵化
void Enemy::ToInvincible()
{
	is_invincibility = true;
	//当たり判定を取らない状態にする
	m_hurtBox->SetCollide(!is_invincibility);
	//ライフを減らす
	m_life--;
}

//無敵化解除
void Enemy::UnlockInvicinble()
{
	is_invincibility = false;
	//当たり判定を取る状態にする
	m_hurtBox->SetCollide(!is_invincibility);
}

//動く
void Enemy::Move()
{
	//移動
	m_pos += m_vel;
	m_hitBox->SetPos(m_pos);
	m_hurtBox->SetPos(m_pos);
}

//エネミー同士の衝突処理
void Enemy::OnColliderToFamiry(GameObject* famiry)
{
	//同族と当たった場合軽く反発させる

}

//モデルの作成
void Enemy::CreateModel()
{
	//モデルの作成
	m_model = DirectX::Model::CreateFromCMO(
		ResourceManager::GetInstance()->GetDevice(),
		ResourceManager::GetInstance()->GetModelData("Enemy"),
		*ResourceManager::GetInstance()->GetModelPath());
}

//ノックバック
void Enemy::KickBack(const DirectX::SimpleMath::Vector3& objPos)
{
	//自分と相手の距離を求める
	DirectX::SimpleMath::Vector3 distance = DirectX::SimpleMath::Vector3::Zero;
	distance.x = objPos.x - m_pos.x;
	distance.z = objPos.z - m_pos.z;
	distance.Normalize();
	//ノックバック
	m_pos -= distance * BACK;
	ApplyWorld();
}

void Enemy::ApplyDirection()
{
	//回転軸を作成
	DirectX::SimpleMath::Vector3 axis = {0.0f, 1.0f, 0.0f};
	//角度(ラジアン角)
	float angle = DirectX::XMConvertToRadians(m_angle);

	//Quaternionの作成
	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);
}
