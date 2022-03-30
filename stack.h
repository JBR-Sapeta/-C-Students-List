#pragma once

struct STACK_ELEMENT
{
	void* ptr_data;    //wskaznik do danych typu void *
	STACK_ELEMENT* previous; //wskaznik do nastepnego elementu stosu	

};

typedef void (*FreeData)(void* ptr_data);
typedef void (*PrintData)(void* ptr_data);
typedef int (*CompareData)(void* ptr_CurData, void* ptr_SearchData);
typedef void* (*ReadData)(FILE* ptr_file, __int64* file_desc);
typedef void (*SaveData)(FILE* ptr_file, __int64* file_desc, void* ptr_data);

void STACK_ELEMENT_Init();
void STACK_ELEMENT_Free(FreeData ptr_f_FreeData);
void STACK_ELEMENT_Print(PrintData ptr_f_PrintData);

STACK_ELEMENT* STACK_ELEMENT_Push(void* ptr_data, FreeData ptr_f_FreeData);
void  STACK_ELEMENT_Pop(FreeData ptr_f_FreeData, PrintData ptr_f_PrintData);

void* STACK_ELEMENT_Search(void* ptr_SearchData, CompareData ptr_f_CompData, int FirstEntry);

void STACK_ELEMENT_Save(char* filename, SaveData ptr_SaveData, FreeData ptr_f_FreeData);
void STACK_ELEMENT_Read(char* filename, ReadData ptr_SaveData, FreeData ptr_f_FreeData);

unsigned int STACK_ELEMENT_Number(STACK_ELEMENT* top);


