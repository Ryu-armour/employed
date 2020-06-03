#pragma once
#include "Game\GameObject\GameObject.h"


class Player;


class Life : public GameObject
{
//�萔
public:
	//�e�N�X�`���̃T�C�Y
	const int SIZE = 50;
	//�ʒu
	const DirectX::SimpleMath::Vector3 POS = DirectX::SimpleMath::Vector3(10.0f, 10.0f, 0.0f);

//�����o�ϐ�
private:
	//�v���C���[
	const Player* m_player;
	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

//�����o�֐�
public:
	//�R���X�g���N�^
	Life(const Player* player);
	//�f�X�g���N�^
	~Life();
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
};