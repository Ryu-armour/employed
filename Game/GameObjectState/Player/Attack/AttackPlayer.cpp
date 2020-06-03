#include "AttackPlayer.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\GameObject\Player\Player.h"
#include "Game\GameObject\Player\ArmR\ArmR.h"
#include "Game\GameObject\Weapon\Sword\Sword.h"

#include "Game\GameObjectState\Player\PlayerState.h"
#include "Game\GameObjectState\Sword\SwordState.h"


AttackPlayer::AttackPlayer(Player * player): m_direction(false)
{
	//変数の初期化
	m_player = player;
	m_stateName = L"AtackState";
}

AttackPlayer::~AttackPlayer()
{
	Finalize();
}

void AttackPlayer::Initialize()
{
	//カウントのリセット
	m_attackCount = 0;

	//フラグの切り替え
	m_direction = !m_direction;

	//武器を攻撃状態に
	m_player->GetSword()->ToAttack();

	//位置の初期化
	m_armPos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.6f);
}

void AttackPlayer::Update()
{
	//剣を振る
	Swing();

	//移動
	m_player->Move();

	if (m_attackCount >= ATTACK_TIME)
	{
		//カウントのリセット
		m_attackCount = 0;
		//武器を待機させる
		m_player->GetSword()->ToStay();
		//状態の遷移
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(m_player->WALKING));
	}
}

void AttackPlayer::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの描画
	DirectX::SimpleMath::Matrix world = m_player->GetWorld();

	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void AttackPlayer::Finalize()
{
}

void AttackPlayer::Swing()
{
	//腕の回転行列
	DirectX::SimpleMath::Matrix rot;

	//カウントの更新
	m_attackCount++;

	//振る処理
	if (m_attackCount < ATTACK_TIME - 20)
	{

		rot = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-static_cast<float>(m_attackCount * 20.0f)));
		
		//m_armPos += DirectX::SimpleMath::Vector3(0.0f,0.0f,-0.1f);
		if (m_direction)
		{
			//rot *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(static_cast<float>(m_attackCount * 10.0f)));
			//m_armPos += DirectX::SimpleMath::Vector3(-0.1f,-0.1f,0.1f);
		}
		else
		{
			//rot *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-static_cast<float>(m_attackCount * 10.0f)));
			//m_armPos += DirectX::SimpleMath::Vector3(0.1f, -0.1f, 0.1f);
		}

		//if(rot != DirectX::SimpleMath::Matrix::Identity)
		m_player->GetArmR()->SetWorld(rot * m_player->GetArmR()->GetWorld());
		//m_player->GetArmR()->SetWorld(rot * m_player->GetArmR()->GetWorld());
		//m_player->GetArmR()->SetWorld(DirectX::SimpleMath::Matrix::CreateTranslation(m_armPos) * m_player->GetArmR()->GetWorld());
	}
}