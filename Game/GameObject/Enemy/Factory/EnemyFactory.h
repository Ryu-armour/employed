#pragma once
#include "Game\Common\Singleton.h"

#include <array>
#include <vector>


class GameObject;
class Enemy;


class EnemyFactory final : public Singleton<EnemyFactory>
{
//�����o�֐�
public:
	//�I�u�W�F�N�g�̐���
	void Create(GameObject* player, std::vector<std::vector<int>>& data);
	void Create(GameObject* player, DirectX::SimpleMath::Vector3& pos, int num = 1);
private:
	//�����ʒu�̐ݒ�
	void SetFirstPosition(std::unique_ptr<Enemy>&& enemy, DirectX::SimpleMath::Vector3& pos);

//�V���O���g��
public:
	friend class Singleton<EnemyFactory>;
protected:
	EnemyFactory() {};
	virtual ~EnemyFactory() {};
};