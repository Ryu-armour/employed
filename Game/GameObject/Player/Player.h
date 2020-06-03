#pragma once
#include <map>
#include <list>

#include "Game\Collider\Shape\Sphere\SphereCollider.h"

#include "Game\GameObject\GameObject.h"
#include "Game\GameObject\Player\ArmR\ArmR.h"


//クラスの前方宣言
class IState;
class Sword;
class ArmR;


//クラスの宣言
class Player final : public GameObject
{
public:
	enum PLAYER_STATE
	{
		STANDING = 0,
		WALKING,
		ATTACK,
		DAMAGE,

		NUM
	};

//定数
public:
	//カプセルのサイズ
	const DirectX::SimpleMath::Vector3 CAPSULE_SIZE = { 0.0f, 1.0f, 0.0f };
	//カプセルの半径
	const float CAPSULE_RADIUS = 0.5f;
	//無敵時間
	const int INVINCIBLE_TIME = 3 * 60;
	//ノックバックの大きさ
	const float BACK = 0.6f;
	//腕パーツの位置
	static const DirectX::SimpleMath::Vector3 ARMR_ADJUSTMENT;

//メンバ変数
private:
	//モデル
	std::unique_ptr<DirectX::Model>			 	 m_model;
	//当たり判定
	std::unique_ptr<Sphere>						 m_collider;
	//右腕
	ArmR*										 m_armR;
	//武器
	Sword*										 m_weapon;
	//現在の状態
	IState*										 m_state;
	//ヒットポイント
	unsigned int								 m_life;
	//無敵時間
	unsigned int								 m_invincibleTime;
	//無敵カウント
	int											 m_invincibilityCount;
	//点滅カウント
	int											 m_flashCount;
	//モデルのサイズ
	float										 m_size;
	//プレイヤーの移動速さ
	float										 m_speed;
	//向き(デグリー角)
	float										 m_angle;
	//プレイヤーの移動速度
	DirectX::SimpleMath::Vector3				 m_vel;
	//吹っ飛ぶベクトル
	DirectX::SimpleMath::Vector3				 m_blowAwayVec;
	//プリミティブの色(デバッグ)
	DirectX::SimpleMath::Vector4				 m_color;
	//無敵状態かどうか
	bool										 is_invincibility;
	//モデルの描画フラグ
	bool										 is_drawModel;
	//プリミティブの描画フラグ
	bool										 is_drawPrimitive;


//メンバ関数
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	//Jsonファイルを開く
	void ReadFile() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	//無敵化
	void ToInvincible();
	//無敵化解除
	void UnlockInvicinble();
	//動く
	void Move();
	//点滅
	void Flash();
	//ステートの切り替え
	void ChangeState(IState* state);
	//velに値を入れる
	void SetVel(const DirectX::SimpleMath::Vector3& vel);
	//velの値を渡す
	DirectX::SimpleMath::Vector3& GetVel();
	//吹っ飛ぶベクトルを入れる
	void SetBlowAwayVec(const DirectX::SimpleMath::Vector3& vec);
	//吹っ飛ぶベクトルを渡す
	DirectX::SimpleMath::Vector3& GetBlowAwayVec();
	//状態を返す
	IState* GetState() const;
	//腕をセット
	const void SetArmR(ArmR* arm);
	//腕を取得
	ArmR* GetArmR();
	//武器をセット
	const void SetWeapon(Sword* sword);
	//武器を返す
	Sword* GetSword() const;
	//ライフを返す
	unsigned int GetLife() const;
	//色を設定
	void SetColor(const DirectX::XMVECTORF32& color);

//メンバ関数
private:
	//モデルの作成
	void CreateModel();
	//ノックバック
	void KickBack(const DirectX::SimpleMath::Vector3& objPos);
	//カメラの向きをプレイヤーに適用
	void FaceCamera();
};

inline void Player::SetVel(const DirectX::SimpleMath::Vector3& vel)
{
	m_vel = vel;
}

inline DirectX::SimpleMath::Vector3& Player::GetVel()
{
	return m_vel;
}

inline void Player::SetBlowAwayVec(const DirectX::SimpleMath::Vector3& vec)
{
	m_blowAwayVec = vec;
}

inline DirectX::SimpleMath::Vector3& Player::GetBlowAwayVec()
{
	return m_blowAwayVec;
}

inline IState* Player::GetState() const
{
	return m_state;
}

inline const void Player::SetArmR(ArmR* arm)
{
	m_armR = arm;
}

inline ArmR* Player::GetArmR()
{
	return m_armR;
}

inline const void Player::SetWeapon(Sword* sword)
{
	m_weapon = sword;
	m_armR->SetWeapon(sword);
}

inline Sword* Player::GetSword() const
{
	return m_weapon;
}

inline unsigned int Player::GetLife() const
{
	return m_life;
}

inline void Player::SetColor(const DirectX::XMVECTORF32& color)
{
	m_color = color;
}