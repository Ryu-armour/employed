#pragma once
#include "Game\GameObject\GameObject.h"

#include "Game\Collider\Shape\Sphere\SphereCollider.h"

#include "Game\GameObjectState\Enemy\EnemyStateList.h"


class IState;


class Enemy : public GameObject
{
//定数
public:
	//攻撃判定の半径
	const float HIT_SIZE = 1.5f;
	//くらい判定の半径
	const float HURT_SIZE = 2.0f;
	//ノックバックの大きさ
	const float BACK = 2.0f;
	//視界の長さ
	const float SIGHT = 20.0f;

//メンバ変数
private:
	//モデル
	std::unique_ptr<DirectX::Model>  m_model;
	//くらい判定
	std::unique_ptr<Sphere>			 m_hurtBox;
	//攻撃判定
	std::unique_ptr<Sphere>			 m_hitBox;
	//HP
	int								 m_life;
	//向き
	float							 m_angle;
	//クォータニオン
	DirectX::SimpleMath::Quaternion  m_quaternion;
	//無敵状態かどうか
	bool							 is_invincibility;
	//移動ベクトル
	DirectX::SimpleMath::Vector3	 m_vel;
	//次の移動先
	DirectX::SimpleMath::Vector3	 m_destination;
	//現在の状態
	IState*							 m_state;
	//歩き状態
	std::unique_ptr<WalkingEnemy>	 m_walk;
	//目的地を探す状態
	std::unique_ptr<SearchingEnemy>  m_search;
	//ダメージを受けた状態
	std::unique_ptr<GetHurtEnemy>	 m_gethurt;
	//プレイヤー
	GameObject*						 m_player;

//メンバ関数
public:
	//コンストラクタ
	Enemy(GameObject* player = nullptr);
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//ファイル読み込み
	void ReadFile() override;
	//無敵化
	void ToInvincible();
	//無敵化解除
	void UnlockInvicinble();
	//動く
	void Move();
	//向きをセット
	void SetAngle(const float& angle);
	//向きを取得
	float GetAngle();
	//ベクトルをセット
	void SetVel(const DirectX::SimpleMath::Vector3& vel);
	//ベクトルを取得
	DirectX::SimpleMath::Vector3 GetVel();
	//次の移動先をセット
	void SetDestination(const DirectX::SimpleMath::Vector3& destination);
	//移動先を返す
	DirectX::SimpleMath::Vector3 GetDestination();
	//ステートの切り替え
	void ChangeState(IState* state);
	//SearchingStateを取得
	IState* GetSearchState();
	//WalkingStateを取得
	IState* GetWalkState();
	//プレイヤーの取得
	GameObject* GetPlayer();

//メンバ関数
private:
	//同族との衝突判定
	void OnColliderToFamiry(GameObject* famiry);
	//モデルの作成
	void CreateModel();
	//ノックバック
	void KickBack(const DirectX::SimpleMath::Vector3& objPos);
	//向いてる向きに回転
	void ApplyDirection();
};

inline void Enemy::SetAngle(const float& angle)
{
	m_angle = angle;
}

inline float Enemy::GetAngle()
{
	return m_angle;
}

inline void Enemy::SetVel(const DirectX::SimpleMath::Vector3& vel)
{
	m_vel = vel;
}

inline DirectX::SimpleMath::Vector3 Enemy::GetVel()
{
	return m_vel;
}

inline void Enemy::SetDestination(const DirectX::SimpleMath::Vector3& destination)
{
	m_destination = destination;
}

inline DirectX::SimpleMath::Vector3 Enemy::GetDestination()
{
	return m_destination;
}

inline void Enemy::ChangeState(IState* state)
{
	m_state = state;
	m_state->Initialize();
}

inline IState* Enemy::GetSearchState()
{
	return m_search.get();
}

inline IState* Enemy::GetWalkState()
{
	return m_walk.get();
}

inline GameObject* Enemy::GetPlayer()
{
	return m_player;
}