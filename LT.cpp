#include "LT.h"
#include "Error.h"
#include "In.h"
#include <fstream>


LT::Entry::Entry()
{
	lexem = '\0';
	lineNumber = LT_TI_NULLXDX;
	idxTI = LT_TI_NULLXDX;
}

LT::Entry::Entry(const char lex, int lineNum, int id)
{
	lexem = lex;
	lineNumber = lineNum;
	idxTI = id;
}

LT::LexTable::LexTable()
{
	maxSize = LT_MAXSIZE;
	currentSize = 0;
	table = new Entry[LT_MAXSIZE];
}

void LT::LexTable::Add(Entry entry)
{
	(currentSize < maxSize) ? table[currentSize++] = entry : throw ERROR_THROW(121);	
}

LT::Entry LT::LexTable::GetEntry(int number)
{
	if (number < maxSize && number >= 0) return table[number];
	throw ERROR_THROW(121); // to do error;
}

void LT::LexTable::PrintTableInFile(const wchar_t* inFile)
{
	// создания имя файла
	// 2 варианта с расшир. и без
	int i = 0; wchar_t lex[300];
	for (; inFile[i] != IN_CODE_ENDL; i++)
		lex[i] = inFile[i];
	lex[i] = IN_CODE_ENDL;
	wcscat_s(lex, PARM_LEX_DEFAULT_EXT);


	std::ofstream* lexStream = new std::ofstream;
	lexStream->open(lex);

	if (lexStream->is_open())
	{
		int currentString = 0;
		(*lexStream) << IN_CODE_ENDL << currentString + 1 << IN_CODE_TAB;
		for (int i = 0; i < currentSize;)
		{
			if (currentString == table[i].lineNumber)
				(*lexStream) << table[i++].lexem;
			else
			{
				(*lexStream) << IN_CODE_ENDL << currentString++ + 2 << IN_CODE_TAB;

				if (currentString == table[i].lineNumber)
					(*lexStream) << table[i++].lexem;
			}


		}
	}
	else
		throw ERROR_THROW(125);
	lexStream->close();
	delete lexStream;
}

void LT::LexTable::Delete()
{
	delete[] table;
	table = nullptr;
}



