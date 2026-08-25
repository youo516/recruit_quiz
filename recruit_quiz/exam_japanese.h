#pragma once
#include "question.h"

//漢字の読み取り問題の作成
QuestionList CreateKanjiExam();

//慣用句の意味を答える問題を作成
QuestionList CreateIdiomExam();

//同音異義語の問題を作成する
QuestionList CreateHomophoneExam();

//対義語の問題を作成
QuestionList CreateAntonymExam();

//類義語の問題を作成
QuestionList CreateSynonymExam();

//国語の問題を作成
QuestionList CreateJapaneseExam();