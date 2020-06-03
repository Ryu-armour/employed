#pragma once
#include "Game\Collider\Collider.h"

#include <memory>

#include "Game\Common\ResourcesManager.h"


class Sphere;


class Capsule final : public Collider
{
	//�����o�ϐ�
private:
	//������
	std::unique_ptr<DirectX::GeometricPrimitive>	m_cylinder;
	//���̏�
	std::unique_ptr<DirectX::GeometricPrimitive>	m_sphere1;
	//���̉�
	std::unique_ptr<DirectX::GeometricPrimitive>	m_sphere2;
	//���Ԃ̐����̊J�n�_
	DirectX::SimpleMath::Vector3 m_biginingOfLine;
	//���Ԃ̐����̏I���_
	DirectX::SimpleMath::Vector3 m_endOfLine;
	//���a
	float m_radius;
	//���̒���
	float m_segmentLength;
	//�p�x
	float m_angle;
	//����(true:�c, false:��)
	bool is_portraitOrientation;

	//�����o�֐�
public:
	//�R���X�g���N�^
	Capsule(GameObject* owner, float segmentLength = 1.0f, float radius = 1.0f, bool portraitOrientation = true);
	//�f�X�g���N�^
	~Capsule() = default;
	//�`��
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const override;
	//�^����
	bool IsCollided(const Collider* collider) const override;
	bool IsCollided(const Capsule* collider) const override;
	bool IsCollided(const Sphere* collider) const override;

	//�����̊J�n�_�̃Z�b�g
	void SetBiginingOfLine(const DirectX::SimpleMath::Vector3& pos);
	//�����̊J�n�_��Ԃ�
	const DirectX::SimpleMath::Vector3& GetBiginingOfLine() const;
	//�����̊J�n�_�̃Z�b�g
	void SetEndOfLine(const DirectX::SimpleMath::Vector3& pos);
	//�����̏I�_��Ԃ�
	const DirectX::SimpleMath::Vector3& GetEndOfLine() const;
	//���a���Z�b�g
	void SetRadius(const float& radius);
	//���a��Ԃ�
	const float& GetRadius() const;
	void SetPos(const DirectX::SimpleMath::Vector3& pos);
	void SetAngle(const float& angle);
	const float& GetAngle() const;
};

inline void Capsule:: SetBiginingOfLine(const DirectX::SimpleMath::Vector3& pos)
{
	m_biginingOfLine = pos;
}

inline const DirectX::SimpleMath::Vector3& Capsule::GetBiginingOfLine() const
{
	return m_biginingOfLine;
}

inline void Capsule::SetEndOfLine(const DirectX::SimpleMath::Vector3& pos)
{
	m_endOfLine = pos;
}

inline const DirectX::SimpleMath::Vector3& Capsule:: GetEndOfLine() const
{
	return m_endOfLine;
}

inline void Capsule::SetRadius(const float& radius)
{
	m_radius = radius;
}

inline const float& Capsule:: GetRadius() const
{
	return m_radius;
}

inline void Capsule::SetPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;
	m_biginingOfLine = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y + m_segmentLength, m_pos.z);
	m_endOfLine = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y - m_segmentLength, m_pos.z);
}

inline void Capsule::SetAngle(const float& angle)
{
	m_angle = angle;
}

inline const float& Capsule::GetAngle() const
{
	return m_angle;
}