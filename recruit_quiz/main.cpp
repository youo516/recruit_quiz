#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "question.h"
#include "utility.h"
#include "exam_mathematics.h"
#include "exam_japanese.h"
#include "exam_english.h"
#include "exam_science.h"
#include "exam_geography.h"
#include "exam_politics.h"
#include "exam_economics.h"
using namespace std;

int main()
{
	vector<Question> questions(3);

	cout << "[リクルート試験対策クイズ]\n";

	cout << "教科を選んでください\n1.数学\n2.国語\n3.英語\n4.理科\n5.地理\n6.政治\n7.経済\n";
	int subject;
	cin >> subject;

	if (subject == 1)
	{
		questions = CreateMathematicsExam();
	}
	else if (subject == 2)
	{
		questions = CreateJapaneseExam();
	}
	else if (subject == 3)
	{
		questions = CreateEnglishExam();
	}
	else if (subject == 4)
	{
		questions = CreatePhysicsExam();
	}
	else if (subject == 5)
	{
		questions = CreatePrefecturesExam();
	}
	else if (subject == 6)
	{
		questions = CreatePoliticsExam();
	}
	else if (subject == 7)
	{
		questions = CreateEconomicsExam();
	}

	for (const auto& e : questions)
	{
		cout << e.q << "\n";

		string answer;
		cin >> answer;

		//入力された答えをSJISからASCIIに変換
		const string ascii = ConvertSjisNumberToAscii(answer);

		//変換が成功した場合はASCII文字列に置き換える
		if (!ascii.empty())
		{
			answer = ascii;
		}

		if (answer == e.a)
		{
			cout << "正解!\n";
		}
		else if (e.b.empty())
		{
			cout << "不正解!正解は" << e.a << "\n";
		}
		else
		{
			//回答が複数存在する場合
			bool isMatch = false;
			for (const auto& b : e.b)
			{
				if (answer == b)
				{
					isMatch = true;
					break;
				}
			}

			//比較結果を出力
			if (isMatch)
			{
				cout << "正解!\n";
			}
			else
			{
				cout << "不正解!正解は" << e.a << "(または";

				for (auto& b : e.b)
				{
					cout << "、" << b;
				}

				cout << ")\n";
			}
		}
	}	//for questions
}