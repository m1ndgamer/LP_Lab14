#include "PolishNotation.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#define BACK_LEXEM lextable.GetEntry(stack.back()).lexem
#define GET_LEXEM(i) lextable.GetEntry(i).lexem
namespace PolishNotation
{

	// 1. Допустимые символы ( ) v i l = ; ,
	// 2. Соответствие скобок
	// 3. Отсутствие строкового литерала
	// 4. Отсутствие двойных знаков
	// 5. Отсутствие двойных опрандов 
	// 6.
	//
	//
	//
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
		// скобка была найдена?
		bool braceWasFounded = false;
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
			if (isOperand(entry.lexem) && 
				prev != LEX_LITERAL && prev != LEX_ID && 
				idTable.GetEntry(entry.idxTI).iddatatype != IT::STR)
				// добавить в стек операторов и скобок.
				expression.push_back(lextable_pos);
			// операция
			else if (isOperation(entry.lexem) && prev != LEX_SIGN)
			{
				// если стек пустой или пред. элем. '(', то добавляем лексему в стек операторов
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS);
				// если стек не пустой и пред. элем. операция
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					// перебор элементов с верхнего
					for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority(*i))
						{
							expression.push_back(*i);
							// удаление элементов стека
							i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else { break; }
				}
				else return false;
				stack.push_back(lextable_pos);
			}
			// левая скобка
			else if (entry.lexem == LEX_LEFTHESIS)
				stack.push_back(lextable_pos);
			// правая скобка скобка.
			else if (entry.lexem == LEX_RIGHTHESIS && !stack.empty() && prev != LEX_LEFTHESIS)
			{
				braceWasFounded = false;
				for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					// запись 
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						expression.push_back(*i);
						i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else { braceWasFounded = true; stack.erase(i.base() - 1); break; }
				if (!braceWasFounded) return false;
			}
			// конец выражения.
			else if (entry.lexem == LEX_COMMA || entry.lexem == LEX_SEMICOLON) break;
			// выражение.
			else return false;
			prev = entry.lexem;
		}
		// запись оставшихся операторов в выражение.
		for (std::vector<int>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
		{
			if (lextable.GetEntry(*i).lexem == LEX_LEFTHESIS) return false;
			expression.push_back(*i);
		}
		
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