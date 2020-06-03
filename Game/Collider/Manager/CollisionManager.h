#pragma once
#include "Game\Common\Singleton.h"

#include<vector>
#include <unordered_map>


//�O���錾
class Collider;
class Capsule;
class Sphere;
class GameObject;


class CollisionManager final : public Singleton<CollisionManager>
{ 
//���O���
	//Collider�̊Ǘ�
	using ColliderList	     = std::vector<Collider*>;
	using ColliderGroupList  = std::unordered_map<std::string, ColliderList>;
	//Collider�̎�ނ̊Ǘ�
	using CollisionGroup	 = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;
	
//�����o�ϐ�
private:
	ColliderGroupList  m_colliders;
	CollisionGroupList m_collisions;

//�����o�֐�
public:
	//�����蔻��̎�ނ̒ǉ�
	void Add(const std::string& name,Collider* collider);
	//�����蔻��̃O���[�v���쐬
	void AllowCollision(const std::string& name1, const std::string& name2);
	//�Փˏ���
	void DetectCollision();
	void DetectCollision(const ColliderList& collider);
	void DetectCollision(const ColliderList& col1, const ColliderList& col2);
	//�Փ˔���
	static bool IsCollided(const Capsule* col1, const Capsule* col2);
	static bool IsCollided(const Capsule* col1, const Sphere* col2);
	static bool IsCollided(const Sphere* col1, const Capsule* col2);
	static bool IsCollided(const Sphere* col1, const Sphere* col2);
private:
	//�Ԃ�l�A�_c�Ɛ����̊Ԃ̋���ab�̕���
	static float SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b,
		const DirectX::SimpleMath::Vector3& c);
	static float ClosestPtSegmentSegment(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& q1,
		const DirectX::SimpleMath::Vector3& p2, const DirectX::SimpleMath::Vector3& q2, float& s, float& t,
		DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);
	//�N�����v
	static float Clamp(float n, float min, float max);

//�V���O���g��
	friend class Singleton<CollisionManager>;
protected:
	CollisionManager();
	~CollisionManager();
};