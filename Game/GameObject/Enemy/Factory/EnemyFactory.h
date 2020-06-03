#pragma once
#include "Game\Common\Singleton.h"

#include <array>
#include <vector>


class GameObject;
class Enemy;


class EnemyFactory final : public Singleton<EnemyFactory>
{
//メンバ関数
public:
	//オブジェクトの生成
	void Create(GameObject* player, std::vector<std::vector<int>>& data);
	void Create(GameObject* player, DirectX::SimpleMath::Vector3& pos, int num = 1);
private:
	//初期位置の設定
	void SetFirstPosition(std::unique_ptr<Enemy>&& enemy, DirectX::SimpleMath::Vector3& pos);

//シングルトン
public:
	friend class Singleton<EnemyFactory>;
protected:
	EnemyFactory() {};
	virtual ~EnemyFactory() {};
};