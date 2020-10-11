#include "PolishNotation.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#define BACK_LEXEM lextable.GetEntry(stack.back()).lexem
#define GET_LEXEM(i) lextable.GetEntry(i).lexem
namespace PolishNotation
{

	// 1. ���������� ������� ( ) v i l = ; ,
	// 2. ������������ ������
	// 3. ���������� ���������� ��������
	// 4. ���������� ������� ������
	// 5. ���������� ������� �������� 
	// 6.
	//
	//
	//
	// �������� ��������� ��������.
	int getPriority(char sign)
	{
		if (sign == '(' || sign == ')') return 1;
		else if (sign == '+' || sign == '-') return 2;
		else if (sign == '*' || sign == '/') return 3;
		else return 0;
	}
	// ��� �������������� ��������?
	bool isOperation(char symbol) { return symbol == LEX_SIGN; }
	// ��� ������� ������?
	bool isBrace(char symbol) { return symbol == LEX_LEFTHESIS || symbol == LEX_RIGHTHESIS; }
	// ��� ������������� ��� �������?
	bool isOperand(char symbol) { return symbol == LEX_ID || symbol == LEX_LITERAL; }

	bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable)
	{
		// ���������.
		std::vector<int> expression;
		// ���� ���������� � ������.
		std::vector<int> stack;
		LT::Entry entry, bufferEntry;
		// ������ ���� �������?
		bool braceWasFounded = false;
		// ������� ������ ������� ��������� � ��.
		int startInLT = lextable_pos;
		// ���������� ������ ���������.
		char prev = '@';
		// 
		for (lextable_pos; lextable_pos < lextable.currentSize; lextable_pos++)
		{
			// ��������� ������ �� ��.
			entry = lextable.GetEntry(lextable_pos);
			// �������
			if (isOperand(entry.lexem) && 
				prev != LEX_LITERAL && prev != LEX_ID && 
				idTable.GetEntry(entry.idxTI).iddatatype != IT::STR)
				// �������� � ���� ���������� � ������.
				expression.push_back(lextable_pos);
			// ��������
			else if (isOperation(entry.lexem) && prev != LEX_SIGN)
			{
				// ���� ���� ������ ��� ����. ����. '(', �� ��������� ������� � ���� ����������
				if (stack.empty() || BACK_LEXEM == LEX_LEFTHESIS);
				// ���� ���� �� ������ � ����. ����. ��������
				else if (!stack.empty() && isOperation(BACK_LEXEM))
				{
					// ������� ��������� � ��������
					for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						if ((isOperation(GET_LEXEM(*i)) || isBrace(GET_LEXEM(*i))) && getPriority(entry.lexem) <= getPriority(*i))
						{
							expression.push_back(*i);
							// �������� ��������� �����
							i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else { break; }
				}
				else return false;
				stack.push_back(lextable_pos);
			}
			// ����� ������
			else if (entry.lexem == LEX_LEFTHESIS)
				stack.push_back(lextable_pos);
			// ������ ������ ������.
			else if (entry.lexem == LEX_RIGHTHESIS && !stack.empty() && prev != LEX_LEFTHESIS)
			{
				braceWasFounded = false;
				for (std::vector<int>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					// ������ 
					if (GET_LEXEM(*i) != LEX_LEFTHESIS)
					{
						expression.push_back(*i);
						i = std::vector<int>::reverse_iterator(stack.erase(i.base() - 1));
					}
					else { braceWasFounded = true; stack.erase(i.base() - 1); break; }
				if (!braceWasFounded) return false;
			}
			// ����� ���������.
			else if (entry.lexem == LEX_COMMA || entry.lexem == LEX_SEMICOLON) break;
			// ���������.
			else return false;
			prev = entry.lexem;
		}
		// ������ ���������� ���������� � ���������.
		for (std::vector<int>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
		{
			if (lextable.GetEntry(*i).lexem == LEX_LEFTHESIS) return false;
			expression.push_back(*i);
		}
		
		// ��������� ������� � �� � �� ������ �� �������� ������.
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