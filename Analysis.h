#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#define ANALYSIS_ENDLINE '|'
#define keyTokens_size 20

struct flagForTypeOfVar
{
	enum { V = 1, F = 2, P = 3, L = 3 } ;
	enum { INT = 1, STR = 2 } type = INT;
};
void parsingIntoLexems(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
bool isIdentificator(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable);