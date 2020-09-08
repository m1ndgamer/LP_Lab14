//#pragma once
//
//#define ID_MAXSIZE		5				// допустима€ длина идентификатора
//#define TI_MAXSIZE		4096			// максимальное количество строк в таблице идентификаторов 
//#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
//#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string 
//#define TI_NULLIDX		0xffffffff		// нет элемента таблицы идентификаторов
//#define TI_STR_MAXSIZE	255
//
//#define PARM_ID_DEFAULT_EXT L".id.txt" // расширение файла с итогами лексического анализa
//
//namespace IT	// таблица идентификатов
//{
//	enum IDDATATYPE {INT = 1, STR = 2 };		// типы идентификаторов: integer, string
//	enum IDTYPE {V = 1, F = 2, P = 3, L = 3};	// типы идентификаторов: переменна€, функци€, параметр, лексема
//
//	// строка таблицы идентификаторов
//	struct Entry
//	{
//		int idxfirstLE;					// индекс первой записи в таблице
//		//char parrentFunc[ID_MAXSIZE];
//		char id[ID_MAXSIZE];			// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
//		IDDATATYPE	iddatatype;			// тип данных
//		IDTYPE	idtype;					// тип идентикатора
//		union VALUE
//		{
//			int vint;					// значение integer
//			struct
//			{
//				unsigned char len;				// количесво символов в string
//				char str[TI_STR_MAXSIZE - 1]; // символы string
//			} vstr;	// значение string
//		} value;	// значение идентификатора
//
//		// создать строку таблицы
//		Entry();
//		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
//	};
//
//	// экземпл€р таблицы идентификаторов
//	struct IdTable 
//	{
//		int maxsize;				// максимальный размер таблицы
//		int current_size;			// текущий размер таблицы
//		Entry* table;				// массив строк таблицы
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