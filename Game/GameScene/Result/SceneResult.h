#pragma once
#include "Game\GameScene\Scene.h"


class SceneResult final : public Scene
{
	//メンバ変数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear;
	std::unique_ptr<DirectX::SpriteBatch>    m_spriteBatch;

//メンバ関数
public:
	static Scene*  Create();
public:
	SceneResult();
	virtual ~SceneResult();
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