/*
テキストを管理しているマネジャークラス
*/

// ヘッダファイルの読み込み ----------
#include "TextManager.h"
//----------------------------------

// 静的メンバ変数を初期化する
TextManager::Instance TextManager::s_instance = nullptr;

// <コンストラクタ>
TextManager::TextManager()
{
}

// <デストラクタ>
TextManager::~TextManager()
{
}

// <インスタンスを取得する処理>
TextManager* TextManager::GetInstance()
{
	// インスタンスが生成されていなかった場合、インスタンスを生成する
	if (!s_instance) s_instance.reset(new TextManager());
	// インスタンスのポインタを返す
	return s_instance.get();
}

// <インスタンスを解放する処理>
void TextManager::Reset()
{
	// インスタンスを解放する
	s_instance.reset();
}

// <初期化する処理>
void TextManager::Initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, const wchar_t* _font)
{
	// メンバ変数を初期化する
	m_batch = std::make_unique<DirectX::SpriteBatch>(_context);
	m_font = std::make_unique<DirectX::SpriteFont>(_device, _font);

	// リストを初期化する
	m_textList.clear();
	m_textListOnlyOneFrame.clear();
}

// <リストに追加する処理>
void TextManager::Register(const std::wstring& _text, bool _isOnlyOneFrame, const DirectX::XMVECTOR& _color)
{
	// どちらかのリストに追加する
	(_isOnlyOneFrame ? m_textListOnlyOneFrame : m_textList).push_back(std::make_pair(_text, _color));
}

// <出力を開始する処理>
void TextManager::Begin()
{
	// 開始する
	m_batch->Begin();
}

// <テキストを出力する処理>
void TextManager::Print()
{
	float count = 0.0f;		// 行数

	// テキストリストの数だけループ処理
	for (const auto& text : m_textList)
	{
		// テキストを表示する
		m_font->DrawString(m_batch.get(), text.first.c_str(), DirectX::SimpleMath::Vector2(0.0f, 20.f * count), text.second);
		// カウントを更新する
		count += 1.0f;
	}

	// 1フレームのみ文字列リストの数だけループ処理
	for (const auto& text : m_textListOnlyOneFrame)
	{
		// テキストを表示する
		m_font->DrawString(m_batch.get(), text.first.c_str(), DirectX::SimpleMath::Vector2(0.0f, 20.f * count), text.second);
		// カウントを更新する
		count += 1.0f;
	}

	// 1フレームのみの文字列リストの中身を空にする
	m_textListOnlyOneFrame.clear();
}

// <出力を終了する処理>
void TextManager::End()
{
	// 終了する
	m_batch->End();
}

// <後始末する処理>
void TextManager::Finalize()
{
	// リストの中身を空にする
	m_textList.clear();
}
