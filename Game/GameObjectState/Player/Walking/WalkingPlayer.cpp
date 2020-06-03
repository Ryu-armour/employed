#include "WalkingPlayer.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameObjectState\Player\PlayerState.h"


WalkingPlayer::WalkingPlayer(Player * player)
{
	//変数の初期化
	m_player = player;
	m_stateName = L"WalkingState";
}

WalkingPlayer::~WalkingPlayer()
{
	Finalize();
}

void WalkingPlayer::Initialize()
{
	//当たり判定の色のリセット
	m_player->SetColor(DirectX::Colors::Yellow);
}

void WalkingPlayer::Update()
{
	//移動
	MovePlayer();
}

void WalkingPlayer::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
	DirectX::SimpleMath::Matrix world = m_player->GetWorld();
	
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void WalkingPlayer::Finalize()
{
}

//プレイヤーの移動
void WalkingPlayer::MovePlayer()
{
	//ベクトルのリセット
	m_player->SetVel(DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f));

	//入力にされたキーによってVelocityを入れる
	AssignVelocity();

	//カメラの向きを適用
	m_player->SetVel(DirectX::SimpleMath::Vector3::Transform(m_player->GetVel(), DirectX::SimpleMath::Matrix::CreateRotationY(-FollowCamera::GetInstance()->GetYAngle())));

	//現在の位置に速度を足す
	m_player->SetPos(m_player->GetPos() + m_player->GetVel());
	
	//プレイヤーのワールドに適用
	m_player->ApplyWorld();
}

//入力されたキーによってVelocityを入れる
void WalkingPlayer::AssignVelocity()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//右
	if (keyState.IsKeyDown(DirectX::Keyboard::D))
		m_player->GetVel().x = 0.1f;

	//左
	if (keyState.IsKeyDown(DirectX::Keyboard::A))
		m_player->GetVel().x = -0.1f;

	//奥
	if (keyState.IsKeyDown(DirectX::Keyboard::W))
		m_player->GetVel().z = -0.1f;

	//手前
	if (keyState.IsKeyDown(DirectX::Keyboard::S))
		m_player->GetVel().z = 0.1f;

	//歩き状態以外は以降の処理を飛ばす
	if (m_player->GetState() != PlayerStateClass::GetInstance()->GetState(Player::WALKING))
		return;

	//AttackStateへ移動
	if (DirectX::Mouse::Get().GetState().leftButton)
 		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::ATTACK));

	//StandingStateへ移動
	if (m_player->GetVel() == DirectX::SimpleMath::Vector3::Zero)
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::STANDING));
}