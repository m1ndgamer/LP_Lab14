#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"
#include <fstream>
#include "In.h"
#include "Error.h"
#include <ctype.h>
#include <mbstring.h>


namespace In
{
	IN getIn(wchar_t infile[])
	{
		char symbol; unsigned char un_symbol; int position = 1;
		std::ifstream fileReader(infile);
		IN in = { 0, 1, 0, new unsigned char[IN_MAX_LEN_TEXT], IN_CODE_TABLE };
		// Чтение файла.
		if (fileReader.is_open())
			while (fileReader.get(symbol))
			{
				un_symbol = (unsigned char)symbol;
				if (in.code[un_symbol] == IN::T || in.code[un_symbol] == IN::A || in.code[un_symbol] == IN::N)
				{
					in.text[in.size++] = un_symbol; position++;
				}
				else if (in.code[un_symbol] == IN::I) in.ignor++;
				else if (in.code[un_symbol] == IN::F) { throw ERROR_THROW_IN(111, in.lines, position, un_symbol); }
				else
				{
					if (un_symbol == IN_CODE_ENDLINE)
					{
						in.text[in.size++] = in.code[un_symbol];
						in.lines++;
						position = 1;
					}
				}
			}
		else throw ERROR_THROW(110);
		in.text[in.size] = IN_CODE_ENDSTRING;
		fileReader.close();	
		InHandler(&in);
		return in;
	}

	// удаление лишних пробелов строки строки
	void InHandler(IN *in)
	{
		int position = 0;
		for (int i = 0; i < in->size; i++)
		{
			if (!(in->text[i] == IN_CODE_SPACE && (in->code[in->text[i - 1]] == IN::A || in->code[in->text[i + 1]] == IN::A)) &&
			!(in->text[i] == '|' && in->text[i + 1] == '|'))
			{
				in->text[position++] = in->text[i];
			}
		}
		if (in->text[position - 1] == '|') position--;
		in->text[position] = IN_CODE_ENDSTRING;
		in->size = position;
	}
}