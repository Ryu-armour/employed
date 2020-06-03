#include "StandingPlayer.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameObjectState\Player\PlayerState.h"


StandingPlayer::StandingPlayer(Player* player)
{
	//�����l�̑��
	m_player = player;
	m_stateName = L"StandingState";
}

StandingPlayer::~StandingPlayer()
{
	Finalize();
}

void StandingPlayer::Initialize()
{
	//�����蔻��̐F�̃��Z�b�g
	m_player->SetColor(DirectX::Colors::Yellow);
}

void StandingPlayer::Update()
{
	//�L�[�{�[�h�̎擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//�L�[�ɑΉ�����State�Ɉړ�
	if (keyState.A || keyState.D || keyState.W || keyState.S)
	{
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::WALKING));
	}
	
	if (DirectX::Mouse::Get().GetState().leftButton)
	{
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::ATTACK));
	}
}

void StandingPlayer::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	DirectX::SimpleMath::Matrix world = m_player->GetWorld();

	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void StandingPlayer::Finalize()
{
}