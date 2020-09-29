#pragma once
#include "stdafx.h"
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "IT.h"
namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream *stream;
	};
	static const LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void PrintIdTable(LOG log, IT::IdTable in);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG log);
	void WriteInsideOutFile(Parm::PARM parm, In::IN in);
}