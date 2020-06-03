#pragma once
#include "Game\GameObject\GameObject.h"


class Weapon : public GameObject
{
protected:
//メンバ変数
	//大きさ
	float m_size;
	//攻撃状態
	bool isAttack;
	//プリミティブの描画フラグ
	bool is_drawPrimitive;

//メンバ関数
public:
	//コンストラクタ
	Weapon() : m_size(0), isAttack(false)
	{
		m_tag = GameObject::WEAPON;
	};
	//デストラクタ
	virtual ~Weapon() {};
	//初期化
	void Initialize() override = 0;
	//更新
	void Update() override = 0;
	//描画
	void Render() override = 0;
	//終了処理
	void Finalize() override = 0;
	//Jsonファイルを開く
	void ReadFile() override = 0;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override = 0;
	//攻撃
	virtual void Attack() = 0;
	//サイズの設定
	void SetSize(float size);
	//攻撃状態の取得
	bool IsAttack();
	//攻撃状態にする
	void ToAttackState();
	//待機状態にする
	void ToStayState();
};

inline void Weapon::SetSize(float size)
{
	m_size = size;
}

inline bool Weapon::IsAttack()
{
	return isAttack;
}

inline void Weapon::ToAttackState()
{
	isAttack = true;
}

inline void Weapon::ToStayState()
{
	isAttack = false;
}