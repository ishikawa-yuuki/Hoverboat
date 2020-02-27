#pragma once
#include <winnt.h>
#include <profileapi.h>
/*!
	 *@brief	�X�g�b�v�E�H�b�`�N���X�B
	 *@details
	 * C#��Stopwatch�̂悤�Ɏg����B</br>
	 *@code
	   �T���v���R�[�h
	   Stopwatch sw;
	   sw.Start();		//�v���J�n�B
	   for(int i = 0; i < 100; i++ ){
	   }
	   sw.Stop();		//�v���I��
	   printf("�o�ߎ��� = %lf(�P�ʁF�b)\n", sw.GetElapsed());
	   printf("�o�ߎ��� = %lf(�P�ʁF�~��)\n", sw.GetElapsedMillisecond());
	 *@endcode
	 *
	 */
class StopWatch {
public:
	StopWatch()
	{
		freq = 0;
		end = 0;
		begin = 0;
		elapsed = 0.0;
		elapsedMill = 0.0;
		elapsedMicro = 0.0;
	}
	~StopWatch() {}
	//�v���J�n
	void Start()
	{
		//�v���J�n���̃J�E���g�����擾

		QueryPerformanceCounter((LARGE_INTEGER*)&begin);

	}
	//�v���I��
	void Stop()
	{
		//�J�E���^�̎��g�����擾
		::QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		//�v���I�����̃J�E���g�����擾
		::QueryPerformanceCounter((LARGE_INTEGER*)&end);

		elapsed = double(end - begin) / freq;

		elapsedMill = elapsed * 1000.0;

		elapsedMicro = elapsedMill * 1000.0;

	}

	//�o�ߎ��Ԃ��擾(�b)
	double GetElapsed() const
	{
		return elapsed;
	}

	//�o�ߎ��Ԃ��擾(�~���b)
	double GetElapsedMillisecond() const
	{
		return elapsedMill;
	}

	//�o�ߎ��Ԃ��擾(�}�C�N���b)
	double GetElapsedMicrosecond() const
	{
		return elapsedMicro;
	}
private:
	//�K��64�r�b�g(LONGLONG�^)
	LONGLONG freq;
	LONGLONG end;
	LONGLONG begin;
	double elapsed;			//�o�ߎ���(�P�ʁF�b)
	double elapsedMill;		//�o�ߎ���(�P�ʁF�~���b)
	double elapsedMicro;	//�o�ߎ���(�P�ʁF�}�C�N���b)
};