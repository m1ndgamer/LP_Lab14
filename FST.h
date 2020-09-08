#include <iostream>
namespace FST
{
	struct RELATION
	{
		char transitionSymbol; // ������ ��������
		short nnode; // ����� ������� �������
		RELATION(char transitionSymbol = 0x00, short newState = NULL);
	};

	struct NODE
	{
		short relationCounter; // ��-�� ����
		RELATION* relations; // ����
		NODE();
		NODE(short relationCount, RELATION rel, ...);
	};

	struct FST
	{
		const char* string; /*�������*/
		short position; /*������� � �������*/
		short statesCounter; /*���-�� ���������*/
		NODE* nodes; /*���� ��������*/
		short* rstates; /*��������� ���������*/
		FST();
		FST(const char* s, short statesCounter, NODE states, ...);
	};

	bool step(FST& fst, short* rstates); // ������ ������ �������
	bool execute(FST& fsts /*�������� �������*/);  //������������ �������
}


#pragma region automats

#pragma region FUNCTION

#define A_FUNCTION(string) string, 9,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE(1, FST::RELATION('i', 6)),  \
			FST::NODE(1, FST::RELATION('o', 7)),  \
			FST::NODE(1, FST::RELATION('n', 8)),  \
			FST::NODE()			

#pragma endregion

#pragma region INTEGER

#define A_INTEGER(string) string, 8,			  \
			FST::NODE(1, FST::RELATION('i', 1)),  \
			FST::NODE(1, FST::RELATION('n', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE(1, FST::RELATION('e', 4)),  \
			FST::NODE(1, FST::RELATION('g', 5)),  \
			FST::NODE(1, FST::RELATION('e', 6)),  \
			FST::NODE(1, FST::RELATION('r', 7)),  \
			FST::NODE()		

#pragma endregion

#pragma region STRING

#define A_STRING(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('s', 1)),  \
			FST::NODE(1, FST::RELATION('t', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('i', 4)),  \
			FST::NODE(1, FST::RELATION('n', 5)),  \
			FST::NODE(1, FST::RELATION('g', 6)),  \
			FST::NODE()		

#pragma endregion

#pragma region DECLARE

#define A_DECLARE(string) string, 8,			  \
			FST::NODE(1, FST::RELATION('d', 1)),  \
			FST::NODE(1, FST::RELATION('e', 2)),  \
			FST::NODE(1, FST::RELATION('c', 3)),  \
			FST::NODE(1, FST::RELATION('l', 4)),  \
			FST::NODE(1, FST::RELATION('a', 5)),  \
			FST::NODE(1, FST::RELATION('r', 6)),  \
			FST::NODE(1, FST::RELATION('e', 7)),  \
			FST::NODE()	

#pragma endregion

#pragma region RETURN

#define A_RETURN(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('r', 1)),  \
			FST::NODE(1, FST::RELATION('e', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE(1, FST::RELATION('u', 4)),  \
			FST::NODE(1, FST::RELATION('r', 5)),  \
			FST::NODE(1, FST::RELATION('n', 6)),  \
			FST::NODE()	

#pragma endregion

#pragma region PRINT

#define A_PRINT(string) string, 6,				  \
			FST::NODE(1, FST::RELATION('p', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('n', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE()	

#pragma endregion

#pragma region IDENTIFICATOR

#define A_IDENTIFICATOR(string) string, 1,	\
			FST::NODE(27,	FST::RELATION('a', 0),	\
							FST::RELATION('b', 0),	\
							FST::RELATION('c', 0),	\
							FST::RELATION('d', 0),	\
							FST::RELATION('e', 0),	\
							FST::RELATION('f', 0),	\
							FST::RELATION('g', 0),	\
							FST::RELATION('h', 0),	\
							FST::RELATION('i', 0),	\
							FST::RELATION('j', 0),	\
							FST::RELATION('k', 0),	\
							FST::RELATION('l', 0),	\
							FST::RELATION('m', 0),	\
							FST::RELATION('n', 0),	\
							FST::RELATION('o', 0),	\
							FST::RELATION('p', 0),	\
							FST::RELATION('q', 0),	\
							FST::RELATION('r', 0),	\
							FST::RELATION('s', 0),	\
							FST::RELATION('t', 0),	\
							FST::RELATION('u', 0),	\
							FST::RELATION('v', 0),	\
							FST::RELATION('w', 0),	\
							FST::RELATION('x', 0),	\
							FST::RELATION('y', 0),	\
							FST::RELATION('z', 0),	\
							FST::RELATION('_', 0)),	\
			FST::NODE()			

#pragma endregion

#pragma region STRING_LITERAL
#define A_STRING_LITERAL(string) string, 3,	\
	FST::NODE(1, FST::RELATION('\"', 1)),	\
	FST::NODE(85,	FST::RELATION(' ', 1),	\
					FST::RELATION('a', 1),	\
					FST::RELATION('b', 1),	\
					FST::RELATION('c', 1),	\
					FST::RELATION('d', 1),	\
					FST::RELATION('e', 1),	\
					FST::RELATION('f', 1),	\
					FST::RELATION('g', 1),	\
					FST::RELATION('h', 1),	\
					FST::RELATION('i', 1),	\
					FST::RELATION('j', 1),	\
					FST::RELATION('k', 1),	\
					FST::RELATION('l', 1),	\
					FST::RELATION('m', 1),	\
					FST::RELATION('n', 1),	\
					FST::RELATION('o', 1),	\
					FST::RELATION('p', 1),	\
					FST::RELATION('q', 1),	\
					FST::RELATION('r', 1),	\
					FST::RELATION('s', 1),	\
					FST::RELATION('t', 1),	\
					FST::RELATION('u', 1),	\
					FST::RELATION('v', 1),	\
					FST::RELATION('w', 1),	\
					FST::RELATION('x', 1),	\
					FST::RELATION('y', 1),	\
					FST::RELATION('z', 1),	\
					FST::RELATION('0', 1),	\
					FST::RELATION('1', 1),	\
					FST::RELATION('2', 1),	\
					FST::RELATION('3', 1),	\
					FST::RELATION('4', 1),	\
					FST::RELATION('5', 1),	\
					FST::RELATION('6', 1),	\
					FST::RELATION('7', 1),	\
					FST::RELATION('8', 1),	\
					FST::RELATION('9', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('�', 1),	\
					FST::RELATION('=', 1),	\
					FST::RELATION('+', 1),	\
					FST::RELATION('-', 1),	\
					FST::RELATION('*', 1),	\
					FST::RELATION('/', 1),	\
					FST::RELATION('(', 1),	\
					FST::RELATION(')', 1),	\
					FST::RELATION('{', 1),	\
					FST::RELATION('}', 1),	\
					FST::RELATION(';', 1),	\
					FST::RELATION(',', 1),	\
					FST::RELATION('?', 1),	\
					FST::RELATION('!', 1),	\
					FST::RELATION('\"', 2)),\
	FST::NODE()
#pragma endregion

#pragma region INTEGER_LITERAL

#define A_INTEGER_LITERAL(string) string, 1,	\
	FST::NODE(10,	FST::RELATION('0', 0),	\
					FST::RELATION('1', 0),	\
					FST::RELATION('2', 0),	\
					FST::RELATION('3', 0),	\
					FST::RELATION('4', 0),	\
					FST::RELATION('5', 0),	\
					FST::RELATION('6', 0),	\
					FST::RELATION('7', 0),	\
					FST::RELATION('8', 0),	\
					FST::RELATION('9', 0)),	\
	FST::NODE()
#pragma endregion