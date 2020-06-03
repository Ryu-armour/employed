/// <summary>
/// 受け渡しする変数や情報の保管場所
/// </summary>
#pragma once
#include "Singleton.h"

#include <assert.h>
#include <Effects.h>
#include <unordered_map>

#include "DeviceResources.h"


class ResourceManager final : public Singleton<ResourceManager>
{
//メンバ変数
private:
	//デバイスリソース
	const DX::DeviceResources*						 m_deviceResources;
	//コモンステート
	const DirectX::CommonStates*					 m_commonStates;
	//テクスチャの読み込みパス
	DirectX::EffectFactory*							 m_factory;
	//モデルパス
	std::unordered_map<const char*, const wchar_t*>	 m_modelsData;
	//テクスチャパス
	std::unordered_map<const char*, const wchar_t*>	 m_textureData;
	//スプライトバッチ
	DirectX::SpriteBatch*							 m_spritebatch;

//メンバ関数
public:
	//DeviceResource のセット
	void SetDeviceResources(const DX::DeviceResources* deviceResources);
	//DeviceResource を返す
	const DX::DeviceResources* GetDeviceResources();
	//Device を返す
	ID3D11Device* GetDevice() const;
	//DeviceContext を返す
	ID3D11DeviceContext* GetContext() const;
	//DeviceContext を返す
	ID3D11DeviceContext1* GetContext1() const;
	//CommonState をセット
	void SetCommonStates(const DirectX::CommonStates* commonStates);
	//CommonState を返す
	const DirectX::CommonStates* GetCommonStates();
	//モデルの読み込み用のパスのセット
	void SetModelPath(const wchar_t* filename);
	//モデルの読み込み用のパスを返す
	DirectX::EffectFactory* GetModelPath() const;
	//モデルのパスのセット
	void SetModelData(const char* name, const wchar_t* filename);
	//テクスチャのパスを返す
	const wchar_t* GetModelData(const char* name);
	//テクスチャのパスのセット
	void SetTextureData(const char* name, const wchar_t* filename);
	//テクスチャのパスを返す
	const wchar_t* GetTextureData(const char* name);
	//SpriteBatch の取得
	DirectX::SpriteBatch* GetSpriteBath();
	//SpriteBatch のセット
	void SetSpriteBatch(DirectX::SpriteBatch* spritebatch);

//シングルトン
public:
	friend class Singleton<ResourceManager>;
protected:
	//コンストラクタ
	ResourceManager();
	//デストラクタ
	~ResourceManager();
};

//コンストラクタ
inline ResourceManager::ResourceManager()
{
	//初期化
	m_deviceResources = nullptr;
	m_commonStates = nullptr;
	m_factory = nullptr;
}

//デストラクタ
inline ResourceManager::~ResourceManager()
{
	//ポインタの削除
	delete m_factory;
}

//DeviceResource のセット
inline void ResourceManager::SetDeviceResources(const DX::DeviceResources* deviceResources)
{
	//メンバ変数にセット
	m_deviceResources = deviceResources;
}

//DeviceResource を返す
inline const DX::DeviceResources* ResourceManager::GetDeviceResources()
{
	//nullチェック
	assert(m_deviceResources != nullptr && "m_deviceResources is null");

	//返す
	return m_deviceResources;
}

//Device を返す
inline ID3D11Device* ResourceManager::GetDevice() const
{
	//nullチェック
	assert(m_deviceResources != nullptr && "m_deviceResources is null");

	//返す
	return m_deviceResources->GetD3DDevice();
}

//DeviceContext を返す
inline ID3D11DeviceContext* ResourceManager::GetContext() const
{
	//nullチェック
	assert(m_deviceResources != nullptr && "deviceResources is null");

	//返す
	return m_deviceResources->GetD3DDeviceContext();
}

//DeviceContext1 を返す
inline ID3D11DeviceContext1* ResourceManager::GetContext1() const
{
	//nullチェック
	assert(m_deviceResources != nullptr && "deviveResouces is null");

	//返す
	return m_deviceResources->GetD3DDeviceContext();
}

//CommonState をセット
inline void ResourceManager::SetCommonStates(const DirectX::CommonStates* commonStates)
{
	//メンバ変数にセット
	m_commonStates = commonStates;
}

//CommonState を返す
inline const DirectX::CommonStates* ResourceManager::GetCommonStates()
{
	//m_commonStates が null かチェック
	assert(m_commonStates != nullptr && "m_commonStates is null");

	//返す
	return m_commonStates;
}

//モデルの読み込みパスのセット
inline void ResourceManager::SetModelPath(const wchar_t* filename)
{
	//データのセット
	m_factory = new DirectX::EffectFactory(m_deviceResources->GetD3DDevice());
	m_factory->SetDirectory(filename);
}

//モデルの読み込みパスを返す
inline DirectX::EffectFactory* ResourceManager::GetModelPath() const
{
	//nullチェック
	assert(m_factory != nullptr && "m_factory is null");

	//パスを返す
	return m_factory;
}

//モデルデータのセット
inline void ResourceManager::SetModelData(const char* name, const wchar_t* filename)
{
	//データのセット
	m_modelsData.insert(std::make_pair(name, filename));
}

//モデルデータを渡す
inline const wchar_t* ResourceManager::GetModelData(const char* name)
{
	//引き数に応じたデータを返す
	return m_modelsData.at(name);
}

inline void ResourceManager::SetTextureData(const char* name, const wchar_t* filename)
{
	//データのセット
	m_textureData.insert(std::make_pair(name, filename));
}

inline const wchar_t* ResourceManager::GetTextureData(const char* name)
{
	//引き数に応じたデータを返す
	return m_textureData.at(name);
}

//SpriteBatch を返す
inline DirectX::SpriteBatch * ResourceManager::GetSpriteBath()
{
	//nullチェック
	assert(m_spritebatch != nullptr && "m_spritebatch is null");

	//返す
	return m_spritebatch;
}

//SpriteBatch のセット
inline void ResourceManager::SetSpriteBatch(DirectX::SpriteBatch * spritebatch)
{
	m_spritebatch = spritebatch;
}
