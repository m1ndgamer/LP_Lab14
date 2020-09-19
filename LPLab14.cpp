#include "stdafx.h"
#include <locale>
#include <cwchar>
#include <fstream>
#include <string>
#include <iomanip>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Analysis.h"
#include "LT.h"
#include "IT.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try 
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getIn(parm.in);
		LT::LexTable lexTable = lexTable.Create();
		IT::IdTable idTable = idTable.Create();
		Lex(in, lexTable, idTable);
		int current = 0;
		for (int i = 0; i < lexTable.currentSize; i++)
		{
			LT::Entry entry = lexTable.GetEntry(lexTable, i);
			if (entry.lineNumber != current)
			{
				std::cout << '\n';
				current++;
				std::cout << std::setw(4) << entry.lineNumber << " | ";
			}
			std::cout << entry.lexem;
		}
		std::cout << std::endl;
		for (int i = 0; i < idTable.currentSize; i++)
		{
			IT::Entry e = idTable.GetEntry(idTable, i);
			//if (entry.lineNumber != current)
			//{
			//	std::cout << '\n';
			//	current++;
			//	std::cout << std::setw(4) << entry.lineNumber << " | ";
			//}
			std::cout << e.idxfirstLE << "  ";
			std::cout << e.id << "  ";
			std::cout << std::setw(4) << e.iddatatype;
			std::cout << std::setw(4) << e.idtype << std::endl;
		}
		

		std::cout << std::endl;
		Log::WriteInsideOutFile(parm, in);
		Log::WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L"без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Log::Close(log);
		std::wcout
			<< L"--------------- Результат -------------" << std::endl
			<< L"-in: " << parm.in << std::endl
			<< L"-out: " << parm.out << std::endl
			<< L"-log: " << parm.log << std::endl
			<< L"---------------------------------------" << std::endl;
	}
	catch (Error::ERROR e)
	{	
		if (log.stream != NULL && log.stream->is_open())
		{
			// Вывод информации об ошибке в консоль и закрытие потока.
			Log::WriteLine(log, (wchar_t*)L"Тест: ", L"обнаружна ошибка ", L"");
			Log::WriteLine(log, (char*)getErrorInfo(e).c_str(), "");
			Log::Close(log);
		}
		// Вывод информации об ошибке в консоль.
		std::cout << getErrorInfo(e);
	}

	system("pause");	
	return 0;
}
#pragma region test keys
//-in:D:\code.txt
//-in:F:\LP_Labs\Lab10\testIn.txt
//-in:F:\LP_Labs\Lab10\testIn2.txt
//-out:F:\LP_Labs\Lab10\testOut.txt
//-log:F:\LP_Labs\Lab10\testLog.txt
#pragma endregion

