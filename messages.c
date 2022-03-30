#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "messages.h"
#include "stack.h"


static const char* error_message_array[] = {

	"W Warning - File data  can be overwrite !",		    // MESSAGE_FILE_OVERWRITE_WARNING
	"E Memory allocation error...",							// MESSAGE_MEMORY_ALOCATION_ERROR
	"E File open error...",									// MESSAGE_FILE_OPEN_ERROR
	"E File write error...",								// MESSAGE_FILE_WRITE_ERROR
	"E File read error...",									// MESSAGE_FILE_READ_ERROR
	"W Warning - Stack is empty !",							// MESSAGE_EMPTY_STACK_WARNING
	"W Warning - Unknown command !",						// MESSAGE_UNKNOWN_COMAND
};
static FreeData ptr_f_FreeData;


void ERROR_MESSAGES_Function(enum ERROR_MESSAGES message, FILE* ptr_file, __int64* file_desc, FreeData ptr_FreeData)
{
	ptr_f_FreeData = ptr_FreeData;

	if (error_message_array[message][0] == 'W')
	{
		printf("\n--------------------------------------------------\n\n");
		puts(error_message_array[message] + 1);
		printf(" \n");
	}

	if (error_message_array[message][0] == 'E')
	{
		printf("\n--------------------------------------------------\n\n");
		puts(error_message_array[message] + 1);
		printf(" \n");

		if (ptr_file)               //zamykamy plik jezeli byl otwarty
			fclose(ptr_file);

		if (file_desc)				//zwalniamy  file_desc  jezeli byl utworzony
			free(file_desc);

		if (ptr_FreeData)			//zwalniamy  stos  
			STACK_ELEMENT_Free(ptr_FreeData);

		switch (message)
		{
		case MESSAGE_MEMORY_ALOCATION_ERROR:
			system("pause");
			exit(1);

		case MESSAGE_FILE_OPEN_ERROR:
			system("pause");
			exit(2);

		case MESSAGE_FILE_WRITE_ERROR:
			system("pause");
			exit(3);
		case MESSAGE_FILE_READ_ERROR:
			system("pause");
			exit(4);

		}
	}


}