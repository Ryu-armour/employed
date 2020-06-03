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
	//Velocity��������
	void AssignVelocity();
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}

private:
	//�v���C���[�̈ړ�
	void MovePlayer();
};