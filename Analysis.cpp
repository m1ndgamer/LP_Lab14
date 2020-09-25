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
#define ADD_LEXEM(lexem, index)  lexTable.Add({ lexem, strNumber, index }); \
		return true;
#define DELETE_AUTOMAT delete automat; automat = NULL;
#define IS_CORRECT if (FST::execute(*automat))
#define IS_VARIABLE return isVar(token, strNumber, lexTable, idTable);
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
								IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(lexem, LT_TI_NULLXDX) } \
								else { DELETE_AUTOMAT IS_VARIABLE }
///////////////////////////////////////////////////////////////////////////////////////////////
#define IS_MAIN strcmp(token, "main") == 0 
#define PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 1).lexem
#define BEFORE_PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 2).lexem

IT::IDDATATYPE getType(char lexem)
{
	switch (lexem)
	{
		case 't': return IT::INT;
		case 's': return IT::STR;
		default: return IT::INT;
	}
}

int GetParentID(LT::LexTable& lexTable, IT::IdTable& idTable, bool isParm = false)
{
	char startFunction;
	isParm ? startFunction = LEX_LEFTHESIS : startFunction = LEX_LEFTBRACE;
	bool startSymbolFounded = false;
	for (int i = lexTable.currentSize - 1; i > 0; i--)
	{
		if (lexTable.GetEntry(i).lexem == LEX_RIGHTBRACE) break;
		if (lexTable.GetEntry(i).lexem == startFunction) startSymbolFounded = true;
		if (startSymbolFounded && lexTable.GetEntry(i).lexem == LEX_ID &&
			idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
			return lexTable.GetEntry(i).idxTI;
	}
	return TI_NULLIDX;
}


bool tokenAnaliz(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	// первая буква в токене
	switch (*token)
	{
		
		case LEX_SEMICOLON: ADD_LEXEM(LEX_SEMICOLON, LT_TI_NULLXDX)
		case LEX_COMMA: ADD_LEXEM(LEX_COMMA, LT_TI_NULLXDX)
		case LEX_LEFTBRACE: ADD_LEXEM(LEX_LEFTBRACE, LT_TI_NULLXDX)
		case LEX_RIGHTBRACE: ADD_LEXEM(LEX_RIGHTBRACE, LT_TI_NULLXDX)
		case LEX_LEFTHESIS: ADD_LEXEM(LEX_LEFTHESIS, LT_TI_NULLXDX)
		case LEX_RIGHTHESIS: ADD_LEXEM(LEX_RIGHTHESIS, LT_TI_NULLXDX)
		case LEX_PLUS: ADD_LEXEM(LEX_PLUS, LT_TI_NULLXDX)
		case LEX_MINUS: ADD_LEXEM(LEX_MINUS, LT_TI_NULLXDX)
		case LEX_STAR: ADD_LEXEM(LEX_STAR, LT_TI_NULLXDX)
		case LEX_DIRSLASH: ADD_LEXEM(LEX_DIRSLASH, LT_TI_NULLXDX)
		case LEX_EQUAL_SIGN: ADD_LEXEM(LEX_EQUAL_SIGN, LT_TI_NULLXDX)
		case LEX_FUNCTION: { TOKEN_PROCESS(A_FUNCTION, LEX_FUNCTION) }
		case LEX_DECLARE: { TOKEN_PROCESS(A_DECLARE, LEX_DECLARE) }
		case LEX_RETURN: { TOKEN_PROCESS(A_RETURN, LEX_RETURN) }
		case LEX_PRINT: { TOKEN_PROCESS(A_PRINT, LEX_PRINT) }
		case LEX_MAIN: { TOKEN_PROCESS(A_MAIN, LEX_MAIN) }
		case BACKTICK: 
		{
			CREATE_AUTOMAT(A_STRING_LITERAL)
			IS_CORRECT
			{
				DELETE_AUTOMAT
					int num2 = lexTable.GetEntry(lexTable.currentSize - 2).idxTI;
					int num = lexTable.table[lexTable.currentSize - 2].idxTI;
					if (num != -1)
					{
						strcpy(idTable.table[num2].value.vstr->str, token);
						idTable.table[num2].value.vstr->len = strlen(token);
						/////// TO 
						lexTable.Add({ LEX_LITERAL, strNumber, LT_TI_NULLXDX });
						
					}
					return true;
			}
		}
		/// ПУСТОЕ ЗНАЧЕНИЕ СТРОКОВЫХ ИНДЕТИФИКАТОРОВ
		/// ДОБАВИТЬ.
		case 's':
		{
			CREATE_AUTOMAT(A_STRING);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_STRING, LT_TI_NULLXDX)
			}
			else { IS_VARIABLE }
		}
	
		case 'i':
		{
			CREATE_AUTOMAT(A_INTEGER);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_INTEGER, LT_TI_NULLXDX)
			}
			else { IS_VARIABLE }
		}
		default:
		{
			if (isdigit(*token))
			{
				CREATE_AUTOMAT(A_INTEGER_LITERAL);
				IS_CORRECT
				{
					DELETE_AUTOMAT
					idTable.table[idTable.currentSize - 1].value.vint = atoi(token);
					lexTable.Add({ LEX_LITERAL, strNumber, LT_TI_NULLXDX });
					return true;
				}
			}
			else { IS_VARIABLE }
		}
	}
}

void Lex(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[64]{};
	int lineNumber = 1;
	int positionInLine = 0;


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

bool isVar(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	CREATE_AUTOMAT(A_IDENTIFICATOR)
	bool alreadyChecked = false; // проверена переменная
	IS_CORRECT
	{
		if (IS_MAIN || (PREVIOUS_LEXEM == LEX_FUNCTION))
		{
			idTable.Add({ strNumber, (char*)token, getType(BEFORE_PREVIOUS_LEXEM), IT::F, GetParentID(lexTable, idTable) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });		
			alreadyChecked = true;
		}
		//else
		//	throw ERROR_THROW_IN(123, strNumber, -1);
		//для переменной(с проверкой переопределения)
		if (!alreadyChecked && (BEFORE_PREVIOUS_LEXEM == LEX_DECLARE))
		{
			idTable.Add({ strNumber, (char*)token, getType(PREVIOUS_LEXEM), IT::V, GetParentID(lexTable, idTable)});
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			alreadyChecked = true;

		}
		/*else
			throw ERROR_THROW_IN(123, strNumber, -1);*/
		//для параметра функции
		if	(!alreadyChecked && 
			(BEFORE_PREVIOUS_LEXEM == LEX_LEFTHESIS || 
			 BEFORE_PREVIOUS_LEXEM == LEX_COMMA)) // ПРОВЕРКА НА ТО ЧТО ПРЕД ЭТО ПАРАМЕТР
		{
			idTable.Add({ strNumber, (char*)token, getType(PREVIOUS_LEXEM), IT::P, GetParentID(lexTable, idTable, true) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			alreadyChecked = true;
		}
		if (!alreadyChecked)
		{
			for (int i = idTable.currentSize; i >= 0; i--)
			{
				int parentElement = GetParentID(lexTable, idTable);
				if(!strcmp(token, idTable.GetEntry(i).id) && parentElement == idTable.GetEntry(i).parentId)
					lexTable.Add({ LEX_ID, strNumber, i});
			}
			
		}
		DELETE_AUTOMAT
		return true;
	}
	else
	{
		DELETE_AUTOMAT
		return false;
	}
}