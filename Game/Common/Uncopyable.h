/*
�p����̃N���X�̕������֎~����N���X
*/

// ���d�C���N���[�h�̖h�~
#pragma once

// <<Uncopyable�N���X>>
class Uncopyable
{
	// <�����o�֐�>
protected:
	// �R���X�g���N�^
	Uncopyable() = default;
	// �f�X�g���N�^
	~Uncopyable() = default;

	// �������֎~����
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
};