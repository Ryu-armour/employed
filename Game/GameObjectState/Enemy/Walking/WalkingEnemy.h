#pragma once
#include "Game\GameObjectState\IState.h"


class Enemy;


class WalkingEnemy final : public IState
{
//�萔
public:
	//�ړ���
	const float MOVEMENT = 0.06f;
//�����o�ϐ�
private:
	//�G�l�~�[
	Enemy*							m_enemy;
	//�^�[�Q�b�g
	DirectX::SimpleMath::Vector3*	m_targetPos;

//�����o�֐�
public:
	WalkingEnemy(Enemy* enemy);
	~WalkingEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	void LookAtThePlayer();
};

inline std::wstring& WalkingEnemy::GetStateName()
{
	return m_stateName;
}