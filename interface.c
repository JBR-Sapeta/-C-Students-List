#pragma once
#pragma warning (disable : 4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"
#include "windows.h"


static const char* menu_array[] =
{
	"0 - Zakoncz progrma.",							//INTERF_STOP
	"1 - Dodaj element do stosu.",					//INTERF_PUSH		
	"2 - Zdejmi element ze stosu.",					//INTERF_POP
	"3 - Szukaj elementu na stosie.",				//INTERF_FIND
	"4 - Wypisz elementy stosu.",					//INTERF_PRIT_STACK
	"5 - Wyczysc stos.",							//INTERF_CLEAR
	"6 - Wczytaj dane z pliku.",					//INTERF_READ_FILE
	"7 - Zapisz dane do pliku.",					//INTERF_WRITE_FILE
	"8 - Wyczysc ekran.",							//INTERF_CLS
};

char FileName[] = "MyFile.bin";

void menu()
{
	int i;
	printf("--------------------------------------------------\n");
	for (i = 0; i < INTERF_TOT; ++i)
	{
		printf("%s\n", menu_array[i]);
	}
	printf("--------------------------------------------------\n");
}

void push()
{
	char lastname[512];
	unsigned int year = 0;
	DEGREE_COURSE dgree;
	printf("Wprowdz nazwsiko studenta:\n");
	scanf("%s", &lastname);
	printf("Wprowdz rok urodzenia studenta:\n");
	scanf("%ud", &year);
	printf("Wprowdz kierunek studenta:\n");
	DEGREE_COURSE_Print();
	scanf("%de", &dgree);

	void* p_data = STUDENT_DATA_Push(lastname, year, dgree);
	if (!STACK_ELEMENT_Push(p_data, STUDENT_DATA_Free))
		printf("push error\n");
}

void pop()
{
	STACK_ELEMENT_Pop(STUDENT_DATA_Free, STUDENT_DATA_Print);
}

void find_element()
{
	int button;

	printf("Wprowadz numer polecenie:\n1.Szukaj studenta po nazwisku.\n2.Szukaj studenta po roku urodzenia.\n3.Szukaj studenta po kierunku.\n");
	scanf("%d", &button);
	switch (button)
	{
	case 1:
		find_lastname();
		break;

	case 2:
		find_year();
		break;
	case 3:
		find_dgree();
		break;

	default:
		ERROR_MESSAGES_Function(MESSAGE_UNKNOWN_COMAND, NULL, NULL, NULL);
		break;
	}
}

void find_lastname()
{
	char str[128];
	printf("Wprowadz nazwisko szukanego studenta :\n");
	scanf("%s", str, sizeof(str));
	printf("--------------------------------------------------\n");
	MY_STUDENT* serachDat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!serachDat)
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, STUDENT_DATA_Free);

	serachDat->lastname = (char*)malloc((strlen(str) + 1) * sizeof(char));
	strcpy(serachDat->lastname, str);

	int i = 0;
	void* pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchLastName, 1); 



	if (pDat)
	{
		printf("Odnaleziono szukany element na stosie: \n\n");
		STUDENT_DATA_Print(pDat);
		i++;
	}

	while (pDat)
	{
		pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchLastName, 0);
		if (pDat)
		{
			printf("Odnaleziono szukany element na stosie: \n\n");
			STUDENT_DATA_Print(pDat);
			i++;
		}
	}
	if (i == 0)
		printf("Nieodnaleziono szukanego elementu. \n");

	free(serachDat->lastname);
	free(serachDat);
}

void find_year()
{
	unsigned int year;
	printf("Wprowadz rok urodzenia szukanego studenta: \n");
	scanf("%d", &year);
	printf("--------------------------------------------------\n");
	MY_STUDENT* serachDat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!serachDat)
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, STUDENT_DATA_Free);

	serachDat->year = year;
	serachDat->lastname = NULL;
	int i = 0;
	void* pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchYear, 1); 

	if (pDat)
	{
		printf("Odnaleziono szukany element na stosie: \n\n");
		STUDENT_DATA_Print(pDat);
		i++;
	}

	while (pDat)
	{
		pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchYear, 0);
		if (pDat)
		{
			printf("Odnaleziono szukany element na stosie:: \n\n");
			STUDENT_DATA_Print(pDat);
			i++;
		}

	}
	if (i == 0)
		printf("Nieodnaleziono szukanego elementu. \n");
	free(serachDat);
}

void find_dgree()
{
	DEGREE_COURSE dgree;
	printf("Wprowadz kierunek szukanego studenta: \n");
	DEGREE_COURSE_Print();
	scanf("%de", &dgree);
	printf("--------------------------------------------------\n");
	MY_STUDENT* serachDat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!serachDat)
		ERROR_MESSAGES_Function(MESSAGE_MEMORY_ALOCATION_ERROR, NULL, NULL, STUDENT_DATA_Free);

	serachDat->dgree = dgree;
	serachDat->lastname = NULL;

	int i = 0;
	void* pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchDegree, 1); 

	if (pDat)
	{
		printf("Odnaleziono szukany element na stosie: \n\n");
		STUDENT_DATA_Print(pDat);
		i++;
	}

	while (pDat)
	{
		pDat = STACK_ELEMENT_Search(serachDat, STUDENT_DATA_SerchDegree, 0);
		if (pDat)
		{
			printf("Odnaleziono szukany element na stosie:: \n\n");
			STUDENT_DATA_Print(pDat);
			i++;
		}
	}
	if (i == 0)
		printf("Nieodnaleziono szukanego elementu. \n");

	free(serachDat);
}

void clear()
{
	STACK_ELEMENT_Free(STUDENT_DATA_Free);
}



void print_stack()
{
	printf("--------------------------------------------------\n");
	STACK_ELEMENT_Print(STUDENT_DATA_Print);
}

void read_file_all()
{
	int button;

	printf("--------------------------------------------------\n");
	printf("Wprowadz numer polecenie:\n1.Wyczysc stos przed wczytaniem pliku.\n2.Wczytaj dane z pliku na koniec stosu.\n");
	scanf("%d", &button);

	switch (button)
	{
	case 1:
		STACK_ELEMENT_Free(STUDENT_DATA_Free);
		STACK_ELEMENT_Read(FileName, STUDENT_DATA_Read, STUDENT_DATA_Free);
		break;

	case 2:
		STACK_ELEMENT_Read(FileName, STUDENT_DATA_Read, STUDENT_DATA_Free);
		break;

	default:
		ERROR_MESSAGES_Function(MESSAGE_UNKNOWN_COMAND, NULL, NULL, NULL);
		break;
	}

}





void write_file_all()
{
	ERROR_MESSAGES_Function(MESSAGE_FILE_OVERWRITE_WARNING, NULL, NULL, STUDENT_DATA_Free);

	int button;

	printf("--------------------------------------------------\n");
	printf("Czy na pewno chcesz zapisac plik ?\n1.TAK.\n2.NIE.\n");
	scanf("%d", &button);

	switch (button)
	{
	case 1:
		STACK_ELEMENT_Save(FileName, STUDENT_DATA_Save, STUDENT_DATA_Free);
		break;


	case 2:
		break;

	default:
		ERROR_MESSAGES_Function(MESSAGE_UNKNOWN_COMAND, NULL, NULL, NULL);
		break;
	}

}

void cls()
{
	system("cls");

}