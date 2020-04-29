#include "stdafx.h"
#include "system/system.h"
#include "GameObjectManager.h"
#include "GameData.h"
#include "Title.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	g_soundEngine->Init();
	GameData::GetInstance();
	StopWatch stopWatch;
	g_goMgr->NewGameObject<Title>();
	//デバッグモードのオンオフ
	bool m_isDebug = false;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//計測開始
		stopWatch.Start();

		//描画開始。
		g_graphicsEngine->BegineRender();
		
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//サウンド更新
		g_soundEngine->Update();
		
		//物理エンジンの更新。
		g_physics.Update();

		//毎フレーム呼び出す。
		g_goMgr->Update();
		
		if (g_pad[0].IsTrigger(enButtonSelect))
		{
			m_isDebug = !m_isDebug;
		}
		if (m_isDebug)
		{
			//デバッグモード
			g_physics.DebugDraw();
		}
		//描画終了。
		g_graphicsEngine->EndRender();

		//計測終了
		stopWatch.Stop();

		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());
	}
}