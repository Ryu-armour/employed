#include "PlayerState.h"

#include "Game\GameObjectState\IState.h"


PlayerStateClass::~PlayerStateClass()
{
	AllDelete();
}

void PlayerStateClass::Add(const int& type, std::unique_ptr<IState>&& state)
{
	m_states.insert(std::make_pair(type, std::move(state)));
}

IState* PlayerStateClass::GetState(const int& type)
{
	return m_states.at(type).get();
}

void PlayerStateClass::AllDelete()
{
	m_states.clear();
}