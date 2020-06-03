#pragma once
#include "Game\GameObject\GameObject.h"


class Skydome final : public GameObject
{
//�����o�ϐ�
private:
	//�V��
	std::unique_ptr<DirectX::Model> m_model;

//�����o�֐�
public:
	//�R���X�g���N�^
	Skydome();
	//�f�X�g���N�^
	~Skydome();
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
	//���f���̍쐬
	void CreateModel();
};