#include "stdafx.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "FST.h"
#include "RegularExpessions.h"
#include "IT.h"
#include "Error.h"

// ������ �������.
#define LEXEM_ANALYSIS	if (LexemAnalysis(buffer, lineNumber, lexTable, idTable)) { RESET_BUFFER continue; } \
						else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
/////////////////  LEXEM ANALYSIS  /////////////////
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
/////////////////  IDENTIFICATOR ANALYSIS  /////////////////
#define IS_MAIN strcmp(token, "main") == 0 
#define PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 1).lexem
#define BEFORE_PREVIOUS_LEXEM lexTable.GetEntry(lexTable.currentSize - 2).lexem

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
			idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
			return lexTable.GetEntry(i).idxTI;
	}
	return TI_NULLIDX;
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
		case '+': ADD_LEXEM(LEX_PLUS, LT_TI_NULLXDX)
		case '-': ADD_LEXEM(LEX_MINUS, LT_TI_NULLXDX)
		case '*': ADD_LEXEM(LEX_STAR, LT_TI_NULLXDX)
		case '/': ADD_LEXEM(LEX_DIRSLASH, LT_TI_NULLXDX)
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
					int identificator = lexTable.GetEntry(lexTable.currentSize - 2).idxTI;
					if (identificator != -1)
					{
						strcpy(idTable.table[identificator].value.vstr->str, token);
						idTable.table[identificator].value.vstr->len = strlen(token);
						ADD_LEXEM(LEX_LITERAL, LT_TI_NULLXDX)					
					}
					// else throw
					return true;
			}
		}
		/// ������ �������� ��������� ���������������
		/// ��������.
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
					ADD_LEXEM(LEX_LITERAL, LT_TI_NULLXDX)
				}
				DELETE_AUTOMAT return false;
			}
		}
	}
	// �������� �� �������������
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
	char* buffer = new char[512]{}; // ����� ��� ������������� ������
	int lineNumber = 1;				// ����� ������ � �������� ������
	int positionInLine = 1;			// ����� ������� � ������ ��������� ������

	// ���������������� ��������� ��������� ������.
	// i ������� � �������� ������.
	// j ������� � �������.
	for (int i = 0, j = 0; i < source.size; i++)
	{
		// ������� ���������� � �������������� � ����������������� �����.
		if (source.code[source.text[i]] == In::IN::N)
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
					if (source.text[i] == BACKTICK) { buffer[j] = source.text[i]; LEXEM_ANALYSIS }
					else throw ERROR_THROW_IN(130, lineNumber, positionInLine);
				}
				if (source.text[i] != ANALYSIS_ENDLINE)
				{ 
					// ��������� ���������� ��������.
					if (source.text[i] == IN_CODE_SPACE || source.text[i] == IN_CODE_TAB ) { positionInLine++; continue; }
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
bool isIdentificator(const char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	CREATE_AUTOMAT(A_IDENTIFICATOR)
	bool idWasFounded = false; // ������������� ������?
	IS_CORRECT
	{
		// ��� main ��� �������?
		if (IS_MAIN || (PREVIOUS_LEXEM == LEX_FUNCTION))
		{
			for (int i = 0; i < idTable.currentSize; i++)
			{
				// �������� �� �������������
				// to do: main over
				if (idTable.GetEntry(i).id == "main") throw ERROR_THROW(141);
				if (idTable.GetEntry(i).id == token) throw ERROR_THROW(140);
			}
			idTable.Add({ lexTable.currentSize, (char*)token, getType(BEFORE_PREVIOUS_LEXEM), IT::F, GetParentID(lexTable, idTable) });
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });		
			idWasFounded = true;
			
		}
		// ��� ����������?
		if (!idWasFounded && (BEFORE_PREVIOUS_LEXEM == LEX_DECLARE))
		{
			for (int i = 0; i < idTable.currentSize; i++)
				if (idTable.GetEntry(i).id == token && idTable.GetEntry(i).parentId == GetParentID(lexTable, idTable)) 
					throw ERROR_THROW(142);
			idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::V, GetParentID(lexTable, idTable)});
			lexTable.Add({ LEX_ID, strNumber, idTable.currentSize - 1 });
			idWasFounded = true;

		}
		// ��� �������� �������?
		if	(!idWasFounded && 
			(BEFORE_PREVIOUS_LEXEM == LEX_LEFTHESIS || 
			 BEFORE_PREVIOUS_LEXEM == LEX_COMMA)) // �������� �� �� ��� ���� ��� ��������
		{
			for (int i = 0; i < idTable.currentSize; i++)
				if (idTable.GetEntry(i).id == token && idTable.GetEntry(i).parentId == GetParentID(lexTable, idTable))
					throw ERROR_THROW(143);
			idTable.Add({ lexTable.currentSize, (char*)token, getType(PREVIOUS_LEXEM), IT::P, GetParentID(lexTable, idTable, true) });
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
				if(!strcmp(token, idTable.GetEntry(i).id) && parentElement == idTable.GetEntry(i).parentId)
					lexTable.Add({ LEX_ID, strNumber, i});
				idWasFounded = true;
			}
		}	
	}
	DELETE_AUTOMAT
	return idWasFounded;
}