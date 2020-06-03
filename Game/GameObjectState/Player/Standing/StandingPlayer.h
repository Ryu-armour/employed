#pragma once
#include "Game\GameObjectState\IState.h"


//ƒNƒ‰ƒX‚Ì‘O•ûéŒ¾
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