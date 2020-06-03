#pragma once
#include "Game\GameObjectState\IState.h"

#include <memory.h>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"


class Enemy;


class SearchingEnemy final : public IState
{
//定数
public:
	const float DISTANCE = 4.0f;
	//視界の
	const float ANGLE	 = 30.0f;

//メンバ変数
private:
	//エネミー
	Enemy*					m_enemy;
	//視界
	std::unique_ptr<Sphere>	m_sight;
	//視界の判定の色
	DirectX::SimpleMath::Color	m_color;

//メンバ関数
public:
	//コンストラクタ
	SearchingEnemy(Enemy* enemy);
	//デストラクタ
	~SearchingEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	//プレイヤーが視界内に入ってきたか
	bool CommingIntoSight();
};

inline std::wstring& SearchingEnemy::GetStateName()
{
	return m_stateName;
}