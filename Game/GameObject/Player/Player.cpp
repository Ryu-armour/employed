#include "Player.h"

#include "Game\Common\ResourcesManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\GameObject\Player\Player.h"
#include "Game\GameObject\Weapon\Sword\Sword.h"
#include "Game\GameObject\Manager\GameObjectManager.h"

#include "Game\GameObjectState\Player\PlayerState.h"
#include "Game\GameObjectState\Player\PlayerStateList.h"

#include "Game\GameScene\Manager\SceneManager.h"

const DirectX::SimpleMath::Vector3 Player::ARMR_ADJUSTMENT = { 0.7f, 1.0f,0.0f };


Player::Player() : m_vel{0.0f, 0.0f, 0.0f},m_blowAwayVec{0.0f, 0.0f, 0.0f},
m_angle(0.0f),is_drawPrimitive(false),is_invincibility(false), 
m_invincibilityCount(INVINCIBLE_TIME),m_invincibleTime(INVINCIBLE_TIME)
{
}

Player::~Player()
{
}

//������
void Player::Initialize()
{	
	//Json�t�@�C���̓ǂݍ���
	ReadFile();

	//���f���̍쐬
	m_model = std::make_unique<DirectX::Model>();
	CreateModel();

	//���[���h�s��ɓK�p
	ApplyWorld();

	//�����蔻��̍쐬
	m_collider = std::make_unique<Sphere>(this, 0.75f);
	m_collider->SetPos(this->GetPos());
	m_collider->SetCollide(Collider::COLLIDER_TAG::PLAYER);
	m_collider->SetCollide(true);
	m_color = DirectX::Colors::Yellow;

	//�^�O�̐ݒ�
	SetTag(GAMEOBJECT_TAG::PLAYER);
	
	//State���Z�b�g
	PlayerStateClass* playerState = PlayerStateClass::GetInstance();
	playerState->Add(STANDING,std::move(std::make_unique<StandingPlayer>(this)));
	playerState->Add(WALKING, std::move(std::make_unique<WalkingPlayer>(this)));
	playerState->Add(ATTACK,  std::move(std::make_unique<AttackPlayer>(this)));
	playerState->Add(DAMAGE,  std::move(std::make_unique<GetHurtPlayer>(this)));

	//����State�̐ݒ�
	m_state = playerState->GetState(STANDING);

}

//�X�V
void Player::Update()
{
	//�����蔻��̍X�V
	m_collider->SetPos(m_pos);

	//�����蔻��̃}�l�[�W���[�ɓo�^
	CollisionManager::GetInstance()->Add("PLAYER", m_collider.get());

	//HP��0�ɂȂ����玩��
	if (!m_life)
	{
		//�J�����̃^�[�Q�b�g��null��
		FollowCamera::GetInstance()->SetObject(nullptr);
		//�s�v��Ԃɂ���
		ToParaphernalia();
		//�V�[���J��
		SceneManager::GetInstance()->RequestScene(SCENE_FAILURE);
	}

	//���G�J�E���g�̍X�V
	if (is_invincibility)
	{
		//�J�E���g�̍X�V
		m_invincibilityCount--;

		//�_��
		Flash();

		//���Ԃ��؂ꂽ�疳�G�Ɠ_�ŉ���
		if (m_invincibilityCount == 0)
		{
			is_invincibility = false;
			is_drawModel = true;
		}
	}

	//�p�[�c�̍��W�̍X�V
	m_armR->SetPos(m_pos + ARMR_ADJUSTMENT);
	m_armR->SetWorld(DirectX::SimpleMath::Matrix::CreateTranslation(ARMR_ADJUSTMENT) * m_world);

	//���݂�State�̎��s
	m_state->Update();

	//�J�����̕����Ɍ�������
	FaceCamera();

	//E�L�[�Ńv���~�e�B�u�`��t���O�𔽓]
	if (MyKeyBoard::GetInstance()->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawPrimitive = !is_drawPrimitive;
	}
}

