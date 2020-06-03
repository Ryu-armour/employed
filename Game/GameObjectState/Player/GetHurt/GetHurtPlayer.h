#pragma once
#include "Game\GameObjectState\IState.h"


class Player;


class GetHurtPlayer final : public IState
{
//定数
public:
	const int WINCE_TIME = 30;

//メンバ変数
private:
	//エネミー
	Player*	m_player;
	//吹っ飛ぶベクトル
	DirectX::SimpleMath::Vector3 m_blowAwayVec;
	//経過時間
	int		m_count;
	//描画フラグ
	bool	is_draw;

//メンバ関数
public:
	GetHurtPlayer(Player* player);
	~GetHurtPlayer();
	void Initialize() override;
	void Update() override;
	void Render(DirectX::Model* model) override;
	void Finalize() override;
	std::wstring& GetStateName() override
	{
		return m_stateName;
	}

//メンバ関数
private:
	//ノックバック
	void KickBack();
};