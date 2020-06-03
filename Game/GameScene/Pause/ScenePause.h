#pragma once
#include "Game\GameScene\Scene.h"

#include <unordered_map>

#include "Game\GameScene\Manager\SceneManager.h"


class ScenePause final:public Scene
{
//�I����
	enum OPTION
	{
		BACK,
		FINISH,

		NUM_OPTIONS
	};

//�萔
	//�I�����̉摜��X���W
	const int OPTIN_POS_X = 200;
	//�I�����̉摜��Y���W
	const int OPTIN_POS_Y = 100;
	//�I�����̉摜��Y�Ԋu
	const int SPACING = 30;

//�O���錾
	using Requester = void(ScenePause::*)();


//�����o�ϐ�
private:
	//�Q�[���ɖ߂�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_back;
	//�Q�[���I��(�I����)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_finish;
	//SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//���ݑI�����Ă������
	int m_choice;
	//�I�����Ƃ���ɑΉ����鏈�����q����
	std::unordered_map<int, Requester> m_manipulation_mediator;
	//�I������SceneID���Ȃ���
	std::unordered_map<int, SceneID> m_scene_id_mediator;

//�����o�֐�
public:
	static Scene*  Create();
public:
	ScenePause();
	virtual ~ScenePause();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
	void RequestScene();
	void FinishGame();
};

