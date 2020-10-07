#include "Lex.h"
namespace LEX
{
	Lex::Lex()
	{
		lextable;
		idTable;
	}

	Lex::Lex(LT::LexTable& lt, IT::IdTable& it)
	{
		lextable = &lt;
		idTable = &it;
	}
	void Lex::Delete()
	{
		idTable->Delete();
		lextable->Delete();
		lextable = nullptr;
		idTable = nullptr;
	}
}

