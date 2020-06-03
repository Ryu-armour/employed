#pragma once
#include "Game\Common\Singleton.h"

#include <memory>
#include <vector>
#include <array>


//�V�[����ID�f�[�^
enum SceneID
{
	SCENE_NONE = -1,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_PAUSE,
	SCENE_RESULT,
	SCENE_FAILURE,

	NUM_SCENES
};

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
//�O���錾
	using FactoryMethod = Scene* (*)();

// �����o�ϐ�
private:
	// �������̃V�[��
	std::unique_ptr<Scene> m_active_scene;
	// �ύX�\��̃V�[����ID
	SceneID m_next_scene_id;
	// �e�V�[���̃t�@�N�g�����\�b�h
	std::array<FactoryMethod, NUM_SCENES> m_scene_factory_methods;


//�����o�֐�
public:
	// �V�[���̒ǉ�
	void AddScene(SceneID scene_id, FactoryMethod factory_method);
	// �J�n�V�[���̐ݒ�
	void SetStartScene(SceneID scene_id);
	// �������̃V�[���̍X�V
	void UpdateActiveScene();
	// �������̃V�[���̕`��
	void RenderActiveScene();
	// �V�[���ύX�̗v��
	void RequestScene(SceneID scene_id);
private:
	// �V�[���ύX
	void ChangeScene(SceneID scene_id);

//�V���O���g��
public:
	friend class Singleton<SceneManager>;
protected:
	SceneManager();
	~SceneManager();

// �����̋֎~
	//�R�s�[�R���X�g���N�^�̍폜
	SceneManager(const SceneManager&) = delete;
	// ������Z�q�̍폜
	SceneManager& operator=(const SceneManager&) = delete;
	// ���[�u�R���X�g���N�^�̍폜
	SceneManager(SceneManager&&) = delete;
	// ���[�u������Z�q�̍폜
	SceneManager& operator=(SceneManager&&) = delete;
};