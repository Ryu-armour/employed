#pragma once
#include "Game\GameObjectState\IState.h"

#include <memory.h>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"


class Enemy;


class SearchingEnemy final : public IState
{
//�萔
public:
	const float DISTANCE = 4.0f;
	//���E��
	const float ANGLE	 = 30.0f;

//�����o�ϐ�
private:
	//�G�l�~�[
	Enemy*					m_enemy;
	//���E
	std::unique_ptr<Sphere>	m_sight;
	//���E�̔���̐F
	DirectX::SimpleMath::Color	m_color;

//�����o�֐�
public:
	//�R���X�g���N�^
	SearchingEnemy(Enemy* enemy);
	//�f�X�g���N�^
	~SearchingEnemy();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override;

private:
	//�v���C���[�����E���ɓ����Ă�����
	bool CommingIntoSight();
};

inline std::wstring& SearchingEnemy::GetStateName()
{
	return m_stateName;
}