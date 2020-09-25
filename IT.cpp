#define _CRT_SECURE_NO_WARNINGS
#include "IT.h"
#include "Error.h"
#include <string.h>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace IT
{
	IT::Entry::Entry()
	{
		idxfirstLE = 0;
		id = new char[64];
		strcpy(id, "undef");
		iddatatype = INT;
		idtype = V;
	}

	IT::Entry::Entry(int first, char* i, IDDATATYPE datatype, IDTYPE type, int parent)
	{
		idxfirstLE = first;
		parentId = parent;
		id = new char[64];
		strcpy(id, i);
		iddatatype = datatype;
		idtype = type;
	}

	IdTable::IdTable(int size)
	{
		if (size > ID_MAXSIZE); // исключение
		maxsize = TI_MAXSIZE;
		currentSize = 0;
		table = new Entry[TI_MAXSIZE];
	}

	void IdTable::Add(Entry entry)
	{
		(currentSize < maxsize) ? table[currentSize++] = entry : throw ERROR_THROW(121);
	}

	Entry IdTable::GetEntry(int n)
	{
		if (n < maxsize && n >= 0)
			return table[n];
	}

	int IdTable::IsId(char* id)
	{
		for (int i = 0; i < currentSize; i++)
			if (!strcmp(table[i].id, id)) return i;
		return TI_NULLIDX;
	}

	void IdTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
}