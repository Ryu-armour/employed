/// <summary>
/// テキストの表示
/// </summary>

// 多重インクルードの防止
#pragma once

// ヘッダファイルの読み込み --------------
#include "Uncopyable.h"
#include <string>
#include <memory>
#include <list>
//---------------------------------------

// <<TextManagerクラス：Uncopyableクラス継承>>
class TextManager : private Uncopyable
{
	// <エイリアス宣言>
private:
	using Instance = std::unique_ptr<TextManager>;
	using TextList = std::list<std::pair<std::wstring, DirectX::XMVECTOR>>;

	// <メンバ変数>
private:
	static Instance s_instance;							// インスタンス
	std::unique_ptr<DirectX::SpriteBatch> m_batch;		// スプライトバッチ
	std::unique_ptr<DirectX::SpriteFont> m_font;		// スプライトフォント
	TextList m_textList;								// テキストリスト
	TextList m_textListOnlyOneFrame;					// 1フレームのみ表示するテキストリスト

	// <メンバ関数>
private:
	// コンストラクタ
	TextManager();
public:
	// デストラクタ
	~TextManager();
	// インスタンスを取得する処理
	static TextManager* GetInstance();
	// インスタンスを解放する処理
	void Reset();
	// 初期化する処理
	void Initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, const wchar_t* _font = L"Resources/Font/SegoeUI_18.spritefont");
	// リストに登録する処理
	void Register(const std::wstring& _text, bool _isOnlyOneFrame, const DirectX::XMVECTOR& _color = DirectX::Colors::White);
	// 出力を開始する処理
	void Begin();
	// テキストを出力する処理
	void Print();
	// 出力を終了する処理
	void End();
	// 後始末する処理
	void Finalize();
};