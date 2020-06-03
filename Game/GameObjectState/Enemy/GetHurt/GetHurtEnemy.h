#pragma once
#include "Game\GameObjectState\IState.h"


class Enemy;

class GetHurtEnemy final : public IState
{
public:
//�萔
	const float WINCE_TIME = 60.0f * 0.5f;

//�����o�ϐ�
private:
	//�G�l�~�[
	Enemy*	m_enemy;
	//�o�ߎ���
	int		m_count;

//�����o�֐�
public:
	GetHurtEnemy(Enemy* enemy);
	~GetHurtEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	void LookToThePlayer();

};

inline std::wstring& GetHurtEnemy::GetStateName()
{
	return m_stateName;
}