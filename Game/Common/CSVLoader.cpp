#include "CSVLoader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cassert>


void CSVLoader::LoadEnemyData(wchar_t * fname)
{
	std::wstring str;

	//�t�@�C���̃I�[�v��
	std::wifstream ifs(fname);

	// �J���Ȃ������ꍇ�A��O����
	assert(ifs.is_open() && "file can't opened");

	//�z��̊m��
	m_stageData.enemyData.resize(STAGE_H);
	for (int h = 0; h < STAGE_H; h++)
	{
		m_stageData.enemyData[h].resize(STAGE_W);
	}

	//�w�b�_������
	std::wstring objectHeadName = L"Enemy";

	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		std::getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}

	//�I�u�W�F�N�g�f�[�^�̓ǂ݂���
	for (int i = 0; i < STAGE_H; i++)
	{
		std::getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.enemyData[i][j] = std::stoi(tmp);
		}
	}

	//�t�@�C���̃N���[�Y
	ifs.close();
}
