#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include <ctime>

namespace Log
{
	// ������� ����� ��� ������.
	LOG getlog(wchar_t logfile[])
		{
		static std::ofstream writer;
		LOG log; wcscpy(log.logfile, logfile); log.stream = &writer;	
		log.stream->open(log.logfile);
		if (!log.stream->is_open()) ERROR_THROW(112)
		return log;
	}

#pragma region WriteLine
	void WriteLine(LOG& log, char* c, ...)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		for (char** ptr = &c; *ptr != ""; ptr++)
			*log.stream << *ptr << std::endl;
	}

	void WriteLine(LOG& log, wchar_t* c, ...)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		char temp[256];
		for (wchar_t** ptr = &c; *ptr != L""; ptr++)
		{
			wcstombs(temp, *ptr++, sizeof(temp));
			*log.stream << temp << std::endl;
		}
	}
#pragma endregion
	
	// ������� ����� � ���-����.
	void WriteLog(LOG& log)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[128];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, strlen(buffer), 
			"------- �������� -------\n����: %d.%m.%Y %H:%M:%S\n------------------------", timeinfo);
		*log.stream << buffer << std::endl;
	}

	// ������� ����� � ���-����.
	void WriteParm(LOG& log, Parm::PARM parm)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		char result[300];
		wcstombs(result, parm.in, wcslen(parm.in) + 1); *log.stream << "-in: " << result << std::endl;
		wcstombs(result, parm.out, wcslen(parm.out) + 1); *log.stream << "-out: " << result << std::endl;
		wcstombs(result, parm.log, wcslen(parm.log) + 1); *log.stream << "-log: " << result << std::endl;
	}

	// �������� ���������� �� ��������� � ���-����.
	void WriteIn(LOG& log, In::IN in)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		*log.stream << "------- �������� ������ -------" << std::endl;
		*log.stream << "���������� ��������: " << in.size << std::endl;
		*log.stream << "���������� �����: " << in.lines << std::endl;
		*log.stream << "���������������: " << in.ignor << std::endl;
	}

	// �������� � �������� ����.
	void WriteInsideOutFile(Parm::PARM parm, In::IN in)
	{
		std::ofstream outFile;
		outFile.open(parm.out);
		if (!outFile) throw ERROR_THROW(101);
		outFile << in.text;
		outFile.close();
	}

	// �������� ������ � ���-����.
	void WriteError(LOG& log, Error::ERROR error)
	{
		*log.stream << error.message;
	}

	// ������� ����� ������.
	void Close(LOG& log)
	{
		if (log.stream != NULL && (*log.stream).is_open()) (*log.stream).close();
	}
}