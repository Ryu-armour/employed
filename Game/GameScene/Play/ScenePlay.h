#pragma once
#include "Game\GameScene\Scene.h"


class ScenePlay final : public Scene
{
//メンバ変数
	//プリミティブの描画フラグ(デバッグ用)
	bool is_drawDebugValue;

	//メンバ関数
public:
	static Scene*  Create();
public:
	ScenePlay();
	virtual ~ScenePlay();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
private:
	//当たり判定の組み合わせのセット
	void SetCollisionGroup();
	//オブジェクトの作成
	void CreateObject();
};