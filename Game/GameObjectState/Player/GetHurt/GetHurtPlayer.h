#pragma once
#include "Game\GameObjectState\IState.h"


class Player;


class GetHurtPlayer final : public IState
{
//�萔
public:
	const int WINCE_TIME = 30;

//�����o�ϐ�
private:
	//�G�l�~�[
	Player*	m_player;
	//������ԃx�N�g��
	DirectX::SimpleMath::Vector3 m_blowAwayVec;
	//�o�ߎ���
	int		m_count;
	//�`��t���O
	bool	is_draw;

//�����o�֐�
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

//�����o�֐�
private:
	//�m�b�N�o�b�N
	void KickBack();
};