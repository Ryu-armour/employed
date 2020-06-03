#pragma once
#include "Game\GameScene\Scene.h"


class SceneTitle final : public Scene
{
//メンバ変数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	std::unique_ptr<DirectX::SpriteBatch>    m_spriteBatch;

	//メンバ関数
public:
	static Scene*  Create();
public:
	SceneTitle();
	virtual ~SceneTitle();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
private:
	//オブジェクトの作成
	void CreateObject();
};