//#pragma once
//
//#define ID_MAXSIZE		5				// ���������� ����� ��������������
//#define TI_MAXSIZE		4096			// ������������ ���������� ����� � ������� ��������������� 
//#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
//#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string 
//#define TI_NULLIDX		0xffffffff		// ��� �������� ������� ���������������
//#define TI_STR_MAXSIZE	255
//
//#define PARM_ID_DEFAULT_EXT L".id.txt" // ���������� ����� � ������� ������������ ������a
//
//namespace IT	// ������� �������������
//{
//	enum IDDATATYPE {INT = 1, STR = 2 };		// ���� ���������������: integer, string
//	enum IDTYPE {V = 1, F = 2, P = 3, L = 3};	// ���� ���������������: ����������, �������, ��������, �������
//
//	// ������ ������� ���������������
//	struct Entry
//	{
//		int idxfirstLE;					// ������ ������ ������ � �������
//		//char parrentFunc[ID_MAXSIZE];
//		char id[ID_MAXSIZE];			// ������������� (������������� ��������� �� ID_MAXSIZE)
//		IDDATATYPE	iddatatype;			// ��� ������
//		IDTYPE	idtype;					// ��� ������������
//		union VALUE
//		{
//			int vint;					// �������� integer
//			struct
//			{
//				unsigned char len;				// ��������� �������� � string
//				char str[TI_STR_MAXSIZE - 1]; // ������� string
//			} vstr;	// �������� string
//		} value;	// �������� ��������������
//
//		// ������� ������ �������
//		Entry();
//		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
//	};
//
//	// ��������� ������� ���������������
//	struct IdTable 
//	{
//		int maxsize;				// ������������ ������ �������
//		int current_size;			// ������� ������ �������
//		Entry* table;				// ������ ����� �������
//	
//		IdTable();
//		void Add(Entry entry);
//		Entry GetEntry(int n);
//		int IsId(const char id[ID_MAXSIZE]);
//		int IsId(const char id[ID_MAXSIZE], const char parentFunc[ID_MAXSIZE]);
//		void PrintIdTable(const wchar_t* in);
//		void Delete();
//	};
//}