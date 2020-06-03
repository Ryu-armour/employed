#pragma once


class GameObject;


class FollowCamera
{
//定数
public:
	const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

//メンバ変数
private:
	//ビュー行列
	DirectX::SimpleMath::Matrix m_viewMatrix;
	//プロジェクション行列
	DirectX::SimpleMath::Matrix m_projMatrix;
	//アイ
	DirectX::SimpleMath::Vector3 m_eye;
	//ターゲット
	DirectX::SimpleMath::Vector3 m_target;
	//アップ
	DirectX::SimpleMath::Vector3 m_up;
	//参照視点
	DirectX::SimpleMath::Vector3 m_refEyePos;
	//参照注視点
	DirectX::SimpleMath::Vector3 m_refTargetPos;
	//アングルY
	float						 m_fovAngleY;
	//ターゲット
	GameObject*					 m_subject;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
	// 横回転
	float m_yAngle;
	// 縦回転
	float m_xAngle;
	//カメラを追従をゴムにするか
	bool m_is_gom;

//メンバ関数
private:
	//コンストラクタ
	FollowCamera(bool is_gom = true);
	//行列の計算
	void motion(int x, int y);
	//アングルをセット
	void SetAngle(float angle) { m_fovAngleY = DirectX::XMConvertToRadians(angle); }
	//プロジェクション行列を作る
	void ReflectionMatrix(float aspectRatio);
	//クランプ
	float Clamp(const float& value, const float& min, const float& max);

//メンバ関数
public:
	//インスタンスの取得
	static FollowCamera* GetInstance();
	//初期化
	void Init(GameObject* subject,float angle,
		DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Zero);
	//更新
	void Update();
	//ビュー行列を返す
	DirectX::SimpleMath::Matrix GetViewMatrix();
	//マトリクス行列を返す
	DirectX::SimpleMath::Matrix GetProjMatrix();
	//ターゲットのポジションをセットする
	void SetTargetPos(DirectX::SimpleMath::Vector3 targetPos);
	//視点のセット
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