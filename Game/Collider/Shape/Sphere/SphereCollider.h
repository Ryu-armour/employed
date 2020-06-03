#pragma once
#include "Game\Collider\Collider.h"

#include <memory>


class Capsule;


class Sphere final : public Collider
{
	//�����o�ϐ�
private:
	//��
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
	//���a
	float m_radius;

	//�����o�֐�
public:
	//�R���X�g���N�^
	Sphere(GameObject* owner, float radius = 1.0f);
	// �f�X�g���N�^
	~Sphere() = default;
	//�����蔻��
	bool IsCollided(const Collider* collider) const override;
	bool IsCollided(const Capsule* collider) const override;
	bool IsCollided(const Sphere* collider) const override;
	//�`��
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const override;
	//���a�̃Z�b�g
	const void SetRadius(const float& radius);
	//���a��Ԃ�
	const float& GetRadius() const;
};

inline const void Sphere::SetRadius(const float& radius)
{
	m_radius = radius;
}

inline const float& Sphere::GetRadius() const
{
	return m_radius;
}