#pragma once
#include "Game\Collider\Collider.h"

#include <memory>


class Capsule;


class Sphere final : public Collider
{
	//メンバ変数
private:
	//球
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
	//半径
	float m_radius;

	//メンバ関数
public:
	//コンストラクタ
	Sphere(GameObject* owner, float radius = 1.0f);
	// デストラクタ
	~Sphere() = default;
	//当たり判定
	bool IsCollided(const Collider* collider) const override;
	bool IsCollided(const Capsule* collider) const override;
	bool IsCollided(const Sphere* collider) const override;
	//描画
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const override;
	//半径のセット
	const void SetRadius(const float& radius);
	//半径を返す
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