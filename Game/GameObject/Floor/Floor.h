#pragma once
#include "Game\GameObject\GameObject.h"


class Floor final : public GameObject 
{
//定数
public:
	//マップの列
	const int MAP_ROW = 30;
	//マップの行
	const int MAP_COLUMN = 30;
	//床モデルのサイズ
	const float FLOOR_SIZE = 100;

//メンバ変数
private:
	std::unique_ptr<DirectX::Model> m_model;

//メンバ関数
public:
	Floor();
	~Floor();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
	void ReadFile() override;
	//衝突判定
	void OnCollision(GameObject* gameObject, Collider* designation = nullptr) override;
	void CreateModel();
};