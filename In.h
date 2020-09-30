#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDLINE '\n'
#define IN_CODE_TAB '\t'
#define IN_CODE_SPACE ' '
#define IN_CODE_ENDSTRING '\0'

//Symbols
#define IN_CODE_TABLE {\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::A,	'|',	IN::T,	IN::T,	IN::I,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::A,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::A,	IN::A,	IN::A,	IN::A,	IN::A,	IN::A,	IN::T,	IN::A,\
	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::A,	IN::T,	IN::A,	IN::T,	IN::T,\
	IN::T,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,\
	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::T,	IN::T,	IN::T,	IN::T,	IN::N,\
	IN::T,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,\
	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::N,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::A,	IN::T,	IN::A,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T \
}	

namespace In
{
	
	struct IN
	{
		enum {T = 1024, A = 1025, N = 1026,  F = 2048, I = 4096};
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
	};
	IN getIn(wchar_t infile[]);
	void InHandler(IN* in);
}