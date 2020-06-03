#pragma once
#include "Game\Common\Singleton.h"

#include <memory>
#include <vector>
#include <array>


//シーンのIDデータ
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
//前方宣言
	using FactoryMethod = Scene* (*)();

// メンバ変数
private:
	// 活動中のシーン
	std::unique_ptr<Scene> m_active_scene;
	// 変更予定のシーンのID
	SceneID m_next_scene_id;
	// 各シーンのファクトリメソッド
	std::array<FactoryMethod, NUM_SCENES> m_scene_factory_methods;


//メンバ関数
public:
	// シーンの追加
	void AddScene(SceneID scene_id, FactoryMethod factory_method);
	// 開始シーンの設定
	void SetStartScene(SceneID scene_id);
	// 活動中のシーンの更新
	void UpdateActiveScene();
	// 活動中のシーンの描画
	void RenderActiveScene();
	// シーン変更の要求
	void RequestScene(SceneID scene_id);
private:
	// シーン変更
	void ChangeScene(SceneID scene_id);

//シングルトン
public:
	friend class Singleton<SceneManager>;
protected:
	SceneManager();
	~SceneManager();

// 複製の禁止
	//コピーコンストラクタの削除
	SceneManager(const SceneManager&) = delete;
	// 代入演算子の削除
	SceneManager& operator=(const SceneManager&) = delete;
	// ムーブコンストラクタの削除
	SceneManager(SceneManager&&) = delete;
	// ムーブ代入演算子の削除
	SceneManager& operator=(SceneManager&&) = delete;
};