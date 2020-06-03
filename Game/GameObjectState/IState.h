#pragma once
#include <string>

#include "Game\Common\StepTimer.h"
#include "Game\Common\ResourcesManager.h"


class IState
{
protected:
	std::wstring m_stateName;

public:
	virtual ~IState() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(DirectX::Model* model) = 0;
	virtual void Finalize() = 0;
	virtual std::wstring& GetStateName() = 0;
};