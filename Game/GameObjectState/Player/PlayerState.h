#pragma once
#include "Game\Common\Singleton.h"

#include <unordered_map>
#include <memory>


class IState;


class PlayerStateClass final : public Singleton<PlayerStateClass>
{
public:
	friend class Singleton<PlayerStateClass>;

private:
	std::unordered_map<int, std::unique_ptr<IState>> m_states;

protected:
	PlayerStateClass() {};
	virtual ~PlayerStateClass();

public:
	void Add(const int& type, std::unique_ptr<IState>&& state);
	IState* GetState(const int& type);
	void AllDelete();
};