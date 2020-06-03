#pragma once
#include "Game\GameObject\GameObject.h"


class Floor final : public GameObject 
{
//�萔
public:
	//�}�b�v�̗�
	const int MAP_ROW = 30;
	//�}�b�v�̍s
	const int MAP_COLUMN = 30;
	//�����f���̃T�C�Y
	const float FLOOR_SIZE = 100;

//�����o�ϐ�
private:
	std::unique_ptr<DirectX::Model> m_model;

//�����o�֐�
public:
	Floor();
	~Floor();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
	void ReadFile() override;
	//�Փ˔���
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	void CreateModel();
};