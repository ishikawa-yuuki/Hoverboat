#include "stdafx.h"
#include "system/system.h"
#include "GameObjectManager.h"
#include "Game.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	
	
	
	g_goMgr.NewGameObject<Game>();
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		
		//毎フレーム呼び出す。
		g_goMgr.Update();
		
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}