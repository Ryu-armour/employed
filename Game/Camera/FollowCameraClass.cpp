#include "FollowCameraClass.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\GameObject\GameObject.h"


FollowCamera* FollowCamera::GetInstance()
{
	static FollowCamera camera;
	return &camera;
}

FollowCamera::FollowCamera(bool is_gom) : TARGET_TO_EYE_VEC(DirectX::SimpleMath::Vector3(0.0f, 2.0f, 5.0f))
{
	m_is_gom = is_gom;
}

void FollowCamera::motion(int x, int y)
{
	// �}�E�X�|�C���^�̑O�񂩂�̕ψ�
	float dx = static_cast<float>(x);
	float dy = static_cast<float>(y);

	if (dx != 0.0f || dy != 0.0f)
	{
		// �x���̉�]
		float yAngle = dx * DirectX::XM_PI / 180.0f;																																																																																		
		
		// �w���̉�]
		float xAngle = dy * DirectX::XM_PI / 180.0f;

		m_xAngle += xAngle;
		m_yAngle += yAngle;

		//�J�����̃A���O���͈̔͂��w��
		m_xAngle = Clamp(m_xAngle, DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(45.0f));
	}
}

void FollowCamera::Init(GameObject* subject,float angle,
	DirectX::SimpleMath::Vector3 up)
{
	//�ϐ��̏�����
	m_subject = subject;
	m_target = m_subject->GetPos();
	m_up = up;

	//�E�B���h�E�T�C�Y�������Ă���
	RECT size = ResourceManager::GetInstance()->GetDeviceResources()->GetOutputSize();

	//�A�X�y�N�g����Z�o����
	float aspectRatio = float(size.right) / float(size.bottom);

	//�A���O�������W�A���p�ɕϊ����ă����o�ϐ��ɃZ�b�g
	SetAngle(angle);

	//�}�g���N�X�s��ɔ��f
	ReflectionMatrix(aspectRatio);
}

void FollowCamera::Update()
{
	//�J�����̉�]
	auto state = DirectX::Mouse::Get().GetState();

	//�g���b�J�[�̍X�V
	m_tracker.Update(state);

	//�A���O���̍쐬
	motion(state.x / 2, state.y / 2);

	// �r���[�s����Z�o����
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_yAngle);
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(m_xAngle);

	//��]�s��̍쐬
	DirectX::SimpleMath::Matrix rt = rotY * rotX;
	//���_
	DirectX::SimpleMath::Vector3 eye(TARGET_TO_EYE_VEC);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//���_�ɂ�]
	m_eye = DirectX::SimpleMath::Vector3::Transform(eye, rt.Invert());
	//�^�[�Q�b�g�ɒǏ]
	m_eye += m_target;
	//�����_���^�[�Q�b�g��菭����ɂ��炷
	if (m_subject)
	{
		m_target = m_subject->GetPos();
		m_target -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, -4.0f, -4.0f), rt.Invert());
	}

	//�r���[�s��̍쐬
	m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
	//�S��
	if (m_is_gom)
	{
		m_target += (m_refTargetPos - m_target) * 0.05f;
		m_eye += (m_refEyePos - m_eye) * 0.05f;
	}
}

void FollowCamera::ReflectionMatrix(float aspectRatio)
{
	//�v���W�F�N�V�����s�������ăZ�b�g
	m_projMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		m_fovAngleY, aspectRatio, 0.01f, 1000.0f);
}

float FollowCamera::Clamp(const float & value, const float & min, const float & max)
{
	//�w��͈̔͂ŕԂ�
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
