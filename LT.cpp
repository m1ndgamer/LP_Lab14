#include "LT.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include <fstream>
#include <iomanip>

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
namespace Log
{
	void PrintLexTable(LOG& log, LT::LexTable& lexTable)
	{
		if ((*log.stream).is_open())
		{
			*log.stream << "+================================+" << std::endl;
			*log.stream << "|         ТАБЛИЦА ЛЕКСЕМ         |" << std::endl;
			*log.stream << "+================================+" << std::endl;
			*log.stream << '|' << std::setw(10) << "Лексема" << "|"
				<< std::setw(10) << "№ стр." << "|"
				<< std::setw(10) << "№ в ТИ" << "|" << std::endl;

			*log.stream << "+================================+" << std::endl;
			LT::Entry entry;
			for (int i = 0; i < lexTable.currentSize; i++)
			{
				entry = lexTable.GetEntry(i);
				std::string idTI = "";
				if (entry.idxTI != -1)
				{
					idTI = std::to_string(entry.idxTI);
				}
				else
					idTI = "-";
				*log.stream << '|' << std::setw(10) << entry.lexem
							<< "|" << std::setw(10) << entry.lineNumber
							<< '|' << std::setw(10) << idTI
							<< '|' << std::endl;
			}
			*log.stream << "+================================+" << std::endl;
			*log.stream << std::endl << std::endl;
			int line = 0;
			for (int i = 0; i < lexTable.currentSize; i++)
			{			
				entry = lexTable.GetEntry(i);
				if (entry.lineNumber != line)
				{
					*log.stream << std::endl;
					line++;
					*log.stream << std::setw(4) << entry.lineNumber << " | ";
				}
				*log.stream << entry.lexem;
			}
		}
		else ERROR_THROW(112)
	}
}