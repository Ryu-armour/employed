#pragma once


class Capsule;
class Sphere;
class GameObject;


class Collider
{
//構造体
public:
	//コライダーのタグ
	enum COLLIDER_TAG
	{
		DEFAULT,
		PLAYER,
		HITENEMY,
		HURTENEMY,
		SWORD,
		CORE,
		NUM
	};

//メンバ変数
protected:
	//当たり判定の位置
	DirectX::SimpleMath::Vector3 m_pos;
	//オブジェクト
	GameObject*					 m_owner;
	//当たり判定の状態(0 : 当たり判定を取らない)
	bool						 is_collide;
	//タグ
	COLLIDER_TAG				 m_tag;

//メンバ関数
public:
	Collider(GameObject* owner);
	virtual ~Collider() {};
	//描画
	virtual void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const = 0;
	//型判別用
	virtual bool IsCollided(const Collider* collider) const = 0;
	virtual bool IsCollided(const Capsule* capsule) const;
	virtual bool IsCollided(const Sphere* sphere) const;
	//自身の型を渡して判定する
	void OnCollision(Collider* collider);

	const DirectX::SimpleMath::Vector3& GetPos() const;
	const void SetPos(DirectX::SimpleMath::Vector3& pos);
	GameObject* GetOwner() const;
	//当たり判定の状態をセット
	void SetCollide(bool collide);
	//当たり判定の状態の取得
	bool GetCollide();
	//タグをセット
	void SetTag(COLLIDER_TAG tag);
	//タグを取得
	COLLIDER_TAG GetTag();
};

inline const DirectX::SimpleMath::Vector3& Collider::GetPos() const
{
	return m_pos;
}

inline const void Collider::SetPos(DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;
}

inline GameObject* Collider::GetOwner() const
{
	return m_owner;
}

inline void Collider::SetCollide(bool collide)
{
	is_collide = collide;
}

inline bool Collider::GetCollide()
{
	return is_collide;
}

inline void Collider::SetTag(COLLIDER_TAG tag)
{
	m_tag = tag;
}

inline Collider::COLLIDER_TAG Collider::GetTag()
{
	if(m_tag)
	return m_tag;

	return COLLIDER_TAG::DEFAULT;
}