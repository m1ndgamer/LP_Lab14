#pragma once
#define keyTokens_size 20

struct flagForTypeOfVar
{
	int posInLT = -1;
	enum { DEF = 0, INT = 1, STR = 2 } type = DEF;
};
void Lex(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
bool a_func_var(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeOfVar);