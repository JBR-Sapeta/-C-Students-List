#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "messages.h"
#include "stack.h"


static STACK_ELEMENT* top = NULL;
static FreeData ptr_f_FreeData;
static CompareData ptr_f_CompData;
static PrintData ptr_f_PrintData;
static ReadData ptr_f_ReadData;
static SaveData ptr_f_SaveData;

#pragma warning (disable : 4996)

void STACK_ELEMENT_Init()
{
	top = NULL;
	ptr_f_FreeData = NULL;
	ptr_f_PrintData = NULL;
	ptr_f_CompData = NULL;
	ptr_f_ReadData = NULL;
	ptr_f_SaveData = NULL;
}

void STACK_ELEMENT_Free(FreeData ptr_FreeData)
{
	ptr_f_FreeData = ptr_FreeData;

	if (top == NULL)
	{
		ERROR_MESSAGES_Function(MESSAGE_EMPTY_STACK_WARNING, NULL, NULL, NULL);
	}
	else
	{
		STACK_ELEMENT* ptr_top = top;
		STACK_ELEMENT* ptr_temp = NULL;
		if (ptr_top)
		{

			while (ptr_top->previous != NULL)    //Zwlanimay od ko�ca poszczegolne elementy stosu az dotrzemy do ostatniego
			{
				(*ptr_f_FreeData)(ptr_top->ptr_data);
				ptr_top->ptr_data = NULL;


				top = ptr_top->previous;
				free(ptr_top);	//zwalniamy pamiec
				ptr_top = top;

			}
			(*ptr_f_FreeData)(ptr_top->ptr_data);
			top = NULL;
		}
		if (top == NULL)
			printf("Stos zostal zwolniony poprawnie !\n");
	}


}
STACK_ELEMENT* STACK_ELEMENT_Push(void* ptr, FreeData ptr_FreeData)
{

	ptr_f_FreeData = ptr_FreeData;
	STACK_ELEMENT* new_stack_el = (STACK_ELEMENT*)malloc(sizeof(STACK_ELEMENT));
	if (!new_stack_el)
	{
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, ptr_FreeData);
	}
	if (!top)
	{
		top = new_stack_el;
		new_stack_el->previous = NULL;
		new_stack_el->ptr_data = ptr;
	}
	else
	{
		new_stack_el->previous = top;
		new_stack_el->ptr_data = ptr;
	}

	top = new_stack_el;


	return new_stack_el;
}


void STACK_ELEMENT_Pop(FreeData ptr_FreeData, PrintData ptr_PrintData)
{
	ptr_f_FreeData = ptr_FreeData;
	ptr_f_PrintData = ptr_PrintData;

	if (top) // Sprawdzamy czy na stosie jest jakis element
	{

		STACK_ELEMENT* ptr_top = top;
		if (top->previous == NULL)			// Sprawdzamy czy na stosie nie ma tylko 1 elementu
		{
			printf("Zwolniono ostatni element Stosu:\n");
			printf("--------------------------------------------------\n");
			(*ptr_f_PrintData)(ptr_top->ptr_data);				// drukujemy zawartosc ostatniego elementu stosu
			(*ptr_f_FreeData)(ptr_top->ptr_data);				// zwalniamy zawartosc ostatniego elementu stosu											
			ptr_top->ptr_data = NULL;

			free(ptr_top);									// zwalniamy ostatni elemen stosu 
			top = NULL;											// ustawiamy top na NULL
		}
		else
		{
			printf("Zwolniono ostatni element Stosu:\n");
			printf("--------------------------------------------------\n");
			(*ptr_f_PrintData)(ptr_top->ptr_data);				// drukujemy zawartosc ostatniego elementu stosu
			(*ptr_f_FreeData)(ptr_top->ptr_data);				// zwalniamy zawartosc ostatniego elementu stosu

			top = ptr_top->previous;							// Zmieniamy wska�nik na nowy koniec stosu
			free(ptr_top);										// zwalniamy ostatni elemen stosu
		}
	}
	else
	{
		ERROR_MESSAGES_Function(MESSAGE_EMPTY_STACK_WARNING, NULL, NULL, NULL);
	}
}

void STACK_ELEMENT_Print(PrintData ptr_PrintData)
{
	ptr_f_PrintData = ptr_PrintData;

	if (top == NULL)    // Sprawdzamy czy na stosie jest jakis element
	{
		ERROR_MESSAGES_Function(MESSAGE_EMPTY_STACK_WARNING, NULL, NULL, NULL);
	}
	else
	{
		STACK_ELEMENT* ptr_top = top;
		STACK_ELEMENT* ptr_tmp = top;

		if (ptr_top->previous == NULL) // Jezeli jest tylko 1 wyswietlamy go
		{
			printf("1 element stosu:\n\n");
			(*ptr_f_PrintData)(ptr_top->ptr_data);
		}
		else
		{

			unsigned int i = STACK_ELEMENT_Number(ptr_tmp);
			ptr_tmp = NULL;
			while (ptr_top)  // Gdy jest ich wiecej drukujemy kolejno elementy stosu od pierwszego
			{

				printf("%d element stosu :\n\n", i);
				(*ptr_f_PrintData)(ptr_top->ptr_data);
				ptr_tmp = ptr_top->previous;
				ptr_top = ptr_tmp;
				i--;

			}
		}

	}

}
void* STACK_ELEMENT_Search(void* ptr_SearchData, CompareData ptr_CompData, int FirstEntry)
{
	static STACK_ELEMENT* ptr;
	STACK_ELEMENT* ptr_tmp;
	ptr_f_CompData = ptr_CompData;

	if (FirstEntry)
	{
		ptr = top;
	}

	while (ptr)
	{

		if (!(*ptr_f_CompData)(ptr->ptr_data, ptr_SearchData))
		{
			ptr = ptr->previous;
		}
		else
		{
			ptr_tmp = ptr;
			ptr = ptr->previous;
			return ptr_tmp->ptr_data;
		}
	}
	return NULL;

}

