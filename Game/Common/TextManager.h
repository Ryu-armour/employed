/// <summary>
/// �e�L�X�g�̕\��
/// </summary>

// ���d�C���N���[�h�̖h�~
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� --------------
#include "Uncopyable.h"
#include <string>
#include <memory>
#include <list>
//---------------------------------------

// <<TextManager�N���X�FUncopyable�N���X�p��>>
class TextManager : private Uncopyable
{
	// <�G�C���A�X�錾>
private:
	using Instance = std::unique_ptr<TextManager>;
	using TextList = std::list<std::pair<std::wstring, DirectX::XMVECTOR>>;

	// <�����o�ϐ�>
private:
	static Instance s_instance;							// �C���X�^���X
	std::unique_ptr<DirectX::SpriteBatch> m_batch;		// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteFont> m_font;		// �X�v���C�g�t�H���g
	TextList m_textList;								// �e�L�X�g���X�g
	TextList m_textListOnlyOneFrame;					// 1�t���[���̂ݕ\������e�L�X�g���X�g

	// <�����o�֐�>
private:
	// �R���X�g���N�^
	TextManager();
public:
	// �f�X�g���N�^
	~TextManager();
	// �C���X�^���X���擾���鏈��
	static TextManager* GetInstance();
	// �C���X�^���X��������鏈��
	void Reset();
	// ���������鏈��
	void Initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, const wchar_t* _font = L"Resources/Font/SegoeUI_18.spritefont");
	// ���X�g�ɓo�^���鏈��
	void Register(const std::wstring& _text, bool _isOnlyOneFrame, const DirectX::XMVECTOR& _color = DirectX::Colors::White);
	// �o�͂��J�n���鏈��
	void Begin();
	// �e�L�X�g���o�͂��鏈��
	void Print();
	// �o�͂��I�����鏈��
	void End();
	// ��n�����鏈��
	void Finalize();
};