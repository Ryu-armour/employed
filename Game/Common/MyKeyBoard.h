/// <summary>
/// 自分の使いやすい関数を追加したキーボードクラス
/// </summary>
#pragma once
#include "Singleton.h"


class MyKeyBoard final : public Singleton<MyKeyBoard>
{
private:
//メンバ変数
	//現在のキーボードの状態
	DirectX::Keyboard::State m_currentKeyState;
	//前回のキーボードの状態
	DirectX::Keyboard::State m_previousKeyState;

//メンバ関数
public:
	//更新
	void UpdateCurrentKey();
	void UpdatePreviousKey();
	//指定のキーが押された瞬間を返す
	bool IsKeyMomentDown(DirectX::Keyboard::Keys key);
	//指定のキーが離された瞬間を返す
	bool IsKeyMomentUp(DirectX::Keyboard::Keys key);

//シングルトン
protected:
	friend class Singleton<MyKeyBoard>;
	MyKeyBoard();
	~MyKeyBoard();
};