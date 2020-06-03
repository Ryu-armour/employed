#include "CollisionManager.h"

#include <typeinfo>

#include "Game\Collider\Collider.h"
#include "Game\Collider\Shape\ShapeList.h"

#include "Game\GameObject\GameObject.h"


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}


void CollisionManager::Add(const std::string& name, Collider* object)
{
	//リストに追加
	m_colliders[name].push_back(object);
}

void CollisionManager::AllowCollision(const std::string& name1, const std::string& name2)
{
	//引数の情報を入れる
	if (name1 == name2)
	{
		m_collisions.push_back(std::make_pair(name1, ""));
	}
	else
	{
		m_collisions.push_back(std::make_pair(name1, name2));
	}
}

void CollisionManager::DetectCollision()
{
	for (const CollisionGroup& collisionGroup : m_collisions)
	{
		//当たり判定が1種類のみ
		if (collisionGroup.second.empty())
		{
			//当たり判定の格納
			ColliderList& colliders = m_colliders[collisionGroup.first];
			
			//当たり判定
			DetectCollision(colliders);
		}
		else
		{
			//当たり判定の種類の格納
			ColliderList& col1 = m_colliders[collisionGroup.first];
			ColliderList& col2 = m_colliders[collisionGroup.second];

			//当たり判定
			DetectCollision(col1, col2);
		}
	}

	//判定を取るオブジェクトのリセット
	m_colliders.clear();
}

void CollisionManager::DetectCollision(const ColliderList& colliders)
{
	//オブジェクトの総数
	int numObjects = colliders.size();
	
	//1種類の当たり判定
	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (colliders[i]->GetCollide() || colliders[j]->GetCollide())
			{
				if (colliders[i]->IsCollided(colliders[j]))
				{
					if (colliders[j]->GetCollide())
					{
						colliders[i]->OnCollision(colliders[j]);
					}
					if (colliders[i]->GetCollide())
					{
						colliders[j]->OnCollision(colliders[i]);
					}
				}
			}
		}
	}
}

void CollisionManager::DetectCollision(const ColliderList& col1, const ColliderList& col2)
{
	//2種類の当たり判定
	for (Collider* collider1 : col1)
	{
		for (Collider* collider2 : col2)
		{
			if (collider1->IsCollided(collider2))
			{
				if (collider2->GetCollide())
				{
					collider1->OnCollision(collider2);
				}
				if (collider1->GetCollide())
				{
					collider2->OnCollision(collider1);
				}
			}
		}
	}
}

bool CollisionManager::IsCollided(const Capsule * cap1, const Capsule * cap2)
{
	//変数の準備
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	
	float dist2 = ClosestPtSegmentSegment(cap1->GetBiginingOfLine(),cap1->GetEndOfLine(),
		cap2->GetBiginingOfLine(),cap2->GetEndOfLine(),s,t,c1,c2);
	float radius = cap1->GetRadius() + cap2->GetRadius();
	return dist2 <= radius * radius;
}

bool CollisionManager::IsCollided(const Capsule * col1, const Sphere * col2)
{
	//球の中心とカプセルの中心の線分との距離の平方を計算
	float dist2 = SqDistPointSegment(col1->GetBiginingOfLine(), col1->GetEndOfLine(), col2->GetPos());
	float radius = col1->GetRadius() + col2->GetRadius();
	return dist2 <= radius * radius;
}

bool CollisionManager::IsCollided(const Sphere * col1, const Capsule * col2)
{
	//球の中心とカプセルの中心の線分との距離の平方を計算
	float dist2 = SqDistPointSegment(col2->GetBiginingOfLine(), col2->GetEndOfLine(), col1->GetPos());
	float radius = col2->GetRadius() + col1->GetRadius();
	return dist2 <= radius * radius;
}

bool CollisionManager::IsCollided(const Sphere * col1, const Sphere * col2)
{
	//球と球の当たり判定
	float dist = DirectX::SimpleMath::Vector3(col2->GetPos() - col1->GetPos()).Length();
	float radius = col1->GetRadius() + col2->GetRadius();
	return dist * dist <= radius * radius;
}

float CollisionManager::SqDistPointSegment(const DirectX::SimpleMath::Vector3 & a,
	const DirectX::SimpleMath::Vector3 & b, const DirectX::SimpleMath::Vector3 & c)
{
	DirectX::SimpleMath::Vector3 ab = b - a;
	DirectX::SimpleMath::Vector3 ac = c - a;
	DirectX::SimpleMath::Vector3 bc = c - b;
	float e = ac.Dot(ab);
	if (e <= 0.0f)
		return ac.Dot(ac); 
	float f = ab.Dot(ab);
	if (e >= f) 
		return bc.Dot(bc);
	return ac.Dot(ac) - e * e / f;
}

float CollisionManager::ClosestPtSegmentSegment(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& q1,
	const DirectX::SimpleMath::Vector3& p2, const DirectX::SimpleMath::Vector3& q2, float& s, float& t,
	DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
{
	//カプセルの中心の線分間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d1 = q1 - p1; DirectX::SimpleMath::Vector3 d2 = q2 - p2;
	DirectX::SimpleMath::Vector3 r = p1 - p2; float a = d1.Dot(d1);
	float e = d2.Dot(d2); float f = d2.Dot(r);

	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return (c1 - c2).Dot(c1 - c2);
	}
	if (a <= FLT_EPSILON)
	{
		s = 0.0f;
		t = f / e;
		t = Clamp(t, 0.0f, 1.0f);
	}
	else
	{
		float c = d1.Dot(r);
		if (e <= FLT_EPSILON)
		{
			t = 0.0f;
			s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			float b = d1.Dot(d2);
			float denom = a * e - b * b;
			if (denom != 0.0f)
			{
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				s = 0.0f;
			}
			float tnom = (b * s + f);
			if (tnom < 0.0f)
			{
				t = 0.0f; s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (tnom > e)
			{
				t = 1.0f; s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
			else
			{
				t = tnom / e;
			}
		}
	}
	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;
	return (c1 - c2).Dot(c1 - c2);
}

float CollisionManager::Clamp(float n, float min, float max)
{
	if (n < min)
		return min;
	else if (max < n)
		return max;

	return n;
}