//�`��
void Player::Render()
{
	//��Ԃ̕`��
	if(is_drawModel)
		m_state->Render(m_model.get());

	//�v���~�e�B�u�̕`��
	if (is_drawPrimitive)
	{
		FollowCamera* camera = FollowCamera::GetInstance();
		DirectX::SimpleMath::Matrix world = m_world * DirectX::SimpleMath::Matrix::CreateTranslation(0.0f, 1.0f, 0.0f);
		m_collider->Draw(world, camera->GetViewMatrix(), camera->GetProjMatrix(), m_color);
	}
}

//�I������
void Player::Finalize()
{
	//�X�e�[�g�����폜
	PlayerStateClass::GetInstance()->AllDelete();
}

//Json�t�@�C�����J��
void Player::ReadFile()
{
	//�t�@�C���̓ǂݍ���
	std::ifstream ifs("Game\\Resources\\Json\\Player.json");

	//���s����
	//assert(ifs.is_open && "file is not open");

	//�ϐ��錾
	picojson::value value;

	//�t�@�C�����J��
	ifs >> value;

	//�f�[�^�̎g�p
	picojson::object& root  = value.get<picojson::object>();
	
	//���̎擾
	picojson::array	 pos	= root["position"].get<picojson::array>();
	m_life					= (int)   root["life"].get<double>();
	m_size					= (float) root["size"].get<double>();
	m_pos.x					= (float) pos[0].get<double>();
	m_pos.y					= (float) pos[1].get<double>();
	m_pos.z					= (float) pos[2].get<double>();

	//�t�@�C�������
	ifs.close();
}

//�Փˎ�
void Player::OnCollision(GameObject* gameObject, Collider* designation)
{
	if (designation)
	{
		//�G�Ɠ��������ۂ̏Փˏ���(���G��ԂłȂ��Ƃ�)
		if (designation->GetTag() == Collider::COLLIDER_TAG::HITENEMY && !is_invincibility)
		{
			//�_���[�W���󂯂�
			m_color = DirectX::Colors::Red;
			m_life--;
			//�m�b�N�o�b�N�̃x�N�g�����쐬
			KickBack(gameObject->GetPos());
			//�X�e�[�g�̑J��
			ChangeState(PlayerStateClass::GetInstance()->GetState(DAMAGE));
		}
	}
	gameObject;
}

void Player::ToInvincible()
{
	//���G��Ԃɂ���
	is_invincibility = true;
	//�����蔻������Ȃ���Ԃɂ���
	m_collider->SetCollide(!is_invincibility);
}

//���G��ԉ���
void Player::UnlockInvicinble()
{
	//���G����
	is_invincibility = false;
	//�����蔻�������Ԃɂ���
	m_collider->SetCollide(!is_invincibility);
}

//�����̍X�V
void Player::Move()
{
	PlayerStateClass::GetInstance()->GetState(WALKING)->Update();
}

void Player::Flash()
{
	if (m_invincibilityCount % 10 == 0)
	{
		is_drawModel = !is_drawModel;
	}
}

//��Ԃ̐؂�ւ�
void Player::ChangeState(IState * state)
{
	m_state = state;
	m_state->Initialize();
}

//���f���̍쐬
void Player::CreateModel()
{
	//�쐬
	m_model = DirectX::Model::CreateFromCMO(
		ResourceManager::GetInstance()->GetDevice() ,
		ResourceManager::GetInstance()->GetModelData("Player"),
		*ResourceManager::GetInstance()->GetModelPath());
}

//�m�b�N�o�b�N
void Player::KickBack(const DirectX::SimpleMath::Vector3& objPos)
{
	//�����Ƒ���̋��������߂�
	DirectX::SimpleMath::Vector3 relativePos = m_pos - objPos;
	relativePos.Normalize();

	//�����o�ϐ��Ɋi�[
	m_blowAwayVec = relativePos;
}

//�J�����̌������v���C���[�ɓK�p
void Player::FaceCamera()
{
	m_angle = -FollowCamera::GetInstance()->GetYAngle();
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}