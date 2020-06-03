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
	// マウスポインタの前回からの変位
	float dx = static_cast<float>(x);
	float dy = static_cast<float>(y);

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * DirectX::XM_PI / 180.0f;																																																																																		
		
		// Ｘ軸の回転
		float xAngle = dy * DirectX::XM_PI / 180.0f;

		m_xAngle += xAngle;
		m_yAngle += yAngle;

		//カメラのアングルの範囲を指定
		m_xAngle = Clamp(m_xAngle, DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(45.0f));
	}
}

void FollowCamera::Init(GameObject* subject,float angle,
	DirectX::SimpleMath::Vector3 up)
{
	//変数の初期化
	m_subject = subject;
	m_target = m_subject->GetPos();
	m_up = up;

	//ウィンドウサイズを持ってくる
	RECT size = ResourceManager::GetInstance()->GetDeviceResources()->GetOutputSize();

	//アスペクト比を算出する
	float aspectRatio = float(size.right) / float(size.bottom);

	//アングルをラジアン角に変換してメンバ変数にセット
	SetAngle(angle);

	//マトリクス行列に反映
	ReflectionMatrix(aspectRatio);
}

void FollowCamera::Update()
{
	//カメラの回転
	auto state = DirectX::Mouse::Get().GetState();

	//トラッカーの更新
	m_tracker.Update(state);

	//アングルの作成
	motion(state.x / 2, state.y / 2);

	// ビュー行列を算出する
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_yAngle);
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(m_xAngle);

	//回転行列の作成
	DirectX::SimpleMath::Matrix rt = rotY * rotX;
	//視点
	DirectX::SimpleMath::Vector3 eye(TARGET_TO_EYE_VEC);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//視点にを転
	m_eye = DirectX::SimpleMath::Vector3::Transform(eye, rt.Invert());
	//ターゲットに追従
	m_eye += m_target;
	//注視点をターゲットより少し上にずらす
	if (m_subject)
	{
		m_target = m_subject->GetPos();
		m_target -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, -4.0f, -4.0f), rt.Invert());
	}

	//ビュー行列の作成
	m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
	//ゴム
	if (m_is_gom)
	{
		m_target += (m_refTargetPos - m_target) * 0.05f;
		m_eye += (m_refEyePos - m_eye) * 0.05f;
	}
}

void FollowCamera::ReflectionMatrix(float aspectRatio)
{
	//プロジェクション行列を作ってセット
	m_projMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		m_fovAngleY, aspectRatio, 0.01f, 1000.0f);
}

float FollowCamera::Clamp(const float & value, const float & min, const float & max)
{
	//指定の範囲で返す
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
