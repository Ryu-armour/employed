#pragma once
#include "Game\Common\Singleton.h"

#include<vector>
#include <unordered_map>


//前方宣言
class Collider;
class Capsule;
class Sphere;
class GameObject;


class CollisionManager final : public Singleton<CollisionManager>
{ 
//名前空間
	//Colliderの管理
	using ColliderList	     = std::vector<Collider*>;
	using ColliderGroupList  = std::unordered_map<std::string, ColliderList>;
	//Colliderの種類の管理
	using CollisionGroup	 = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;
	
//メンバ変数
private:
	ColliderGroupList  m_colliders;
	CollisionGroupList m_collisions;

//メンバ関数
public:
	//当たり判定の種類の追加
	void Add(const std::string& name,Collider* collider);
	//当たり判定のグループを作成
	void AllowCollision(const std::string& name1, const std::string& name2);
	//衝突処理
	void DetectCollision();
	void DetectCollision(const ColliderList& collider);
	void DetectCollision(const ColliderList& col1, const ColliderList& col2);
	//衝突判定
	static bool IsCollided(const Capsule* col1, const Capsule* col2);
	static bool IsCollided(const Capsule* col1, const Sphere* col2);
	static bool IsCollided(const Sphere* col1, const Capsule* col2);
	static bool IsCollided(const Sphere* col1, const Sphere* col2);
private:
	//返り値、点cと線分の間の距離abの平方
	static float SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b,
		const DirectX::SimpleMath::Vector3& c);
	static float ClosestPtSegmentSegment(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& q1,
		const DirectX::SimpleMath::Vector3& p2, const DirectX::SimpleMath::Vector3& q2, float& s, float& t,
		DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);
	//クランプ
	static float Clamp(float n, float min, float max);

//シングルトン
	friend class Singleton<CollisionManager>;
protected:
	CollisionManager();
	~CollisionManager();
};