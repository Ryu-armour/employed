#include "GameObject.h"


GameObject::GameObject() : isNeed(true),
						   m_pos(DirectX::SimpleMath::Vector3::Zero), 
						   m_world(DirectX::SimpleMath::Matrix::Identity),
						   m_tag(GameObject::GAMEOBJECT_TAG::DEFAULT),
						   isDebug(false)
{
}
