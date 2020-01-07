#pragma once
#include <DxLib.h>
#include "WindowInfo.h"

class Fps {
	int startTime;         //測定開始時刻
	int count;             //カウンタ
	float fps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		startTime = 0;
		count = 0;
		fps = 0;
	}

	bool Update() {
		if (count == 0) { //1フレーム目なら時刻を記憶
			startTime = GetNowCount();
		}
		if (count == N) { //60フレーム目なら平均を計算する
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
		int tookTime = GetNowCount() - startTime;	//かかった時間
		int waitTime = count * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};