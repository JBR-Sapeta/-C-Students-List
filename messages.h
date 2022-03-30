#pragma once

const enum ERROR_MESSAGES
{
	MESSAGE_FILE_OVERWRITE_WARNING,	 // 0
	MESSAGE_MEMORY_ALOCATION_ERROR,  // 1
	MESSAGE_FILE_OPEN_ERROR,         // 2
	MESSAGE_FILE_WRITE_ERROR,		 // 3
	MESSAGE_FILE_READ_ERROR,	     // 4
	MESSAGE_EMPTY_STACK_WARNING,	 // 5
	MESSAGE_UNKNOWN_COMAND			 // 6
};

typedef void (*FreeData)(void* ptr_data);

void ERROR_MESSAGES_Function(enum ERROR_MESSAGES message, FILE* ptr_file, __int64* file_desc, FreeData ptr_freedata);

