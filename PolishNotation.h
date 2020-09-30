#pragma once
#include "LT.h"
#include "IT.h"
namespace PolishNotation
{
	bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable);
	int getPriority(char sign);
	bool isOperation(char symbol);
	bool isBrace(char symbol);
	bool isOperand(char symbol);
}