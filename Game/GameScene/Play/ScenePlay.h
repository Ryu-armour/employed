#pragma once
#include "Game\GameScene\Scene.h"


class ScenePlay final : public Scene
{
//�����o�ϐ�
	//�v���~�e�B�u�̕`��t���O(�f�o�b�O�p)
	bool is_drawDebugValue;

	//�����o�֐�
public:
	static Scene*  Create();
public:
	ScenePlay();
	virtual ~ScenePlay();
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