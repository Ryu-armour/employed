#include "EnemyState.h"

#include "Game\GameObjectState\IState.h"


EnemyState::~EnemyState()
{
	AllDelete();
}

void EnemyState::Add(EnemyStateList stateName, std::unique_ptr<IState>&& state)
{
	m_states.insert(std::make_pair(stateName, std::move(state)));
}

IState * EnemyState::GetState(EnemyStateList stateName)
{
	return m_states.at(stateName).get();
}

void EnemyState::AllDelete()
{
	m_states.clear();
}