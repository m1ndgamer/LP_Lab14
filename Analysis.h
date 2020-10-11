#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#define ANALYSIS_ENDLINE '|'
#define keyTokens_size 20

void parsingIntoLexems(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
bool isIdentificator(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, bool isKeyword = 0);

struct backtickPosition
{
	int row;
	int col;
};