#pragma once
#include <istream>
#include <fstream>

#include "3rdParty\Picojson\picojson.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Common\StepTimer.h"

#include "Game\Collider\Collider.h"


class GameObject
{
//構造体
public:
	//オブジェクトのタグ
	enum GAMEOBJECT_TAG
	{
		DEFAULT,
		PLAYER,
		ENEMY,
		CORE,
		WEAPON
	};

//メンバ変数
protected:
	//位置
	DirectX::SimpleMath::Vector3	 m_pos;
	//ワールド行列
	DirectX::SimpleMath::Matrix		 m_world;
	//オブジェクトのタグ
	GAMEOBJECT_TAG					 m_tag;
	//デバッグか
	bool							 isDebug;
private:
	//使用状態
	bool							 isNeed;

//メンバ関数
public:
	//コンストラクタ
	GameObject();
	//デストラクタ
	virtual ~GameObject() {};
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Render() = 0;
	//終了処理
	virtual void Finalize() = 0;
	//Jsonファイルの読み込み
	virtual void ReadFile() = 0;
	//衝突判定
	virtual void OnCollision(GameObject* gameObject, Collider* designation = nullptr) = 0;
	//ポジションを設定する
	virtual void SetPos(const DirectX::SimpleMath::Vector3& pos);
	//ポジションを返す
	virtual DirectX::SimpleMath::Vector3& GetPos();
	//ワールド行列を設定する
	virtual void SetWorld(const DirectX::SimpleMath::Matrix& world);
	//ワールド行列を返す
	virtual DirectX::SimpleMath::Matrix& GetWorld();
	//タグを設定する
	virtual void SetTag(GAMEOBJECT_TAG tag);
	//タグを返す
	virtual const GAMEOBJECT_TAG GetTag();
	//不要になる
	void ToParaphernalia();
	//必要な状態を返す
	bool IsNeed() const;
	//不要な状態を返す
	bool IsNeedless() const;
	//ワールド座標に位置を適用
	void ApplyWorld();
	//デバッグ状態だとフラグを入れる
	void IsDebug();
};

inline void GameObject::SetPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetPos()
{
	return m_pos;
}

inline void GameObject::SetWorld(const DirectX::SimpleMath::Matrix& world)
{
	m_world = world;
}

inline DirectX::SimpleMath::Matrix& GameObject::GetWorld()
{
	return m_world;
}

inline void GameObject::SetTag(GAMEOBJECT_TAG tag)
{
	m_tag = tag;
}

inline const GameObject::GAMEOBJECT_TAG GameObject::GetTag()
{
	if (m_tag)
		return m_tag;

	return GAMEOBJECT_TAG::DEFAULT;
}

inline void GameObject::ToParaphernalia()
{
	isNeed = false;
}

inline bool GameObject::IsNeed() const
{
	return isNeed;
}

inline bool GameObject::IsNeedless() const
{
	return !isNeed;
}

inline void GameObject::ApplyWorld()
{
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}

inline void GameObject::IsDebug()
{
	isDebug = true;
}