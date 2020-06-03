/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
#pragma once
#include "Singleton.h"

#include <vector>


class CSVLoader final : public Singleton<CSVLoader>
{
//�萔�A�\����
public:
	//�X�e�[�W�̉���
	static const int STAGE_W = 100;
	//�X�e�[�W�̗���
	static const int STAGE_H = 100;
	//�X�e�[�W�f�[�^�̍\����
	struct StageData
	{
		//�G���
		std::vector<std::vector<int>> enemyData;
	};

//�����o�ϐ�
private:
	//�X�e�[�W�f�[�^
	StageData m_stageData;

//�����o�֐�
public:
//�X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	void LoadEnemyData(wchar_t* fname);
	//�X�e�[�W�f�[�^�̎擾
	StageData& GetStageData()
	{
		return m_stageData;
	}
	//�G�l�~�[�̔z��̎擾
	std::vector<std::vector<int>>& GetEnemyData()
	{
		return m_stageData.enemyData;
	}

//�V���O���g��
public:
	friend class Singleton<CSVLoader>;
protected:
	CSVLoader() {};
	~CSVLoader() {};
};