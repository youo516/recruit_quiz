#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <time.h>
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
	//教科データ配列
	static const struct
	{
		const char* name;
		QuestionList(*create)();
	}subjectData[] = {
		{"数学", CreateMathematicsExam},
		{"国語", CreateJapaneseExam},
		{"英語", CreateEnglishExam},
		{"物理", CreatePhysicsExam},
		{"地理", CreatePrefecturesExam},
		{"政治", CreatePoliticsExam},
		{"経済", CreateEconomicsExam},
	};

	vector<Question> questions(3);

	cout << "[リクルート試験対策クイズ]\n";

	cout << "教科を選んでください\n";
	cout << "0=総合テスト\n";

	for (int i = 0; i < size(subjectData); i++)
	{
		cout << i + 1 << '=' << subjectData[i].name << '\n';
	}

	vector<int> questionCnt(size(subjectData));
	int subject;
	cin >> subject;

	if (subject > 0 && subject <= size(subjectData))
	{
		questions = subjectData[subject - 1].create();
	}
	else if (subject == 0)
	{
		questions.clear();
		for (int i = 0; i < size(subjectData); i++)
		{
			QuestionList tmp = subjectData[i].create();
			questions.insert(questions.end(), tmp.begin(), tmp.end());
			questionCnt[i] = (int)tmp.size();
		}
	}

	vector<int> correctCnt(size(subjectData));
	int currentSubjectNo = 0;
	int currentAnsweredCnt = 0;
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
			correctCnt[currentSubjectNo]++;
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
				correctCnt[currentSubjectNo]++;
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

		//回答数が教科の問題数以上になったら次の強化に進む
		if (subject == 0)
		{
			currentAnsweredCnt++;
			if (currentAnsweredCnt >= questionCnt[currentSubjectNo])
			{
				currentSubjectNo++;
				currentAnsweredCnt = 0;
			}
		}
	}	//for questions

	//成績を表示
	cout << "\n---成績---\n";
	if (subject > 0 && subject <= size(subjectData))
	{
		cout << subjectData[subject - 1].name << ":" << correctCnt[0] << "/" << questions.size() << "/n";
	}
	else if (subject == 0)
	{
		//教科ごとの成績を表示しつつ、正答数の合計を表示
		size_t totalCorrectCnt = 0;
		for (int i = 0; i < size(subjectData); i++)
		{
			cout << subjectData[i].name << ":" << correctCnt[i] << "/" << questionCnt[i] << "\n";
			totalCorrectCnt += correctCnt[i];
		}
		cout << "合計:" << totalCorrectCnt << "/" << questions.size() << "\n";
	}

	//成績をファイルに出力する
	static const char filename[] = "リクルート対策試験成績表.txt";
	ofstream ofs(filename, ios_base::app);
	if (!ofs)
	{
		cerr << "Error:" << filename << "を開けません\n";
	}
	else
	{
		//現在の時刻を取得
		const time_t t = time(nullptr);

		//協定世界時刻を時間構造体に変換
		tm examDate;
		localtime_s(&examDate, &t);

		//時間構造体を文字列に変換
		char strDate[100];
		strftime(strDate, size(strDate), "%Y/%m/%d(%a) %T", &examDate);

		if (subject > 0 && subject <= size(subjectData))
		{
			//教科テストの場合、試験した教科の成績だけを出力し、それ以外は空欄とする
			ofs << strDate;
			for (int i = 0; i < size(subjectData); i++)
			{
				ofs << ',';
				if (i == subject - 1)
				{
					ofs << correctCnt[0] << '/' << questions.size();
				}
			}
			ofs << '\n';
			cout << "成績を" << filename << "に出力しました\n";
		}
		else if (subject == 0)
		{
			//総合テストの場合、すべての強化の成績を出力
			ofs << strDate;
			for (int i = 0; i < size(subjectData); i++)
			{
				ofs << ',' << correctCnt[i] << '/' << questionCnt[i];
			}
			ofs << '\n';
			cout << "成績を" << filename << "に出力しました\n";
		}
	}
}