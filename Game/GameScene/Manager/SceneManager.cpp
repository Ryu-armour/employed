#include "SceneManager.h"

#include <cassert>

#include "Game\GameScene\Scene.h"


SceneManager::SceneManager()
{
	//���ۃN���X�̏�����
	m_active_scene.reset();
	m_next_scene_id = SCENE_NONE;

	for (int i = 0; i < NUM_SCENES; i++)
	{
		m_scene_factory_methods[i] = nullptr;
	}
}

SceneManager::~SceneManager()
{

}

void SceneManager::AddScene(SceneID scene_id, FactoryMethod factory_method)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "�V�[��ID���s���ł��B");
	assert(factory_method && "�����p�֐����w�肳��Ă��܂���B");

	m_scene_factory_methods[scene_id] = factory_method;
}

void SceneManager::SetStartScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "�V�[��ID���s���ł��B");

	ChangeScene(scene_id);
}

void SceneManager::UpdateActiveScene()
{
	assert(m_active_scene && "�������̃V�[��������܂���B");



	// �V�[���̕ύX�i�v�����������ꍇ)
	if (m_next_scene_id != SCENE_NONE)
	{
		//�O�V�[���̏I������
		m_active_scene->Final();
		//�V�[���X�V
		ChangeScene(m_next_scene_id);
		//���̃V�[�������
		m_next_scene_id = SCENE_NONE;
	}
	// �������̃V�[���̍X�V
	m_active_scene->Update();
}

void SceneManager::RenderActiveScene()
{
	assert(m_active_scene && "�������̃V�[��������܂���B");

	// �������̃V�[���̕`��
	m_active_scene->Render();
}

void SceneManager::RequestScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "�V�[��ID���s���ł��B");

	m_next_scene_id = scene_id;
}

void SceneManager::ChangeScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "�V�[��ID���s���ł��B");
	assert(m_scene_factory_methods[scene_id] && "�����p�֐����o�^����Ă��܂���B");

	// �V�����V�[���̐���
	m_active_scene.reset(m_scene_factory_methods[scene_id]());
	m_active_scene->Init();
}