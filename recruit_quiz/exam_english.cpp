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
		{"routine", "ルーティン", "決まった手順、日課"},
		{"management", "マネジメント", "管理、経営"},
		{"account", "アカウント", "会計、口座"},
		{"unique", "ユニーク", "他に類を見ない、個性的な"},
		{"variety", "バラエティー", "変化に富む、多様な"},
		{"schedule", "スケジュール", "予定、計画"},
		{"agenda", "アジェンダ", "課題、議題"},
		{"technology", "テクノロジー", "科学技術"},
		{"collaboration", "コラボレーション", "協力、共同事業、共同作業"},
		{"tax", "タックス", "税金"},
		{"stock", "ストック", "在庫、株券"},
		{"product", "プロダクト", "製品"},
		{"booking", "ブッキング", "予約、帳簿への記入"},
		{"weight", "ウェイト", "重さ"},
		{"conpliance", "コンプライアンス", "法令・社会的規範を守る"},
		{"receipt", "レシート", "領収書"},
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
		//正しい番号を答える問題
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

//英語の定型文の問題を作成
QuestionList CreateEnglishPhraseExam()
{
	const struct {
		const char* phrase;
		const char* meaning;
		const char* example;
		const char* translation;
		int blankCnt;
		int blankOptions[3];
	}data[]{
		{"too [A] to [B]", "とても[A]なので[B]できない", "The tea was too hot to drink.", "お茶が熱すぎて飲めなかった。", 2,{3, 5}},
		{"be looking forward to [A]", "[A]を楽しみにする", "I'm looking forward to seeing you.", "私はあなたに会うのを楽しみにしています。", 3,{1, 2, 3}},
		{"according to [A]", "[A]によると", "According to the weather forcast, today is rain.", "天気予報によると今日は雨だ", 2,{0, 1}},
		{"as soon as [A]", "[A]するとすぐに", "As soon as I arrive, I'll call you.", "到着したらすぐに連絡します。", 3,{0, 1, 2}},
		{"be not supposed to[A]", "[A]してはいけないことになっている", "You are not supposed to enter this room.", "この部屋に入ってはいけません", 3,{2, 3, 4}},
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

			//例文を単語に分解
			vector<string> words;
			const char* start = e.example;
			for (const char* p = e.example; *p; p++)
			{
				words.push_back(string(start, p));
				start = p + 1;
			}
			words.push_back(string(start));

			//穴にする単語を選ぶ
			int n = uniform_int_distribution<>(0, e.blankCnt - 1)(rd);
			int blankIndex = e.blankOptions[n];

			//穴にする位置の単語を答えとする
			string a = words[blankIndex];

			//穴にする位置の単語を「空欄」に置き換える
			words[blankIndex] = "[ ? }";

			//単語を分に復元
			string s = words[0];
			for (int j = 1; j < words.size(); j++)
			{
				s += " " + words[j];
			}

			//問題文と答えを追加
			questions.push_back({ "[ ? ] に適切な語を入れて英文を完成させよ\n" + string(e.translation) + "\n" + s, a });
		}
		break;

	case 1:
		//正しい番号を答える問題
		for (int i = 0; i < quizCnt; i++)
		{
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題を作成
			string s = "「" + string(data[correctIndex].phrase) + "」の意味として正しい番号を選べ\n";
			for (int j = 0; j < 3; j++)
			{
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].meaning;
			}

			questions.push_back({ s, to_string(correctNo) });
		}
		break;

	case 2:
		//正しい番号を答える問題
		for (int i = 0; i < quizCnt; i++)
		{
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題を作成
			string s = "「" + string(data[correctIndex].meaning) + "」の意味として正しい番号を選べ\n";
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