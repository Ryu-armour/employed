#pragma once
#include"Game\GameObjectState\IState.h"


class Player;


class AttackPlayer final : public IState
{
//定数
	const int ATTACK_TIME = 30;
	DirectX::SimpleMath::Vector3 m_armPos;

//メンバ変数
private:
	Player*				m_player;
	int					m_attackCount;
	bool				m_direction;

//メンバ関数
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

//内部関数
private:
	//攻撃
	void Swing();
};