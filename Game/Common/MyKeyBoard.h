/// <summary>
/// �����̎g���₷���֐���ǉ������L�[�{�[�h�N���X
/// </summary>
#pragma once
#include "Singleton.h"


class MyKeyBoard final : public Singleton<MyKeyBoard>
{
private:
//�����o�ϐ�
	//���݂̃L�[�{�[�h�̏��
	DirectX::Keyboard::State m_currentKeyState;
	//�O��̃L�[�{�[�h�̏��
	DirectX::Keyboard::State m_previousKeyState;

//�����o�֐�
public:
	//�X�V
	void UpdateCurrentKey();
	void UpdatePreviousKey();
	//�w��̃L�[�������ꂽ�u�Ԃ�Ԃ�
	bool IsKeyMomentDown(DirectX::Keyboard::Keys key);
	//�w��̃L�[�������ꂽ�u�Ԃ�Ԃ�
	bool IsKeyMomentUp(DirectX::Keyboard::Keys key);

//�V���O���g��
protected:
	friend class Singleton<MyKeyBoard>;
	MyKeyBoard();
	~MyKeyBoard();
};