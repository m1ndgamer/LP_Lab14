#include "stdafx.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "FST.h"
#include "RegularExpessions.h"
#include "IT.h"
#include "Error.h"


/////////////////  LEXEM ANALYSIS  /////////////////
// ������ �������.
#define LEXEM_ANALYSIS	if (LexemAnalysis(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; } \
						else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
#define RESET_BUFFER *buffer = '\0'; j = 0;
#define NEXT_LINE i++; lineNumber++; positionInLine = 0;
#define CREATE_AUTOMAT(expression) FST::FST* automat = new FST::FST(expression(token));
#define ADD_LEXEM(lexem, index)  lexTable.Add({ lexem, strNumber, index }); \
		return true;
#define DELETE_AUTOMAT delete automat; automat = NULL;
#define IS_CORRECT if (FST::execute(*automat))
#define IS_IDENTIFICATOR return isIdentificator(token, strNumber, lexTable, idTable);
#define TOKEN_PROCESS(automat, lexem) 		CREATE_AUTOMAT(automat); \
											IS_CORRECT{ DELETE_AUTOMAT ADD_LEXEM(lexem, LT_TI_NULLXDX) } \
											else DELETE_AUTOMAT
/////////////////  IDENTIFICATOR ANALYSIS  /////////////////
#define IS_MAIN strcmp(token, "main") == 0
#define PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 1).lexem
#define BEFORE_PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 2).lexem
#define IS_TYPE(value)		(lexTable.GetEntry(lexTable.currentSize - value).lexem == LEX_STRING || \
							lexTable.GetEntry(lexTable.currentSize - value).lexem == LEX_INTEGER)
#define ADD_SIGN_IN_ID_TABLE idTable.Add({ lexTable.currentSize, (char*)token, IT::INT, IT::L, -1 });

/// <summary>
/// �������� ��� �������.
/// </summary>
/// <param name="lexem">������.</param>
/// <returns>��� �������.</returns>
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
/// �������� ID ������������� �����.
/// </summary>
/// <param name="lexTable">��.</param>
/// <param name="idTable">��.</param>
/// <param name="isParm">��� ��������?</param>
/// <returns>���������� ID ������������� �����.</returns>
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
			(idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F ||
				idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::V))
			return lexTable.GetEntry(i).idxTI;
	}
	return TI_NULLIDX;
}

/// <summary>
/// �������� ������� � ��������� ��������.
/// </summary>
/// <param name="source">������.</param>
/// <returns>������ ��� �������.</returns>
char* deleteBacktick(char* source)
{
	int length = strlen(source);
	int currentSize = 0;
	for (int i = 0; i < length; i++)
	{
		if (i != 0 && i != length - 1) source[currentSize++] = source[i];
	}
	source[currentSize] = IN_CODE_ENDSTRING;
	return source;
}

