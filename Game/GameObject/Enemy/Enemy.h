#pragma once
#include "Game\GameObject\GameObject.h"

#include "Game\Collider\Shape\Sphere\SphereCollider.h"

#include "Game\GameObjectState\Enemy\EnemyStateList.h"


class IState;


class Enemy : public GameObject
{
//�萔
public:
	//�U������̔��a
	const float HIT_SIZE = 1.5f;
	//���炢����̔��a
	const float HURT_SIZE = 2.0f;
	//�m�b�N�o�b�N�̑傫��
	const float BACK = 2.0f;
	//���E�̒���
	const float SIGHT = 20.0f;

//�����o�ϐ�
private:
	//���f��
	std::unique_ptr<DirectX::Model>  m_model;
	//���炢����
	std::unique_ptr<Sphere>			 m_hurtBox;
	//�U������
	std::unique_ptr<Sphere>			 m_hitBox;
	//HP
	int								 m_life;
	//����
	float							 m_angle;
	//�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion  m_quaternion;
	//���G��Ԃ��ǂ���
	bool							 is_invincibility;
	//�ړ��x�N�g��
	DirectX::SimpleMath::Vector3	 m_vel;
	//���̈ړ���
	DirectX::SimpleMath::Vector3	 m_destination;
	//���݂̏��
	IState*							 m_state;
	//�������
	std::unique_ptr<WalkingEnemy>	 m_walk;
	//�ړI�n��T�����
	std::unique_ptr<SearchingEnemy>  m_search;
	//�_���[�W���󂯂����
	std::unique_ptr<GetHurtEnemy>	 m_gethurt;
	//�v���C���[
	GameObject*						 m_player;

//�����o�֐�
public:
	//�R���X�g���N�^
	Enemy(GameObject* player = nullptr);
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize() override;
	//�X�V
	void Update() override;
	//�`��
	void Render() override;
	//�I������
	void Finalize() override;
	//�Փ˔���
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//�t�@�C���ǂݍ���
	void ReadFile() override;
	//���G��
	void ToInvincible();
	//���G������
	void UnlockInvicinble();
	//����
	void Move();
	//�������Z�b�g
	void SetAngle(const float& angle);
	//�������擾
	float GetAngle();
	//�x�N�g�����Z�b�g
	void SetVel(const DirectX::SimpleMath::Vector3& vel);
	//�x�N�g�����擾
	DirectX::SimpleMath::Vector3 GetVel();
	//���̈ړ�����Z�b�g
	void SetDestination(const DirectX::SimpleMath::Vector3& destination);
	//�ړ����Ԃ�
	DirectX::SimpleMath::Vector3 GetDestination();
	//�X�e�[�g�̐؂�ւ�
	void ChangeState(IState* state);
	//SearchingState���擾
	IState* GetSearchState();
	//WalkingState���擾
	IState* GetWalkState();
	//�v���C���[�̎擾
	GameObject* GetPlayer();

//�����o�֐�
private:
	//�����Ƃ̏Փ˔���
	void OnColliderToFamiry(GameObject* famiry);
	//���f���̍쐬
	void CreateModel();
	//�m�b�N�o�b�N
	void KickBack(const DirectX::SimpleMath::Vector3& objPos);
	//�����Ă�����ɉ�]
	void ApplyDirection();
};

inline void Enemy::SetAngle(const float& angle)
{
	m_angle = angle;
}

inline float Enemy::GetAngle()
{
	return m_angle;
}

inline void Enemy::SetVel(const DirectX::SimpleMath::Vector3& vel)
{
	m_vel = vel;
}

inline DirectX::SimpleMath::Vector3 Enemy::GetVel()
{
	return m_vel;
}

inline void Enemy::SetDestination(const DirectX::SimpleMath::Vector3& destination)
{
	m_destination = destination;
}

inline DirectX::SimpleMath::Vector3 Enemy::GetDestination()
{
	return m_destination;
}

inline void Enemy::ChangeState(IState* state)
{
	m_state = state;
	m_state->Initialize();
}

inline IState* Enemy::GetSearchState()
{
	return m_search.get();
}

inline IState* Enemy::GetWalkState()
{
	return m_walk.get();
}

inline GameObject* Enemy::GetPlayer()
{
	return m_player;
}