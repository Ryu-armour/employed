#pragma once
#include "Game\GameObjectState\IState.h"


class Enemy;

class GetHurtEnemy final : public IState
{
public:
//定数
	const float WINCE_TIME = 60.0f * 0.5f;

//メンバ変数
private:
	//エネミー
	Enemy*	m_enemy;
	//経過時間
	int		m_count;

//メンバ関数
public:
	GetHurtEnemy(Enemy* enemy);
	~GetHurtEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	void LookToThePlayer();

};

inline std::wstring& GetHurtEnemy::GetStateName()
{
	return m_stateName;
}