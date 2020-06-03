#pragma once
#include "Game\GameObject\GameObject.h"

#include <memory>


class Sword;


class ArmR final : public GameObject
{
private:
//メンバ変数
	//武器
	Sword* m_weapon;
	//モデル
	std::unique_ptr<DirectX::Model> m_model;

public:
//メンバ関数
	//コンストラクタ
	ArmR();
	//デストラクタ
	~ArmR();
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
	//武器をセット
	void SetWeapon(Sword* sword);
	//武器を取得
	Sword* GetSword();

//メンバ関数
private:
	void CreateModel();
};

inline void ArmR::SetWeapon(Sword* sword)
{
	m_weapon = sword;
}

inline Sword* ArmR::GetSword()
{
	return m_weapon;
}
