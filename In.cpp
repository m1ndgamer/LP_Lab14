#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"
#include <fstream>
#include "In.h"
#include "Error.h"
#include <ctype.h>
#include <mbstring.h>
#include "Analysis.h"

#define	IS_EMPTY_LINE			(in->text[i] == '|' && (in->text[i - 1] == IN_CODE_ENDLINE))
#define	IS_UNNECESSARY_SPACE	((un_symbol == IN_CODE_SPACE || un_symbol == IN_CODE_TAB) && \
								(in.code[in.text[in.size - 1]] == IN::S))
#define	PREVIOUS_IS_SPACE		(in.code[un_symbol] == IN::S && \
								(in.text[in.size - 1] == IN_CODE_SPACE || in.text[in.size - 1] == IN_CODE_TAB))
#define NEW_LINE 				in.lines++; position = 1;
namespace In
{
	IN getIn(wchar_t infile[])
	{
		bool isLit = false; char symbol; unsigned char un_symbol; int position = 1, literalSize = 0;
		backtickPosition pos;
		std::ifstream fileReader(infile);
		IN in = { 0, 1, 0, new unsigned char[IN_MAX_LEN_TEXT], IN_CODE_TABLE };
		// „тение файла.
		if (fileReader.is_open())
			while (fileReader.get(symbol))
			{
				un_symbol = (unsigned char)symbol;
				if (in.code[un_symbol] == IN::T || in.code[un_symbol] == IN::S)
				{
					// конец/начало строкового литерала
					if (un_symbol == '\'')
					{
						pos = { in.lines, position };
						in.text[in.size++] = un_symbol;
						isLit = !isLit;
						if (!isLit) literalSize = 0;
					}
					// если не строковый литерал
					else if (!isLit)
					{
						if (un_symbol == IN_CODE_ENDLINE)
						{
							// удаление пустых строк
							if (in.text[in.size - 1] != IN_CODE_ENDLINE)
							{
								PREVIOUS_IS_SPACE ? in.text[in.size - 1] = '|' : in.text[in.size++] = '|';
								in.text[in.size++] = IN_CODE_ENDLINE;
								NEW_LINE
							}
						}
#pragma region ”даление лишних пробелов
						else if (PREVIOUS_IS_SPACE) in.text[in.size - 1] = un_symbol;
						else if (IS_UNNECESSARY_SPACE) continue;
#pragma endregion		
						// запрещенные символы
						else if (IS_UPPER_CASE_ENG((char)un_symbol) ||
							IS_UPPER_CASE_RUS((char)un_symbol) ||
							IS_LOWER_CASE_RUS((char)un_symbol))
						{
							throw ERROR_THROW_IN(111, in.lines, position, un_symbol);
						}
						else in.text[in.size++] = un_symbol;
					}
					// если строковый литерал
					else
					{
						++literalSize;
						if (literalSize >= TI_STR_MAXSIZE) throw ERROR_THROW_IN(139, pos.col, pos.row);
						if (un_symbol == IN_CODE_ENDLINE) { NEW_LINE }
						in.text[in.size++] = un_symbol;
					}
					position++;
				}
				else if (in.code[un_symbol] == IN::I) in.ignor++;
				else throw ERROR_THROW_IN(111, in.lines, position, un_symbol);
			}
		else throw ERROR_THROW(110);
		if (in.text[in.size - 1] == IN_CODE_ENDLINE)
		{
			in.size--;
			in.lines--;
		}
		in.text[in.size] = IN_CODE_ENDSTRING;
		fileReader.close();
		return in;
	}
}