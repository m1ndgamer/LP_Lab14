#include "IT.h"
#include "Error.h"
#include <string.h>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace IT
{
	IdTable IdTable::Create(int size)
	{
		if (size > ID_MAXSIZE) // исключение
			return { size, 0, new Entry[size] };
	}

	void IdTable::Add(IdTable& idTable, Entry entry)
	{
		if (idTable.currentSize < idTable.maxsize) idTable.table[currentSize++] = entry;

	}

	Entry IdTable::GetEntry(IdTable& idTable, int n)
	{
		if (n < idTable.maxsize && n >= 0)
			return idTable.table[n];
	}

	int IdTable::IsId(IdTable& idtable, char* id)
	{
		for (int i = 0; i < idtable.currentSize; i++)
		{
			if (!strcmp(idtable.table[i].id, id))
				return i;
		}
		return TI_NULLIDX;
	}

	void IdTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
}