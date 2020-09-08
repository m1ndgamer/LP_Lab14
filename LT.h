#pragma once

#define LEXEM_SIZE		1			// ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � �������
#define	LT_TI_NULLXDX	0xffffffff	// ��� �������� ������� ���������������				
#define	LEX_INTEGER		't'			// integer
#define	LEX_STRING		't'			// string
#define	LEX_ID			'i'			// �������������
#define	LEX_LITERAL		'l'			// �������
#define	LEX_FUNCTION	'f'			// function
#define	LEX_DECLARE		'd'			// declare
#define	LEX_RETURN		'r'			// return
#define	LEX_PRINT		'p'			// print
#define	LEX_SEMICOLON	';'			// ;
#define	LEX_COMMA		','			// ,
#define	LEX_LEFTBRACE	'{'			// {
#define	LEX_RIGHTBRACE	'}'			// }
#define	LEX_LEFTHESIS	'('			// (
#define	LEX_RIGHTHESIS	')'			// )
#define	LEX_PLUS		'+'			// +
#define	LEX_MINUS		'-'			// -
#define	LEX_STAR		'*'			// *
#define	LEX_DIRSLASH	'/'			// /
#define	LEX_EQUAL_SIGN	'='			// =

#define PARM_LEX_DEFAULT_EXT L".lex.txt" //���������� ����� � ������ ������������ ������a


// ������� ������
namespace LT
{
	struct Entry						// ������
	{
		char lexem;						// ������
		int lineNumber;					// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��� LT_TI_NULLIDX
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable						// ������� ������
	{
		int maxSize;					// ������������ ������ �������
		int currentSize;				// ������� ������ �������
		Entry* table;					// ������ �������

		// ������� �������
		LexTable();

		void Add(Entry entry);						// �������� ������
		Entry GetEntry(int n);						// �������� ������ �� ������
		void PrintTableInFile(const wchar_t* in);	// ����� ������� � ����
		void Delete();								// ������� �������
	};
}