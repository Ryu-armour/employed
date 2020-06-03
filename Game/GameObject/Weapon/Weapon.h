#pragma once
#include "Game\GameObject\GameObject.h"


class Weapon : public GameObject
{
protected:
//�����o�ϐ�
	//�傫��
	float m_size;
	//�U�����
	bool isAttack;
	//�v���~�e�B�u�̕`��t���O
	bool is_drawPrimitive;

//�����o�֐�
public:
	//�R���X�g���N�^
	Weapon() : m_size(0), isAttack(false)
	{
		m_tag = GameObject::WEAPON;
	};
	//�f�X�g���N�^
	virtual ~Weapon() {};
	//������
	void Initialize() override = 0;
	//�X�V
	void Update() override = 0;
	//�`��
	void Render() override = 0;
	//�I������
	void Finalize() override = 0;
	//Json�t�@�C�����J��
	void ReadFile() override = 0;
	//�Փ˔���
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override = 0;
	//�U��
	virtual void Attack() = 0;
	//�T�C�Y�̐ݒ�
	void SetSize(float size);
	//�U����Ԃ̎擾
	bool IsAttack();
	//�U����Ԃɂ���
	void ToAttackState();
	//�ҋ@��Ԃɂ���
	void ToStayState();
};

inline void Weapon::SetSize(float size)
{
	m_size = size;
}

inline bool Weapon::IsAttack()
{
	return isAttack;
}

inline void Weapon::ToAttackState()
{
	isAttack = true;
}

inline void Weapon::ToStayState()
{
	isAttack = false;
}