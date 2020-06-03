#pragma once
#include "Game\GameObjectState\IState.h"


class Sword;


class AttackSword final : public IState
{
//�萔
	static const int ATTACK_TIME = 60 * 1;

//�����o�ϐ�
private:
	Sword*				m_sword;
	int					m_attackCount;

//�����o�֐�
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