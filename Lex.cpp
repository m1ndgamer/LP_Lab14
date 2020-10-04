LEX::LEX()
{
	lextable = LT::LexTable();
	idTable = IT::IdTable();
}

LEX::LEX(LT::LexTable lt, IT::IdTable it)
{
	lextable = lt;
	idTable = it;
}
