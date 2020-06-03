#pragma once
#include <list>
#include <memory>

#include "Game\Common\Singleton.h"

#include "Game\GameObject\GameObject.h"


class GameObjectManager final : public Singleton<GameObjectManager>
{
//���O���
	using UniqueGameObject = std::unique_ptr<GameObject>;

//�����o�ϐ�
private:
	//�Ǘ�����I�u�W�F�N�g
	std::list<UniqueGameObject> m_objects;
	//�ǉ��҂��̃I�u�W�F�N�g
	std::list<UniqueGameObject> m_queue;

//�����o�֐�
public:
	//�X�V
	void Update();
	//�`��
	void Render();
	//�Ǘ�����I�u�W�F�N�g�̒ǉ�
	void Add(UniqueGameObject&& gameObject);
	//�Ǘ�����I�u�W�F�N�g�S�Ă��폜
	void DeleteAllObject();

//�����o�֐�
private:
	//�I�u�W�F�N�g�̍X�V
	void UpdateObjects();
	//�ǉ��҂��I�u�W�F�N�g�̒ǉ�
	void ExtendObjects();
	//�I�u�W�F�N�g�̌ʍ폜
	void DeleteObjects();

//�V���O���g��
public:
	friend class Singleton<GameObjectManager>;
protected:
	//�R���X�g���N�^
	GameObjectManager();
	//�f�X�g���N�^
	virtual ~GameObjectManager();
};