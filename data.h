#pragma once

const enum DEGREE_COURSE
{
	DEG_PHYSICS,
	DEG_ARCHITECTURE,
	DEG_MATHEMATICS,
	DEG_COMPUTING,
	DEG_LOGISTIC,
	DEG_TOT
};

struct MY_STUDENT
{
	unsigned int year;
	enum DEGREE_COURSE dgree;
	char* lastname;
	unsigned int s_lenght;
};

void* STUDENT_DATA_Init(char* new_lastname, unsigned int new_year, enum DEGREE_COURSE new_dgree);
void STUDENT_DATA_Free(void* ptr);
void* STUDENT_DATA_Push(char* lastname, unsigned int year, enum DEGREE_COURSE dgree);
void STUDENT_DATA_Print(void* ptr);
int  STUDENT_DATA_SerchLastName(void* pCurData, void* pSearchData);
int  STUDENT_DATA_SerchYear(void* ptr_CurData, void* ptr_SearchData);
int  STUDENT_DATA_SerchDegree(void* ptr_CurData, void* ptr_SearchData);
void STUDENT_DATA_Save(FILE* ptr_file, __int64* file_desc, void* ptr_data);
void* STUDENT_DATA_Read(FILE* ptr_file, __int64* file_desc);
void DEGREE_COURSE_Print();
