#include "CSVLoader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cassert>


void CSVLoader::LoadEnemyData(wchar_t * fname)
{
	std::wstring str;

	//ファイルのオープン
	std::wifstream ifs(fname);

	// 開けなかった場合、例外処理
	assert(ifs.is_open() && "file can't opened");

	//配列の確保
	m_stageData.enemyData.resize(STAGE_H);
	for (int h = 0; h < STAGE_H; h++)
	{
		m_stageData.enemyData[h].resize(STAGE_W);
	}

	//ヘッダ文字列
	std::wstring objectHeadName = L"Enemy";

	//ファイルポインタを先頭へシーク
	ifs.clear();
	ifs.seekg(0);

	//ヘッダ部分までシーク
	while (!ifs.eof())
	{
		std::getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}

	//オブジェクトデータの読みこみ
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

	//ファイルのクローズ
	ifs.close();
}
