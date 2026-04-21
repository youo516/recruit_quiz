#include <iostream>
#include <string>
using namespace std;

//
struct Question
{
	string q;
	int a;
};

int main()
{
	Question questions[] = {
		{"13 x (-5)", 13 * -5},
		{"(-21) ÷ (-3)", -21 / -3},
		{"7 - (4 + 2) ÷ 2", 7 - (4 + 2) / 2},
	};

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