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