#include "SceneManager.h"

#include <cassert>

#include "Game\GameScene\Scene.h"


SceneManager::SceneManager()
{
	//抽象クラスの初期化
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
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(factory_method && "生成用関数が指定されていません。");

	m_scene_factory_methods[scene_id] = factory_method;
}

void SceneManager::SetStartScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	ChangeScene(scene_id);
}

void SceneManager::UpdateActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");



	// シーンの変更（要求があった場合)
	if (m_next_scene_id != SCENE_NONE)
	{
		//前シーンの終了処理
		m_active_scene->Final();
		//シーン更新
		ChangeScene(m_next_scene_id);
		//次のシーンを空に
		m_next_scene_id = SCENE_NONE;
	}
	// 活動中のシーンの更新
	m_active_scene->Update();
}

void SceneManager::RenderActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");

	// 活動中のシーンの描画
	m_active_scene->Render();
}

void SceneManager::RequestScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	m_next_scene_id = scene_id;
}

void SceneManager::ChangeScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(m_scene_factory_methods[scene_id] && "生成用関数が登録されていません。");

	// 新しいシーンの生成
	m_active_scene.reset(m_scene_factory_methods[scene_id]());
	m_active_scene->Init();
}