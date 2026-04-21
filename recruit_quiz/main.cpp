#include <iostream>
#include <string>
#include <random>
using namespace std;

//
struct Question
{
	string q;
	int a;
};

int main()
{
	Question questions[3];

	random_device rd;
	mt19937 rand(rd());

	int x;
	int y;
	int z;
	int w;

	//乗算
	x = uniform_int_distribution<>(1, 30)(rand);
	y = uniform_int_distribution<>(1, 20)(rand);
	questions[0].q = to_string(x) + "x" + to_string(y);
	questions[0].a = x * y;

	//除算
	x = uniform_int_distribution<>(1, 30)(rand);
	y = uniform_int_distribution<>(1, 20)(rand);
	questions[1].q = to_string(x * y) + "÷" + to_string(y);
	questions[1].a = x / y;

	//複雑な式
	x = uniform_int_distribution<>(1, 100)(rand);
	y = z = w = uniform_int_distribution<>(1, 10)(rand);
	questions[2].q = to_string(x) + "-(" + to_string(y * w) + "+" + to_string(z * w) + ")÷" + to_string(w);
	questions[2].a = x - (y + z);

	cout << "[リクルート試験対策クイズ]\n";

	for (const auto& e : questions)
	{
		cout << e.q << "の答えは？\n";

		int answer;
		cin >> answer;

		if (answer == e.a)
		{
			cout << "正解!\n";
		}
		else
		{
			cout << "間違い!正解は" << e.a << "\n";
		}
	}	//for questions
}