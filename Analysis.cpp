#include "stdafx.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "FST.h"
#include "RegularExpessions.h"
#include "IT.h"
#include "Error.h"

#define RESET_BUFFER buffer[0] = '\0'; j = 0;
#define NEXT_LINE lineNumber++; positionInLine = 0;
#define CREATE_AUTOMAT(expression) FST::FST* automat = new FST::FST(expression(token));
#define ADD_LEXEM(lexem) lexTable.Add({ lexem, strNumber, LT_TI_NULLXDX }); \
					return true;
#define DELETE_AUTOMAT delete automat; automat = NULL;
#define IS_CORRECT if (FST::execute(*automat))
#define IS_FUNC_VARIABLE return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
								IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(LEX_INTEGER) } \
								else { DELETE_AUTOMAT IS_FUNC_VARIABLE }

bool tokenAnaliz(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	static flagForTypeOfVar FlagForTypeOfVar;
	// первая буква в токене
	switch (*token)
	{
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

			return a_func_var(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
		}
	}
	/*case LEX_SEMICOLON: ADD_LEXEM(LEX_SEMICOLON)
	case LEX_COMMA: ADD_LEXEM(LEX_SEMICOLON)
	case LEX_LEFTBRACE: ADD_LEXEM(LEX_LEFTBRACE)
	case LEX_RIGHTBRACE: ADD_LEXEM(LEX_RIGHTBRACE)
	case LEX_LEFTHESIS: ADD_LEXEM(LEX_LEFTHESIS)
	case LEX_RIGHTHESIS: ADD_LEXEM(LEX_RIGHTHESIS)
	case LEX_PLUS: ADD_LEXEM(LEX_PLUS)
	case LEX_MINUS: ADD_LEXEM(LEX_MINUS)
	case LEX_STAR: ADD_LEXEM(LEX_STAR)
	case LEX_DIRSLASH: ADD_LEXEM(LEX_DIRSLASH)
	case LEX_EQUAL_SIGN: ADD_LEXEM(LEX_EQUAL_SIGN)
	case 'f': { TOKEN_PROCESS(A_FUNCTION, LEX_FUNCTION) }
	case 'i': { TOKEN_PROCESS(A_INTEGER, LEX_INTEGER) }
	case 'd': { TOKEN_PROCESS(A_DECLARE, LEX_DECLARE) }
	case 'r': { TOKEN_PROCESS(A_RETURN, LEX_RETURN) }
	case 'p': { TOKEN_PROCESS(A_PRINT, LEX_PRINT) }
	case 'm': { TOKEN_PROCESS(A_MAIN, LEX_MAIN) }
	
	
	case 's':
	{
		CREATE_AUTOMAT(A_STRING);
		IS_CORRECT
		{
			DELETE_AUTOMAT
			lexTable.Add({ LEX_STRING, strNumber, LT_TI_NULLXDX });
			FlagForTypeOfVar.posInLT = lexTable.currentSize - 1;
			FlagForTypeOfVar.type = flagForTypeOfVar::STR;
			return true;
		}
		else { DELETE_AUTOMAT IS_FUNC_VARIABLE }
	}*/
	


	//int IT::IdTable::IsLit(const char lit[TI_STR_MAXSIZE])
	//{
	//	char* temp = new char[TI_STR_MAXSIZE];
	//	int j = 0;
	//	for (int i = 0; lit[i] != '\0'; i++)
	//	{
	//		if (lit[i] != '\"')
	//		{
	//			temp[j] = lit[i];
	//			j++;
	//		}
	//	}
	//	temp[j] = '\0';

	//	for (int i = 0; i < this->current_size; i++)
	//	{
	//		if (this->table[i].idtype == IT::IDTYPE::L)
	//		{
	//			if (this->table[i].value.vint == atoi(lit))
	//			{
	//				delete[] temp;
	//				return i;
	//			}

	//			if (strcmp(this->table[i].value.vstr.str, temp) == 0)
	//			{
	//				delete[] temp;
	//				return i;
	//			}
	//		}
	//	}

	//	delete[] temp;
	//	return TI_NULLIDX;
	//}



	//case '\'':
	//{
	//	CREATE_AUTOMAT(A_STRING_LITERAL)
	//	IS_CORRECT
	//	{
	//		int i = idTable.IsLit(token);
	//		if (i != LT_TI_NULLXDX)
	//			lexTable.Add({ LEX_LITERAL, strNumber, i });
	//		else
	//		{
	//			idTable.Add({ "\0", "\0", IT::IDDATATYPE::STR,  IT::IDTYPE::L });

	//			idTable.table[idTable.currentSize - 1].value.vstr.len = 0;
	//			int i = 0, j = 0;
	//			for (; token[i] != '\0'; i++)
	//			{
	//				if (token[i] != '\"')
	//				{
	//					idTable.table[idTable.current_size - 1].value.vstr.str[j] = token[i];
	//					idTable.table[idTable.current_size - 1].value.vstr.len++;
	//					j++;
	//				}
	//			}
	//			idTable.table[idTable.current_size - 1].value.vstr.str[j] = '\0';

	//			lexTable.Add({ LEX_LITERAL, strNumber, idTable.current_size - 1 });
	//		}
	//		DELETE_AUTOMAT return true;
	//	}
	//}

	/*delete string_literal;
	string_literal = NULL;
	return false;*/

		//default:
		//{
		//CREATE_AUTOMAT(A_INTEGER_LITERAL)
		//IS_CORRECT
		//{}
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
		//}
	}
}


void Lex(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[64]{};
	int lineNumber = 0;
	int positionInLine = 0;

	// i 
	for (int i = 0, j = 0; i < source.size; i++)
	{
		// символы допустимые в идентификаторах и ключевых словах
		if (source.code[source.text[i]] == In::IN::N)
		{
			buffer[j++] = source.text[i];
			positionInLine++;
			continue;
		}
		// если знак без лексемы
		else
		{
			if (j != 0)
			{
				i--; buffer[j] = IN_CODE_ENDSTRING;
				/////////// если токен распознан - добавляем ////////////
				if (tokenAnaliz(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; }
				else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
			}
			else
			{
				// скобки
				if (source.text[i] == '\'')
				{
					// открывающая скобка
					buffer[j++] = source.text[i++];
					// читаю строку до закрывающей
					// to do: если конец входного файла
					for (int c = 0; source.text[i] != '\''; c++)
					{
						if (c <= TI_STR_MAXSIZE) buffer[j++] = source.text[i++];
						else throw ERROR_THROW_IN(139, lineNumber, positionInLine);
					}			
					if (source.text[i] == '\'')
					{
						// закрывающая скобка
						buffer[j] = source.text[i];
						if (tokenAnaliz(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; }
						else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
					}
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
				}
				// пробелы
				if (source.text[i] != IN_CODE_ENDLINE)
				{ 
					// пустое пространство
					if (source.text[i] == IN_CODE_SPACE || source.text[i] == IN_CODE_TAB ) { positionInLine++; continue; }

					buffer[0] = source.text[i]; 
					buffer[1] = IN_CODE_ENDSTRING;
					if (tokenAnaliz(buffer, lineNumber, lexTable, idTable)) positionInLine++;
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
					RESET_BUFFER // хмммммм?
				}
			}
		}
		if (source.text[i] == IN_CODE_ENDLINE) NEXT_LINE
	}
	delete[] buffer;
}

bool a_func_var(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeOfVar)
{
	FST::FST* identificator = new FST::FST(A_IDENTIFICATOR(token));
	if (FST::execute(*identificator))
	{
		
		return true;
	}
}