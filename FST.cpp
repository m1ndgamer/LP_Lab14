#include "FST.h"
#include <iostream>

FST::RELATION::RELATION(char symbol, short newState)
{
	transitionSymbol = symbol;
	nnode = newState;
}

FST::NODE::NODE()
{
	relationCounter = 0;
	relations = NULL;
}

FST::NODE::NODE(short n, RELATION rel, ...)
{
	relationCounter = n;
	relations = new RELATION[n];

	RELATION* ptr = &rel;
	for (short i = 0; i < n; i++)
		relations[i] = *ptr++;
}

FST::FST::FST(const char* s, short countOfStates, NODE states, ...)
{
	string = s;
	statesCounter = countOfStates;
	nodes = new NODE[countOfStates];

	NODE* p = &states;
	for (int k = 0; k < countOfStates; k++)
		nodes[k] = *p++;

	rstates = new short[countOfStates];
	memset(rstates, -1, sizeof(short) * statesCounter);
	rstates[0] = 0;
	position = -1;
}

bool FST::step(FST& fst, short* rstates)
{
	std::swap(rstates, fst.rstates);
	bool rc = false;

	for (short i = 0; i < fst.statesCounter; i++)
	{
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].relationCounter; j++)
				if (fst.nodes[i].relations[j].transitionSymbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}
	}
	return rc;
}

bool FST::execute(FST& fst)
{
	short* rstates = new short[fst.statesCounter];
	memset(rstates, -1, sizeof(short) * fst.statesCounter);
	short lstring = strlen(fst.string);
	bool rc = true;

	for (short i = 0; (i < lstring) && rc; i++)
	{
		fst.position++;
		rc = step(fst, rstates);
	}
	(fst.rstates[fst.statesCounter - 1]) == (lstring) ? rc = true : rc = false;
	return rc;
}