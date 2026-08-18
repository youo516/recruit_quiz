#include "exam_economics.h"

#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>
using namespace std;

//経済の問題を作成
QuestionList CreateEconomicsExam()
{
	//経済問題データ
	struct EconomicsData
	{
		string genre;
		string text;
		vector<vector<string>> answers;
	};
	unordered_map<string, vector<EconomicsData>> data;

	//経済問題のデータを読み込み
	{
		constexpr char filename[] = "japanese_economics.txt";
		ifstream ifs(filename);
		if (!ifs)
		{
			cerr << "error：" << filename << "を読み込めません\n";
			return {};
		}

		while (true)
		{
			string s;
			getline(ifs, s);
			if (!ifs) break;
			const vector<string> v = Split(s, ',');
			const string& genre = v[0];

			//答えを解析
			vector<vector<string>> answers;
			for (auto i = v.begin() + 2; i != v.end(); i++)
			{
				answers.push_back(Split(*i, '|'));
			}

			//問題データを追加
			data[genre].push_back({ genre, v[1], answers });
		}
	}

	constexpr int genreCnt = 2;
	constexpr int quizCnt = 5;
	QuestionList questions;
	questions.reserve(genreCnt* quizCnt);
	random_device rd;

	//ランダムに選んだ2つのジャンルから、ジャンル内でランダムに選出
	const vector<int> genreIndices = CreateRandomIndices((int)data.size());
	for (int i = 0; i < genreCnt; i++)
	{
		//出題するジャンルを選択
		auto itr = data.begin();
		advance(itr, genreIndices[i]);
		const auto& genre = itr->second;

		//ジャンル内でランダムに選出
		const vector<int> questionIndices = CreateRandomIndices((int)genre.size());
		for (int j = 0; j < quizCnt; j++)
		{
			const auto& question = genre[questionIndices[j]];

			//空欄の位置と数を調べる
			vector<int> blanks;
			for (int k = 0; k < question.text.size() - 1; k++)
			{
				if (question.text[k] == '{' && question.text[k + 1] == '}')
				{
					blanks.push_back(k);
				}
			}

			//空欄のうち一つをランダムに選出
			const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

			//問題文のコピーを作成しつつ、選ばれなかった空欄を答えに置き換える
			string s = "[" + question.genre + "] 次の文章の[ ? ]に入る単語を答えよ\n";
			int from = 0;
			for (int k = 0; k < blanks.size(); k++)
			{
				const int end = blanks[k];
				s.append(question.text, from, end - from);

				if (k != index)
				{
					s += question.answers[k][0];
				}
				else
				{
					s.append("[ ? ]");
				}

				from = end + 2;
			}
			s.append(question.text, from);

			questions.push_back({ s, question.answers[index][0] });

			//回答が複数ありうる場合、それらを答えbの配列に代入
			const auto& answer = question.answers[index];
			if (answer.size() > 1)
			{
				questions.back().b.assign(answer.begin() + 1, answer.end());
			}
		}
	}

	return questions;
}