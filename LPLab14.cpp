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

static flagForTypeOfVar FlagForTypeOfVar;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	IT::IdTable idTable;
	LT::LexTable lexTable;
	try 
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getIn(parm.in);
		lexTable = lexTable.Create();
		parsingIntoLexems(in, lexTable, idTable);
		Log::WriteInsideOutFile(parm, in);
		WriteLine(log, (wchar_t*)L"����: ", (wchar_t*)L"��� ������ ", L"");
		WriteLog(log);
		WriteParm(log, parm);
		WriteIn(log, in);
		PrintIdTable(log, idTable);
		PrintLexTable(log, lexTable);
		//for (int i = 0; i < lexTable.currentSize; i++)
		//{
		//	LT::Entry entry = lexTable.GetEntry(i);
		//	Log::WriteLine(log, (char*)entry, "");
		//	
		//}


		
		Log::Close(log);
		std::wcout
			<< L"--------------- ��������� -------------" << std::endl
			<< L"-in: " << parm.in << std::endl
			<< L"-out: " << parm.out << std::endl
			<< L"-log: " << parm.log << std::endl
			<< L"---------------------------------------" << std::endl;
	}
	catch (Error::ERROR e)
	{	
		if (log.stream != NULL && log.stream->is_open())
		{
			// ����� ���������� �� ������ � ������� � �������� ������.
			Log::WriteLine(log, (wchar_t*)L"����: ", L"��������� ������ ", L"");
			Log::WriteLine(log, (char*)getErrorInfo(e).c_str(), "");
			Log::Close(log);
		}
		// ����� ���������� �� ������ � �������.
		std::cout << getErrorInfo(e);
	}
	lexTable.Delete();
	idTable.Delete();
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

