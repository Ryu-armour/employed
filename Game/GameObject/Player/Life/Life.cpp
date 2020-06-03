#include "Life.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\GameObject\Player\Player.h"


//�R���X�g���N�^
Life::Life(const Player* player)
	: m_player(player)
{
	m_pos = POS;
}

//�f�X�g���N�^
Life::~Life()
{
}

//������
void Life::Initialize()
{
	//�e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(ResourceManager::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		ResourceManager::GetInstance()->GetTextureData("Life"), nullptr, m_texture.GetAddressOf());
}

//�X�V
void Life::Update()
{
}

//�`��
void Life::Render()
{
	//�摜��񂪂Ȃ��ꍇ�͕`������Ȃ�
	if (!m_texture)
		return;

	//���C�t���`��
	if (m_player->GetLife())
	{
		DirectX::SpriteBatch* spriteBatch = ResourceManager::GetInstance()->GetSpriteBath();
		for (unsigned int i = 0; i < m_player->GetLife(); i++)
		{
			spriteBatch->Draw(
				m_texture.Get(),
				DirectX::SimpleMath::Vector2(m_pos.x + SIZE * i, m_pos.y),
				nullptr);
		}
	}
}

//�I������
void Life::Finalize()
{
}

//�Փ˔���
void Life::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//�t�@�C���ǂݍ���
void Life::ReadFile()
{
}
