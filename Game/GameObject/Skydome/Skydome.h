#pragma once
#include "Game\GameObject\GameObject.h"


class Skydome final : public GameObject
{
//メンバ変数
private:
	//天球
	std::unique_ptr<DirectX::Model> m_model;

//メンバ関数
public:
	//コンストラクタ
	Skydome();
	//デストラクタ
	~Skydome();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	//Jsonファイルを開く
	void ReadFile() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//モデルの作成
	void CreateModel();
};