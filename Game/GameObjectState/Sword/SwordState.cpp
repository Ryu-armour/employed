#include "SwordState.h"

#include "Game\GameObjectState\IState.h"


SwordState::~SwordState()
{
	AllDelete();
}

void SwordState::Add(const int & type, std::unique_ptr<IState>&& state)
{
	m_states.insert(std::make_pair(type, std::move(state)));
}

IState * SwordState::GetState(const int & type)
{
	return m_states.at(type).get();
}

void SwordState::AllDelete()
{
	m_states.clear();
}
