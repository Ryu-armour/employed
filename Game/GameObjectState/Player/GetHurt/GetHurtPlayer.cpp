#include "GetHurtPlayer.h"

#include "Game\GameObject\Player\Player.h"
#include "Game\GameObject\Weapon\Sword\Sword.h"

#include "Game\GameObjectState\Player\PlayerState.h"


GetHurtPlayer::GetHurtPlayer(Player * player) : m_player(player), m_count(0),is_draw(true)
{
}

GetHurtPlayer::~GetHurtPlayer()
{
	Finalize();
}

void GetHurtPlayer::Initialize()
{
	//カウントのリセット
	m_count = 0;
	//吹っ飛ぶベクトルを入れる
	m_blowAwayVec = m_player->GetBlowAwayVec();
	//無敵状態
	m_player->ToInvincible();
	//コライダーの色を変更
	m_player->SetColor(DirectX::Colors::Silver);
	//攻撃状態を解除
	m_player->GetSword()->ToStay();
}

void GetHurtPlayer::Update()
{
	//カウントの更新
	m_count++;

	//操作
	//m_player->Move();

	//吹っ飛ぶ
	KickBack();

	//シーン遷移
	if (m_count >= WINCE_TIME)
	{
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::STANDING));
	}
}

void GetHurtPlayer::Render(DirectX::Model* model)
{
	if (is_draw)
	{
		ResourceManager* resourceManager = ResourceManager::GetInstance();

		//モデルの描画
		DirectX::SimpleMath::Matrix world = m_player->GetWorld();

		model->Draw(resourceManager->GetContext(),
			*resourceManager->GetCommonStates(), world,
			FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
	}
}

void GetHurtPlayer::Finalize()
{
}

void GetHurtPlayer::KickBack()
{
	//吹っ飛ぶベクトル
	m_blowAwayVec *= 0.7f;

	//吹っ飛ぶ
	m_player->SetPos(m_player->GetPos() + m_blowAwayVec);
}