#include "AttackPlayer.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\GameObject\Player\Player.h"
#include "Game\GameObject\Player\ArmR\ArmR.h"
#include "Game\GameObject\Weapon\Sword\Sword.h"

#include "Game\GameObjectState\Player\PlayerState.h"
#include "Game\GameObjectState\Sword\SwordState.h"


AttackPlayer::AttackPlayer(Player * player): m_direction(false)
{
	//�ϐ��̏�����
	m_player = player;
	m_stateName = L"AtackState";
}

AttackPlayer::~AttackPlayer()
{
	Finalize();
}

void AttackPlayer::Initialize()
{
	//�J�E���g�̃��Z�b�g
	m_attackCount = 0;

	//�t���O�̐؂�ւ�
	m_direction = !m_direction;

	//������U����Ԃ�
	m_player->GetSword()->ToAttack();

	//�ʒu�̏�����
	m_armPos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.6f);
}

void AttackPlayer::Update()
{
	//����U��
	Swing();

	//�ړ�
	m_player->Move();

	if (m_attackCount >= ATTACK_TIME)
	{
		//�J�E���g�̃��Z�b�g
		m_attackCount = 0;
		//�����ҋ@������
		m_player->GetSword()->ToStay();
		//��Ԃ̑J��
		m_player->ChangeState(PlayerStateClass::GetInstance()->GetState(m_player->WALKING));
	}
}

void AttackPlayer::Render(DirectX::Model* model)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//���f���̕`��
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
	//�r�̉�]�s��
	DirectX::SimpleMath::Matrix rot;

	//�J�E���g�̍X�V
	m_attackCount++;

	//�U�鏈��
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