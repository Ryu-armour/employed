#pragma once
#include "Game\Common\Singleton.h"

#include <unordered_map>
#include <memory>


class IState;


class SwordState final : public Singleton<SwordState>
{
public:
	friend class Singleton<SwordState>;

private:
	std::unordered_map<int, std::unique_ptr<IState>> m_states;

protected:
	SwordState() {};
	virtual ~SwordState();

public:
	void Add(const int& type, std::unique_ptr<IState>&& state);
	IState* GetState(const int& type);
	void AllDelete();
};