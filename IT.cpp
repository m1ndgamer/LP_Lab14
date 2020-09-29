#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "In.h"
#include "IT.h"
#include "Error.h"
#include "Log.h"

namespace IT
{
	IT::Entry::Entry()
	{
		idxfirstLE = 0;
		*id = IN_CODE_ENDSTRING;
		strcpy(id, "undef");
		iddatatype = INT;
		idtype = V;
	}

	IT::Entry::Entry(int first, char* i, IDDATATYPE datatype, IDTYPE type, int parent)
	{
		idxfirstLE = first;
		parentId = parent;
		strcpy(id, i);
		iddatatype = datatype;
		idtype = type;
	}

	IdTable::IdTable(int size)
	{
		maxsize = TI_MAXSIZE;
		currentSize = 0;
		table = new Entry[TI_MAXSIZE];
	}

	void IdTable::Add(Entry entry)
	{
		switch (entry.iddatatype)
		{
		case IT::STR:
			strcpy(entry.value.vstr->str, "\0");
			entry.value.vstr->len = TI_INT_DEFAULT;
			break;
		default:
			entry.value.vint = TI_INT_DEFAULT;
			break;
		}
		(currentSize < maxsize) ? table[currentSize++] = entry : throw ERROR_THROW(121);
	}

	Entry IdTable::GetEntry(int n)
	{
		if (n < maxsize && n >= 0) return table[n];
		else throw ERROR_THROW(122);
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
namespace Log
{
	void PrintIdTable(LOG log, IT::IdTable in)
	{
		log.stream->write()
		idStream->open(id);
		if (idStream->is_open())
		{
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << "|								ÒÀÁËÈÖÀ ÈÍÄÅÒÈÔÈÊÀÒÎÐÎÂ		                       |" << std::endl;
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(3) << "¹: " << "|" << std::setw(8) << "ID: " << '|' << std::setw(10) << "Ðîä. áëîê" << '|'
				<< std::setw(18) << "¹ â òàáë. ëåêñ." << '|' << std::setw(10) << "Òèï çíà÷." << '|'
				<< std::setw(16) << "Òèï ID" << '|' << std::endl;

			*(idStream) << "====================================================================================" << std::endl;

			for (int i = 0; i < currentSize; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::L)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(15) << "INT  " << '|' << std::setw(50) << this->table[i].value.vint << '|' << std::setw(15) << "-" << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(15) << "STR  " << '|' << std::setw(50) << this->table[i].value.vstr.str << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}
			}

			*(idStream) << "====================================================================================" << std::endl;

		}
	}
}