#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"
#include <fstream>
#include "In.h"
#include "Error.h"
#include <ctype.h>
#include <mbstring.h>

#define	IS_EMPTY_LINE (in->text[i] == '|' && (in->text[i - 1] == IN_CODE_ENDLINE))
#define	IS_UNNECESSARY_SPACE	((in->text[i] == IN_CODE_SPACE || in->text[i] == IN_CODE_TAB) && \
								(in->code[in->text[i - 1]] == IN::S || in->code[in->text[i + 1]] == IN::S || in->text[i + 1] == '|'))

namespace In
{
	IN getIn(wchar_t infile[])
	{
		bool isLit = false; char symbol; unsigned char un_symbol; int position = 1;
		std::ifstream fileReader(infile);
		IN in = { 0, 1, 0, new unsigned char[IN_MAX_LEN_TEXT], IN_CODE_TABLE };
		// „тение файла.
		if (fileReader.is_open())
			while (fileReader.get(symbol))
			{
				un_symbol = (unsigned char)symbol;
				if (in.code[un_symbol] == IN::T || in.code[un_symbol] == IN::S)
				{
					if (un_symbol == IN_CODE_ENDLINE)
					{
						if (in.text[in.size - 1] != IN_CODE_ENDLINE)
						{
							in.text[in.size++] = '|';
							in.text[in.size++] = IN_CODE_ENDLINE;
							in.lines++;
							position = 1;
						}
					}
					else if (un_symbol == '\'')
					{
						in.text[in.size++] = un_symbol;
						isLit = !isLit;
					}
					else if ((	IS_UPPER_CASE_ENG((char)un_symbol) || 
								IS_UPPER_CASE_RUS((char)un_symbol) ||
								IS_LOWER_CASE_RUS((char)un_symbol) )
								&& !isLit)
					{
						throw ERROR_THROW_IN(111, in.lines, position, un_symbol);
					}						
					else
					{
						in.text[in.size++] = un_symbol;
						position++;
					}
				}
				else if (in.code[un_symbol] == IN::I) in.ignor++;
				else if (in.code[un_symbol] == IN::F) { throw ERROR_THROW_IN(111, in.lines, position, un_symbol); }
				else throw ERROR_THROW_IN(111, in.lines, position, un_symbol);
			}
		else throw ERROR_THROW(110);
		if (in.text[in.size - 1] == IN_CODE_ENDLINE) in.size--;
		in.text[in.size] = IN_CODE_ENDSTRING;
		fileReader.close();
		InHandler(&in);
		return in;
	}
		



	// удаление лишних пробелов строки строки
	void InHandler(IN *in)
	{
		int position = 0;
		bool isLit = false;
		for (int i = 0; i < in->size; i++)
		{
			// Ёто строковый литерал?
			if (in->text[i] == '\'')
			{
				in->text[position++] = in->text[i];
				isLit = !isLit;
			}
			else if (isLit || !IS_UNNECESSARY_SPACE)
				in->text[position++] = in->text[i];				
		}
		in->text[position] = IN_CODE_ENDSTRING;
		in->size = position;
	}
}