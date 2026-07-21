#include "utility.h"
#include <random>
using namespace std;

//ランダムな番号配列を作成
vector<int> CreateRandomIndices(int n)
{
	//番号を配列に格納
	vector<int> indices(n);
	for (int i = 0; i < n; i++)
	{
		indices[i] = i;
	}

	//番号の配列をシャッフル
	Shuffle(indices);
	return indices;
}

void Shuffle(vector<int>& indices)
{
	const int n = static_cast<int>(indices.size());

	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--)
	{
		const int j = uniform_int_distribution<>(0, i)(rand);
		const int temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}
}

//間違った番号の配列を作成
vector<int> CreateWrongIndices(int n, int correctIndex)
{
	//番号を配列に格納
	vector<int> indices(n - 1);
	for (int i = 0; i < correctIndex; i++)
	{
		indices[i] = i;
	}
	for (int i = correctIndex; i < n - 1; i++)
	{
		indices[i] = i + 1;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}

//文字列を分割する
vector <string> Split(const string& s, char c)
{
	vector<string> v;

	//すべての文字列をループ処理
	auto begin = s.begin();
	const auto end = s.end();
	for (auto p = begin; p != end; ++p)
	{
		//区切り文字の前までを文字列として分割
		if (*p == c)
		{
			v.push_back(string(begin, p));
			begin = p + 1;
		}
	}

	//残りの部分を配列に追加
	v.push_back(string(begin, end));

	return v;
}

//SJIS数値文字列をASCII数値文字列に変換する
std::string ConvertSjisNumberToAscii(const std::string& sjis)
{
	//数値文字のSJISからASCIIへの変換表
	static const struct
	{
		unsigned int sjis;
		char ascii;
	}conversionTable[] = {
		{0x824f, '0'}, {0x8250, '1'}, {0x8251, '2'}, {0x8252, '3'}, {0x8253, '4'},{0x8254, '5'},{0x8255, '6'},{0x8256, '7'},{0x8257, '8'},{0x8258, '9'},{0x8244, '.'},{0x817c, '-'},
	};

	//文字コードを変換
	string ascii;
	for (auto i = sjis.begin(); i != sjis.end(); i++)
	{
		const unsigned char a = (unsigned char)i[0];
		if (a < 0x80)
		{
			//ASCII文字の場合はそのままコピー
			ascii.push_back(*i);
		}
		else
		{
			//SJIS文字の場合はASCII文字に変換
			const unsigned int code = a * 0x100 + (unsigned char)i[1];
			const auto itr = find_if(begin(conversionTable), end(conversionTable), [code](const auto& e) {return e.sjis == code; });
			if (itr == end(conversionTable))
			{
				break;
			}
			ascii.push_back(itr->ascii);
			i++;
		}
	}
	return ascii;
}