/// <summary>
/// ����������� ������.
/// </summary>
/// <param name="token"></param>
/// <param name="strNumber">����� ������ � �������� ������.</param>
/// <param name="lexTable">��.</param>
/// <param name="idTable">��.</param>
/// <returns>������� ����������?</returns>
bool LexemAnalysis(const char* token, int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	// �������� �� ������������������ ����� ����� � �������.
	switch (*token)
	{
	case LEX_SEMICOLON: ADD_LEXEM(LEX_SEMICOLON, LT_TI_NULLXDX)
	case LEX_COMMA: ADD_LEXEM(LEX_COMMA, LT_TI_NULLXDX)
	case LEX_LEFTBRACE: ADD_LEXEM(LEX_LEFTBRACE, LT_TI_NULLXDX)
	case LEX_RIGHTBRACE: ADD_LEXEM(LEX_RIGHTBRACE, LT_TI_NULLXDX)
	case LEX_LEFTHESIS: ADD_LEXEM(LEX_LEFTHESIS, LT_TI_NULLXDX)
	case LEX_RIGHTHESIS: ADD_LEXEM(LEX_RIGHTHESIS, LT_TI_NULLXDX)
	case '+': ADD_SIGN_IN_ID_TABLE ADD_LEXEM(LEX_PLUS, idTable.currentSize - 1)
	case '-': ADD_SIGN_IN_ID_TABLE ADD_LEXEM(LEX_MINUS, idTable.currentSize - 1)
	case '*': ADD_SIGN_IN_ID_TABLE ADD_LEXEM(LEX_STAR, idTable.currentSize - 1)
	case '/': ADD_SIGN_IN_ID_TABLE ADD_LEXEM(LEX_DIRSLASH, idTable.currentSize - 1)
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
				idTable.Add({ lexTable.currentSize, (char*)"L", IT::STR, IT::L, GetParentID(lexTable, idTable) });
			strcpy(idTable.table[idTable.currentSize - 1].value.vstr->str, deleteBacktick((char*)token));
			idTable.table[idTable.currentSize - 1].value.vstr->len = strlen(token);
			ADD_LEXEM(LEX_LITERAL, idTable.currentSize)
				return true;
		}
		DELETE_AUTOMAT
	}
	case LEX_STRING:
	{
		CREATE_AUTOMAT(A_STRING);
		IS_CORRECT { ADD_LEXEM(LEX_STRING, LT_TI_NULLXDX) }
		automat = new FST::FST(A_FUNC_SUBSTR(token));
		IS_CORRECT { return isIdentificator(ID_SUBSTR, strNumber, lexTable, idTable, 1); }

		automat = new FST::FST(A_FUNC_STRLEN(token));
		IS_CORRECT { return isIdentificator(ID_STRLEN, strNumber, lexTable, idTable, 1); }

		DELETE_AUTOMAT
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
				idTable.Add({ lexTable.currentSize, (char*)"L", IT::INT, IT::L, GetParentID(lexTable, idTable) });
				idTable.table[idTable.currentSize - 1].value.vint = atoi(token);
				ADD_LEXEM(LEX_LITERAL, idTable.currentSize - 1)
			}
			DELETE_AUTOMAT return false;
		}
	}
	}
	// �������� �� �������������
	if (strlen(token) > 5) throw ERROR_THROW(136);
	IS_IDENTIFICATOR
}

/// <summary>
/// ���������������� ������ ��������� ������.
/// </summary>
/// <param name="source">�������� �����.</param>
/// <param name="lexTable">��.</param>
/// <param name="idTable">��.</param>
void parsingIntoLexems(In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* buffer = new char[TI_STR_MAXSIZE] {}; // ����� ��� ������������� ������
	int lineNumber = 1;				// ����� ������ � �������� ������
	int positionInLine = 1;			// ����� ������� � ������ ��������� ������

	// ���������������� ��������� ��������� ������.
	// i ������� � �������� ������.
	// j ������� � �������.
	for (int i = 0, j = 0; i < source.size; i++)
	{
		// �������� �� ���������� ������������� ������� �������.
		if (j >= TI_STR_MAXSIZE) throw ERROR_THROW_IN(137, lineNumber, positionInLine);
		// ������� ���������� � �������������� � ����������������� �����.
		if (IS_UPPER_CASE_ENG((char)source.text[i]) || IS_LOWER_CASE_ENG((char)source.text[i]) || isdigit(source.text[i]))
		{
			buffer[j++] = source.text[i];
			positionInLine++;
			continue;
		}
		// ���� �������� ������ ������������ � �������������� � ����������������� �����.
		else
		{
			// ���� � ������ ���������� �������.
			if (j != 0)
			{
				i--;
				buffer[j] = IN_CODE_ENDSTRING;
				LEXEM_ANALYSIS
			}
			else
			{
				if (source.text[i] == BACKTICK)
				{
					// ���������� � ������ ������� ������������ �������.
					buffer[j++] = source.text[i++];
					// ������ � ������ �� ����������� ��������.
					// c ����� ���������� ��������.
					for (int c = 0; source.text[i] != BACKTICK; c++)
					{
						// �������� �� ����� �������� �����.
						if (c == source.size - 1) throw ERROR_THROW_IN(138, lineNumber, positionInLine);
						// ������ ������ � ������, ���� �� �������� ����. ������ ���������� ��������.
						if (c <= TI_STR_MAXSIZE) buffer[j++] = source.text[i++];
						else throw ERROR_THROW_IN(139, lineNumber, positionInLine);
					}
					// ���������� � ����� ������� ����������� �������.
					if (source.text[i] == BACKTICK) { buffer[j++] = source.text[i]; buffer[j++] = IN_CODE_ENDSTRING; LEXEM_ANALYSIS }
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
				}
				if (source.text[i] != ANALYSIS_ENDLINE)
				{
					positionInLine++;
					// ��������� ���������� ��������.
					if (source.text[i] == IN_CODE_SPACE || source.text[i] == IN_CODE_TAB) { continue; }
					// ��������� �������� ����������.
					buffer[0] = source.text[i];
					buffer[1] = IN_CODE_ENDSTRING;
					LEXEM_ANALYSIS
					RESET_BUFFER
				}
				// ������� �� ��������� ������ ��������� ������.
				else { NEXT_LINE }
			}
		}
	}
	delete[] buffer;
}

