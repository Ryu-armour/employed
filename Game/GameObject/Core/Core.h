#pragma once
#include "Game\GameObject\GameObject.h"

#include <array>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"


class Core final : public GameObject
{
//�萔
public:
	//�����蔻��̊g�嗦
	const float SCALE = 0.1f;
	//�����蔻��̔��a
	const float RADIUS = 5.0f;
	//���G����
	const int INVINCIBLE_TIME = 1 * 60;
	//�M�A�̐�
	static const int NUM_GEAR = 7;

//��
public:
	enum MODEL_DATA
	{
		CORE,
		GEAR1,
		GEAR2,
		GEAR3,
		GEAR4,
		GEAR5,
		GEAR6
	};

//�����o�ϐ�
private:
	//�M�A���f��
	std::array<std::unique_ptr<DirectX::Model>, Core::NUM_GEAR> m_gears;
	std::unique_ptr<DirectX::Model>	 m_gear;
	//���C�t
	int								 m_life;
	//���G����
	unsigned int					 m_invincibleTime;
	//���G��Ԃ��ǂ���
	bool							 is_invincibility;
	//�����蔻��
	std::array<std::unique_ptr<Sphere>,8>			 m_collider;
	//�����蔻��̐F
	DirectX::SimpleMath::Vector4	 m_color;
	//�����t���O
	bool							 isAlive;
	//�v���~�e�B�u�̕`��t���O
	bool							 is_drawPrimitive;

//�����o�֐�
public:
	Core();
	~Core();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
	//�Փ˔���
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//�t�@�C���̓ǂݍ���
	void ReadFile() override;
	//���f���̍쐬
	void CreateModel();
	//�v���C���[�Ƃ̏Փ˔���
	bool OnCollisionToPlayer();
	//����
	void Brake();
};