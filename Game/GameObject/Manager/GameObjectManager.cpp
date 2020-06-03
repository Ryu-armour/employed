#include "GameObjectManager.h"


//�R���X�g���N�^
GameObjectManager::GameObjectManager() : m_objects(),m_queue()
{
}

//�f�X�g���N�^
GameObjectManager::~GameObjectManager()
{
}

//�X�V
void GameObjectManager::Update()
{
	//�s�v�ɂȂ����I�u�W�F�N�g������
	DeleteObjects();
	
	//�L���[���X�g�̃I�u�W�F�N�g��������
	if (!m_queue.empty())
	{
		ExtendObjects();
	}

	//�I�u�W�F�N�g�̍X�V
	UpdateObjects();
}

//�`��
void GameObjectManager::Render()
{
	//�I�u�W�F�N�g�̕`��
	for (std::unique_ptr<GameObject>& object : m_objects)
	{
		object->Render();
	}
}

//�Ǘ�����I�u�W�F�N�g�̒ǉ�
void GameObjectManager::Add(UniqueGameObject&& gameObject)
{
	//�L���[���X�g�Ɉ�U�ǉ�
	m_queue.push_back(std::move(gameObject));
}

//�Ǘ�����I�u�W�F�N�g�S�Ă��폜
void GameObjectManager::DeleteAllObject()
{
	//�󂩃`�F�b�N
	if (!m_objects.empty())
	{
		//�I�u�W�F�N�g�̏I������
		for (UniqueGameObject& object : m_objects)
		{
			object->Finalize();
		}

		//���X�g����O��
		m_objects.clear();
	}
}

//�I�u�W�F�N�g�̍X�V
void GameObjectManager::UpdateObjects()
{
	for (UniqueGameObject& object : m_objects)
	{
		object->Update();
	}
}

//�ǉ��҂��I�u�W�F�N�g�̒ǉ�
void GameObjectManager::ExtendObjects()
{
	m_objects.splice(m_objects.end(),m_queue);
}

//�I�u�W�F�N�g�̌ʍ폜
void GameObjectManager::DeleteObjects()
{
	m_objects.remove_if(std::mem_fn(&GameObject::IsNeedless));
}
