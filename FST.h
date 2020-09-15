#include <iostream>
namespace FST
{
	struct RELATION
	{
		char transitionSymbol; // символ перехода
		short nnode; // номер смежной вершины
		RELATION(char transitionSymbol = 0x00, short newState = NULL);
	};

	struct NODE
	{
		short relationCounter; // ко-во рёбер
		RELATION* relations; // рёбра
		NODE();
		NODE(short relationCount, RELATION rel, ...);
	};

	struct FST
	{
		const char* string; /*цепочка*/
		short position; /*позиция в цепочке*/
		short statesCounter; /*кол-во состояний*/
		NODE* nodes; /*граф перехода*/
		short* rstates; /*возможные состояния*/
		FST();
		FST(const char* s, short statesCounter, NODE states, ...);
	};

	bool step(FST& fst, short* rstates); // разбор одного символа
	bool execute(FST& fsts /*конечный автомат*/);  //распонование цепочки
}