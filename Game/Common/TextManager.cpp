/*
�e�L�X�g���Ǘ����Ă���}�l�W���[�N���X
*/

// �w�b�_�t�@�C���̓ǂݍ��� ----------
#include "TextManager.h"
//----------------------------------

// �ÓI�����o�ϐ�������������
TextManager::Instance TextManager::s_instance = nullptr;

// <�R���X�g���N�^>
TextManager::TextManager()
{
}

// <�f�X�g���N�^>
TextManager::~TextManager()
{
}

// <�C���X�^���X���擾���鏈��>
TextManager* TextManager::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ������ꍇ�A�C���X�^���X�𐶐�����
	if (!s_instance) s_instance.reset(new TextManager());
	// �C���X�^���X�̃|�C���^��Ԃ�
	return s_instance.get();
}

// <�C���X�^���X��������鏈��>
void TextManager::Reset()
{
	// �C���X�^���X���������
	s_instance.reset();
}

// <���������鏈��>
void TextManager::Initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, const wchar_t* _font)
{
	// �����o�ϐ�������������
	m_batch = std::make_unique<DirectX::SpriteBatch>(_context);
	m_font = std::make_unique<DirectX::SpriteFont>(_device, _font);

	// ���X�g������������
	m_textList.clear();
	m_textListOnlyOneFrame.clear();
}

// <���X�g�ɒǉ����鏈��>
void TextManager::Register(const std::wstring& _text, bool _isOnlyOneFrame, const DirectX::XMVECTOR& _color)
{
	// �ǂ��炩�̃��X�g�ɒǉ�����
	(_isOnlyOneFrame ? m_textListOnlyOneFrame : m_textList).push_back(std::make_pair(_text, _color));
}

// <�o�͂��J�n���鏈��>
void TextManager::Begin()
{
	// �J�n����
	m_batch->Begin();
}

// <�e�L�X�g���o�͂��鏈��>
void TextManager::Print()
{
	float count = 0.0f;		// �s��

	// �e�L�X�g���X�g�̐��������[�v����
	for (const auto& text : m_textList)
	{
		// �e�L�X�g��\������
		m_font->DrawString(m_batch.get(), text.first.c_str(), DirectX::SimpleMath::Vector2(0.0f, 20.f * count), text.second);
		// �J�E���g���X�V����
		count += 1.0f;
	}

	// 1�t���[���̂ݕ����񃊃X�g�̐��������[�v����
	for (const auto& text : m_textListOnlyOneFrame)
	{
		// �e�L�X�g��\������
		m_font->DrawString(m_batch.get(), text.first.c_str(), DirectX::SimpleMath::Vector2(0.0f, 20.f * count), text.second);
		// �J�E���g���X�V����
		count += 1.0f;
	}

	// 1�t���[���݂̂̕����񃊃X�g�̒��g����ɂ���
	m_textListOnlyOneFrame.clear();
}

// <�o�͂��I�����鏈��>
void TextManager::End()
{
	// �I������
	m_batch->End();
}

// <��n�����鏈��>
void TextManager::Finalize()
{
	// ���X�g�̒��g����ɂ���
	m_textList.clear();
}
