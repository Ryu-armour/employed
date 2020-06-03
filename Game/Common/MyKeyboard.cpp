#include "MyKeyBoard.h"


void MyKeyBoard::UpdateCurrentKey()
{
	m_currentKeyState = DirectX::Keyboard::Get().GetState();
}

void MyKeyBoard::UpdatePreviousKey()
{
	m_previousKeyState = DirectX::Keyboard::Get().GetState();
}

bool MyKeyBoard::IsKeyMomentDown(DirectX::Keyboard::Keys key)
{
	if (m_currentKeyState.IsKeyDown(key) && m_previousKeyState.IsKeyUp(key))
	{
		return true;
	}

	return false;
}

bool MyKeyBoard::IsKeyMomentUp(DirectX::Keyboard::Keys key)
{
	//情報の取得
	m_currentKeyState = DirectX::Keyboard::Get().GetState();

	if (m_currentKeyState.IsKeyUp(key) && m_previousKeyState.IsKeyDown(key))
	{
		m_previousKeyState = DirectX::Keyboard::Get().GetState();
		return true;
	}

	m_previousKeyState = DirectX::Keyboard::Get().GetState();
	return false;
}

MyKeyBoard::MyKeyBoard()
{
	//キーボードの取得
	m_currentKeyState = DirectX::Keyboard::Get().GetState();
	m_previousKeyState = DirectX::Keyboard::Get().GetState();
}

MyKeyBoard::~MyKeyBoard()
{
}
