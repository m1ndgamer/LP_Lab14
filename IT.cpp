#include "IT.h"
#include "Error.h"
#include <string.h>
#include <fstream>
#include <iomanip>

namespace IT
{
	IdTable IdTable::Create(int size)
	{
		if (size >= ID_MAXSIZE) // исключение
			return { size, 0, new Entry[size] };
	}

	void IdTable::Add(IdTable& idTable, Entry entry)
	{
		if (idTable.current_size >= idTable.maxsize) // исключение
			idTable.table[idTable.current_size++] = entry;
	}

	Entry IdTable::GetEntry(IdTable& idTable, int n)
	{
		if (n < idTable.maxsize && n >= 0)
			return idTable.table[n];
	}

	int IdTable::IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.current_size; i++)
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