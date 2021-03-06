#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class AttackSword final : public IState
{
//定数
	static const int ATTACK_TIME = 60 * 1;

//メンバ変数
private:
	Sword*				m_sword;
	int					m_attackCount;

//メンバ関数
public:
	AttackSword(Sword* sword);
	~AttackSword();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}
};