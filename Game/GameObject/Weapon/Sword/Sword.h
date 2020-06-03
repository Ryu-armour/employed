#pragma once
#include "Game\GameObject\Weapon\Weapon.h"

#include "Game\Collider\Shape\Capsule\CapsuleCollider.h"


class Player;
class IState;


class Sword final : public Weapon
{
//��
public:
	//���̏��
	enum SWORD_STATE
	{
		WAIT = 0,
		ATTACK,

		NUM
	};

//�萔
	static const DirectX::SimpleMath::Vector3  COLLIDER_ADJUSTMENT;

//�����o�ϐ�
private:
	//���[�U�[
	Player* m_user;
	//���[�U�[�Ƃ̋�����
	DirectX::SimpleMath::Vector3	m_adjustment;
	//���[�U�[�̏����ʒu
	DirectX::SimpleMath::Vector3	m_userPos;
	//�����蔻��
	std::unique_ptr<Capsule>		m_collider;
	//�����蔻��̐F
	DirectX::SimpleMath::Vector4	m_color;
	//���݂̏��
	IState*							m_state;
	//���f��
	std::unique_ptr<DirectX::Model> m_model;

//�����o�֐�
public:
	//�R���X�g���N�^
	Sword(Player* user);
	//������
	void Initialize() override;
	//�X�V
	void Update() override;
	//�`��
	void Render() override;
	//�I������
	void Finalize() override;
	//Json�t�@�C�����J��
	void ReadFile() override;
	//�Փ˔���
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//��Ԃ̐؂�ւ�
	void ChangeState(IState* state);
	//�U��
	void Attack() override;
	//�U����Ԃ�
	void ToAttack();
	//�ҋ@��Ԃ�
	void ToStay();
	//���f���̍쐬
	void CreateModel();
	//���̎擾
	void SetColor(const DirectX::XMVECTORF32& color);
	//�R���C�_�[�̎擾
	Collider* GetCollider();
};

inline void Sword::SetColor(const DirectX::XMVECTORF32& color)
{
	m_color = color;
}

inline Collider* Sword::GetCollider()
{
	return m_collider.get();
}