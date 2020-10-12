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
		LT::Entry entry;
		// скобка была найдена?
		bool braceWasFounded = false;
		// TO DO
		// ожидаются лексемы принадлеж. функции
		bool isFunction = false;
		// позиция первой лексемы выражения в ТЛ.
		int startInLT = lextable_pos;
		// предыдущий символ выражения.
		char prev = '@';
		// 
		for (lextable_pos; lextable_pos < lextable.currentSize; lextable_pos++)
		{
			// получение записи из ТЛ.
			entry = lextable.GetEntry(lextable_pos);

			std::cout << "СТЕК: ";
			for (int i = 0; i < stack.size(); i++)
				std::cout << lextable.GetEntry(stack[i]).lexem;
			std::cout << std::endl;
			std::cout << "ВЫРАЖЕНИЕ: ";
			for (int i = 0; i < expression.size(); i++)
				std::cout << lextable.GetEntry(expression[i]).lexem;
			std::cout << std::endl;
			std::cout << std::endl;
			// операнд
			if (isOperand(entry.lexem) && prev != LEX_LITERAL && prev != LEX_ID)
			{
				if (entry.idxTI != LT_TI_NULLXDX && idTable.GetEntry(entry.idxTI).idtype == IT::F)
				{			
					stack.push_back(lextable_pos);
				}
				else
				{
					// добавить в стек операторов и скобок.
					expression.push_back(lextable_pos);
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
				if (!stack.empty() && lextable.GetEntry(stack.back()).lexem == LEX_ID)
				{
					expression.push_back(stack.back());
					stack.pop_back();
				}
			}
			else if (entry.lexem == LEX_COMMA && prev == LEX_ID || prev == LEX_LITERAL) prev = LEX_COMMA;
			// конец выражения.
			else if (entry.lexem == LEX_SEMICOLON) break;
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
		std::cout << "СТЕК: ";
		for (int i = 0; i < stack.size(); i++)
			std::cout << lextable.GetEntry(stack[i]).lexem;
		std::cout << std::endl;
		std::cout << "ВЫРАЖЕНИЕ: ";
		for (int i = 0; i < expression.size(); i++)
			std::cout << lextable.GetEntry(expression[i]).lexem;
		std::cout << std::endl;
		std::cout << std::endl;
		// установка позиций в ТЛ и ТИ исходя из польской записи.
#pragma region SortElems
		for (int i = 0; i < expression.size(); i++)
		{
			entry = lextable.GetEntry(expression[i]);
			// !!!!!!!!!если это первое вхождение ид УДАЛИТЬ УДАЛИТЬ
			if (expression[i] == idTable.GetEntry(entry.idxTI).idxfirstLE)
			{
				idTable.GetEntry(entry.idxTI).idxfirstLE == startInLT;
			}
			lextable.table[expression[i]] = lextable.GetEntry(startInLT);
			lextable.table[startInLT++] = entry;
		}
		for (startInLT; startInLT < lextable_pos; startInLT++)
		{
			lextable.table[startInLT] = { '@', -1, -1 };
		}
#pragma endregion
		return true;
	}
}