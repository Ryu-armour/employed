#pragma once


class GameObject;


class FollowCamera
{
//�萔
public:
	const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

//�����o�ϐ�
private:
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;
	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projMatrix;
	//�A�C
	DirectX::SimpleMath::Vector3 m_eye;
	//�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_target;
	//�A�b�v
	DirectX::SimpleMath::Vector3 m_up;
	//�Q�Ǝ��_
	DirectX::SimpleMath::Vector3 m_refEyePos;
	//�Q�ƒ����_
	DirectX::SimpleMath::Vector3 m_refTargetPos;
	//�A���O��Y
	float						 m_fovAngleY;
	//�^�[�Q�b�g
	GameObject*					 m_subject;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;
	// ����]
	float m_yAngle;
	// �c��]
	float m_xAngle;
	//�J������Ǐ]���S���ɂ��邩
	bool m_is_gom;

//�����o�֐�
private:
	//�R���X�g���N�^
	FollowCamera(bool is_gom = true);
	//�s��̌v�Z
	void motion(int x, int y);
	//�A���O�����Z�b�g
	void SetAngle(float angle) { m_fovAngleY = DirectX::XMConvertToRadians(angle); }
	//�v���W�F�N�V�����s������
	void ReflectionMatrix(float aspectRatio);
	//�N�����v
	float Clamp(const float& value, const float& min, const float& max);

//�����o�֐�
public:
	//�C���X�^���X�̎擾
	static FollowCamera* GetInstance();
	//������
	void Init(GameObject* subject,float angle,
		DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Zero);
	//�X�V
	void Update();
	//�r���[�s���Ԃ�
	DirectX::SimpleMath::Matrix GetViewMatrix();
	//�}�g���N�X�s���Ԃ�
	DirectX::SimpleMath::Matrix GetProjMatrix();
	//�^�[�Q�b�g�̃|�W�V�������Z�b�g����
	void SetTargetPos(DirectX::SimpleMath::Vector3 targetPos);
	//���_�̃Z�b�g
	void SetEyePos(DirectX::SimpleMath::Vector3 eye);
	//
	void SetRefEyePos(DirectX::SimpleMath::Vector3 refEyePos) {m_refEyePos = refEyePos;}
	//
	void SetRefTargetPos(DirectX::SimpleMath::Vector3 refTargetPos) { m_refTargetPos = refTargetPos; }

	DirectX::SimpleMath::Vector3 GetEyePosition() { return m_eye; }

	const void SetObject(GameObject* obj);
	float& GetYAngle();
};

inline DirectX::SimpleMath::Matrix FollowCamera::GetViewMatrix()
{
	return m_viewMatrix;
}

inline DirectX::SimpleMath::Matrix FollowCamera::GetProjMatrix() 
{
	return m_projMatrix; 
}

inline void FollowCamera::SetEyePos(DirectX::SimpleMath::Vector3 eye) 
{
	m_eye = eye;
}

inline void FollowCamera::SetTargetPos(DirectX::SimpleMath::Vector3 targetPos) 
{
	m_target = targetPos; 
}

inline const void FollowCamera::SetObject(GameObject* obj)
{
	m_subject = obj;
}

inline float& FollowCamera::GetYAngle()
{
	return m_yAngle;
}