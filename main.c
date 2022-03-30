// Projekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "stack.h"
#include "messages.h"

#pragma warning (disable : 4996)

int main(int argc, char* argv[])
{

	STACK_ELEMENT_Init();
	int button = 1;

	while (button != INTERF_STOP)
	{
		menu();
		scanf("%d", &button);

		switch (button)
		{
		case INTERF_PUSH:push();
			break;
		case INTERF_POP:pop();
			break;

		case INTERF_FIND:find_element();
			break;

		case INTERF_PRIT_STACK:print_stack();
			break;

		case INTERF_CLEAR:clear();
			break;

		case INTERF_READ_FILE:read_file_all();
			break;

		case INTERF_WRITE_FILE:write_file_all();
			break;

		case INTERF_CLS:cls();
			break;

		case INTERF_STOP:clear();
			return 0;

		default:
			ERROR_MESSAGES_Function(MESSAGE_UNKNOWN_COMAND, NULL, NULL, NULL);
			break;
		}
	}

	return 0;


}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
