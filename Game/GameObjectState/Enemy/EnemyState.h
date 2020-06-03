#pragma once
#include "Game\Common\Singleton.h"

#include <unordered_map>
#include <memory>


class IState;


class EnemyState final : public Singleton<EnemyState>
{
public:
	enum EnemyStateList
	{
		Search = 0,
		Walking,
		GetHurt,

		Num
	};

public:
	friend class Singleton<EnemyState>;

private:
	using SearchList = std::list<IState>;
	using WalkingList = std::list<IState>;
	using GetHurtList = std::list<IState>;

private:
	std::unordered_map<EnemyStateList, std::unique_ptr<IState>> m_states;

protected:
	EnemyState() {};
	virtual ~EnemyState();

public:
	//�ǉ�
	void Add(EnemyStateList stateName, std::unique_ptr<IState>&& state);
	//State�̎擾
	IState* GetState(EnemyStateList stateName);
	//�f�[�^�̍폜
	void AllDelete();
};