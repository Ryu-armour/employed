/// <summary>
/// CSVファイルを読み込む
/// </summary>
#pragma once
#include "Singleton.h"

#include <vector>


class CSVLoader final : public Singleton<CSVLoader>
{
//定数、構造体
public:
	//ステージの横幅
	static const int STAGE_W = 100;
	//ステージの立幅
	static const int STAGE_H = 100;
	//ステージデータの構造体
	struct StageData
	{
		//敵情報
		std::vector<std::vector<int>> enemyData;
	};

//メンバ変数
private:
	//ステージデータ
	StageData m_stageData;

//メンバ関数
public:
//ステージデータの読み込み関数
	void LoadEnemyData(wchar_t* fname);
	//ステージデータの取得
	StageData& GetStageData()
	{
		return m_stageData;
	}
	//エネミーの配列の取得
	std::vector<std::vector<int>>& GetEnemyData()
	{
		return m_stageData.enemyData;
	}

//シングルトン
public:
	friend class Singleton<CSVLoader>;
protected:
	CSVLoader() {};
	~CSVLoader() {};
};