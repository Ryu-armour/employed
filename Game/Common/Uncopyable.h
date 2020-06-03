/*
継承先のクラスの複製を禁止するクラス
*/

// 多重インクルードの防止
#pragma once

// <<Uncopyableクラス>>
class Uncopyable
{
	// <メンバ関数>
protected:
	// コンストラクタ
	Uncopyable() = default;
	// デストラクタ
	~Uncopyable() = default;

	// 複製を禁止する
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
};