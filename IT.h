#pragma once

#define ID_MAXSIZE		6				// ���������� ����� ��������������
#define TI_MAXSIZE		4096			// ������������ ���������� ����� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	""			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		0xffffffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255

#define ID_SUBSTR "$s1"
#define ID_STRLEN "$s2"

#define PARM_ID_DEFAULT_EXT L".id.txt" // ���������� ����� � ������� ������������ ������a

namespace IT	// ������� �������������
{
	enum IDDATATYPE { INT = 1, STR = 2 };		// ���� ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };	// ���� ���������������: ����������, �������, ��������, �������

	// ������ ������� ���������������
	struct Entry
	{
		int idxfirstLE;					// ������ ������ ������ � ������� ������
		int parentId;					// ������ ������������� �����
		char id[ID_MAXSIZE];			// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype;			// ��� ������
		IDTYPE idtype;					// ��� ������������
		union
		{
			int vint;					// �������� integer
			struct
			{
				char len;						// ��������� �������� � string
				char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr[TI_STR_MAXSIZE];				// �������� string
		} value;	// �������� ��������������
		Entry();
		Entry(int first, char* i, IDDATATYPE datatype, IDTYPE type, int parentId = TI_NULLIDX);
	};

	// ��������� ������� ���������������
	struct IdTable
	{
		int maxsize;				// ������������ ������ �������
		int currentSize;			// ������� ������ �������
		Entry* table;				// ������ ����� �������	
		//IdTable(int size = TI_MAXSIZE);
		IdTable(int size = TI_MAXSIZE);
		void Add(Entry entry);
		Entry GetEntry(int n);
		int IsId(char* id);
		void Delete();
	};
}