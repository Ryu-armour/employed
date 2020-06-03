#include "WalkingPlayer.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameObjectState\Player\PlayerState.h"


WalkingPlayer::WalkingPlayer(Player * player)
{
	//�ϐ��̏�����
	m_player = player;
	m_stateName = L"WalkingState";
}

WalkingPlayer::~WalkingPlayer()
{
	Finalize();
}

void WalkingPlayer::Initialize()
{
	//�����蔻��̐F�̃��Z�b�g
	m_player->SetColor(DirectX::Colors::Yellow);
}

void WalkingPlayer::Update()
{
	//�ړ�
	MovePlayer();
}

void WalkingPlayer::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
	DirectX::SimpleMath::Matrix world = m_player->GetWorld();
	
	model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), world,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void WalkingPlayer::Finalize()
{
}

//�v���C���[�̈ړ�
void WalkingPlayer::MovePlayer()
{
	//�x�N�g���̃��Z�b�g
	m_player->SetVel(DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f));

	//���͂ɂ��ꂽ�L�[�ɂ����Velocity������
	AssignVelocity();

	//�J�����̌�����K�p
	m_player->SetVel(DirectX::SimpleMath::Vector3::Transform(m_player->GetVel(), DirectX::SimpleMath::Matrix::CreateRotationY(-FollowCamera::GetInstance()->GetYAngle())));

	//���݂̈ʒu�ɑ��x�𑫂�
	m_player->SetPos(m_player->GetPos() + m_player->GetVel());
	
	//�v���C���[�̃��[���h�ɓK�p
	m_player->ApplyWorld();
}

//���͂��ꂽ�L�[�ɂ����Velocity������
void WalkingPlayer::AssignVelocity()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//�E
	if (keyState.IsKeyDown(DirectX::Keyboard::D))
		m_player->GetVel().x = 0.1f;

	//��
	if (keyState.IsKeyDown(DirectX::Keyboard::A))
		m_player->GetVel().x = -0.1f;

	//��
	if (keyState.IsKeyDown(DirectX::Keyboard::W))
		m_player->GetVel().z = -0.1f;

	//��O
	if (keyState.IsKeyDown(DirectX::Keyboard::S))
		m_player->GetVel().z = 0.1f;

	//������ԈȊO�͈ȍ~�̏������΂�
	if (m_player->GetState() != PlayerStateClass::GetInstance()->GetState(Player::WALKING))
		return;

	//AttackState�ֈړ�
	if (DirectX::Mouse::Get().GetState().leftButton)
 		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::ATTACK));

	//StandingState�ֈړ�
	if (m_player->GetVel() == DirectX::SimpleMath::Vector3::Zero)
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(Player::STANDING));
}