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
		// выражение.
		std::vector<int> expression;
		// стек операторов и скобок.
		std::vector<int> stack;
		LT::Entry entry, bufferEntry;
		// позиция первой лексемы выражения в ТЛ.
		int startInLT = lextable_pos;
		// предыдущий символ выражения.
		char prev = '@';
		// 
		for (lextable_pos; lextable_pos < lextable.currentSize; lextable_pos++)
		{
			// получение записи из ТЛ.
			entry = lextable.GetEntry(lextable_pos);
			// операнд
			if (isOperand(entry.lexem) && (prev != LEX_LITERAL || prev != LEX_ID))
				// добавить в стек операторов и скобок.
				expression.push_back(lextable_pos);
			// операция
			else if (isOperation(entry.lexem) && prev != LEX_SIGN)
			{
				// если стек пустой или пред. элем. '(', то добавляем лексему в стек операторов
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS) stack.push_back(lextable_pos);
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority(*i))
						{
							expression.push_back(*i);
							i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else { break; }
					stack.push_back(lextable_pos);
				}
				else return false;
			}
			// левая скобка
			else if (entry.lexem == LEX_LEFTHESIS)
				stack.push_back(lextable_pos);
			// правая скобка скобка.
			else if (entry.lexem == LEX_RIGHTHESIS)
				for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					// запись 
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						expression.push_back(*i);
						i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else { stack.erase(i.base() - 1); break; }
			// конец выражения.
			else if (entry.lexem == LEX_COMMA || entry.lexem == LEX_SEMICOLON) break;
			// выражение.
			else return false;
			prev = lextable.GetEntry(lextable_pos).lexem;
		}
		// запись оставшихся операторов в выражение.
		for (std::vector<int>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
			expression.push_back(*i);
		// установка позиций в ТЛ и ТИ исходя из польской записи.
#pragma region SortElems
		for (int i = 0; i < expression.size(); i++)
		{
			entry = lextable.GetEntry(expression[i]);
			if (expression[i] == idTable.GetEntry(entry.idxTI).idxfirstLE)
			{
				idTable.GetEntry(entry.idxTI).idxfirstLE == startInLT;
			}
			bufferEntry = lextable.GetEntry(startInLT);
			lextable.table[startInLT++] = entry;
			lextable.table[expression[i]] = bufferEntry;
		}
		for (startInLT; startInLT < lextable_pos; startInLT++)
		{
			lextable.table[startInLT] = { '@', -1, -1 };
		}
#pragma endregion
		return true;
	}
}