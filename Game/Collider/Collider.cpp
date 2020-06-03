#include "Collider.h"

#include "Game\GameObject\GameObject.h"


Collider::Collider(GameObject* owner) : m_owner(owner), m_pos(0.0f, 0.0f, 0.0f), is_collide(false)
{
	m_tag = COLLIDER_TAG::DEFAULT;
}

bool Collider::IsCollided(const Capsule * capsule) const
{
	capsule;
	return false;
}

bool Collider::IsCollided(const Sphere * sphere) const
{
	sphere;
	return false;
}

void Collider::OnCollision(Collider * collider)
{
	m_owner->OnCollision(collider->GetOwner(),collider);
}
