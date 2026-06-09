#include "exam_english.h"
#include "utility.h"
#include <random>
using namespace std;

//英単語の問題を作成
QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word;
		const char* reading;
		const char* meaning;
	}data[]{
		{"state", "ステート", "状態"},
		{"business", "ビジネス", "事業、仕事"},
		{"abstruct", "アブストラクト", "抽象的な"},
		{"concrete", "コンクリート", "具体的な"},
		{"digital", "デジタル", "数字で情報を伝える"},
		{"analogue", "アナログ", "類似している、類似物"},
		{"exchange", "エクスチェンジ", "交換、両替、為替"},
		{"infrastructure", "インフラストラクチャ", "下部構造、基盤となる施設や設備"},
		{"knowledge", "ナレッジ", "知識"},
		{"credit", "クレジット", "信用"},
	};

	constexpr int quizCnt = 5;
	QuestionList questions;
	questions.reserve(quizCnt);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//問題の種類をランダムに出題
	const int type = uniform_int_distribution<>(0, 3)(rd);
	switch (type)
	{
	case 0:
		for (int i = 0; i < quizCnt; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({ "「" + string(e.meaning) + "」を意味する英単語を答えよ", e.word });
		}
		break;

	case 1:
		for (int i = 0; i < quizCnt; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({ "カタカナの読み「" + string(e.reading) + "」に対応した英単語を答えよ", e.word });
		}
		break;

	case 2:
		for (int i = 0; i < quizCnt; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({ string(e.word) + "の読みをカタカナで答えよ", e.word });
		}
		break;

	case 3:
		//正しい熟語を答える問題
		for (int i = 0; i < quizCnt; i++)
		{
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題を作成
			string s = "「" + string(data[correctIndex].word) + "」の意味として正しい番号を選べ\n";
			for (int j = 0; j < 3; j++)
			{
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].meaning;
			}

			questions.push_back({ s, to_string(correctNo) });
		}
		break;
	}

	return questions;
}