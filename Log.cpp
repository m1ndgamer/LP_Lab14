#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include <ctime>

#define EOL	log.stream->write((char*)"\n", 1);
#define LABEL(parm) log.stream->write((char*)parm, strlen(parm));

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
	void WriteLine(LOG log, char* c, ...)
	{
		for (char** ptr = &c; *ptr != ""; ptr++) {
			*log.stream << *ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		char* str = new char[IN_MAX_LEN_TEXT];
		for (wchar_t** ptr = &c; *ptr != L""; ptr++) log.stream->write((const char*)str, wcstombs(str, *ptr, wcslen(*ptr) + 1));
		EOL
			delete[] str;
	}
#pragma endregion
	
	// Записть время в лог-файл.
	void WriteLog(LOG log)
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[128];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, strlen(buffer), 
			"------- Протокол -------\nДата: %d.%m.%Y %H:%M:%S\n------------------------", timeinfo);
		LABEL(buffer) EOL
	}

	// Записть ключи в лог-файл.
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char result[300];
		wcstombs(result, parm.in, wcslen(parm.in) + 1);
		LABEL("-in: ") log.stream->write(result, strlen(result)); EOL
		wcstombs(result, parm.out, wcslen(parm.out) + 1);
		LABEL("-out: ") log.stream->write(result, strlen(result)); EOL
		wcstombs(result, parm.log, wcslen(parm.log) + 1);
		LABEL("-log: ") log.stream->write(result, strlen(result)); EOL
	}

	// Записать информацию об обработке в лог-файл.
	void WriteIn(LOG log, In::IN in)
	{
		char buffer[8];
		LABEL("------- Исходные данные -------") EOL
		LABEL("Количество символов: ") log.stream->write(buffer, strlen(_itoa(in.size, buffer, 10))); EOL
		LABEL("Количество строк: ") log.stream->write(buffer, strlen(_itoa(in.lines, buffer, 10))); EOL
		LABEL("Проигнорировано: ")log.stream->write(buffer, strlen(_itoa(in.ignor, buffer, 10))); EOL
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
	void WriteError(LOG log, Error::ERROR error)
	{
		log.stream->write(error.message, strlen(error.message));
	}

	// Закрыть поток записи.
	void Close(LOG log)
	{
		if (log.stream != NULL && log.stream->is_open()) log.stream->close();
	}
}