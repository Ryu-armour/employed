#pragma once
#include <string>


class Scene
{
//メンバ変数
protected:
	std::wstring m_sceneName;
//メンバ関数
public:
	// コンストラクタ
	Scene() = default;
	// デストラクタ
	virtual ~Scene() = default;
public:
	// 操作
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Final() = 0;
public:
	void SetSceneName(std::wstring string)
	{
		m_sceneName = string;
	}
};