unsigned int STACK_ELEMENT_Number(STACK_ELEMENT* top)
{

	if (top == NULL)
		return 0;

	else
		return 1 + STACK_ELEMENT_Number(top->previous);

}


void STACK_ELEMENT_Save(char* filename, SaveData ptr_SaveData, FreeData ptr_FreeData)
{
	ptr_f_SaveData = ptr_SaveData;
	ptr_f_FreeData = ptr_FreeData;

	if (top)
	{
		STACK_ELEMENT* ptr_top = top;

		size_t it;
		size_t	num_items = (size_t)STACK_ELEMENT_Number(ptr_top);

		unsigned int no_it = (unsigned int)num_items;

		__int64 filepos = 0;
		__int64* file_desc = (__int64*)malloc((num_items + 1) * sizeof(__int64));

		if (!file_desc)
			ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, file_desc, ptr_FreeData);

		FILE* ptr_file = fopen(filename, "wb");

		if (!ptr_file)
			ERROR_MESSAGES_Function(MESSAGE_FILE_OPEN_ERROR, ptr_file, file_desc, ptr_FreeData);

		if (fwrite(&no_it, sizeof(unsigned int), 1, ptr_file) != 1)
			ERROR_MESSAGES_Function(MESSAGE_FILE_WRITE_ERROR, ptr_file, file_desc, ptr_FreeData);


		_fseeki64(ptr_file, (num_items + 1) * sizeof(__int64), SEEK_CUR);  

		ptr_top = top;

		for (it = 0; it < num_items; ++it)
		{
			file_desc[it] = ftell(ptr_file);
			(*ptr_f_SaveData)(ptr_file, file_desc, ptr_top->ptr_data);
			ptr_top = ptr_top->previous;
		}

		file_desc[it] = ftell(ptr_file);   

		_fseeki64(ptr_file, sizeof(unsigned int), SEEK_SET); 	    
		if (fwrite(file_desc, sizeof(__int64), num_items + 1, ptr_file) != num_items + 1)
			ERROR_MESSAGES_Function(MESSAGE_FILE_WRITE_ERROR, ptr_file, file_desc, ptr_FreeData);

		if (ptr_file)
			fclose(ptr_file);
		ptr_file = NULL;

		if (file_desc)
			free(file_desc);
		file_desc = NULL;
		printf("\nElementy stosu zostaly zapisane w pliku!\n");
	}
	else
		ERROR_MESSAGES_Function(MESSAGE_EMPTY_STACK_WARNING, NULL, NULL, NULL);
}

void STACK_ELEMENT_Read(char* filename, ReadData ptr_ReadData, FreeData ptr_FreeData)
{
	ptr_f_ReadData = ptr_ReadData;
	ptr_f_FreeData = ptr_FreeData;

	unsigned int no_items = 0, it, rec;
	__int64* file_desc = NULL;

	FILE* ptr_file = fopen(filename, "rb");
	if (!ptr_file)
		ERROR_MESSAGES_Function(MESSAGE_FILE_OPEN_ERROR, ptr_file, file_desc, ptr_FreeData);

	if (fread(&no_items, sizeof(unsigned int), 1, ptr_file) != 1)
		ERROR_MESSAGES_Function(MESSAGE_FILE_READ_ERROR, ptr_file, file_desc, ptr_FreeData);

	file_desc = (__int64*)malloc((no_items + 1) * sizeof(__int64));

	if (!file_desc)
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, ptr_file, file_desc, ptr_FreeData);

	if (fread(file_desc, sizeof(file_desc[0]), no_items + 1, ptr_file) != no_items + 1)
		ERROR_MESSAGES_Function(MESSAGE_FILE_READ_ERROR, ptr_file, file_desc, ptr_FreeData);

	void* ptr_data = NULL;

	for (it = 0; it < no_items; ++it)
	{
		rec = no_items - it - 1;

		_fseeki64(ptr_file, file_desc[rec], SEEK_SET);
		ptr_data = (*ptr_f_ReadData)(ptr_file, file_desc);
		STACK_ELEMENT_Push(ptr_data, ptr_FreeData);
	}

	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	if (ptr_file)
		fclose(ptr_file);
	ptr_file = NULL;


	printf("\nElementy pliku zostaly wczytane na stos!\n");
}