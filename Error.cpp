#include "stdafx.h"
#include "Error.h"
#include <string>
namespace Error 
{
	// ������� ������.
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������."),
		ERROR_ENTRY(1, "��������� ����."), 
	    ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), 
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in: ������ ���� ����� (-in: ������ ��������)."),
		ERROR_ENTRY(101, "�� ������� ������� �������� ����."),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� ��������� ���������\n ������������ ����� 300 ��������" ),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in:)."),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in:)."),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log:)."),
		ERROR_ENTRY(113, "�������� ������������ ������ ������� ������."),
		ERROR_ENTRY(114, "�������� ������������ ������ ������� ���������������."),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF(120),
		ERROR_ENTRY(121, "��������� � �������������� �������� ������� ������."),
		ERROR_ENTRY(122, "��������� � �������������� �������� ������� ���������������."),
		ERROR_ENTRY_NODEF(123),
		ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "�� ���������� �������."),
		ERROR_ENTRY_NODEF(131),
		ERROR_ENTRY_NODEF(132),
		ERROR_ENTRY_NODEF(133),
		ERROR_ENTRY_NODEF(134),
		ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY(136, "�������� ���������� ������ ��������������."),
		ERROR_ENTRY(137, "�������� ���������� ������ �������."),
		ERROR_ENTRY(138, "�������������� ����� �����."),
		ERROR_ENTRY(139, "�������� ���������� ������ ������."),
		ERROR_ENTRY(140, "��������������� �������."),
		ERROR_ENTRY(141, "��������������� main."),
		ERROR_ENTRY(142, "��������������� ����������."),
		ERROR_ENTRY(143, "��������������� ��������� �������."),
		ERROR_ENTRY(144, "�� ���������� ������� main."),
		ERROR_ENTRY_NODEF(145),
		ERROR_ENTRY_NODEF(146),
		ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF(160),
		ERROR_ENTRY(161, "������������ ���������."),
		ERROR_ENTRY_NODEF(162),
		ERROR_ENTRY_NODEF(163),
		ERROR_ENTRY_NODEF(164),
		ERROR_ENTRY_NODEF(165),
		ERROR_ENTRY_NODEF(166),
		ERROR_ENTRY_NODEF(167),
		ERROR_ENTRY_NODEF(168),
		ERROR_ENTRY_NODEF(169),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), 
		ERROR_ENTRY_NODEF100(300), 
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "�������� ��������� ���������"),
		ERROR_ENTRY(601, "��������� ��������"),
		ERROR_ENTRY(602, "������ � ���������"),
		ERROR_ENTRY(603, "������ � ���������� �������"),
		ERROR_ENTRY(604, "������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF(605),ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	// C ������.
	ERROR getError(int id)
	{
		ERROR e;
		if (id <= 0 || id > ERROR_MAX_ENTRY) e = errors[0];
		else e = errors[id];
		return e;
	}
	// �������� ������ �������� �����.
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
		std::string errorInfo = "������ " + std::to_string(e.id) + ": " + e.message + "\n";
		if (e.inext.col != -1 && e.inext.line != -1 && e.inext.symbol != 'H')
		{
			errorInfo += "������ " + std::to_string(e.inext.line) + " ";
			errorInfo += "������� " + std::to_string(e.inext.col) + "\n";
		}
		return errorInfo;
	}
};