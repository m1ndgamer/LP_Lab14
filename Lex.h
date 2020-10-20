#pragma once
#include "IT.h"
#include "LT.h"
namespace LEX
{
	struct Lex
	{
		LT::LexTable* lextable;
		IT::IdTable* idTable;
		Lex(LT::LexTable& lt, IT::IdTable& it);
		Lex();
		void Delete();
	};
}
