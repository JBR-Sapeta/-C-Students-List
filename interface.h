#pragma once

enum INTERFACE
{
	INTERF_STOP,			//0
	INTERF_PUSH,			//1
	INTERF_POP,				//2	
	INTERF_FIND,			//3
	INTERF_PRIT_STACK,		//4
	INTERF_CLEAR,			//5
	INTERF_READ_FILE,		//6				
	INTERF_WRITE_FILE,		//7
	INTERF_CLS,				//8
	INTERF_TOT				//9
};

void menu();
void push();
void pop();
void print_stack();
void clear();
void read_file_all();
void write_file_all();
void find_element();
void find_lastname();
void find_year();
void find_dgree();
void cls();
