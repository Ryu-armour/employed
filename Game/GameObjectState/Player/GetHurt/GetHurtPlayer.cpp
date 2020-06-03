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
	//�J�E���g�̃��Z�b�g
	m_count = 0;
	//������ԃx�N�g��������
	m_blowAwayVec = m_player->GetBlowAwayVec();
	//���G���
	m_player->ToInvincible();
	//�R���C�_�[�̐F��ύX
	m_player->SetColor(DirectX::Colors::Silver);
	//�U����Ԃ�����
	m_player->GetSword()->ToStay();
}

void GetHurtPlayer::Update()
{
	//�J�E���g�̍X�V
	m_count++;

	//����
	//m_player->Move();

	//�������
	KickBack();

	//�V�[���J��
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

		//���f���̕`��
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
	//������ԃx�N�g��
	m_blowAwayVec *= 0.7f;

	//�������
	m_player->SetPos(m_player->GetPos() + m_blowAwayVec);
}