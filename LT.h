#pragma once

#define LEXEM_SIZE		1			// размер лексемы
#define	LT_MAXSIZE		4096		// максимальное количество строк в таблице
#define	LT_TI_NULLXDX	0xffffffff	// нет элемента таблицы идентификаторов				
#define	LEX_INTEGER		't'			// integer
#define	LEX_STRING		't'			// string
#define	LEX_ID			'i'			// идентификатор
#define	LEX_LITERAL		'l'			// литерал
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

#define PARM_LEX_DEFAULT_EXT L".lex.txt" //расширение файла с итогом лексического анализa


// таблица лексем
namespace LT
{
	struct Entry						// строка
	{
		char lexem;						// лесема
		int lineNumber;					// номер строки в исходном тексте
		int idxTI;						// индекс в таблице или LT_TI_NULLIDX
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable						// таблица лексем
	{
		int maxSize;					// максимальный размер таблицы
		int currentSize;				// текущий размер таблицы
		Entry* table;					// строки таблицы

		// создать таблицу
		LexTable();

		void Add(Entry entry);						// добавить строку
		Entry GetEntry(int n);						// получить строку по номеру
		void PrintTableInFile(const wchar_t* in);	// вывод таблицы в файл
		void Delete();								// удалить таблицу
	};
}