#pragma once
#include <DxLib.h>
#include "WindowInfo.h"

class Fps {
	int startTime;         //����J�n����
	int count;             //�J�E���^
	float fps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps() {
		startTime = 0;
		count = 0;
		fps = 0;
	}

	bool Update() {
		if (count == 0) { //1�t���[���ڂȂ玞�����L��
			startTime = GetNowCount();
		}
		if (count == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			fps = 1000.f / ((t - startTime) / (float)N);
			count = 0;
			startTime = t;
		}
		count++;
		return true;
	}

	void Draw() {
#ifdef _DEBUG_
		DrawFormatString(20, 20, GetColor(255, 255, 255), "FPS : %.0f", fps);
#endif
	}

	void Wait() {
		int tookTime = GetNowCount() - startTime;	//������������
		int waitTime = count * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};