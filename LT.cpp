#include "LT.h"
#include "Error.h"
#include "In.h"
#include <fstream>

namespace LT
{
	// Создать таблицу
	LexTable LexTable::Create(int size)
	{
		if (size > LT_MAXSIZE) throw ERROR_THROW(113);
		return { size, 0, new Entry[size] };
	}
	// добавить запись
	void LexTable::Add(Entry entry)
	{
		(currentSize < maxSize) ? table[currentSize++] = entry : throw ERROR_THROW(113);
	}
	// получить запись
	Entry LexTable::GetEntry(int n)
	{
		if (n >= maxSize || n < 0) throw ERROR_THROW(121);
		return table[n];
	}
	// удалить таблицу
	void LexTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
}