#pragma once
#include <istream>
#include <fstream>

#include "3rdParty\Picojson\picojson.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Common\StepTimer.h"

#include "Game\Collider\Collider.h"


class GameObject
{
//�\����
public:
	//�I�u�W�F�N�g�̃^�O
	enum GAMEOBJECT_TAG
	{
		DEFAULT,
		PLAYER,
		ENEMY,
		CORE,
		WEAPON
	};

//�����o�ϐ�
protected:
	//�ʒu
	DirectX::SimpleMath::Vector3	 m_pos;
	//���[���h�s��
	DirectX::SimpleMath::Matrix		 m_world;
	//�I�u�W�F�N�g�̃^�O
	GAMEOBJECT_TAG					 m_tag;
	//�f�o�b�O��
	bool							 isDebug;
private:
	//�g�p���
	bool							 isNeed;

//�����o�֐�
public:
	//�R���X�g���N�^
	GameObject();
	//�f�X�g���N�^
	virtual ~GameObject() {};
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Render() = 0;
	//�I������
	virtual void Finalize() = 0;
	//Json�t�@�C���̓ǂݍ���
	virtual void ReadFile() = 0;
	//�Փ˔���
	virtual void OnCollision(GameObject* gameObject, Collider* designation = nullptr) = 0;
	//�|�W�V������ݒ肷��
	virtual void SetPos(const DirectX::SimpleMath::Vector3& pos);
	//�|�W�V������Ԃ�
	virtual DirectX::SimpleMath::Vector3& GetPos();
	//���[���h�s���ݒ肷��
	virtual void SetWorld(const DirectX::SimpleMath::Matrix& world);
	//���[���h�s���Ԃ�
	virtual DirectX::SimpleMath::Matrix& GetWorld();
	//�^�O��ݒ肷��
	virtual void SetTag(GAMEOBJECT_TAG tag);
	//�^�O��Ԃ�
	virtual const GAMEOBJECT_TAG GetTag();
	//�s�v�ɂȂ�
	void ToParaphernalia();
	//�K�v�ȏ�Ԃ�Ԃ�
	bool IsNeed() const;
	//�s�v�ȏ�Ԃ�Ԃ�
	bool IsNeedless() const;
	//���[���h���W�Ɉʒu��K�p
	void ApplyWorld();
	//�f�o�b�O��Ԃ��ƃt���O������
	void IsDebug();
};

inline void GameObject::SetPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetPos()
{
	return m_pos;
}

inline void GameObject::SetWorld(const DirectX::SimpleMath::Matrix& world)
{
	m_world = world;
}

inline DirectX::SimpleMath::Matrix& GameObject::GetWorld()
{
	return m_world;
}

inline void GameObject::SetTag(GAMEOBJECT_TAG tag)
{
	m_tag = tag;
}

inline const GameObject::GAMEOBJECT_TAG GameObject::GetTag()
{
	if (m_tag)
		return m_tag;

	return GAMEOBJECT_TAG::DEFAULT;
}

inline void GameObject::ToParaphernalia()
{
	isNeed = false;
}

inline bool GameObject::IsNeed() const
{
	return isNeed;
}

inline bool GameObject::IsNeedless() const
{
	return !isNeed;
}

inline void GameObject::ApplyWorld()
{
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}

inline void GameObject::IsDebug()
{
	isDebug = true;
}