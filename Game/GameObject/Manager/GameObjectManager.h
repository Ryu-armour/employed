#pragma once
#include <list>
#include <memory>

#include "Game\Common\Singleton.h"

#include "Game\GameObject\GameObject.h"


class GameObjectManager final : public Singleton<GameObjectManager>
{
//名前空間
	using UniqueGameObject = std::unique_ptr<GameObject>;

//メンバ変数
private:
	//管理するオブジェクト
	std::list<UniqueGameObject> m_objects;
	//追加待ちのオブジェクト
	std::list<UniqueGameObject> m_queue;

//メンバ関数
public:
	//更新
	void Update();
	//描画
	void Render();
	//管理するオブジェクトの追加
	void Add(UniqueGameObject&& gameObject);
	//管理するオブジェクト全てを削除
	void DeleteAllObject();

//メンバ関数
private:
	//オブジェクトの更新
	void UpdateObjects();
	//追加待ちオブジェクトの追加
	void ExtendObjects();
	//オブジェクトの個別削除
	void DeleteObjects();

//シングルトン
public:
	friend class Singleton<GameObjectManager>;
protected:
	//コンストラクタ
	GameObjectManager();
	//デストラクタ
	virtual ~GameObjectManager();
};