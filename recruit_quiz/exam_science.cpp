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

	{
		constexpr int divisors[] = { 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60 };
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//時速
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//時間
		questions.push_back({ "時速" + to_string(v) + "kmで移動する車がある。\nこの車が" + to_string(v * t / 60) + "km移動するために必要な時間を分単位で求めよ", to_string(t) });
	}
	return questions;
}