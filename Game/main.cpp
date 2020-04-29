#include "stdafx.h"
#include "system/system.h"
#include "GameObjectManager.h"
#include "GameData.h"
#include "Title.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	g_soundEngine->Init();
	GameData::GetInstance();
	StopWatch stopWatch;
	g_goMgr->NewGameObject<Title>();
	//�f�o�b�O���[�h�̃I���I�t
	bool m_isDebug = false;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�v���J�n
		stopWatch.Start();

		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�T�E���h�X�V
		g_soundEngine->Update();
		
		//�����G���W���̍X�V�B
		g_physics.Update();

		//���t���[���Ăяo���B
		g_goMgr->Update();
		
		if (g_pad[0].IsTrigger(enButtonSelect))
		{
			m_isDebug = !m_isDebug;
		}
		if (m_isDebug)
		{
			//�f�o�b�O���[�h
			g_physics.DebugDraw();
		}
		//�`��I���B
		g_graphicsEngine->EndRender();

		//�v���I��
		stopWatch.Stop();

		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());
	}
}