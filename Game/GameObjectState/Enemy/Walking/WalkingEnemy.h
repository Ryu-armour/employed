#pragma once
#include "Game\GameObjectState\IState.h"


class Enemy;


class WalkingEnemy final : public IState
{
//定数
public:
	//移動量
	const float MOVEMENT = 0.06f;
//メンバ変数
private:
	//エネミー
	Enemy*							m_enemy;
	//ターゲット
	DirectX::SimpleMath::Vector3*	m_targetPos;

//メンバ関数
public:
	WalkingEnemy(Enemy* enemy);
	~WalkingEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	void LookAtThePlayer();
};

inline std::wstring& WalkingEnemy::GetStateName()
{
	return m_stateName;
}