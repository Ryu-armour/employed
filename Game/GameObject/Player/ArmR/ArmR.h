#pragma once
#include "Game\GameObject\GameObject.h"

#include <memory>


class Sword;


class ArmR final : public GameObject
{
private:
//�����o�ϐ�
	//����
	Sword* m_weapon;
	//���f��
	std::unique_ptr<DirectX::Model> m_model;

public:
//�����o�֐�
	//�R���X�g���N�^
	ArmR();
	//�f�X�g���N�^
	~ArmR();
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
	//������Z�b�g
	void SetWeapon(Sword* sword);
	//������擾
	Sword* GetSword();

//�����o�֐�
private:
	void CreateModel();
};

inline void ArmR::SetWeapon(Sword* sword)
{
	m_weapon = sword;
}

inline Sword* ArmR::GetSword()
{
	return m_weapon;
}
