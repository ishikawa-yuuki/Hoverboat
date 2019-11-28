#pragma once
#include <vector>
#include "IGameObject.h"
#include "ShadowMap.h"
class GameObjectManager
{
public:
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ゲームオブジェクトを追加。
	/// </summary>
	template <class T>
	T* NewGameObject()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// ゲームオブジェクトを削除。
	/// </summary>
	/// <param name="go">
	/// ゲームオブジェクト名
	/// </param>
	void DeleteGameObject(IGameObject* go)
	{
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++)
		{
			if ((*it == go))
			{
				go->RequestDelete();
				return;
			}
		}
	}
	/// <summary>
/// シャドウマップを取得。
/// </summary>
/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
private:
	ShadowMap m_shadowMap;					//シャドウマップ。
	std::vector< IGameObject* > m_goList;		//ゲームオブジェクトのリスト。
};
//外部からアクセスするので、extern宣言も必要。
extern GameObjectManager* g_goMgr;
