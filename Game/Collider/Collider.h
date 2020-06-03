#pragma once


class Capsule;
class Sphere;
class GameObject;


class Collider
{
//�\����
public:
	//�R���C�_�[�̃^�O
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

//�����o�ϐ�
protected:
	//�����蔻��̈ʒu
	DirectX::SimpleMath::Vector3 m_pos;
	//�I�u�W�F�N�g
	GameObject*					 m_owner;
	//�����蔻��̏��(0 : �����蔻������Ȃ�)
	bool						 is_collide;
	//�^�O
	COLLIDER_TAG				 m_tag;

//�����o�֐�
public:
	Collider(GameObject* owner);
	virtual ~Collider() {};
	//�`��
	virtual void Draw(DirectX::SimpleMath::Matrix world, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		_In_opt_ ID3D11ShaderResourceView* texture = nullptr, bool wireframe = true,
		_In_opt_ std::function<void __cdecl()> setCustomState = nullptr) const = 0;
	//�^���ʗp
	virtual bool IsCollided(const Collider* collider) const = 0;
	virtual bool IsCollided(const Capsule* capsule) const;
	virtual bool IsCollided(const Sphere* sphere) const;
	//���g�̌^��n���Ĕ��肷��
	void OnCollision(Collider* collider);

	const DirectX::SimpleMath::Vector3& GetPos() const;
	const void SetPos(DirectX::SimpleMath::Vector3& pos);
	GameObject* GetOwner() const;
	//�����蔻��̏�Ԃ��Z�b�g
	void SetCollide(bool collide);
	//�����蔻��̏�Ԃ̎擾
	bool GetCollide();
	//�^�O���Z�b�g
	void SetTag(COLLIDER_TAG tag);
	//�^�O���擾
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