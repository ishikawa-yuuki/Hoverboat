#pragma once
/*!
 *@brief	ゲーム時間クラス。
 * シングルトン。
 */
#include <queue>
#include <list>
#include <minwindef.h>
#include "CFont.h"
class CGameTime {
private:
	CGameTime() {}
	~CGameTime() {}
public:

	static CGameTime& GetInstance()
	{
		static CGameTime instance;
		return instance;
	}

	//1フレームごとの経過時間を取得(秒)
	const float GetFrameDeltaTime() const
	{
		return m_frameDeltaTime;
	}

	//1フレームごとの経過時間(秒)を計算
	void PushFrameDeltaTime(float deltaTime)
	{

		//時間を記憶
		m_frameDeltaTimeQue.push_back(deltaTime);

		//配列の長さが60.0f以上なら時間を経過する
		if (m_frameDeltaTimeQue.size() > 60.0f) {

			float totalTime = 0.0f;

			//配列の時間の合計

			for (auto time : m_frameDeltaTimeQue) {

				totalTime += time;
			}

			//平均値をとる、配列の合計時間を配列の長さで割る
			m_frameDeltaTime = min(1.0f / 60.0f, totalTime / m_frameDeltaTimeQue.size());

			//配列の一番最初の要素を削除する
			m_frameDeltaTimeQue.pop_front();

		}

	}
	void Draw() {
		wchar_t output[256];

		swprintf_s(output, L"FPS %f", 1.0f / m_frameDeltaTime);
		m_font.Begin();
		m_font.Draw(output, {-630.0f,350.0f},CVector4::Yellow());
		m_font.End();
	}
private:
	std::list<float> m_frameDeltaTimeQue;
	float m_frameDeltaTime = 1.0f / 60.0f;			//1フレームごとの経過時間
	CFont m_font;
};
static inline CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}