#include "GameObjectManager.h"


//コンストラクタ
GameObjectManager::GameObjectManager() : m_objects(),m_queue()
{
}

//デストラクタ
GameObjectManager::~GameObjectManager()
{
}

//更新
void GameObjectManager::Update()
{
	//不要になったオブジェクトを消す
	DeleteObjects();
	
	//キューリストのオブジェクトを加える
	if (!m_queue.empty())
	{
		ExtendObjects();
	}

	//オブジェクトの更新
	UpdateObjects();
}

//描画
void GameObjectManager::Render()
{
	//オブジェクトの描画
	for (std::unique_ptr<GameObject>& object : m_objects)
	{
		object->Render();
	}
}

//管理するオブジェクトの追加
void GameObjectManager::Add(UniqueGameObject&& gameObject)
{
	//キューリストに一旦追加
	m_queue.push_back(std::move(gameObject));
}

//管理するオブジェクト全てを削除
void GameObjectManager::DeleteAllObject()
{
	//空かチェック
	if (!m_objects.empty())
	{
		//オブジェクトの終了処理
		for (UniqueGameObject& object : m_objects)
		{
			object->Finalize();
		}

		//リストから外す
		m_objects.clear();
	}
}

//オブジェクトの更新
void GameObjectManager::UpdateObjects()
{
	for (UniqueGameObject& object : m_objects)
	{
		object->Update();
	}
}

//追加待ちオブジェクトの追加
void GameObjectManager::ExtendObjects()
{
	m_objects.splice(m_objects.end(),m_queue);
}

//オブジェクトの個別削除
void GameObjectManager::DeleteObjects()
{
	m_objects.remove_if(std::mem_fn(&GameObject::IsNeedless));
}
