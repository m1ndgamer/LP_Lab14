#pragma once
#include "IT.h"
#include "LT.h"
namespace LEX
{
	struct Lex
	{
		LT::LexTable* lextable;
		IT::IdTable* idTable;
		Lex();
		Lex(LT::LexTable& lt, IT::IdTable& it);
		void Delete();
	};
}
