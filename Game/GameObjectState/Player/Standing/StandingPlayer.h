#pragma once
#include "Game\GameObjectState\IState.h"


//�N���X�̑O���錾
class Player;


class StandingPlayer final : public IState
{
private:
	Player*			 m_player;

public:
	StandingPlayer(Player* player);
	~StandingPlayer();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}
};