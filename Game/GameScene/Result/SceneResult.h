#pragma once
#include "Game\GameScene\Scene.h"


class SceneResult final : public Scene
{
	//�����o�ϐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear;
	std::unique_ptr<DirectX::SpriteBatch>    m_spriteBatch;

//�����o�֐�
public:
	static Scene*  Create();
public:
	SceneResult();
	virtual ~SceneResult();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
private:
	//�����蔻��̑g�ݍ��킹�̃Z�b�g
	void SetCollisionGroup();
	//�I�u�W�F�N�g�̍쐬
	void CreateObject();
};