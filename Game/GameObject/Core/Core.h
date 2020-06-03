#pragma once
#include "Game\GameObject\GameObject.h"

#include <array>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"


class Core final : public GameObject
{
//定数
public:
	//当たり判定の拡大率
	const float SCALE = 0.1f;
	//当たり判定の半径
	const float RADIUS = 5.0f;
	//無敵時間
	const int INVINCIBLE_TIME = 1 * 60;
	//ギアの数
	static const int NUM_GEAR = 7;

//列挙
public:
	enum MODEL_DATA
	{
		CORE,
		GEAR1,
		GEAR2,
		GEAR3,
		GEAR4,
		GEAR5,
		GEAR6
	};

//メンバ変数
private:
	//ギアモデル
	std::array<std::unique_ptr<DirectX::Model>, Core::NUM_GEAR> m_gears;
	std::unique_ptr<DirectX::Model>	 m_gear;
	//ライフ
	int								 m_life;
	//無敵時間
	unsigned int					 m_invincibleTime;
	//無敵状態かどうか
	bool							 is_invincibility;
	//当たり判定
	std::array<std::unique_ptr<Sphere>,8>			 m_collider;
	//当たり判定の色
	DirectX::SimpleMath::Vector4	 m_color;
	//生存フラグ
	bool							 isAlive;
	//プリミティブの描画フラグ
	bool							 is_drawPrimitive;

//メンバ関数
public:
	Core();
	~Core();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//ファイルの読み込み
	void ReadFile() override;
	//モデルの作成
	void CreateModel();
	//プレイヤーとの衝突判定
	bool OnCollisionToPlayer();
	//自壊
	void Brake();
};