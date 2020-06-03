/// <summary>
/// �󂯓n������ϐ�����̕ۊǏꏊ
/// </summary>
#pragma once
#include "Singleton.h"

#include <assert.h>
#include <Effects.h>
#include <unordered_map>

#include "DeviceResources.h"


class ResourceManager final : public Singleton<ResourceManager>
{
//�����o�ϐ�
private:
	//�f�o�C�X���\�[�X
	const DX::DeviceResources*						 m_deviceResources;
	//�R�����X�e�[�g
	const DirectX::CommonStates*					 m_commonStates;
	//�e�N�X�`���̓ǂݍ��݃p�X
	DirectX::EffectFactory*							 m_factory;
	//���f���p�X
	std::unordered_map<const char*, const wchar_t*>	 m_modelsData;
	//�e�N�X�`���p�X
	std::unordered_map<const char*, const wchar_t*>	 m_textureData;
	//�X�v���C�g�o�b�`
	DirectX::SpriteBatch*							 m_spritebatch;

//�����o�֐�
public:
	//DeviceResource �̃Z�b�g
	void SetDeviceResources(const DX::DeviceResources* deviceResources);
	//DeviceResource ��Ԃ�
	const DX::DeviceResources* GetDeviceResources();
	//Device ��Ԃ�
	ID3D11Device* GetDevice() const;
	//DeviceContext ��Ԃ�
	ID3D11DeviceContext* GetContext() const;
	//DeviceContext ��Ԃ�
	ID3D11DeviceContext1* GetContext1() const;
	//CommonState ���Z�b�g
	void SetCommonStates(const DirectX::CommonStates* commonStates);
	//CommonState ��Ԃ�
	const DirectX::CommonStates* GetCommonStates();
	//���f���̓ǂݍ��ݗp�̃p�X�̃Z�b�g
	void SetModelPath(const wchar_t* filename);
	//���f���̓ǂݍ��ݗp�̃p�X��Ԃ�
	DirectX::EffectFactory* GetModelPath() const;
	//���f���̃p�X�̃Z�b�g
	void SetModelData(const char* name, const wchar_t* filename);
	//�e�N�X�`���̃p�X��Ԃ�
	const wchar_t* GetModelData(const char* name);
	//�e�N�X�`���̃p�X�̃Z�b�g
	void SetTextureData(const char* name, const wchar_t* filename);
	//�e�N�X�`���̃p�X��Ԃ�
	const wchar_t* GetTextureData(const char* name);
	//SpriteBatch �̎擾
	DirectX::SpriteBatch* GetSpriteBath();
	//SpriteBatch �̃Z�b�g
	void SetSpriteBatch(DirectX::SpriteBatch* spritebatch);

//�V���O���g��
public:
	friend class Singleton<ResourceManager>;
protected:
	//�R���X�g���N�^
	ResourceManager();
	//�f�X�g���N�^
	~ResourceManager();
};

//�R���X�g���N�^
inline ResourceManager::ResourceManager()
{
	//������
	m_deviceResources = nullptr;
	m_commonStates = nullptr;
	m_factory = nullptr;
}

//�f�X�g���N�^
inline ResourceManager::~ResourceManager()
{
	//�|�C���^�̍폜
	delete m_factory;
}

//DeviceResource �̃Z�b�g
inline void ResourceManager::SetDeviceResources(const DX::DeviceResources* deviceResources)
{
	//�����o�ϐ��ɃZ�b�g
	m_deviceResources = deviceResources;
}

//DeviceResource ��Ԃ�
inline const DX::DeviceResources* ResourceManager::GetDeviceResources()
{
	//null�`�F�b�N
	assert(m_deviceResources != nullptr && "m_deviceResources is null");

	//�Ԃ�
	return m_deviceResources;
}

//Device ��Ԃ�
inline ID3D11Device* ResourceManager::GetDevice() const
{
	//null�`�F�b�N
	assert(m_deviceResources != nullptr && "m_deviceResources is null");

	//�Ԃ�
	return m_deviceResources->GetD3DDevice();
}

//DeviceContext ��Ԃ�
inline ID3D11DeviceContext* ResourceManager::GetContext() const
{
	//null�`�F�b�N
	assert(m_deviceResources != nullptr && "deviceResources is null");

	//�Ԃ�
	return m_deviceResources->GetD3DDeviceContext();
}

//DeviceContext1 ��Ԃ�
inline ID3D11DeviceContext1* ResourceManager::GetContext1() const
{
	//null�`�F�b�N
	assert(m_deviceResources != nullptr && "deviveResouces is null");

	//�Ԃ�
	return m_deviceResources->GetD3DDeviceContext();
}

//CommonState ���Z�b�g
inline void ResourceManager::SetCommonStates(const DirectX::CommonStates* commonStates)
{
	//�����o�ϐ��ɃZ�b�g
	m_commonStates = commonStates;
}

//CommonState ��Ԃ�
inline const DirectX::CommonStates* ResourceManager::GetCommonStates()
{
	//m_commonStates �� null ���`�F�b�N
	assert(m_commonStates != nullptr && "m_commonStates is null");

	//�Ԃ�
	return m_commonStates;
}

//���f���̓ǂݍ��݃p�X�̃Z�b�g
inline void ResourceManager::SetModelPath(const wchar_t* filename)
{
	//�f�[�^�̃Z�b�g
	m_factory = new DirectX::EffectFactory(m_deviceResources->GetD3DDevice());
	m_factory->SetDirectory(filename);
}

//���f���̓ǂݍ��݃p�X��Ԃ�
inline DirectX::EffectFactory* ResourceManager::GetModelPath() const
{
	//null�`�F�b�N
	assert(m_factory != nullptr && "m_factory is null");

	//�p�X��Ԃ�
	return m_factory;
}

//���f���f�[�^�̃Z�b�g
inline void ResourceManager::SetModelData(const char* name, const wchar_t* filename)
{
	//�f�[�^�̃Z�b�g
	m_modelsData.insert(std::make_pair(name, filename));
}

//���f���f�[�^��n��
inline const wchar_t* ResourceManager::GetModelData(const char* name)
{
	//�������ɉ������f�[�^��Ԃ�
	return m_modelsData.at(name);
}

inline void ResourceManager::SetTextureData(const char* name, const wchar_t* filename)
{
	//�f�[�^�̃Z�b�g
	m_textureData.insert(std::make_pair(name, filename));
}

inline const wchar_t* ResourceManager::GetTextureData(const char* name)
{
	//�������ɉ������f�[�^��Ԃ�
	return m_textureData.at(name);
}

//SpriteBatch ��Ԃ�
inline DirectX::SpriteBatch * ResourceManager::GetSpriteBath()
{
	//null�`�F�b�N
	assert(m_spritebatch != nullptr && "m_spritebatch is null");

	//�Ԃ�
	return m_spritebatch;
}

//SpriteBatch �̃Z�b�g
inline void ResourceManager::SetSpriteBatch(DirectX::SpriteBatch * spritebatch)
{
	m_spritebatch = spritebatch;
}
