#include "exam_geography.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

//都道府県の問題を作成
QuestionList CreatePrefecturesExam()
{
	//都道府県データ
	struct PrefectureData
	{
		string name;
		string capital;
		vector<string> features;
	};
	vector<PrefectureData> data;

	{
		constexpr char filename[] = "japanese_prefectures.txt";
		ifstream ifs(filename);
		if (!ifs)
		{
			cerr << "error : " << filename << "を読み込めません\n";
			return {};
		}

		string s;
		while (true)
		{
			getline(ifs, s);		//一行読み取り
			if (!ifs)
			{
				break;			//ファイル終端のため終了
			}
			const vector<string> v = Split(s, ',');
			data.push_back({ v[0], v[1], vector<string>(v.begin() + 2, v.end()) });
		}
	}

	constexpr int quizCnt = 5;
	QuestionList questions;
	questions.reserve(quizCnt);
	vector<int> indices = CreateRandomIndices((int)data.size());
	random_device rd;

	const int type = uniform_int_distribution<>(0, 2)(rd);
	switch (type)
	{
	case 0:
		//特徴から都道府県を答える
		for (int i = 0; i < quizCnt; i++)
		{
			//正解以外の答えをランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices((int)data.size(), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "以下の特徴を持つ都道府県の番号を選べ\n";

			//都道府県の特徴をランダムな順番で連結し、問題文に追加
			const auto& features = data[correctIndex].features;
			vector<int> featureIndices = CreateRandomIndices((int)features.size());
			s += features[featureIndices[0]];
			for (int j = 1; j < features.size(); j++)
			{
				s += ',';
				s += features[featureIndices[j]];
			}

			//答えとなる都道府県を問題文に追加
			for (int j = 0; j < 3; j++)
			{
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].name;
			}

			//問題文と答えのペアを問題配列に追加
			questions.push_back({ s, to_string(correctNo) });
		}
		break;

	case 1:
		//都道府県を表す特徴を答える
		for (int i = 0; i < quizCnt; i++)
		{
			//正解以外の答えをランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices((int)data.size(), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + data[correctIndex].name + "」の特徴を持つ都道府県の番号を選べ";
			for (int j = 0; j < 3; j++)
			{
				const auto& features = data[correctIndex].features;
				const int n = uniform_int_distribution<>(0, (int)features.size() - 1)(rd);
				s += "\n " + to_string(j + 1) + ":" + features[n];
			}

			//問題文と答えのペアを問題配列に追加
			questions.push_back({ s, to_string(correctNo) });
		}
		break;

	case 2:
		//
		vector<pair<string, string>> differentNames;
		for (const auto& e : data)
		{
			//都道府県名と県庁所在地名の長さが異なるか、末尾を除く部分の文字列が異なる場合リストに追加
			if (e.name.size() != e.capital.size() || memcmp(e.name.data(), e.capital.data(), e.name.size() - 2) != 0)
			{
				differentNames.push_back({ e.name, e.capital });
			}
		}

		//作成したリストからランダムに出題
		vector<int> indices = CreateRandomIndices((int)differentNames.size());
		for (int i = 0; i < quizCnt; i++)
		{
			const int correctIndex = indices[i];
			questions.push_back({ "「" + differentNames[correctIndex].first + "」の県庁所在地を答えよ", differentNames[correctIndex].second });
		}
		break;
	}
	return questions;
}