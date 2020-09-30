#include "PolishNotation.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

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
	bool isOperand(char symbol) { return symbol == LEX_ID || symbol == LEX_LITERAL; }

	bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable)
	{
		// стек операторов
		std::vector<int> expression;
		std::vector<int> stack;
		LT::Entry entry;
		LT::Entry bufferEntry;
		int startInLT = lextable_pos;
		int lexPosition = lextable_pos;
		char prev = '=';
		for (lextable_pos; lextable_pos < lextable.currentSize; lextable_pos++)
		{
			entry = lextable.GetEntry(lextable_pos);
			// операнд
			if (isOperand(entry.lexem) && (prev != LEX_LITERAL || prev != LEX_ID))
			{
				expression.push_back(lextable_pos);
				prev = lextable.GetEntry(lextable_pos).lexem;
			}
			// операция
			else if (isOperation(entry.lexem) && prev != LEX_SIGN)
			{
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS) stack.push_back(lextable_pos);
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority(*i))
							i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
						else { break; }
					stack.push_back(lextable_pos);
					prev = lextable.GetEntry(lextable_pos).lexem;
				}
				else {}
			}
			// левая скобка
			else if (entry.lexem == LEX_LEFTHESIS)
			{
				stack.push_back(lextable_pos);
				prev = lextable.GetEntry(lextable_pos).lexem;
			}
			else if (entry.lexem == LEX_RIGHTHESIS)
			{
				prev = lextable.GetEntry(lextable_pos).lexem;
				for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
				{
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						expression.push_back(*i);
						i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else { stack.erase(i.base() - 1); break; }
				}
			}
			else if (entry.lexem == LEX_COMMA || entry.lexem == LEX_SEMICOLON) break;
			else return false;
		}
		for (std::vector<int>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
			expression.push_back(*i);
		for (int i = 0; i < expression.size(); i++)
		{
			bufferEntry = lextable.GetEntry(startInLT);
			lextable.table[startInLT++] = lextable.GetEntry(expression[i]);
			lextable.table[expression[i]] = bufferEntry;
		}
		return true;
	}
}