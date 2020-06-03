#pragma once
#include <map>
#include <list>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"

#include "Game\GameObject\GameObject.h"
#include "Game\GameObject\Player\ArmR\ArmR.h"


//�N���X�̑O���錾
class IState;
class Sword;
class ArmR;


//�N���X�̐錾
class Player final : public GameObject
{
public:
	enum PLAYER_STATE
	{
		STANDING = 0,
		WALKING,
		ATTACK,
		DAMAGE,

		NUM
	};

//�萔
public:
	//�J�v�Z���̃T�C�Y
	const DirectX::SimpleMath::Vector3 CAPSULE_SIZE = { 0.0f, 1.0f, 0.0f };
	//�J�v�Z���̔��a
	const float CAPSULE_RADIUS = 0.5f;
	//���G����
	const int INVINCIBLE_TIME = 3 * 60;
	//�m�b�N�o�b�N�̑傫��
	const float BACK = 0.6f;
	//�r�p�[�c�̈ʒu
	static const DirectX::SimpleMath::Vector3 ARMR_ADJUSTMENT;

//�����o�ϐ�
private:
	//���f��
	std::unique_ptr<DirectX::Model>			 	 m_model;
	//�����蔻��
	std::unique_ptr<Sphere>						 m_collider;
	//�E�r
	ArmR*										 m_armR;
	//����
	Sword*										 m_weapon;
	//���݂̏��
	IState*										 m_state;
	//�q�b�g�|�C���g
	unsigned int								 m_life;
	//���G����
	unsigned int								 m_invincibleTime;
	//���G�J�E���g
	int											 m_invincibilityCount;
	//�_�ŃJ�E���g
	int											 m_flashCount;
	//���f���̃T�C�Y
	float										 m_size;
	//�v���C���[�̈ړ�����
	float										 m_speed;
	//����(�f�O���[�p)
	float										 m_angle;
	//�v���C���[�̈ړ����x
	DirectX::SimpleMath::Vector3				 m_vel;
	//������ԃx�N�g��
	DirectX::SimpleMath::Vector3				 m_blowAwayVec;
	//�v���~�e�B�u�̐F(�f�o�b�O)
	DirectX::SimpleMath::Vector4				 m_color;
	//���G��Ԃ��ǂ���
	bool										 is_invincibility;
	//���f���̕`��t���O
	bool										 is_drawModel;
	//�v���~�e�B�u�̕`��t���O
	bool										 is_drawPrimitive;


//�����o�֐�
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
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
	//���G��
	void ToInvincible();
	//���G������
	void UnlockInvicinble();
	//����
	void Move();
	//�_��
	void Flash();
	//�X�e�[�g�̐؂�ւ�
	void ChangeState(IState* state);
	//vel�ɒl������
	void SetVel(const DirectX::SimpleMath::Vector3& vel);
	//vel�̒l��n��
	DirectX::SimpleMath::Vector3& GetVel();
	//������ԃx�N�g��������
	void SetBlowAwayVec(const DirectX::SimpleMath::Vector3& vec);
	//������ԃx�N�g����n��
	DirectX::SimpleMath::Vector3& GetBlowAwayVec();
	//��Ԃ�Ԃ�
	IState* GetState() const;
	//�r���Z�b�g
	const void SetArmR(ArmR* arm);
	//�r���擾
	ArmR* GetArmR();
	//������Z�b�g
	const void SetWeapon(Sword* sword);
	//�����Ԃ�
	Sword* GetSword() const;
	//���C�t��Ԃ�
	unsigned int GetLife() const;
	//�F��ݒ�
	void SetColor(const DirectX::XMVECTORF32& color);

//�����o�֐�
private:
	//���f���̍쐬
	void CreateModel();
	//�m�b�N�o�b�N
	void KickBack(const DirectX::SimpleMath::Vector3& objPos);
	//�J�����̌������v���C���[�ɓK�p
	void FaceCamera();
};

inline void Player::SetVel(const DirectX::SimpleMath::Vector3& vel)
{
	m_vel = vel;
}

inline DirectX::SimpleMath::Vector3& Player::GetVel()
{
	return m_vel;
}

inline void Player::SetBlowAwayVec(const DirectX::SimpleMath::Vector3& vec)
{
	m_blowAwayVec = vec;
}

inline DirectX::SimpleMath::Vector3& Player::GetBlowAwayVec()
{
	return m_blowAwayVec;
}

inline IState* Player::GetState() const
{
	return m_state;
}

inline const void Player::SetArmR(ArmR* arm)
{
	m_armR = arm;
}

inline ArmR* Player::GetArmR()
{
	return m_armR;
}

inline const void Player::SetWeapon(Sword* sword)
{
	m_weapon = sword;
	m_armR->SetWeapon(sword);
}

inline Sword* Player::GetSword() const
{
	return m_weapon;
}

inline unsigned int Player::GetLife() const
{
	return m_life;
}

inline void Player::SetColor(const DirectX::XMVECTORF32& color)
{
	m_color = color;
}