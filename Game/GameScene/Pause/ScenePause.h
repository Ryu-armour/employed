#pragma once
#include "Game\GameScene\Scene.h"

#include <unordered_map>

#include "Game\GameScene\Manager\SceneManager.h"


class ScenePause final:public Scene
{
//選択肢
	enum OPTION
	{
		BACK,
		FINISH,

		NUM_OPTIONS
	};

//定数
	//選択肢の画像のX座標
	const int OPTIN_POS_X = 200;
	//選択肢の画像のY座標
	const int OPTIN_POS_Y = 100;
	//選択肢の画像のY間隔
	const int SPACING = 30;

//前方宣言
	using Requester = void(ScenePause::*)();


//メンバ変数
private:
	//ゲームに戻る
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_back;
	//ゲーム終了(選択肢)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_finish;
	//SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//現在選択しているもの
	int m_choice;
	//選択肢とそれに対応する処理を繋げる
	std::unordered_map<int, Requester> m_manipulation_mediator;
	//選択肢とSceneIDをつなげる
	std::unordered_map<int, SceneID> m_scene_id_mediator;

//メンバ関数
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

