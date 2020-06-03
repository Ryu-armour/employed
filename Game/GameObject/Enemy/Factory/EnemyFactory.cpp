#include "EnemyFactory.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\GameObject\Enemy\Enemy.h"
#include "Game\GameObject\Manager\GameObjectManager.h"


//オブジェクトの生成
void EnemyFactory::Create(GameObject* player,DirectX::SimpleMath::Vector3& pos, int num)
{
	for (int i = 0; i < num; i++)
	{
		//エネミーの生成
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player);

		//指定の位置に置く
		SetFirstPosition(std::move(enemy), pos);
	}
}

void EnemyFactory::Create(GameObject* player, std::vector<std::vector<int>>& data)
{
	//配列
	std::vector<std::vector<int>> enemyData = data;
	// 位置 
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;
	// 移動行列
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	for (unsigned int row = 0; row < enemyData.at(0).size(); row++)
	{
		for (unsigned int column = 0; column < enemyData.at(0).size(); column++)
		{
			//位置を計算する
			pos = DirectX::SimpleMath::Vector3(float(column - enemyData.at(0).size() / 2.0f), 0.0f, float(row - enemyData.size() / 2.0f));

			//マップの属性に応じてエネミーを生成
			if (enemyData[row][column] == 1)
			{
				//エネミーの生成
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player);
				SetFirstPosition(std::move(enemy), pos);
			}
		}
	}
}

//初期位置の設定
void EnemyFactory::SetFirstPosition(std::unique_ptr<Enemy>&& enemy, DirectX::SimpleMath::Vector3& pos)
{
	//初期化
	enemy->Initialize();

	//指定の位置に置く
	enemy->SetPos(pos);

	//オブジェクトマネージャーにセット
	GameObjectManager::GetInstance()->Add(std::move(enemy));
}
