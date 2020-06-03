#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class WaitSword final : public IState
{
//ƒƒ“ƒo•Ï”
private:
	Sword*				m_sword;

//ƒƒ“ƒoŠÖ”
public:
	WaitSword(Sword* sword);
	~WaitSword();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}
};