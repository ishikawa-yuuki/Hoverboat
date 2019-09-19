#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager g_goMgr;

void GameObjectManager::Update()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
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
