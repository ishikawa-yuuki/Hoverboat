#pragma once
/*!
 *@brief	�Q�[�����ԃN���X�B
 * �V���O���g���B
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

	//1�t���[�����Ƃ̌o�ߎ��Ԃ��擾(�b)
	const float GetFrameDeltaTime() const
	{
		return m_frameDeltaTime;
	}

	//1�t���[�����Ƃ̌o�ߎ���(�b)���v�Z
	void PushFrameDeltaTime(float deltaTime)
	{

		//���Ԃ��L��
		m_frameDeltaTimeQue.push_back(deltaTime);

		//�z��̒�����60.0f�ȏ�Ȃ玞�Ԃ��o�߂���
		if (m_frameDeltaTimeQue.size() > 60.0f) {

			float totalTime = 0.0f;

			//�z��̎��Ԃ̍��v

			for (auto time : m_frameDeltaTimeQue) {

				totalTime += time;
			}

			//���ϒl���Ƃ�A�z��̍��v���Ԃ�z��̒����Ŋ���
			m_frameDeltaTime = min(1.0f / 60.0f, totalTime / m_frameDeltaTimeQue.size());

			//�z��̈�ԍŏ��̗v�f���폜����
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
	float m_frameDeltaTime = 1.0f / 60.0f;			//1�t���[�����Ƃ̌o�ߎ���
	CFont m_font;
};
static inline CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}