#pragma once
struct LEX
{
	LT::LexTable lextable;
	IT::IdTable idTable;
	LEX();
	LEX(LT::LexTable lt, IT::IdTable it);
};