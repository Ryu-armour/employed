#pragma once
#include "Game\Collider\Collider.h"

#include <memory>

#include "Game\Common\ResourcesManager.h"


class Sphere;


class Capsule final : public Collider
{
	//メンバ変数
private:
	//筒部分
	std::unique_ptr<DirectX::GeometricPrimitive>	m_cylinder;
	//球の上
	std::unique_ptr<DirectX::GeometricPrimitive>	m_sphere1;
	//球の下
	std::unique_ptr<DirectX::GeometricPrimitive>	m_sphere2;
	//中間の線分の開始点
	DirectX::SimpleMath::Vector3 m_biginingOfLine;
	//中間の線分の終了点
	DirectX::SimpleMath::Vector3 m_endOfLine;
	//半径
	float m_radius;
	//筒の長さ
	float m_segmentLength;
	//角度
	float m_angle;
	//向き(true:縦, false:横)
	bool is_portraitOrientation;

	//メンバ関数
public:
	//コンストラクタ
	Capsule(GameObject* owner, float segmentLength = 1.0f, float radius = 1.0f, bool portraitOrientation = true);
	//デストラクタ
	~Capsule() = default;
	//描画
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const override;
	//型判別
	bool IsCollided(const Collider* collider) const override;
	bool IsCollided(const Capsule* collider) const override;
	bool IsCollided(const Sphere* collider) const override;

	//線分の開始点のセット
	void SetBiginingOfLine(const DirectX::SimpleMath::Vector3& pos);
	//線分の開始点を返す
	const DirectX::SimpleMath::Vector3& GetBiginingOfLine() const;
	//線分の開始点のセット
	void SetEndOfLine(const DirectX::SimpleMath::Vector3& pos);
	//線分の終点を返す
	const DirectX::SimpleMath::Vector3& GetEndOfLine() const;
	//半径をセット
	void SetRadius(const float& radius);
	//半径を返す
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