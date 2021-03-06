#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class WaitSword final : public IState
{
//メンバ変数
private:
	Sword*				m_sword;

//メンバ関数
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