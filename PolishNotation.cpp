#include "PolishNotation.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#define BACK_LEXEM stack.back().lexem
#define GET_LEXEM(i) (i).lexem
namespace PolishNotation
{
	// 1. Допустимые символы ( ) v i l = ; ,
	// 2. Соответствие скобок
	// 3. Отсутствие строкового литерала
	// 4. Отсутствие двойных знаков
	// 5. Отсутствие двойных опрандов 
	// 6.
	// СВАПНУТЬ ЗАПИСИ ...
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

	bool convertExpressions(LT::LexTable& lextable, IT::IdTable& idTable)
	{
		for (int entryInLT = 0; entryInLT < lextable.currentSize; entryInLT++)
		{
			if (lextable.GetEntry(entryInLT).lexem == LEX_EQUAL_SIGN && !polishNotation(++entryInLT, lextable, idTable))
			{
				std::cout << lextable.GetEntry(entryInLT).lexem;
				return false;
			}
				
		}
		return true;
	}

	bool polishNotation(int& lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable)
	{
		if (lextable_pos >= lextable.currentSize) return false;
		// выражение.
		std::vector<LT::Entry> expression;
		// стек операторов и скобок.
		std::vector<LT::Entry> stack;
		LT::Entry entry;
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
			if (isOperand(entry.lexem) && prev != LEX_LITERAL && prev != LEX_ID)
			{
				if (entry.idxTI != LT_TI_NULLXDX && idTable.GetEntry(entry.idxTI).idtype == IT::F)
				{			
					stack.push_back(entry);
				}
				else
				{
					// добавить в стек операторов и скобок.
					expression.push_back(entry);
				}
			}				
			// операция
			else if (isOperation(entry.lexem) && prev != LEX_SIGN)
			{
				// если стек пустой или пред. элем. '(', то добавляем лексему в стек операторов
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS);
				// если стек не пустой и пред. элем. операция
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					// перебор элементов с верхнего
					for (std::vector<LT::Entry>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority((*i).lexem))
						{
							expression.push_back(*i);
							// удаление элементов стека
							i = std::vector<LT::Entry>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else { break; }
				}
				else return false;
				stack.push_back(entry);
			}
			// левая скобка
			else if (entry.lexem == LEX_LEFTHESIS)
				stack.push_back(entry);
			// правая скобка скобка.
			else if (entry.lexem == LEX_RIGHTHESIS && !stack.empty() && prev != LEX_LEFTHESIS)
			{
				braceWasFounded = false;
				for (std::vector<LT::Entry>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					// запись 
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						expression.push_back(*i);
						i = std::vector<LT::Entry>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else { braceWasFounded = true; stack.erase(i.base() - 1); break; }
				if (!braceWasFounded) return false;
				if (!stack.empty() && stack.back().lexem == LEX_ID)
				{
					expression.push_back(stack.back());
					stack.pop_back();
				}
			}
			else if (entry.lexem == LEX_COMMA && (prev == LEX_ID || prev == LEX_LITERAL)) prev = LEX_COMMA;
			// конец выражения.
			else if (entry.lexem == LEX_SEMICOLON) break;
			// выражение.
			else return false;
			prev = entry.lexem;
		}
		// запись оставшихся операторов в выражение.
		for (std::vector<LT::Entry>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
		{
			if ((*i).lexem == LEX_LEFTHESIS) return false;
			expression.push_back(*i);
		}
#pragma region SortElems
		int currentPos = startInLT;
		for (int i = 0; i < expression.size(); i++)
		{
			int id = expression[i].idxTI;
			if (idTable.GetEntry(id).idxfirstLE >= startInLT && idTable.GetEntry(id).idxfirstLE < lextable_pos)
			{
				idTable.table[expression[i].idxTI].idxfirstLE = currentPos;
			}
			lextable.table[currentPos++] = expression[i];
		}
		for (currentPos; currentPos < lextable_pos; currentPos++)
		{
			lextable.table[currentPos] = { '@', -1, -1 };
		}
#pragma endregion
		return true;
	}
}