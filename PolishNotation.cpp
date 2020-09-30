#include "PolishNotation.h"
#include <vector>
#include <string>
#include <iostream>


#define BACK_LEXEM lextable.GetEntry(stack.back()).lexem
#define GET_LEXEM(i) lextable.GetEntry(i).lexem
namespace PolishNotation
{
	// Получить приоритет операции.
	int getPriority(char sign)
	{
		if (sign == '(' || sign == ')') return 1;
		else if (sign == '+' || sign == '-') return 2;
		else if (sign == '*' || sign == '/') return 3;
		else return 0;
	}
	// Это арифметическая операция?
	bool isOperation(char symbol) { return symbol == LEX_SIGN; }
	// Это круглая скобка?
	bool isBrace(char symbol) { return symbol == LEX_LEFTHESIS || symbol == LEX_RIGHTHESIS; }
	// Это индетификатор или литерал?
	bool isLitOrId(char symbol) { return symbol == LEX_ID || symbol == LEX_LITERAL; }

	bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable)
	{
		std::vector<int> stack;
		std::string result = "";
		int posInExp = lextable_pos;
		for (lextable_pos; lextable_pos < lextable.currentSize; lextable_pos++)
		{
			LT::Entry entry = lextable.GetEntry(lextable_pos);
			if (isLitOrId(entry.lexem)) lextable.table[posInExp++] = entry;
			else if (isOperation(entry.lexem))
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS)
				{
					stack.push_back(lextable_pos);
				}
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					{
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority(*i))
						{
							i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else { break; }
					}
					stack.push_back(lextable_pos);
				}
				else {}
			else if (entry.lexem == LEX_LEFTHESIS)
			{
				stack.push_back(lextable_pos);
			}
			else if (entry.lexem == LEX_RIGHTHESIS)
			{
				for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
				{
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						lextable.table[posInExp++] = lextable.GetEntry(*i);
						i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else
					{
						stack.erase(i.base() - 1);
						break;
					}
				}
			}
			else if (entry.lexem == LEX_COMMA || entry.lexem == LEX_SEMICOLON)
			{
				break;
			}
			else return false;
		}
		for (std::vector<int>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
		{
			lextable.table[posInExp++] = lextable.GetEntry(*i);
		}
		for (posInExp; posInExp < lextable_pos; posInExp++)
		{
			lextable.table[posInExp].lexem = '@';
		}
		std::cout << result << std::endl;
		return true;
	}
}