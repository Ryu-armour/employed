#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class AttackSword final : public IState
{
//’è”
	static const int ATTACK_TIME = 60 * 1;

//ƒƒ“ƒo•Ï”
private:
	Sword*				m_sword;
	int					m_attackCount;

//ƒƒ“ƒoŠÖ”
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