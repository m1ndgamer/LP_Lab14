#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include <ctime>

namespace Log
{
	// Открыть поток для записи.
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
	
	// Записть время в лог-файл.
	void WriteLog(LOG& log)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[128];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, strlen(buffer), 
			"------- Протокол -------\nДата: %d.%m.%Y %H:%M:%S\n------------------------", timeinfo);
		*log.stream << buffer << std::endl;
	}

	// Записть ключи в лог-файл.
	void WriteParm(LOG& log, Parm::PARM parm)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		char result[300];
		wcstombs(result, parm.in, wcslen(parm.in) + 1); *log.stream << "-in: " << result << std::endl;
		wcstombs(result, parm.out, wcslen(parm.out) + 1); *log.stream << "-out: " << result << std::endl;
		wcstombs(result, parm.log, wcslen(parm.log) + 1); *log.stream << "-log: " << result << std::endl;
	}

	// Записать информацию об обработке в лог-файл.
	void WriteIn(LOG& log, In::IN in)
	{
		if ((*log.stream).is_open()) ERROR_THROW(112)
		*log.stream << "------- Исходные данные -------" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Количество строк: " << in.lines << std::endl;
		*log.stream << "Проигнорировано: " << in.ignor << std::endl;
	}

	// Записать в выходной файл.
	void WriteInsideOutFile(Parm::PARM parm, In::IN in)
	{
		std::ofstream outFile;
		outFile.open(parm.out);
		if (!outFile) throw ERROR_THROW(101);
		outFile << in.text;
		outFile.close();
	}

	// Записать ошибку в лог-файл.
	void WriteError(LOG& log, Error::ERROR error)
	{
		*log.stream << error.message;
	}

	// Закрыть поток записи.
	void Close(LOG& log)
	{
		if (log.stream != NULL && (*log.stream).is_open()) (*log.stream).close();
	}
}