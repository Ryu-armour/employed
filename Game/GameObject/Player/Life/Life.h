#pragma once
#include "Game\GameObject\GameObject.h"


class Player;


class Life : public GameObject
{
//定数
public:
	//テクスチャのサイズ
	const int SIZE = 50;
	//位置
	const DirectX::SimpleMath::Vector3 POS = DirectX::SimpleMath::Vector3(10.0f, 10.0f, 0.0f);

//メンバ変数
private:
	//プレイヤー
	const Player* m_player;
	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

//メンバ関数
public:
	//コンストラクタ
	Life(const Player* player);
	//デストラクタ
	~Life();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//ファイル読み込み
	void ReadFile() override;
};