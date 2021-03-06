#pragma once
#include "Game\GameObjectState\IState.h"


class Player;


class WalkingPlayer final : public IState
{
private:
	Player*			 m_player;

public:
	WalkingPlayer(Player* player);
	~WalkingPlayer();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	//Velocityを代入する
	void AssignVelocity();
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}

private:
	//プレイヤーの移動
	void MovePlayer();
};