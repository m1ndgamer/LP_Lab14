#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDLINE '\n'
#define IN_CODE_TAB '\t'
#define IN_CODE_SPACE ' '
#define IN_CODE_ENDSTRING '\0'
#define IS_UPPER_CASE_ENG(sym) (sym >= 'A' && sym <= 'Z')
#define IS_LOWER_CASE_ENG(sym) (sym >= 'a' && sym <= 'z')
#define IS_UPPER_CASE_RUS(sym) (sym >= 'À' && sym <= 'ß')
#define IS_LOWER_CASE_RUS(sym) (sym >= 'à' && sym <= 'ÿ')


//Symbols
#define IN_CODE_TABLE {\
	/*		0		1		2		3		4		5		6		7		8		9		A		B		C		D		E		F */\
/*	0 */IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::S,	IN::S,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	1 */IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	2 */IN::S,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::S,	IN::S,	IN::S,	IN::S,	IN::S,	IN::S,	IN::S,	IN::T,	IN::S,\
/*	3 */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::S,	IN::S,	IN::S,	IN::S,	IN::S,\
/*	4 */IN::F,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
/*	5 */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	6 */IN::F,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
/*	7 */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::S,	IN::F,	IN::S,	IN::F,	IN::F,\
		\
/*	8 */IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	9 */IN::F,	IN::F,	IN::F,	IN::T,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	A */IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	B */IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
/*	C */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
/*	D */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
/*	E */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
/*	F */IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
}
namespace In
{
	
	struct IN
	{
		enum {T = 1024, S = 1025,  F = 2048, I = 4096};
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
	};
	IN getIn(wchar_t infile[]);
}