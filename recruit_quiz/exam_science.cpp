#include "exam_science.h"
#include "utility.h"
#include <random>
using namespace std;

//物理の問題を作成
QuestionList CreatePhysicsExam()
{
	QuestionList questions;
	questions.reserve(10);
	random_device rd;

	//等速直線運動
	{
		constexpr int divisors[] = { 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60 };
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//時速
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//時間
		questions.push_back({ "時速" + to_string(v) + "kmで移動する車がある。\nこの車が" + to_string(v * t / 60) + "km移動するために必要な時間を分単位で求めよ", to_string(t) });

		i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//時速
		t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//時間
		questions.push_back({ "ある車が" + to_string(v * t / 60) + "km離れた地点まで移動するのに" + to_string(t) + "分かかった。\nこの車の平均時速を求めよ", to_string(v) });
	}

	//等加速度直線運動
	{
		//v = v0 + at
		int v0 = uniform_int_distribution<>(0, 10)(rd);	//初速
		int a = uniform_int_distribution<>(1, 5)(rd);	//加速度
		int t = uniform_int_distribution<>(1, 20)(rd);	//移動時間
		questions.push_back({ "秒速" + to_string(v0) + "mで移動していた車が、進行方向に大きさ" + to_string(a) + "m/s^2で等加速度直線運動を始めた。\n" + to_string(t) + "秒後の速度m/sを求めよ。", to_string(v0 + a * t)});

		//x = v0t + 1/2 * at^2
		v0 = uniform_int_distribution<>(5, 20)(rd);
		a = uniform_int_distribution<>(1, 5)(rd);
		t = uniform_int_distribution<>(1, 10)(rd);
		questions.push_back({ "秒速" + to_string(v0) + "mで移動していた車が、進行方向に大きさ" + to_string(a) + "m/s^2で等加速度直線運動を始めた。\n加速を始めてから" + to_string(t) + "秒後までに移動した距離をm単位で求めよ。", to_string(v0 * t + a * t * t / 2) });

		//v^2 - v0^2 = 2ax
		a = -uniform_int_distribution<>(1, 5)(rd) * 2;
		t = uniform_int_distribution<>(1, 10)(rd);
		v0 = -a * t;
		questions.push_back({ "秒速" + to_string(v0) + "mで移動していた車がブレーキをかけたところ、"+ to_string(v0 * t + a * t * t / 2) + "m進んで停止した。\nブレーキの加速度m/s^2を求めよ。", to_string(a) });
	}

	//重力加速度
	{
		int t = uniform_int_distribution<>(1, 10)(rd);	//移動時間
		int x = 98 * t * t / 2;		//小数点第1位までを整数として表す
		string answer = to_string(x / 10);
		if (x % 10)
		{
			answer += '.';
			answer += '0' + x % 10;
		}
		questions.push_back({ "重力加速度を9.8m/s^2とし、空気抵抗はないものとする。\n十分に高い位置から物体を静かに落とすと、物体は" + to_string(t) + "秒間でXm落下する。\n" + "Xの値を小数点以下第1位まで求めよ。", answer });

		int v0 = uniform_int_distribution<>(1, 10)(rd);		//初速
		t = uniform_int_distribution<>(1, 10)(rd);			//移動時間
		int v = v0 * 10 - 98 * t;
		answer.clear();
		if (v < 0)
		{
			v = -v;
			answer = '.';
		}
		answer += to_string(v / 10);
		if (v % 10)
		{
			answer += '.';
			answer += '0' + v % 10;
		}
		questions.push_back({ "重力加速度を9.8m/s^2とし、空気抵抗はないものとする。\n初速" + to_string(v0) + "m/sで物体を鉛直に投げたとき、" + to_string(t) + "秒後の物体の速度はXm/sである。\nXの値を小数点以下第1位まで求めよ。", answer });
	}
	return questions;
}