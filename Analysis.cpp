#include "stdafx.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "FST.h"
#include "RegularExpessions.h"
#include "IT.h"
#include "Error.h"

#define RESET_BUFFER *buffer = '\0'; j = 0;
#define NEXT_LINE lineNumber++; positionInLine = 0;
#define CREATE_AUTOMAT(expression) FST::FST* automat = new FST::FST(expression(token));
#define ADD_LEXEM(lexem) lexTable.Add({ lexem, strNumber, LT_TI_NULLXDX }); \
					return true;
#define DELETE_AUTOMAT delete automat; automat = NULL;
#define IS_CORRECT if (FST::execute(*automat))
#define IS_FUNC_VARIABLE return isVar(token, strNumber, lexTable, idTable, FlagForTypeOfVar);
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
								IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(lexem) } \
								//else { DELETE_AUTOMAT IS_FUNC_VARIABLE }
static flagForTypeOfVar FlagForTypeOfVar;

bool tokenAnaliz(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	
	// первая буква в токене
	/*switch (*token)
	{
		
		case LEX_SEMICOLON: ADD_LEXEM(LEX_SEMICOLON)
		case LEX_COMMA: ADD_LEXEM(LEX_COMMA)
		case LEX_LEFTBRACE: ADD_LEXEM(LEX_LEFTBRACE)
		case LEX_RIGHTBRACE: ADD_LEXEM(LEX_RIGHTBRACE)
		case LEX_LEFTHESIS: ADD_LEXEM(LEX_LEFTHESIS)
		case LEX_RIGHTHESIS: ADD_LEXEM(LEX_RIGHTHESIS)
		case LEX_PLUS: ADD_LEXEM(LEX_PLUS)
		case LEX_MINUS: ADD_LEXEM(LEX_MINUS)
		case LEX_STAR: ADD_LEXEM(LEX_STAR)
		case LEX_DIRSLASH: ADD_LEXEM(LEX_DIRSLASH)
		case LEX_EQUAL_SIGN: ADD_LEXEM(LEX_EQUAL_SIGN)
		case LEX_FUNCTION: { TOKEN_PROCESS(A_FUNCTION, LEX_FUNCTION) }
		case LEX_DECLARE: { TOKEN_PROCESS(A_DECLARE, LEX_DECLARE) }
		case LEX_RETURN: { TOKEN_PROCESS(A_RETURN, LEX_RETURN) }
		case LEX_PRINT: { TOKEN_PROCESS(A_PRINT, LEX_PRINT) }
		case LEX_MAIN: { TOKEN_PROCESS(A_MAIN, LEX_MAIN) }
	
	
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
		}
	
		case 'i':
		{
			CREATE_AUTOMAT(A_INTEGER);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				lexTable.Add({ LEX_INTEGER, strNumber, LT_TI_NULLXDX });	
				FlagForTypeOfVar.posInLT = lexTable.currentSize - 1;
				FlagForTypeOfVar.type = flagForTypeOfVar::INT;
				return true;
			}
			else { DELETE_AUTOMAT IS_FUNC_VARIABLE }
		}
		default:
		{
			lexTable.Add({ LEX_ID, strNumber, LT_TI_NULLXDX });
		}
	}*/
	return 1;
}


void Lex(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[64]{};
	int lineNumber = 1;
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
				isVar(buffer, j, lexTable, idTable, FlagForTypeOfVar);
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
				if (source.text[i] != ANALYSIS_ENDLINE)
				{ 
					// пустое пространство
					if (source.text[i] == IN_CODE_SPACE || source.text[i] == IN_CODE_TAB ) { positionInLine++; continue; }

					buffer[0] = source.text[i]; 
					buffer[1] = IN_CODE_ENDSTRING;
					if (tokenAnaliz(buffer, lineNumber, lexTable, idTable)) positionInLine++;
					//else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
					RESET_BUFFER // хмммммм?
				}
			}
		}
		if (source.text[i] == ANALYSIS_ENDLINE) NEXT_LINE
	}
	delete[] buffer;
}

int Random(int min, int max) {
	return min + rand() % (max - min);
}

bool isVar(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeOfVar)
{
	FST::FST* identificator = new FST::FST(A_IDENTIFICATOR(token));
	if (FST::execute(*identificator))
	{
		//std::cout << token << std::endl;
			idTable.Add({ strNumber, (char*)token, IT::INT, IT::V });
		/*if (strcmp(token, "main") == 0)
		{
			idTable.Add(idTable, { token,  })
		}*/
		
	}
	return true;
}