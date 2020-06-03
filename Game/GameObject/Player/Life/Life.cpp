#include "Life.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\GameObject\Player\Player.h"


//コンストラクタ
Life::Life(const Player* player)
	: m_player(player)
{
	m_pos = POS;
}

//デストラクタ
Life::~Life()
{
}

//初期化
void Life::Initialize()
{
	//テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(ResourceManager::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		ResourceManager::GetInstance()->GetTextureData("Life"), nullptr, m_texture.GetAddressOf());
}

//更新
void Life::Update()
{
}

//描画
void Life::Render()
{
	//画像情報がない場合は描画をしない
	if (!m_texture)
		return;

	//ライフ数描画
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

//終了処理
void Life::Finalize()
{
}

//衝突判定
void Life::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//ファイル読み込み
void Life::ReadFile()
{
}
