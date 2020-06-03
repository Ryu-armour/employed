#include "SphereCollider.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\Collider\Shape\Capsule\CapsuleCollider.h"
#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\GameObject\GameObject.h"



Sphere::Sphere(GameObject* owner, float radius) : Collider(owner), m_radius(radius)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_sphere = DirectX::GeometricPrimitive::CreateSphere(resourceManager->GetContext(), m_radius * 2);
}


bool Sphere::IsCollided(const Collider * collider) const
{
	return collider->IsCollided(this);
}

bool Sphere::IsCollided(const Capsule * collider) const
{
	return CollisionManager::GetInstance()->IsCollided(this, collider);
}

bool Sphere::IsCollided(const Sphere * collider) const
{
	return CollisionManager::GetInstance()->IsCollided(this, collider);
}

void Sphere::Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color, ID3D11ShaderResourceView * texture, bool wireframe, std::function<void __cdecl()> setCustomState) const
{
	m_sphere->Draw(world, view, projection, color, texture, wireframe, setCustomState);
}