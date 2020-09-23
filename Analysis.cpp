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
#define IS_VARIABLE isVar(token, strNumber, lexTable, idTable, FlagForTypeOfVar); ADD_LEXEM(LEX_ID) return true;
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
								IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(lexem) } \
								else { DELETE_AUTOMAT IS_VARIABLE }
///////////////////////////////////////////////////////////////////////////////////////////////
#define IS_MAIN strcmp(token, "main") == 0 
#define PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 1).lexem
#define BEFORE_PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 2).lexem
static flagForTypeOfVar FlagForTypeOfVar;

bool tokenAnaliz(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	// первая буква в токене
	switch (*token)
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
		case BACKTICK: 
		{
			CREATE_AUTOMAT(A_STRING_LITERAL)
			IS_CORRECT
			{
				DELETE_AUTOMAT
				lexTable.Add({ LEX_LITERAL, strNumber, LT_TI_NULLXDX });
				return true;
			}
		}

		case 's':
		{
			CREATE_AUTOMAT(A_STRING);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_STRING)
				return true;
			}
			else { IS_VARIABLE }
		}
	
		case 'i':
		{
			CREATE_AUTOMAT(A_INTEGER);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_INTEGER)
				return true;
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
	CREATE_AUTOMAT(A_IDENTIFICATOR)
	bool alreadyChecked = false; // проверена переменная
	IS_CORRECT
	{		
		if (IS_MAIN || (PREVIOUS_LEXEM == LEX_FUNCTION && BEFORE_PREVIOUS_LEXEM == 't'))
		{

			idTable.Add({ strNumber, (char*)token, IT::INT, IT::F });
			alreadyChecked = true;
		}
		//else
		//	throw ERROR_THROW_IN(123, strNumber, -1);
		//для переменной(с проверкой переопределения)
		if (!alreadyChecked && (PREVIOUS_LEXEM == 't' && BEFORE_PREVIOUS_LEXEM == LEX_DECLARE))
		{
			if (idTable.IsId((char*)token) != -1)
			{
				idTable.Add({ strNumber, (char*)token, IT::INT, IT::F });
			}
			else
			{
				idTable.Add({ strNumber, (char*)token, IT::INT, IT::F });
			}
			
			alreadyChecked = true;

		}
		/*else
			throw ERROR_THROW_IN(123, strNumber, -1);*/
		//для параметра функции
		if (!alreadyChecked && PREVIOUS_LEXEM == 't')
		{
			idTable.Add({ strNumber, (char*)token, IT::INT, IT::F });
			
		}
		/*else
			throw ERROR_THROW_IN(123, strNumber, -1);*/
		//добавление идентификаторов с учетом области видимости
		if (!alreadyChecked)
		{
			//bool isLeftBraceWas = false;
			//for (int i = lexTable.currentSize - 1; i > 0; i--)
			//{
			//	if (lexTable.GetEntry(i).lexem == LEX_LEFTBRACE)
			//		isLeftBraceWas = true;

			//	if (isLeftBraceWas &&
			//		lexTable.GetEntry(i).lexem == LEX_ID &&
			//		idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
			//	{
			//		int tempIndex = idTable.IsId((char*)token);
			//		if (tempIndex != -1)
			//		{
			//			lexTable.Add({ LEX_ID, strNumber, tempIndex });
			//			break;
			//		}
			//		else
			//		{
			//			tempIndex = idTable.IsId((char*)token);
			//			if (tempIndex != -1 &&
			//				idTable.GetEntry(tempIndex).idtype == IT::IDTYPE::F)
			//			{
			//				lexTable.Add({ LEX_ID, strNumber, tempIndex });
			//				break;
			//			}
			//			else
			//				throw ERROR_THROW_IN(129, strNumber, -1);
			//		}

			//	}
			//}
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

//
//FST::FST* identificator = new FST::FST(A_IDENTIFICATOR(token));
//if (FST::execute(*identificator))
//{
//	bool alreadyChecked = false; // проверена переменная
//	//для функций
//	if (strcmp(token, "main") == 0 || // если это маин
//		((lexTable.GetEntry(lexTable.current_size - 1).lexema == LEX_FUNCTION && // до этого функция
//			lexTable.GetEntry(lexTable.current_size - 2).lexema == 't') && // переменная
//			FlagForTypeOfVar.posInLT == lexTable.current_size - 2))
//	{
//		if (idTable.IsId(token) == -1)
//		{
//			if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
//				idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
//
//			if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
//				idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F });
//
//			if (strcmp(token, "main") == 0)
//				idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F });
//
//			FlagForTypeOfVar.posInLT = -1;
//			FlagForTypeOfVar.type = flagForTypeOfVar::DEF;
//
//			lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
//			alreadyChecked = true;
//		}
//		else
//			throw ERROR_THROW_IN(123, strNumber, -1);
//	}
//
//	//для переменной(с проверкой переопределения)
//	if (!alreadyChecked &&
//		(lexTable.GetEntry(lexTable.current_size - 1).lexema == 't' &&
//			lexTable.GetEntry(lexTable.current_size - 2).lexema == LEX_DECLARE &&
//			FlagForTypeOfVar.posInLT == lexTable.current_size - 1))
//	{
//		bool isLeftBraceWas = false;
//		for (int i = lexTable.current_size - 1; i > 0; i--)
//		{
//			if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
//				isLeftBraceWas = true;
//
//			if (isLeftBraceWas &&
//				lexTable.GetEntry(i).lexema == LEX_ID &&
//				idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
//			{
//				if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
//				{
//					if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
//						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::V });
//
//					if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
//						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::V });
//
//					FlagForTypeOfVar.posInLT = -1;
//					FlagForTypeOfVar.type = flagForTypeOfVar::DEF;
//
//					lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
//					alreadyChecked = true;
//					break;
//				}
//				else
//					throw ERROR_THROW_IN(123, strNumber, -1);
//
//			}
//		}
//	}
//
//	//для параметра функции
//	if (!alreadyChecked &&
//		(lexTable.GetEntry(lexTable.current_size - 1).lexema == 't' && FlagForTypeOfVar.posInLT == lexTable.current_size - 1))
//		for (int i = lexTable.current_size - 1; i > 0; i--)
//		{
//			if (lexTable.GetEntry(i).lexema == LEX_ID &&
//				idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
//			{
//				if (lexTable.GetEntry(i - 1).lexema == LEX_FUNCTION && lexTable.GetEntry(i - 2).lexema == 't')
//				{
//					if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
//					{
//						if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
//							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::P });
//
//						if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
//							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::P });
//
//						FlagForTypeOfVar.posInLT = -1;
//						FlagForTypeOfVar.type = flagForTypeOfVar::DEF;
//
//						lexTable.Add({ LEX_ID, strNumber, idTable.current_size - 1 });
//						alreadyChecked = true;
//						break;
//					}
//					else
//						throw ERROR_THROW_IN(123, strNumber, -1);
//				}
//			}
//		}
//
//	//добавление идентификаторов с учетом области видимости
//	if (!alreadyChecked)
//	{
//		bool isLeftBraceWas = false;
//		for (int i = lexTable.current_size - 1; i > 0; i--)
//		{
//			if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
//				isLeftBraceWas = true;
//
//			if (isLeftBraceWas &&
//				lexTable.GetEntry(i).lexema == LEX_ID &&
//				idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
//			{
//				int tempIndex = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id);
//				if (tempIndex != -1)
//				{
//					lexTable.Add({ LEX_ID, strNumber, tempIndex });
//					break;
//				}
//				else
//				{
//					tempIndex = idTable.IsId(token);
//					if (tempIndex != -1 &&
//						idTable.GetEntry(tempIndex).idtype == IT::IDTYPE::F)
//					{
//						lexTable.Add({ LEX_ID, strNumber, tempIndex });
//						break;
//					}
//					else
//						throw ERROR_THROW_IN(129, strNumber, -1);
//				}
//
//			}
//		}
//	}
//
//	delete identificator;
//	identificator = NULL;
//	return true;
//}
//else
//{
//	delete identificator;
//	identificator = NULL;
//	return false;
//}