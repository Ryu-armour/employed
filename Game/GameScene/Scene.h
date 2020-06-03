#pragma once
#include <string>


class Scene
{
//�����o�ϐ�
protected:
	std::wstring m_sceneName;
//�����o�֐�
public:
	// �R���X�g���N�^
	Scene() = default;
	// �f�X�g���N�^
	virtual ~Scene() = default;
public:
	// ����
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Final() = 0;
public:
	void SetSceneName(std::wstring string)
	{
		m_sceneName = string;
	}
};