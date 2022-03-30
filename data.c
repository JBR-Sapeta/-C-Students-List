#pragma once
#pragma warning (disable : 4996)


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "messages.h"


static const char* degree_array[] =
{
	"0 - Fizyka. ",			//DEG_PHYSICS
	"1 - Matematyka.",		//DEG_MATHEMATICS			
	"2 - Informatyka. ",	//DEG_COMPUTING	
	"3 - Logistyka. ",		//DEG_LOGISTIC			
	"4 - Architektura. "	//DEG_ARCHITECTURE,									
};

void* STUDENT_DATA_Init(char* new_lastname, unsigned int new_year, enum DEGREE_COURSE new_dgree)
{
	MY_STUDENT* p_data = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	unsigned int string_lenght = (unsigned int)(strlen(new_lastname) + 1);

	if (p_data)
	{
		p_data->lastname = (char*)malloc(string_lenght * sizeof(char));
		if (!p_data->lastname)
		{
			free(p_data);
			ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, STUDENT_DATA_Free);
			return NULL;
		}

		strcpy(p_data->lastname, new_lastname);
		p_data->year = new_year;
		p_data->dgree = new_dgree;
		p_data->s_lenght = string_lenght;
	}
	else
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, STUDENT_DATA_Free);

	return (void*)(p_data);

}
void STUDENT_DATA_Free(void* ptr)
{
	MY_STUDENT* p_data = (MY_STUDENT*)ptr;

	if (p_data)
	{
		if (p_data->lastname)
			free(p_data->lastname);
		p_data->lastname = NULL;

		free(p_data);
	}

}

void* STUDENT_DATA_Push(char* new_lastname, unsigned int new_year, enum DEGREE_COURSE new_dgree)
{
	return STUDENT_DATA_Init(new_lastname, new_year, new_dgree);
}


void STUDENT_DATA_Print(void* ptr)
{
	MY_STUDENT* p_data = (MY_STUDENT*)ptr;
	if (p_data)
	{

		printf("Nazwisko studenta: %s \n", p_data->lastname);
		printf("Rok urodzenia: %d \n", p_data->year);
		printf("Kierunek: %s  \n", degree_array[p_data->dgree]);
		printf("--------------------------------------------------\n");
	}

}
int  STUDENT_DATA_SerchLastName(void* ptr_CurData, void* ptr_SearchData)
{
	MY_STUDENT* p_current_data = (MY_STUDENT*)ptr_CurData;
	MY_STUDENT* p_search_data = (MY_STUDENT*)ptr_SearchData;

	if (strcmp(p_current_data->lastname, p_search_data->lastname) == 0)
		return 1;

	return 0;
}

int  STUDENT_DATA_SerchYear(void* ptr_CurData, void* ptr_SearchData)
{
	MY_STUDENT* p_current_data = (MY_STUDENT*)ptr_CurData;
	MY_STUDENT* p_search_data = (MY_STUDENT*)ptr_SearchData;

	if (p_current_data->year == p_search_data->year)
		return 1;

	return 0;
}

int  STUDENT_DATA_SerchDegree(void* ptr_CurData, void* ptr_SearchData)
{
	MY_STUDENT* p_current_data = (MY_STUDENT*)ptr_CurData;
	MY_STUDENT* p_search_data = (MY_STUDENT*)ptr_SearchData;

	if ((p_current_data->dgree) == (p_search_data->dgree))
		return 1;

	return 0;
}



void STUDENT_DATA_Save(FILE* ptr_file, __int64* file_desc, void* ptr_data)
{
	MY_STUDENT* p_data = (MY_STUDENT*)ptr_data;

	if (p_data)
	{

		if (fwrite(p_data, sizeof(MY_STUDENT), 1, ptr_file) != 1)
			ERROR_MESSAGES_Function(MESSAGE_FILE_WRITE_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);

		if (fwrite(p_data->lastname, _msize(p_data->lastname), (size_t)(p_data->s_lenght), ptr_file) != (size_t)(p_data->s_lenght))
			ERROR_MESSAGES_Function(MESSAGE_FILE_WRITE_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);


	}
	else
		ERROR_MESSAGES_Function(MESSAGE_FILE_WRITE_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);

}


void* STUDENT_DATA_Read(FILE* ptr_file, __int64* file_desc)
{
	MY_STUDENT* p_data = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (p_data)
		p_data->lastname = NULL;
	else
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);


	if (p_data)
	{
		size_t check;
		check = fread(p_data, sizeof(struct MY_STUDENT), 1, ptr_file);
		if (check != 1)
			ERROR_MESSAGES_Function(MESSAGE_FILE_READ_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);


		p_data->lastname = (char*)malloc(p_data->s_lenght * sizeof(char));
		if (!p_data->lastname)
			ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);


		check = fread(p_data->lastname, sizeof(char), p_data->s_lenght, ptr_file);
		if (check = !p_data->s_lenght)
			ERROR_MESSAGES_Function(MESSAGE_FILE_READ_ERROR, ptr_file, file_desc, STUDENT_DATA_Free);


		return (void*)p_data;
	}
	else
		return NULL;
}


void DEGREE_COURSE_Print()
{
	printf("Podaj odpowiedni numer kierunku.\n");
	int i;
	for (i = 0; i < DEG_TOT; ++i)
	{
		printf("%s\n", degree_array[i]);
	}

}