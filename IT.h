#pragma once

#define ID_MAXSIZE		64				// допустима€ длина идентификатора
#define TI_MAXSIZE		4096			// максимальное количество строк в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string 
#define TI_NULLIDX		0xffffffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" // расширение файла с итогами лексического анализa

namespace IT	// таблица идентификатов
{
	enum IDDATATYPE { INT = 1, STR = 2 };		// типы идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 3 };	// типы идентификаторов: переменна€, функци€, параметр, лексема

	// строка таблицы идентификаторов
	struct Entry
	{
		int idxfirstLE;					// индекс первой записи в таблице
		char* id;			// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;			// тип данных
		IDTYPE idtype;					// тип идентикатора
		union
		{
			int vint;					// значение integer
			struct
			{
				char len;						// количесво символов в string
				char str[TI_STR_MAXSIZE - 1];	// символы string
			} vstr[TI_STR_MAXSIZE];				// значение string
		} value;	// значение идентификатора
		Entry();
		Entry(int first, char* i, IDDATATYPE datatype, IDTYPE type);
	};

	// экземпл€р таблицы идентификаторов
	struct IdTable
	{
		int maxsize;				// максимальный размер таблицы
		int currentSize;			// текущий размер таблицы
		Entry* table;				// массив строк таблицы
	
		IdTable(int size = TI_MAXSIZE);
		void Add(Entry entry);
		Entry GetEntry(int n);
		int IsId(char* id);
		void Delete();
	};
}