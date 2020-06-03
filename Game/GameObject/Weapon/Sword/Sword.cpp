#include "Sword.h"

#include <fstream>
#include <istream>

#include "3rdParty\Picojson\picojson.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameObjectState\Sword\SwordState.h"
#include "Game\GameObjectState\Sword\SwordStateList.h"


//�萔�̏�����
const DirectX::SimpleMath::Vector3 Sword::COLLIDER_ADJUSTMENT = { 0.0f, 0.0f, -1.0f };

//�R���X�g���N�^
Sword::Sword(Player* user) : m_user(user),m_color(DirectX::Colors::Yellow)
{
}

//������
void Sword::Initialize()
{
	//Json�t�@�C�����J��
	ReadFile();

	//�ϐ��̏�����
	is_drawPrimitive = false;

	//�����蔻��̍쐬
	m_collider = std::make_unique<Capsule>(this, 2.0f, 1.0f, false);
	m_collider->SetPos(m_user->GetPos() + COLLIDER_ADJUSTMENT);
	m_collider->SetTag(Collider::COLLIDER_TAG::SWORD);
	m_collider->SetCollide(false);

	//�����蔻��̐F�̃��Z�b�g
	m_color = DirectX::Colors::Yellow;

	//State���Z�b�g
	SwordState* swordState = SwordState::GetInstance();
	swordState->Add(WAIT, std::make_unique<WaitSword>(this));
	swordState->Add(ATTACK, std::make_unique<AttackSword>(this));

	//����State�̐ݒ�
	ChangeState(swordState->GetState(WAIT));

	//����̍쐬
	CreateModel();
}

//�X�V
void Sword::Update()
{
	//���݂̏�Ԃ̍X�V
	m_state->Update();

	//�����蔻��̃}�l�[�W���[�ɓo�^
	CollisionManager::GetInstance()->Add("WEAPON", m_collider.get());

	//E�L�[�Ńv���~�e�B�u�`��t���O�𔽓]
	if (MyKeyBoard::GetInstance()->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawPrimitive = !is_drawPrimitive;
	}

	//�����蔻��̍X�V
	m_collider->SetPos(m_user->GetPos() + COLLIDER_ADJUSTMENT);
}

//�`��
void Sword::Render()
{
	//���̎擾
	FollowCamera* camera = FollowCamera::GetInstance();

	//���݂̏�Ԃ�`��
	m_state->Render(m_model.get());

	//�����蔻��̕`��
	if (is_drawPrimitive)
	{
		DirectX::SimpleMath::Matrix mat = DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPos());
		m_collider->Draw(mat, camera->GetViewMatrix(), camera->GetProjMatrix(), m_color);
	}
}

//�I������
void Sword::Finalize()
{
	//���݂̏�Ԃ̔j��
	SwordState::GetInstance()->AllDelete();
}

//Json�t�@�C�����J��
void Sword::ReadFile()
{
	//�t�@�C���̓ǂݍ���
	std::ifstream ifs("Game\\Resources\\Json\\Weapon.json");

	//���s����
	//assert(ifs.is_open && "file is not open");

	//�ϐ��錾
	picojson::value value;

	//�t�@�C�����J��
	ifs >> value;

	//�f�[�^�̎g�p
	picojson::object& root = value.get<picojson::object>();

	//���̎擾
	picojson::object sword = root["Sword"].get<picojson::object>();
	std::string parent = sword["parent"].get<std::string>();
	picojson::array pos = sword["displacement"].get<picojson::array>();
	SetSize((float)sword["size"].get<double>());
	picojson::array color = sword["color"].get<picojson::array>();
	
	//�t�@�C�������
	ifs.close();
}

//�Փ˔���
void Sword::OnCollision(GameObject* gameObject, Collider* designation)
{
	//�R���C�_�[�̐F��ς���
	if (designation->GetTag() == Collider::COLLIDER_TAG::HURTENEMY)
	{
		m_color = DirectX::Colors::Red;
	}
	gameObject;
}

//��Ԃ̐؂�ւ�
void Sword::ChangeState(IState * state)
{
	//��Ԃ̐؂�ւ�
	m_state = state;
	m_state->Initialize();
}

//�U��
void Sword::Attack()
{
	//�����蔻�������Ԃɂ���
	m_collider->SetCollide(true);

	//����U��
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
}

//�U����Ԃ�
void Sword::ToAttack()
{
	//�U����Ԃ�
	ToAttackState();
	//�����蔻�������Ԃ�
	m_collider->SetCollide(true);
	//�F��ς���
	m_color = DirectX::Colors::Red;
	//�X�e�[�g�̐؂�ւ�
	ChangeState(SwordState::GetInstance()->GetState(ATTACK));
}

//�ҋ@��Ԃ�
void Sword::ToStay()
{
	//�ҋ@��Ԃ�
	ToStayState();
	//�����蔻����Ƃ�Ȃ���Ԃ�
	m_collider->SetCollide(false);
	//�F��ς���
	m_color = DirectX::Colors::Blue;
	//�X�e�[�g�̐؂�ւ�
	ChangeState(SwordState::GetInstance()->GetState(WAIT));
}

//���f���̍쐬
void Sword::CreateModel()
{
	//�ϐ��̏���
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_model = std::make_unique<DirectX::Model>();
	
	//���f���̍쐬
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Sword"),
		*resourceManager->GetModelPath());
}