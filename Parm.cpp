#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

// проверка на нахождение ключа key
#define KEY_IS_FOUNDED(key) wcsstr(argv[i], key) != nullptr

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM parms;
		// Если вхоных параметров меньше 1 или ключ -in не задан.
		if (argc <= 1 || wcsstr(argv[1], PARM_IN) == nullptr) throw ERROR_THROW(100)
		for (int i = 0; i < argc; i++)
		{
		    // Если длина параметра больше допустимой.
			if (wcslen(argv[i]) > PARM_MAX_SIZE) throw ERROR_THROW(104)
			// Чтение ключей.
			if (KEY_IS_FOUNDED(PARM_IN)) wcscpy_s(parms.in, argv[i] + wcslen(PARM_IN));
			else if (KEY_IS_FOUNDED(PARM_OUT)) wcscpy_s(parms.out, argv[i] + wcslen(PARM_OUT));
			else if (KEY_IS_FOUNDED(PARM_LOG)) wcscpy_s(parms.log, argv[i] + wcslen(PARM_LOG));
		}
		// Если ключи -out и -in не заданы, то использовать название из -in.
		if (!wcslen(parms.out)) { wcscpy_s(parms.out, parms.in); wcscpy_s(parms.out, wcscat(parms.out, L".out"));}
		if (!wcslen(parms.log)) { wcscpy_s(parms.log, parms.in); wcscpy_s(parms.log, wcscat(parms.log, L".log"));}
		return parms;
	}
}