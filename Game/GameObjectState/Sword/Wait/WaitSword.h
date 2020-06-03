#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class WaitSword final : public IState
{
//�����o�ϐ�
private:
	Sword*				m_sword;

//�����o�֐�
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