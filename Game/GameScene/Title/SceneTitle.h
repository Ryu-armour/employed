#pragma once
#include "Game\GameScene\Scene.h"


class SceneTitle final : public Scene
{
//�����o�ϐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	std::unique_ptr<DirectX::SpriteBatch>    m_spriteBatch;

	//�����o�֐�
public:
	static Scene*  Create();
public:
	SceneTitle();
	virtual ~SceneTitle();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
private:
	//�I�u�W�F�N�g�̍쐬
	void CreateObject();
};