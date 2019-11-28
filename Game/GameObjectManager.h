#pragma once
#include <vector>
#include "IGameObject.h"
#include "ShadowMap.h"
class GameObjectManager
{
public:
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	template <class T>
	T* NewGameObject()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g���폜�B
	/// </summary>
	/// <param name="go">
	/// �Q�[���I�u�W�F�N�g��
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
/// �V���h�E�}�b�v���擾�B
/// </summary>
/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
private:
	ShadowMap m_shadowMap;					//�V���h�E�}�b�v�B
	std::vector< IGameObject* > m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g�B
};
//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern GameObjectManager* g_goMgr;
