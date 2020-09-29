#include "stdafx.h"
#include "Error.h"
#include <string>
namespace Error 
{
	// Табилца ошибок.
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"), 
	    ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), 
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in: должен быть задан (-in: первый параметр)"),
		ERROR_ENTRY(101, "Не удается создать выходной файл"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входящего параметра\n максимальная длина 300 символов" ),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in:)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in:)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log:)"),
		ERROR_ENTRY_NODEF(113, "Превашен маскимальный размер таблицы лексем"), 
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF(120),
		ERROR_ENTRY(121, "Обращение к несуществющему элементу таблицы лексем"),
		ERROR_ENTRY(122, "Обращение к несуществющему элементу таблицы индетификаторов"),
		ERROR_ENTRY_NODEF(123),
		ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "Не распознана лексема"),
		ERROR_ENTRY_NODEF(131),
		ERROR_ENTRY_NODEF(132),
		ERROR_ENTRY_NODEF(133),
		ERROR_ENTRY_NODEF(134),
		ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136),
		ERROR_ENTRY(137, "Превышен допустимый размер лексемы"),
		ERROR_ENTRY(138, "Непредвиденный конец файла"),
		ERROR_ENTRY(139, "Превышен допустимый размер строки"),
		ERROR_ENTRY(140, "Переопределение функции"),
		ERROR_ENTRY(141, "Переопределение main"),
		ERROR_ENTRY(142, "Переопределение переменной"),
		ERROR_ENTRY(143, "Переопределение параметра функции"),
		ERROR_ENTRY_NODEF(144),
		ERROR_ENTRY_NODEF(145),
		ERROR_ENTRY_NODEF(146),
		ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	// C ошибку.
	ERROR getError(int id)
	{
		ERROR e;
		if (id <= 0 || id > ERROR_MAX_ENTRY) e = errors[0];
		else e = errors[id];
		return e;
	}
	// Получить ошибку входного файла.
	ERROR getErrorIn(int id, int line = -1, int col = -1)
	{
		ERROR e;
		if (id <= 0 || id > ERROR_MAX_ENTRY) e = errors[0];
		else 
		{
			e = errors[id];
			e.inext = { (short)line, (short)col};

		}
		return e;
	}

	std::string getErrorInfo(ERROR e)
	{
		std::string errorInfo = "Ошибка " + std::to_string(e.id) + ": " + e.message + "\n";
		if (e.inext.col != -1 && e.inext.line != -1 && e.inext.symbol != 'H')
		{
			errorInfo += "строка " + std::to_string(e.inext.line) + " ";
			errorInfo += "позиция " + std::to_string(e.inext.col) + "\n";
		}
		return errorInfo;
	}
};