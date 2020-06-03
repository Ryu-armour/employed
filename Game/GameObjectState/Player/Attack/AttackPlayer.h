#pragma once
#include"Game\GameObjectState\IState.h"


class Player;


class AttackPlayer final : public IState
{
//’è”
	const int ATTACK_TIME = 30;
	DirectX::SimpleMath::Vector3 m_armPos;

//ƒƒ“ƒo•Ï”
private:
	Player*				m_player;
	int					m_attackCount;
	bool				m_direction;

//ƒƒ“ƒoŠÖ”
public:
	AttackPlayer(Player* player);
	~AttackPlayer();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}

//“à•”ŠÖ”
private:
	//UŒ‚
	void Swing();
};