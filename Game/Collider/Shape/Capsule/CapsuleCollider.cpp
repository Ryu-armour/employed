#include "CapsuleCollider.h"

#include "Game\Collider\Manager\CollisionManager.h"
#include "Game\Collider\Shape\Sphere\SphereCollider.h"

#include "Game\GameObject\GameObject.h"


Capsule::Capsule(GameObject* owner, float segmentLength, float radius, bool portraitOrientation) :
	Collider(owner), m_segmentLength(segmentLength), m_radius(radius), is_portraitOrientation(portraitOrientation)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//プリミティブの作成
	m_cylinder = DirectX::GeometricPrimitive::CreateCylinder(resourceManager->GetContext(), m_segmentLength, m_radius * 2);
	m_sphere1 = DirectX::GeometricPrimitive::CreateSphere(resourceManager->GetContext(), m_radius * 2);
	m_sphere2 = DirectX::GeometricPrimitive::CreateSphere(resourceManager->GetContext(), m_radius * 2);

	//変数の初期化
	if (is_portraitOrientation)
	{
		m_biginingOfLine = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y + m_segmentLength, m_pos.z);
		m_endOfLine = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y - m_segmentLength, m_pos.z);
	}
	else
	{
		m_biginingOfLine = DirectX::SimpleMath::Vector3(m_pos.x + m_segmentLength, m_pos.y, m_pos.z);
		m_endOfLine = DirectX::SimpleMath::Vector3(m_pos.x - m_segmentLength, m_pos.y, m_pos.z);
	}
}

void Capsule::Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection, DirectX::FXMVECTOR color, ID3D11ShaderResourceView * texture, bool wireframe, std::function<void __cdecl()> setCustomState) const
{
	DirectX::SimpleMath::Matrix localCylinder, localSphere1, localSphere2;

	// 移動
	if (is_portraitOrientation)
	{
		localCylinder = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength / 2.0f + m_radius, 0.0f));
		localSphere1 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength + m_radius, 0.0f));
		localSphere2 = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_radius, 0.0f));
	}
	else
	{
		localCylinder = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f)) * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength / 2.0f + m_radius, 0.0f));
		localSphere1 =  DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f)) * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_segmentLength + m_radius, 0.0f));
		localSphere2 =  DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f)) * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, m_radius, 0.0f));
	}

	// 描画
	m_cylinder->Draw(localCylinder * world, view, projection, color, texture, wireframe, setCustomState);
	m_sphere1->Draw(localSphere1 * world, view, projection, color, texture, wireframe, setCustomState);
	m_sphere2->Draw(localSphere2 * world, view, projection, color, texture, wireframe, setCustomState);

}

bool Capsule::IsCollided(const Collider* collider) const
{
	//相手に自身の型を渡す
	return collider->IsCollided(this);
}

bool Capsule::IsCollided(const Capsule * collider) const
{
	return CollisionManager::GetInstance()->IsCollided(this, collider);
}

bool Capsule::IsCollided(const Sphere * collider) const
{
	return CollisionManager::GetInstance()->IsCollided(this, collider);
}