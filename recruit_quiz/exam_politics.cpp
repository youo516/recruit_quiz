#include "exam_politics.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>
using namespace std;

//日本の政治の問題を作成
QuestionList CreatePoliticsExam()
{
	//政治問題データ
	struct PoliticsData
	{
		string genre;
		string text;
		vector<string> answers;
	};
	unordered_map<string, vector<PoliticsData>> data;

	//政治問題データを読み込む
	{
		constexpr char filename[] = "japanese_politics.txt";
		ifstream ifs(filename);
		if (!ifs)
		{
			cerr << "error : " << filename << "を読み込めません\n";
			return {};
		}

		while (true)
		{
			string s;
			getline(ifs, s);		//一行読み取り
			if (!ifs)
			{
				break;			//ファイル終端のため終了
			}
			const vector<string> v = Split(s, ',');
			const string& genre = v[0];
			data[genre].push_back({ genre, v[1], vector<string>(v.begin() + 2, v.end())});
		}
	}

	constexpr int genreCnt = 2;
	constexpr int quizCnt = 5;
	QuestionList questions;
	questions.reserve(genreCnt* quizCnt);
	random_device rd;

	//ランダムに選んだ二つのジャンルから、ジャンル内でランダムに5問出題
	const vector<int> genreIndices = CreateRandomIndices((int)data.size());
	for (int i = 0; i < genreCnt; i++)
	{
		//出題するジャンルを選択
		auto itr = data.begin();
		advance(itr, genreIndices[i]);
		const auto& genre = itr->second;

		//ジャンル内でランダムに5問選ぶ
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

			//空欄のうち1つをランダムに選ぶ
			const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

			//問題文のコピーを作成しつつ、選ばれなかった空欄を「答えに」置き換える
			string s = "[" + question.genre + "]次の文章の[ ? ]に入る単語を答えよ。\n";
			int from = 0;
			for (int k = 0; k < blanks.size(); k++)
			{
				const int end = blanks[k];
				s.append(question.text, from, end - from);

				if (k != index)
				{
					s.append(question.answers[k]);
				}
				else
				{
					s.append("[ ? ]");
				}
				from = end + 2;
			}
			s.append(question.text, from);

			questions.push_back({ s, question.answers[index] });
		}
	}

	return questions;
}