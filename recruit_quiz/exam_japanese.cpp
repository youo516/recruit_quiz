#include"exam_japanese.h"
using namespace std;

//漢字の読み取り問題の作成
QuestionList CreateKanjiExam()
{
	static const struct
	{
		const char* kanji;
		const char* reading;
		const char* meaning;
	}data[] = {
		{ "市井", "しせい", "人が多く集まって暮らすところ、町" },
		{ "捺印", "なついん", "(署名とともに)印鑑を押すこと" },
		{ "相殺", "そうさい", "足し引きの結果、差が無くなること" },
		{ "凡例", "はんれい", "本や図表のはじめに、使い方や約束事を箇条書きにしたもの" },
		{ "約定", "やくじょう", "約束して決めること、契約" },
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	for (int i = 0; i < quizCount; i++)
	{
		const auto& e = data[i];
		questions.push_back({ "「" + string(e.kanji) + "」の読み方を平仮名で答えよ", e.reading });
	}
	return questions;
}