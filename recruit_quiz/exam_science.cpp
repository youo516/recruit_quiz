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

	//浮力
	{
		int s = uniform_int_distribution<>(5, 20)(rd);
		int h = uniform_int_distribution<>(2, 10)(rd);
		int v = s * h + 5;
		string answer = to_string(v / 100);
		v /= 10;
		if (v % 10)
		{
			answer += '.';
			answer += '0' + v % 10;
		}
		questions.push_back({ "質量100gにはたらく重力を1Nとする。\n底面積" + to_string(s) + "cm^2、高さ" + to_string(h) + "cmの円柱を完全に水中に沈めた。\nこのとき、この円柱にはたらく浮力はxNである。\nxの値を小数点以下第2位までを四捨五入して求めよ。", answer});
	
		int x = uniform_int_distribution<>(20, 50)(rd) * 10;
		int y = uniform_int_distribution<>(x / 2, x - 1)(rd);
		int z = x - y + 5;
		answer = to_string(z / 100);
		z /= 10;
		if (z % 10)
		{
			answer += '.';
			answer += '0' + z % 10;
		}
		questions.push_back({ "質量100gの物体にはたらく重力を1Nとする。\nある物体の重さをばねはかりで量ると、" + to_string(x) + "gを示した。\nこのとき、物体にはたらく浮力はxNである。\n" + "xの値を小数点以下第2位までを四捨五入して求めよ。", answer });

		int p0 = uniform_int_distribution<>(1, 9)(rd);
		s = uniform_int_distribution<>(5, 10)(rd);
		h = uniform_int_distribution<>(5, 10)(rd);
		z = h * p0 + 50;
		answer = to_string(z / 1000);
		z /= 100;
		if (z % 10)
		{
			answer += '.';
			answer += '0' + z % 10;
		}
		questions.push_back({ "密度" + to_string(p0) + "kg/m^3、底面積" + to_string(s) + "cm^2、高さ" + to_string(h) + "cmの物体を水に沈めようとしたところ、Xcm沈んで静止した。\nXの値を小数点以下第1位まで求めよ。", answer });
	}

	//ばね
	{
		int a = uniform_int_distribution<>(10, 30)(rd);
		int x = uniform_int_distribution<>(1, a / 2)(rd);
		int m = uniform_int_distribution<>(1, 20)(rd);
		int k = 100 * m / x + 5;
		string answer = to_string(k / 100);
		k /= 10;
		if (k % 10)
		{
			answer += '.';
			answer += '0' + k % 10;
		}
		questions.push_back({ "重力加速度を10m/s^2とする。\n長さ" + to_string(x) + "cmのばねの先端に" + to_string(m) + "gのおもりを付けて、天井から吊り下げた。\nすると、ばねの長さが" + to_string(a + x) + "cmになった。\nこのばねの「ばね定数」を小数点以下第2位を四捨五入して求めよ。", answer });

		int k1 = uniform_int_distribution<>(1, 10)(rd);
		int k2 = uniform_int_distribution<>(1, 9)(rd);
		if (k2 >= k1)
		{
			k2++;
		}
		m = uniform_int_distribution<>(1, 10)(rd) * 10;
		x = 100 * m * (k1 + k2) / (k1 + k2) + 5;
		answer = to_string(x / 100);
		x /= 10;
		if (x % 10)
		{
			answer += '.';
			answer += '0' + x % 10;
		}
		questions.push_back({ "重力加速度を10m/s^2とする。\nばね定数が" + to_string(k1) + "と" + to_string(k2) + "の二つのばねを直列につなぎ、" + to_string(m) + "gのおもりを付けて天井から吊り下げた。\nすると、ばねの長さが合わせてXcm伸びて静止した。\nXの値を小数点以下第2位を四捨五入して求めよ。", answer });
	}
	return questions;
}