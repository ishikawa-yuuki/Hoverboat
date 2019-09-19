#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager g_goMgr;

void GameObjectManager::Update()
{
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList)
	{
		go->Update();
	}
	for (auto go : m_goList) {
		go->Render();
	}
	for (auto it = m_goList.begin();
		it != m_goList.end();)
	{
		if ((*it)->isRequestDelete())
		{
			delete* it;
			it = m_goList.erase(it);
		}
		else
		{
			it++;
		}
	}
}
