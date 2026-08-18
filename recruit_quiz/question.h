#pragma once
#include <string>
#include <vector>

//–â‘è•¶‚Æ‰ñ“š‚ğ‚Ü‚Æ‚ß‚é\‘¢‘Ì
struct Question
{
	std::string q;
	std::string a;
	std::vector<std::string> b;
};

//–â‘è‚Ì”z—ñ‚ğ•\‚·Œ^
using QuestionList = std::vector<Question>;