/// <summary>
/// ��������� �� ��� ������� ���������������?
/// </summary>
/// <param name="token">�������.</param>
/// <param name="strNumber">����� ������ � �������� ������.</param>
/// <param name="lexTable">��.</param>
/// <param name="idTable">��.</param>
/// <returns>������� ����������?</returns>
bool isIdentificator(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, bool isKeyword)
{
	bool idWasFounded = false; // ������������� ������?
	CREATE_AUTOMAT(A_IDENTIFICATOR)
	if (isKeyword || FST::execute(*automat))
	{
		DELETE_AUTOMAT
		// ��� main ��� �������?
		if (IS_MAIN || (PREVIOUS_LEXEM == LEX_FUNCTION && IS_TYPE(2)))
		{
			for (int i = 0; i < idTable.currentSize; i++)
			{
				// �������� �� �������������
				// to do: main over
				if (!strcmp(idTable.GetEntry(i).id, token) && idTable.GetEntry(i).idtype == IT::F) throw ERROR_THROW(140);
			}
			idTable.Add({ lexTable.currentSize, (char*)token, getType(BEFORE_PREVIOUS_LEXEM), IT::F, GetParentID(lexTable, idTable) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			idWasFounded = true;

		}
	// ��� ���������� ����������?
	if (!idWasFounded && (BEFORE_PREVIOUS_LEXEM == LEX_DECLARE && IS_TYPE(1)))
	{
		for (int i = 0; i < idTable.currentSize; i++)
			if (!strcmp(idTable.GetEntry(i).id, token) && idTable.GetEntry(i).parentId == GetParentID(lexTable, idTable) 
				&& idTable.GetEntry(i).idtype == IT::V)
				throw ERROR_THROW(142);
		idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::V, GetParentID(lexTable, idTable)});
		lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
		idWasFounded = true;

	}
	// ��� �������� �������?
	if (!idWasFounded &&
		(BEFORE_PREVIOUS_LEXEM == LEX_LEFTHESIS ||
		 BEFORE_PREVIOUS_LEXEM == LEX_COMMA && IS_TYPE(1))) // �������� �� �� ��� ���� ��� ��������
	{
		int parentId = GetParentID(lexTable, idTable, true);
		for (int i = 0; i < idTable.currentSize; i++)
			if (!strcmp(idTable.GetEntry(i).id, token) &&
				(idTable.GetEntry(i).parentId == parentId))
			{
				std::cout << idTable.GetEntry(i).parentId << std::endl;
				std::cout << GetParentID(lexTable, idTable, true) << std::endl;
				std::cout << idTable.GetEntry(GetParentID(lexTable, idTable, true)).id << std::endl;
				throw ERROR_THROW(143);
			}
		idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::P, parentId });
		lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
		idWasFounded = true;
	}
	// ��� ���������� ����� ����������.
	if (!idWasFounded)
	{
		if (BEFORE_PREVIOUS_LEXEM == LEX_DECLARE) throw ERROR_THROW(142);
		for (int i = idTable.currentSize; i >= 0; i--)
		{
			int parentElement = GetParentID(lexTable, idTable);
			if (!strcmp(token, idTable.GetEntry(i).id) && parentElement == idTable.GetEntry(i).parentId && idTable.GetEntry(i).idtype == IT::V)
				lexTable.Add({ LEX_ID, strNumber, i});
			idWasFounded = true;
		}
	}
	}
	return idWasFounded;
}