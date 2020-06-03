#include "EnemyFactory.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\GameObject\Enemy\Enemy.h"
#include "Game\GameObject\Manager\GameObjectManager.h"


//�I�u�W�F�N�g�̐���
void EnemyFactory::Create(GameObject* player,DirectX::SimpleMath::Vector3& pos, int num)
{
	for (int i = 0; i < num; i++)
	{
		//�G�l�~�[�̐���
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player);

		//�w��̈ʒu�ɒu��
		SetFirstPosition(std::move(enemy), pos);
	}
}

void EnemyFactory::Create(GameObject* player, std::vector<std::vector<int>>& data)
{
	//�z��
	std::vector<std::vector<int>> enemyData = data;
	// �ʒu 
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;
	// �ړ��s��
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	for (unsigned int row = 0; row < enemyData.at(0).size(); row++)
	{
		for (unsigned int column = 0; column < enemyData.at(0).size(); column++)
		{
			//�ʒu���v�Z����
			pos = DirectX::SimpleMath::Vector3(float(column - enemyData.at(0).size() / 2.0f), 0.0f, float(row - enemyData.size() / 2.0f));

			//�}�b�v�̑����ɉ����ăG�l�~�[�𐶐�
			if (enemyData[row][column] == 1)
			{
				//�G�l�~�[�̐���
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player);
				SetFirstPosition(std::move(enemy), pos);
			}
		}
	}
}

//�����ʒu�̐ݒ�
void EnemyFactory::SetFirstPosition(std::unique_ptr<Enemy>&& enemy, DirectX::SimpleMath::Vector3& pos)
{
	//������
	enemy->Initialize();

	//�w��̈ʒu�ɒu��
	enemy->SetPos(pos);

	//�I�u�W�F�N�g�}�l�[�W���[�ɃZ�b�g
	GameObjectManager::GetInstance()->Add(std::move(enemy));
}
