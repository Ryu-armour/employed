#include "Enemy.h"

#include "Game\Common\MyKeyBoard.h"
#include "Game\Common\ResourcesManager.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\GameObjectState\Enemy\EnemyState.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* player) : m_life(3),m_angle(0.0f),m_quaternion(DirectX::SimpleMath::Vector3::Zero, 0.0f),
is_invincibility(false), m_vel(DirectX::SimpleMath::Vector3::Zero),m_player(player)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
	//�����o�ϐ��̏�����
	ApplyWorld();

	//���f���̍쐬
	m_model = std::make_unique <DirectX::Model>();
	CreateModel();

	//�e�X�e�[�g�̐���
	m_gethurt = std::make_unique<GetHurtEnemy>(this);
	m_walk = std::make_unique<WalkingEnemy>(this);
	m_search = std::make_unique<SearchingEnemy>(this);

	//State���Z�b�g
	EnemyState* enemyState = EnemyState::GetInstance();
	enemyState->Add(EnemyState::GetHurt, std::move(std::make_unique<GetHurtEnemy>(this)));
	enemyState->Add(EnemyState::Walking, std::move(std::make_unique<WalkingEnemy>(this)));
	enemyState->Add(EnemyState::Search, std::move(std::make_unique<SearchingEnemy>(this)));

	//����State�̐ݒ�
	ChangeState(m_search.get());

	//�����蔻��̍쐬
	m_hurtBox = std::make_unique<Sphere>(this, HURT_SIZE);
	m_hurtBox->SetPos(this->GetPos());
	m_hurtBox->SetTag(Collider::COLLIDER_TAG::HURTENEMY);
	m_hurtBox->SetCollide(true);
	
	m_hitBox = std::make_unique<Sphere>(this, HIT_SIZE);
	m_hitBox->SetPos(this->GetPos());
	m_hitBox->SetTag(Collider::COLLIDER_TAG::HITENEMY);
	m_hitBox->SetCollide(true);
}

//�X�V
void Enemy::Update()
{
	//���݂�State�̍X�V
	m_state->Update();

	//�����蔻��̍X�V
	m_hitBox->SetPos(m_pos);
	m_hurtBox->SetPos(m_pos);

	//�����蔻��̃}�l�[�W���[�ɓo�^
	CollisionManager::GetInstance()->Add("HITENEMY", m_hitBox.get());
	CollisionManager::GetInstance()->Add("HURTENEMY", m_hurtBox.get());

	//HP��0�ɂȂ����玩��
	if (!m_life)
	{
		ToParaphernalia();
	}

	//����
	DirectX::SimpleMath::Vector3 axis = { 0.0f, 1.0f, 0.0f };
	m_quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(m_angle));

	//���[���h���W�̍X�V
	m_world = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion);
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}

//�`��
void Enemy::Render()
{
	//�����蔻��̕`��(�f�o�b�O)
	m_state->Render(m_model.get());
}

//�I������
void Enemy::Finalize()
{

}

//�t�@�C���ǂݍ���
void Enemy::ReadFile()
{

}

//�Փ˔���
void Enemy::OnCollision(GameObject* gameObject, Collider* designation)
{
	if (designation)
	{
		//����Ɠ��������ۂ̏���(���G��ԂłȂ��Ƃ�)
		if (designation->GetTag() == Collider::COLLIDER_TAG::SWORD && !is_invincibility)
		{
			//�m�b�N�o�b�N
			KickBack(gameObject->GetPos());
			//��_���[�W��Ԃɂ���
			ChangeState(m_gethurt.get());
		}
		//�G�l�~�[���m�œ��������ۂ̏���
		else if (designation->GetTag() == Collider::COLLIDER_TAG::HURTENEMY)
		{
			//�d�Ȃ�Ȃ��悤�ɂ���
			OnColliderToFamiry(gameObject);
		}
	}
}

//���G��
void Enemy::ToInvincible()
{
	is_invincibility = true;
	//�����蔻������Ȃ���Ԃɂ���
	m_hurtBox->SetCollide(!is_invincibility);
	//���C�t�����炷
	m_life--;
}

//���G������
void Enemy::UnlockInvicinble()
{
	is_invincibility = false;
	//�����蔻�������Ԃɂ���
	m_hurtBox->SetCollide(!is_invincibility);
}

//����
void Enemy::Move()
{
	//�ړ�
	m_pos += m_vel;
	m_hitBox->SetPos(m_pos);
	m_hurtBox->SetPos(m_pos);
}

//�G�l�~�[���m�̏Փˏ���
void Enemy::OnColliderToFamiry(GameObject* famiry)
{
	//�����Ɠ��������ꍇ�y������������

}

//���f���̍쐬
void Enemy::CreateModel()
{
	//���f���̍쐬
	m_model = DirectX::Model::CreateFromCMO(
		ResourceManager::GetInstance()->GetDevice(),
		ResourceManager::GetInstance()->GetModelData("Enemy"),
		*ResourceManager::GetInstance()->GetModelPath());
}

//�m�b�N�o�b�N
void Enemy::KickBack(const DirectX::SimpleMath::Vector3& objPos)
{
	//�����Ƒ���̋��������߂�
	DirectX::SimpleMath::Vector3 distance = DirectX::SimpleMath::Vector3::Zero;
	distance.x = objPos.x - m_pos.x;
	distance.z = objPos.z - m_pos.z;
	distance.Normalize();
	//�m�b�N�o�b�N
	m_pos -= distance * BACK;
	ApplyWorld();
}

void Enemy::ApplyDirection()
{
	//��]�����쐬
	DirectX::SimpleMath::Vector3 axis = {0.0f, 1.0f, 0.0f};
	//�p�x(���W�A���p)
	float angle = DirectX::XMConvertToRadians(m_angle);

	//Quaternion�̍쐬
	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);
}
