#include "stdafx.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "FST.h"
#include "RegularExpessions.h"
#include "IT.h"

bool tokenAnaliz(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	static flagForTypeOfVar FlagForTypeOfVar;
	// первая буква в токене
	switch (*token)
	{
	case LEX_SEMICOLON:
	{
		lexTable.Add({ LEX_SEMICOLON, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_COMMA:
	{
		lexTable.Add({ LEX_COMMA, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFTBRACE:
	{
		lexTable.Add({ LEX_LEFTBRACE, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHTBRACE:
	{
		lexTable.Add({ LEX_RIGHTBRACE, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFTHESIS:
	{
		lexTable.Add({ LEX_LEFTHESIS, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHTHESIS:
	{
		lexTable.Add({ LEX_RIGHTHESIS, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_PLUS:
	{
		lexTable.Add({ LEX_PLUS, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_MINUS:
	{
		lexTable.Add({ LEX_MINUS, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_STAR:
	{
		lexTable.Add({ LEX_STAR, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_DIRSLASH:
	{
		lexTable.Add({ LEX_DIRSLASH, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case LEX_EQUAL_SIGN:
	{
		lexTable.Add({ LEX_EQUAL_SIGN, strNumber, LT_TI_NULLXDX });
		return true;
	}

	case 'f':
	{
		FST::FST* a_function = new FST::FST(A_FUNCTION(token));
		if (FST::execute(*a_function))
		{
			lexTable.Add({ LEX_FUNCTION, strNumber, LT_TI_NULLXDX });
			delete a_function;
			a_function = NULL;
			return true;
		}
		else
		{
			delete a_function;
			a_function = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	case 'i':
	{
		FST::FST* a_integer = new FST::FST(A_INTEGER(token));
		if (FST::execute(*a_integer))
		{
			lexTable.Add({ LEX_INTEGER, strNumber, LT_TI_NULLXDX });

			delete a_integer;
			a_integer = NULL;
			//FlagForTypeOfVar.posInLT = lexTable.current_size - 1;
			//FlagForTypeOfVar.type = flagForTypeOfVar::INT;
			return true;
		}
		else
		{
			delete a_integer;
			a_integer = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	case 's':
	{
		FST::FST* a_string = new FST::FST(A_STRING(token));
		if (FST::execute(*a_string))
		{
			lexTable.Add({ LEX_STRING, strNumber, LT_TI_NULLXDX });

			delete a_string;
			a_string = NULL;
			//FlagForTypeOfVar.posInLT = lexTable.current_size - 1;
			//FlagForTypeOfVar.type = flagForTypeOfVar::STR;
			return true;
		}
		else
		{
			delete a_string;
			a_string = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	case '\"':
	{
		/*FST::FST* string_literal = new FST::FST(A_STRING_LITERAL(token));
		if (FST::execute(*string_literal))
		{
			int i = idTable.IsLit(token);
			if (i != LT_TI_NULLXDX)
				lexTable.Add({ LEX_LITERAL, strNumber, i });
			else
			{
				idTable.Add({ "\0", "\0", IT::IDDATATYPE::STR,  IT::IDTYPE::L });

				idTable.table[idTable.current_size - 1].value.vstr.len = 0;
				int i = 0, j = 0;
				for (; token[i] != '\0'; i++)
				{
					if (token[i] != '\"')
					{
						idTable.table[idTable.current_size - 1].value.vstr.str[j] = token[i];
						idTable.table[idTable.current_size - 1].value.vstr.len++;
						j++;
					}
				}
				idTable.table[idTable.current_size - 1].value.vstr.str[j] = '\0';

				lexTable.Add({ LEX_LITERAL, strNumber, idTable.current_size - 1 });
			}

			delete string_literal;
			string_literal = NULL;
			return true;*/
	}

	/*delete string_literal;
	string_literal = NULL;
	return false;*/


	case 'd':
	{
		FST::FST* a_declare = new FST::FST(A_DECLARE(token));
		if (FST::execute(*a_declare))
		{
			lexTable.Add({ LEX_DECLARE, strNumber, LT_TI_NULLXDX });

			delete a_declare;
			a_declare = NULL;
			return true;
		}
		else
		{
			delete a_declare;
			a_declare = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	case 'r':
	{
		FST::FST* a_return = new FST::FST(A_RETURN(token));
		if (FST::execute(*a_return))
		{
			lexTable.Add({ LEX_RETURN, strNumber, LT_TI_NULLXDX });

			delete a_return;
			a_return = NULL;
			return true;
		}
		else
		{
			delete a_return;
			a_return = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	case 'p':
	{
		FST::FST* a_print = new FST::FST(A_PRINT(token));
		if (FST::execute(*a_print))
		{
			lexTable.Add({ LEX_PRINT, strNumber, LT_TI_NULLXDX });

			delete a_print;
			a_print = NULL;
			return true;
		}
		else
		{
			delete a_print;
			a_print = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}

	default:
	{
		//FST::FST* integer_literal = new FST::FST(A_INTEGER_LITERAL(token));
		//if (FST::execute(*integer_literal))
		//{
		//	int i = idTable.IsLit(token);
		//	if (i != LT_TI_NULLXDX)
		//		lexTable.Add({ LEX_LITERAL, strNumber, i });
		//	else
		//	{
		//		//idTable.Add({ "\0", "\0", IT::IDDATATYPE::INT,  IT::IDTYPE::L });
		//		//idTable.table[idTable.current_size - 1].value.vint = atoi(token);
		//		//lexTable.Add({ LEX_LITERAL, strNumber, idTable.current_size - 1 });
		//	}

		//	delete integer_literal;
		//	integer_literal = NULL;
		//	return true;
		//}
		//else
		//{
		//	delete integer_literal;
		//	integer_literal = NULL;

			//return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}
}


void Lex(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[64]{};
	int lineNumber = 0;
	int positionInLine = 0;

	for (int i = 0, j = 0; i < source.size; i++)
	{
		if (source.code[source.text[i]] == In::IN::N)
		{
			buffer += source.text[i];
			positionInLine++;
			continue;
		}
		else
		{
			if (j != 0)
			{
				i--;
				buffer[j] = '\0';
				if (tokenAnaliz(buffer, lineNumber, lexTable, idTable))
				{
					buffer[0] = '\0'; j = 0;
					continue;
				}
				/*else
					throw ERROR_THROW_IN(121, strNum, posInStr);*/
			}
			else
			{
				// скобки
				if (source.text[i] == '\"')
				{
					buffer[j++] = source.text[i++];
					for (int c = 0; source.text[i] != '\"'; c++)
					{
						if (c <= TI_STR_MAXSIZE)
						{
							buffer[j++] = source.text[i++];
						}
						//else
							//throw ERROR_THROW_IN(126, strNum, posInStr);
					}
					if (source.text[i] == '\"')
					{
						buffer[j] = source.text[i];
						if (tokenAnaliz(buffer, lineNumber, lexTable, idTable))
						{
							buffer[0] = '\0'; j = 0;
							continue;
						}
						else {}
							//throw ERROR_THROW_IN(121, lineNumber, positionInLine);
					}
					else {}
						//throw ERROR_THROW_IN(127, lineNumber, positionInLine);
				}
				// пробелы
				if (source.text[i] != '\n')
				{
					if (source.text[i] == ' ' || source.text[i] == '\t')
					{
						positionInLine++;
						continue;
					}

					buffer[0] = source.text[i]; buffer[1] = '\0';
					if (tokenAnaliz(buffer, lineNumber, lexTable, idTable))
						positionInLine++;
					else
					{
					}
						//throw ERROR_THROW_IN(121, lineNumber, positionInLine);

					buffer[0] = '/0'; j = 0; // хмммммм?
				}
			}
		}

		if (source.text[i] == '\n')
		{
			lineNumber++;
			positionInLine = 0;
		}
	}
	delete[] buffer;
}


/// <summary>
/// 
/// </summary>
/// <param name="token"></param>
/// <param name="strNumber"></param>
/// <param name="lexTable"></param>
/// <param name="idTable"></param>
/// <param name="FlagForTypeOfVar"></param>
/// <returns></returns>
bool a_func_var(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeOfVar)
{
	FST::FST* identificator = new FST::FST(A_IDENTIFICATOR(token));
	if (FST::execute(*identificator))
	{
		bool alreadyChecked = false;
		//для функций
		if (strcmp(token, "main") == 0 ||
			((lexTable.GetEntry(lexTable.current_size - 1).lexema == LEX_FUNCTION &&
				lexTable.GetEntry(lexTable.current_size - 2).lexema == 't') &&
				FlagForTypeOfVar.posInLT == lexTable.current_size - 2))
		{
			if (idTable.IsId(token) == -1)
			{
				if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
					idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });

				if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
					idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F });

				if (strcmp(token, "main") == 0)
					idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });

				FlagForTypeOfVar.posInLT = -1;
				FlagForTypeOfVar.type = flagForTypeOfVar::DEF;

				lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
				alreadyChecked = true;
			}
			else
			{
			}
				//throw ERROR_THROW_IN(123, strNumber, -1);
		}

		//для переменной(с проверкой переопределения)
		if (!alreadyChecked &&
			(lexTable.GetEntry(lexTable.current_size - 1).lexema == 't' &&
				lexTable.GetEntry(lexTable.current_size - 2).lexema == LEX_DECLARE &&
				FlagForTypeOfVar.posInLT == lexTable.current_size - 1))
		{
			bool isLeftBraceWas = false;
			for (int i = lexTable.current_size - 1; i > 0; i--)
			{
				if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
					isLeftBraceWas = true;

				if (isLeftBraceWas &&
					lexTable.GetEntry(i).lexema == LEX_ID &&
					idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
				{
					if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
					{
						if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::V });

						if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::V });

						FlagForTypeOfVar.posInLT = -1;
						FlagForTypeOfVar.type = flagForTypeOfVar::DEF;

						lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
						alreadyChecked = true;
						break;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, -1);

				}
			}
		}

		//для параметра функции
		if (!alreadyChecked &&
			(lexTable.GetEntry(lexTable.current_size - 1).lexema == 't' && FlagForTypeOfVar.posInLT == lexTable.current_size - 1))
			for (int i = lexTable.current_size - 1; i > 0; i--)
			{
				if (lexTable.GetEntry(i).lexema == LEX_ID &&
					idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
				{
					if (lexTable.GetEntry(i - 1).lexema == LEX_FUNCTION && lexTable.GetEntry(i - 2).lexema == 't')
					{
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
						{
							if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::P });

							if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::P });

							FlagForTypeOfVar.posInLT = -1;
							FlagForTypeOfVar.type = flagForTypeOfVar::DEF;

							lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
							alreadyChecked = true;
							break;
						}
						else
							throw ERROR_THROW_IN(123, strNumber, -1);
					}
				}
			}

		//добавление идентификаторов с учетом области видимости
		if (!alreadyChecked)
		{
			bool isLeftBraceWas = false;
			for (int i = lexTable.current_size - 1; i > 0; i--)
			{
				if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
					isLeftBraceWas = true;

				if (isLeftBraceWas &&
					lexTable.GetEntry(i).lexema == LEX_ID &&
					idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
				{
					int tempIndex = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id);
					if (tempIndex != -1)
					{
						lexTable.Add({ LEX_ID, strNumber, tempIndex });
						break;
					}
					else
					{
						tempIndex = idTable.IsId(token);
						if (tempIndex != -1 &&
							idTable.GetEntry(tempIndex).idtype == IT::IDTYPE::F)
						{
							lexTable.Add({ LEX_ID, strNumber, tempIndex });
							break;
						}
						else
							throw ERROR_THROW_IN(129, strNumber, -1);
					}

				}
			}
		}

		delete identificator;
		identificator = NULL;
		return true;
	}
	else
	{
		delete identificator;
		identificator = NULL;
		return false;
	}
}