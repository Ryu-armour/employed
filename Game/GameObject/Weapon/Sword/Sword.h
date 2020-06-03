#pragma once
#include "Game\GameObject\Weapon\Weapon.h"

#include "Game\Collider\Shape\Capsule\CapsuleCollider.h"


class Player;
class IState;


class Sword final : public Weapon
{
//列挙
public:
	//剣の状態
	enum SWORD_STATE
	{
		WAIT = 0,
		ATTACK,

		NUM
	};

//定数
	static const DirectX::SimpleMath::Vector3  COLLIDER_ADJUSTMENT;

//メンバ変数
private:
	//ユーザー
	Player* m_user;
	//ユーザーとの距離感
	DirectX::SimpleMath::Vector3	m_adjustment;
	//ユーザーの初期位置
	DirectX::SimpleMath::Vector3	m_userPos;
	//当たり判定
	std::unique_ptr<Capsule>		m_collider;
	//当たり判定の色
	DirectX::SimpleMath::Vector4	m_color;
	//現在の状態
	IState*							m_state;
	//モデル
	std::unique_ptr<DirectX::Model> m_model;

//メンバ関数
public:
	//コンストラクタ
	Sword(Player* user);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	//Jsonファイルを開く
	void ReadFile() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//状態の切り替え
	void ChangeState(IState* state);
	//攻撃
	void Attack() override;
	//攻撃状態へ
	void ToAttack();
	//待機状態へ
	void ToStay();
	//モデルの作成
	void CreateModel();
	//剣の取得
	void SetColor(const DirectX::XMVECTORF32& color);
	//コライダーの取得
	Collider* GetCollider();
};

inline void Sword::SetColor(const DirectX::XMVECTORF32& color)
{
	m_color = color;
}

inline Collider* Sword::GetCollider()
{
	return m_collider.get();
}