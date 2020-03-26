#pragma once
#include <vector>
#include "IGameObject.h"
#include "ShadowMap.h"
#include "RenderTarget.h"
#include "Sprite.h"
#include "SoundEngine.h"
class GameObjectManager
{
public:
	bool Start();
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
	void SetShadowPos()
	{
		m_shadowMapPos = m_shadowMapTarget + m_shadow;
	}
	void SetShadowTarget(CVector3 const& pos)
	{
		m_shadowMapTarget = pos;
	}
	/// <summary>
/// �V���h�E�}�b�v���擾�B
/// </summary>
/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	Effekseer::Manager* GetEffectManeger()
	{
		return m_effekseerManager;
	}
	/// <summary>
	/// �v�������_�����O�B
	/// </summary>
	void PreRender();
	/// <summary>
	/// �t�H���[�h�����_�����O(�ʏ�̕`�悾�ƍl����OK)
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender();
	/// <summary>
   /// Effekseer�̏������B
   /// </summary>
	void InitEffekseer();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager* m_effekseerManager				= nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer	= nullptr;

	CSoundEngine m_soundEngine;						//�T�E���h�G���W���B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	RenderTarget m_mainRenderTarget;			    //���C�������_�����O�^�[�Q�b�g
	ShadowMap m_shadowMap;							//�V���h�E�}�b�v�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	std::vector< IGameObject* > m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g�B
	CVector3 m_shadowMapPos = { 800.0f,800.0f,800.0f };
	CVector3 m_shadow =  {800.0f,800.0f,800.0f} ;
	CVector3 m_shadowMapTarget = {0.0f,0.0f,0.0f};
	bool m_first = false;
};
//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern GameObjectManager* g_goMgr;
