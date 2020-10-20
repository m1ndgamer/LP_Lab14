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
		strcpy(id, "null");
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
		if (size > TI_MAXSIZE) throw ERROR_THROW(114);
		maxsize = size;
		currentSize = 0;
		table = new Entry[size];
		Add(TYPE_UNDEF);
		Add(TYPE_INT);
		Add(TYPE_STR);
	}

	void IdTable::Add(Entry entry)
	{
		switch (entry.iddatatype)
		{
		case IT::STR:
			strcpy(entry.value.vstr->str, "\0");
			entry.value.vstr->len = 0;
			break;
		default:
			entry.value.vint = TI_INT_DEFAULT;
			break;
		}
		(currentSize < maxsize) ? table[currentSize++] = entry : throw ERROR_THROW(114);
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
	void PrintIdTable(LOG& log, IT::IdTable& idTable)
	{
		if ((*log.stream).is_open())
		{
			*log.stream << "+============================================================+" << std::endl;
			*log.stream << "|                   ÒÀÁËÈÖÀ ÈÍÄÅÒÈÔÈÊÀÒÎÐÎÂ                  |" << std::endl;
			*log.stream << "+============================================================+" << std::endl;
			*log.stream << '|' << std::setw(3) << "¹: " << "|" << std::setw(8) << "ID: " << '|' << std::setw(10) << "Ðîä. áëîê" << '|'
				<< std::setw(8) << "¹ â ÒË." << '|'  << std::setw(16) << "Òèï ID" << '|' << 
				std::setw(10) << "Òèï çíà÷." << '|'  << std::endl; //<< std::setw(24) << "Çíà÷." << '|'

			*log.stream << "+============================================================+" << std::endl;
			for (int i = 0; i < idTable.currentSize; i++)
			{
				IT::Entry entry = idTable.GetEntry(i);
				std::string idDataType = "";
				std::string idType = "";
				std::string parentBlock = "";
#pragma region Type
				switch (entry.iddatatype)
				{
				case 1:
					idDataType = "integer";
					break;
				case 2:
					idDataType = "string";
					break;
				default:
					idDataType = "undef";
					break;
				}

				switch (entry.idtype)
				{
				case 1:
					idType = "ïåðåìåííàÿ";
					break;
				case 2:
					idType = "ôóíêöèÿ";
					break;
				case 3:
					idType = "ïàðàìåòð";
					break;
				case 4:
					idType = "ëèòåðàë";
					break;
				default:
					idType = "undef";
					break;
				}

				if (entry.parentId >= 0 && entry.parentId < idTable.currentSize)
					parentBlock = idTable.GetEntry(entry.parentId).id;
				else
					parentBlock = "-";
#pragma endregion
				* log.stream << '|' << std::setw(3) << i << "|" << std::setw(8) << entry.id << '|' << std::setw(10) << parentBlock << '|'
					<< std::setw(8) << entry.idxfirstLE << '|' << std::setw(16) << idType << '|' 
					<< std::setw(10) << idDataType << '|';
				// OUTPUT VALUE? 
				//if (entry.iddatatype == IT::INT)
				//{
				//	*log.stream << std::setw(24) << entry.value.vint << '|';
				//}
				//else
				//{
				//	*log.stream << std::setw(24) << entry.value.vstr->str << '|';
				//}
				*log.stream << std::endl;
			}

			*log.stream << "+============================================================+" << std::endl;
		}	
		else ERROR_THROW(112)
	}
}