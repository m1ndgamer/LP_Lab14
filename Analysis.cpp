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
#define IS_IDENTIFICATOR return isIdentificator(token, strNumber, lexTable, idTable);
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
											IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(lexem, LT_TI_NULLXDX) } \
											else DELETE_AUTOMAT
///////////////////////////////////////////////////////////////////////////////////////////////
#define IS_MAIN strcmp(token, "main") == 0 
#define PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 1).lexem
#define BEFORE_PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 2).lexem


/// <summary>
/// Получить тип лексемы.
/// </summary>
/// <param name="lexem">Лекема.</param>
/// <returns>Тип лексемы.</returns>
IT::IDDATATYPE getType(char lexem)
{
	switch (lexem)
	{
		case 't': return IT::INT;
		case 's': return IT::STR;
		default: return IT::INT;
	}
}

/// <summary>
/// Получить ID родительского блока.
/// </summary>
/// <param name="lexTable">ТЛ.</param>
/// <param name="idTable">ТИ.</param>
/// <param name="isParm">Это параметр?</param>
/// <returns>Возвращает ID родительского блока.</returns>
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

/// <summary>
/// Лексический анализ.
/// </summary>
/// <param name="token"></param>
/// <param name="strNumber">Номер строки в исходном тексте.</param>
/// <param name="lexTable">ТЛ.</param>
/// <param name="idTable">ТИ.</param>
/// <returns>Лексема распознана?</returns>
bool LexemAnalysis(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	// Проверка на зараезервированное слово языка и литерал.
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
						idTable.table[num2].value.vstr->str[idTable.table[num2].value.vstr->len] = 0;
						lexTable.Add({ LEX_LITERAL, strNumber, LT_TI_NULLXDX });
						
					}
					return true;
			}
		}
		/// ПУСТОЕ ЗНАЧЕНИЕ СТРОКОВЫХ ИНДЕТИФИКАТОРОВ
		/// ДОБАВИТЬ.
		case LEX_STRING:
		{
			CREATE_AUTOMAT(A_STRING);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_STRING, LT_TI_NULLXDX)
			}
		}
	
		case 'i':
		{
			CREATE_AUTOMAT(A_INTEGER);
			IS_CORRECT
			{
				DELETE_AUTOMAT
				ADD_LEXEM(LEX_INTEGER, LT_TI_NULLXDX)
			}
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
		}
	}
	// Проверка на идентификатор
	IS_IDENTIFICATOR
}

/// <summary>
/// Последовательный анализ исходного текста.
/// </summary>
/// <param name="source">Исходный текст.</param>
/// <param name="lexTable">ТЛ.</param>
/// <param name="idTable">ТИ.</param>
void parsingIntoLexems(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[512]{}; // буфер для анализуремого текста
	int lineNumber = 1;				// номер строки в исходном тексте
	int positionInLine = 1;			// номер символа в строке исходного текста

	// Последовательная обработка исходного текста.
	// i позиция в исходном тексте.
	// j позиция в буффере.
	for (int i = 0, j = 0; i < source.size; i++)
	{
		// Еимволы допустимые в идентификаторе и зарезервированном слове.
		if (source.code[source.text[i]] == In::IN::N)
		{
			buffer[j++] = source.text[i];
			positionInLine++;
			continue;
		}
		// Если встречен символ недопустимый в идентификаторе и зарезервированном слове.
		else
		{
			// Если в буфере содержатся символы.
			if (j != 0)
			{
				i--;
				buffer[j] = IN_CODE_ENDSTRING;
				// Попытка лексического анализа.
				if (LexemAnalysis(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; }
				else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
			}
			else
			{
				if (source.text[i] == BACKTICK)
				{
					// Добавление в начало буффера открывающией кавычки.
					buffer[j++] = source.text[i++];
					// TO DO: если конец входного файла
					// Чтение в буффер до закрывающей кавычики.
					// c длина строкового литерала.
					for (int c = 0; source.text[i] != BACKTICK; c++)
					{
						// Читать строку в буффер, если не превышен макс. размер строкового литерала.
						if (c <= TI_STR_MAXSIZE) buffer[j++] = source.text[i++];
						else throw ERROR_THROW_IN(139, lineNumber, positionInLine);
					}	
					// Добавление в конец буффера закрывающей кавычки.
					if (source.text[i] == BACKTICK)
					{
						buffer[j] = source.text[i];
						// Попытка лексического анализа.
						if (LexemAnalysis(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; }
						else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
					}
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
				}
				if (source.text[i] != ANALYSIS_ENDLINE)
				{ 
					// Обработка пробельных символов.
					if (source.text[i] == IN_CODE_SPACE || source.text[i] == IN_CODE_TAB ) { positionInLine++; continue; }
					// Обработка знаковых операторов.
					buffer[0] = source.text[i]; 
					buffer[1] = IN_CODE_ENDSTRING;
					if (LexemAnalysis(buffer, lineNumber, lexTable, idTable)) positionInLine++;
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
					RESET_BUFFER
				}
				// Переход на следующую строку исхожного текста.
				else { NEXT_LINE }
			}
		}
	}
	delete[] buffer;
}

/// <summary>
/// Являентся ли эта лексема идентификатором?
/// </summary>
/// <param name="token">Лексема.</param>
/// <param name="strNumber">Номер строки в исходном тексте.</param>
/// <param name="lexTable">ТЛ.</param>
/// <param name="idTable">ТИ.</param>
/// <returns>Лексема распознана?</returns>
bool isIdentificator(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	CREATE_AUTOMAT(A_IDENTIFICATOR)
	bool idWasFounded = false; // Идентификатор найден?
	IS_CORRECT
	{
		// Это main или функция?
		if (IS_MAIN || (PREVIOUS_LEXEM == LEX_FUNCTION))
		{
			idTable.Add({ lexTable.currentSize, (char*)token, getType(BEFORE_PREVIOUS_LEXEM), IT::F, GetParentID(lexTable, idTable) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });		
			idWasFounded = true;
		}
		//else
		//	throw ERROR_THROW_IN(123, strNumber, -1);
		// Это переменная?
		if (!idWasFounded && (BEFORE_PREVIOUS_LEXEM == LEX_DECLARE))
		{
			idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::V, GetParentID(lexTable, idTable)});
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			idWasFounded = true;

		}
		/*else
			throw ERROR_THROW_IN(123, strNumber, -1);*/
		// Это параметр функции?
		if	(!idWasFounded && 
			(BEFORE_PREVIOUS_LEXEM == LEX_LEFTHESIS || 
			 BEFORE_PREVIOUS_LEXEM == LEX_COMMA)) // ПРОВЕРКА НА ТО ЧТО ПРЕД ЭТО ПАРАМЕТР
		{
			idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::P, GetParentID(lexTable, idTable, true) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			idWasFounded = true;
		}
		// Для обявленной ранее переменной.
		if (!idWasFounded)
		{
			for (int i = idTable.currentSize; i >= 0; i--)
			{
				int parentElement = GetParentID(lexTable, idTable);
				if(!strcmp(token, idTable.GetEntry(i).id) && parentElement == idTable.GetEntry(i).parentId)
					lexTable.Add({ LEX_ID, strNumber, i});
				idWasFounded = true;
			}
		}
	}
	DELETE_AUTOMAT
	return idWasFounded;
}