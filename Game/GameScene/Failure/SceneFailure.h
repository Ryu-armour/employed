#pragma once
#include "Game\GameScene\Scene.h"


class SceneFailure : public Scene
{
	//ƒƒ“ƒo•Ï”
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_failure;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_continue;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_close;

	std::unique_ptr<DirectX::SpriteBatch>    m_spriteBatch;

//ƒƒ“ƒoŠÖ”
public:
	static Scene*  Create();
	
public:
	virtual ~SceneFailure();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Final() override;
};