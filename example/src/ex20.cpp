#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
enum class BOOL { FALSE, TRUE } ;
enum class DataType { INT, DOUBLE, STRING, NONE } ;

struct Data
{
	void* pdata;
	DataType type; //1:int, 2:double, 3:string
};
struct DataArray
{
	Data* buf;
	int capacity;
	int size;
};
void InitDataArray(DataArray* pda, int cap)
{
	pda->capacity = cap;
	pda->size = 0;
	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
	for (int i = 0; i < pda->size; ++i)
	{
		//if (pda->buf[i].pdata)
		//{
			free(pda->buf[i].pdata);
			pda->buf[i].pdata = NULL;
		//}
	}
	free(pda->buf);
}
void PrintData(const Data* pd)
{
	switch (pd->type)
	{
	case DataType::INT:
		printf("int : %d\n", *(int*)pd->pdata);
		break;
	case DataType::DOUBLE:
		printf("double : %g\n", *(double*)pd->pdata);
		break;
	case DataType::STRING:
		printf("string : %s\n", (char*)pd->pdata);
		break;
	default: //오류..
		break;
	}
}
void Flush()
{
	while (getchar() != '\n')
		; //empty;
}
Data CreateData(DataType dt)
{
	Data data = { 0 };
	switch (dt)
	{
	case DataType::INT: {
		int item;
		printf("정수 입력:");
		scanf_s("%d", &item); Flush();
		data.pdata = (int*)malloc(sizeof(int));
		if( data.pdata )
			*(int*)data.pdata = item;
		data.type = DataType::INT;
	}
			break;
	case DataType::DOUBLE: {
		double item;
		printf("실수 입력:");
		scanf_s("%lf", &item); Flush();
		data.pdata = (double*)malloc(sizeof(double));
		if( data.pdata)
			*(double*)data.pdata = item;
		data.type = DataType::DOUBLE;
	}
			   break;
	case DataType::STRING: {
		char buf[500] = "";
		printf("문자열 입력:");
		gets_s(buf, 500);
		data.pdata = (char*)malloc(strlen(buf) + 1);
		if( data.pdata )
			strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
		data.type = DataType::STRING;
	}
			   break;
	}
	return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
	pda->buf[pda->size++] = *pd; //Data d2 = d1;
}
void PrintDataArray(const DataArray* pda)
{
	for (int i = 0; i < pda->size; ++i)
		PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
	return pda->buf[idx];
}
void Menu()
{
	puts("1. 정수, 실수, 문자열 입력:");
	puts("2. 모든 데이터 출력:");
	puts("3. 부가 기능");
	puts("0. 프로그램 종료!");
	puts("");
}
Data ChooseData()
{
	printf("정수[0], 실수[1], 문자열[2] 입력하세요:");
	Data data = { 0 };
	switch ((DataType)(_getch()-'0'))
	{
	case DataType::INT:
		data = CreateData(DataType::INT);
		break;
	case DataType::DOUBLE:
		data = CreateData(DataType::DOUBLE);
		break;
	case DataType::STRING:
		data = CreateData(DataType::STRING);
		break;
	}
	return data;
}
int main()
{
	BOOL run = BOOL::TRUE;
	DataArray da;
	InitDataArray(&da, 10000);

	DataType dt = (DataType)5;
	while (run == BOOL::TRUE)
	{
		Menu();
		switch (_getch())
		{
		case '1':
		{ 
			Data data = ChooseData();
			AddDataArray(&da, &data);
		}
			break;
		case '2':
			PrintDataArray(&da);
			break;
		case '3':
			break;
		case '0':
			run = BOOL::FALSE;
			break;
		}
	}

	UninitDataArray(&da);
}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<conio.h>
//typedef enum { FALSE, TRUE} BOOL;
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		free(pda->buf[i].pdata);
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//void Flush()
//{
//	while (getchar() != '\n')
//		; //empty;
//}
//Data CreateData(DataType dt)
//{
//	Data data = { 0 };
//	switch (dt)
//	{
//	case INT: {
//		int item;
//		printf("정수 입력:");
//		scanf_s("%d", &item); Flush();
//		data.pdata = (int*)malloc(sizeof(int));
//		*(int*)data.pdata = item;
//		data.type = INT;
//	}
//			break;
//	case DOUBLE: {
//		double item;
//		printf("실수 입력:");
//		scanf_s("%lf", &item); Flush();
//		data.pdata = (double*)malloc(sizeof(double));
//		*(double*)data.pdata = item;
//		data.type = DOUBLE;
//	}
//			break;
//	case STRING: {
//		char buf[500] = "";
//		printf("문자열 입력:");
//		gets_s(buf, 500); 
//		data.pdata = (char*)malloc(strlen(buf) + 1);
//		strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
//		data.type = STRING;
//	}
//			break;
//	}
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//void Menu()
//{
//	puts("1. 정수, 실수, 문자열 입력:");
//	puts("2. 모든 데이터 출력:");
//	puts("3. 부가 기능");
//	puts("0. 프로그램 종료!");
//	puts("");
//}
//int main()
//{
//	BOOL run = TRUE;
//	DataArray da;
//	InitDataArray(&da, 10000);
//
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			break;
//		case '2':
//			break;
//		case '3':
//			break;
//		case '0':
//			run = FALSE;
//			break;
//		}
//	}
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//int main()
//{
//	char c = getchar();
//	printf("%d\n", c);
//
//	c = getchar();
//	printf("%d\n", c);
//
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//int main()
//{
//	int n = 0;
//	scanf_s("%d", &n);
//	printf("int : %d\n", n);
//
//	scanf_s("%d", &n);
//	getchar();
//	printf("int : %d\n", n);
//
//
//	char buf[100];
//	gets_s(buf, 100);
//	printf("string : %s\n", buf);
//}


//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		free(pda->buf[i].pdata);
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//Data CreateData(DataType dt)
//{
//	Data data = { 0 };
//	switch (dt)
//	{
//	case INT: {
//		int item;
//		printf("정수 입력:");
//		scanf_s("%d", &item);
//		data.pdata = (int*)malloc(sizeof(int));
//		*(int*)data.pdata = item;
//		data.type = INT;
//	}
//			break;
//	case DOUBLE: {
//		double item;
//		printf("실수 입력:");
//		scanf_s("%lf", &item);
//		data.pdata = (double*)malloc(sizeof(double));
//		*(double*)data.pdata = item;
//		data.type = DOUBLE;
//	}
//			break;
//	case STRING: {
//		char buf[500] = "";
//		printf("문자열 입력:");
//		gets_s(buf, 500);
//		data.pdata = (char*)malloc(strlen(buf) + 1);
//		strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
//		data.type = STRING;
//	}
//			break;
//	}
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = CreateData(INT);
//	AddDataArray(&da, &data);
//	data = CreateData(DOUBLE);
//	AddDataArray(&da, &data);
//	data = CreateData(STRING);
//	AddDataArray(&da, &data);
//
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		free(pda->buf[i].pdata);
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//Data CreateData(DataType dt)
//{
//	Data data = { 0 };
//	switch (dt)
//	{
//	case INT: {
//		data.pdata = (int*)malloc(sizeof(int));
//		*(int*)data.pdata = 100;
//		data.type = INT;
//	}
//			break;
//	case DOUBLE: {
//		data.pdata = (double*)malloc(sizeof(double));
//		*(double*)data.pdata = 2.56;
//		data.type = DOUBLE;
//	}
//			   break;
//	case STRING: {
//		char buf[500] = "Hello!";
//		data.pdata = (char*)malloc(strlen(buf) + 1);
//		strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
//		data.type = STRING;
//	}
//			   break;
//	}
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = CreateData(INT);
//	AddDataArray(&da, &data);
//	data = CreateData(DOUBLE);
//	AddDataArray(&da, &data);
//	data = CreateData(STRING);
//	AddDataArray(&da, &data); 
//
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}
// 
 
//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		free(pda->buf[i].pdata);
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//Data CreateData(int item)
//{
//	Data data = { 0 };
//	data.pdata = (int*)malloc(sizeof(int));
//	*(int*)data.pdata = item;
//	data.type = INT;
//
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = CreateData(100);
//	AddDataArray(&da, &data);
//	data = CreateData(200);
//	AddDataArray(&da, &data);
//	data = CreateData(300);
//	AddDataArray(&da, &data);
//
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		free(pda->buf[i].pdata);
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//Data CreateData(int item)
//{
//	Data data = { 0 };
//	data.pdata = (int*)malloc(sizeof(int));
//	*(int*)data.pdata = item;
//	data.type = INT;
//
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = CreateData(100);
//	AddDataArray(&da, &data);
//	data = CreateData(200);
//	AddDataArray(&da, &data);
//	data = CreateData(300);
//	AddDataArray(&da, &data);
//
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//Data CreateData(int item)
//{
//	Data data = { 0 };
//	data.pdata = (int*)malloc(sizeof(int));
//	*(int*)data.pdata = item;
//	data.type = INT;
//
//	return data;
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = CreateData(100);
//	AddDataArray(&da, &data);
//	data = CreateData(200);
//	AddDataArray(&da, &data);
//	data = CreateData(300);
//	AddDataArray(&da, &data);
//
//	*(int*)GetDataArray(&da, 0).pdata = 200;
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd; //Data d2 = d1;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//
//	Data data = { 0 };
//	data.pdata = (int*)malloc(sizeof(int));
//	*(int*)data.pdata = 100;
//	data.type = INT;
//	AddDataArray(&da, &data);
//	AddDataArray(&da, &data);
//	AddDataArray(&da, &data);
//	*(int*)GetDataArray(&da, 0).pdata = 200;
//	PrintDataArray(&da);
//
//	UninitDataArray(&da);
//}

//#pragma warning(disable:26812 6011 6387)
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//struct DataArray
//{
//	Data* buf;
//	int capacity;
//	int size;
//};
//void InitDataArray(DataArray* pda, int cap)
//{
//	pda->capacity = cap;
//	pda->size = 0;
//	pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
//}
//void UninitDataArray(DataArray* pda)
//{
//	free(pda->buf);
//}
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//void AddDataArray(DataArray* pda, Data* pd)
//{
//	pda->buf[pda->size++] = *pd;
//}
//void PrintDataArray(const DataArray* pda)
//{
//	for (int i = 0; i < pda->size; ++i)
//		PrintData(&pda->buf[i]);
//}
//Data GetDataArray(const DataArray* pda, int idx)
//{
//	return pda->buf[idx];
//}
//int main()
//{
//	DataArray da;
//
//	InitDataArray(&da, 10000);
//	
//	Data data = { 0 };
//	data.pdata = (int*)malloc(sizeof(int));
//	*(int*)data.pdata = 100;
//	data.type = INT;
//	AddDataArray(&da, &data);
//	AddDataArray(&da, &data);
//	AddDataArray(&da, &data);
//
//	PrintDataArray(&da);
//
//	Data data2 = GetDataArray(&da, 0);
//	PrintData(&data2);
//	UninitDataArray(&da);
//}

//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef enum { INT, DOUBLE, STRING, NONE } DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//
//void PrintData(const Data* pd)
//{
//	switch (pd->type)
//	{
//	case INT:
//		printf("int : %d\n", *(int*)pd->pdata);
//		break;
//	case DOUBLE:
//		printf("double : %g\n", *(double*)pd->pdata);
//		break;
//	case STRING:
//		printf("string : %s\n", (char*)pd->pdata);
//		break;
//	default: //오류..
//		break;
//	}
//}
//int main()
//{
//	Data data;
//
//	int* pn = (int*)malloc(sizeof(int));
//	*pn = 100;
//	data.pdata = pn;
//	data.type = INT;
//
//	Data data2;
//	double* pd = (double*)malloc(sizeof(double));
//	*pd = 2.56;
//	data2.pdata = pd;
//	data2.type = DOUBLE;
//
//	Data data3;
//	char* s = (char*)malloc(sizeof(char) * 100);
//	strcpy_s(s, strlen("Hello!") + 1, "Hello!");
//	data3.pdata = s;
//	data3.type = STRING;
//
//	PrintData(&data);
//	PrintData(&data2);
//	PrintData(&data3);
//}

//#include<stdio.h>
//typedef enum { INT, DOUBLE, STRING, NONE} DataType;
//
//struct Data
//{
//	void* pdata;
//	DataType type; //1:int, 2:double, 3:string
//};
//
//int main()
//{
//	DataType type = INT;
//
//	printf("%d\n", type);
//	printf("%d\n", DOUBLE);
//	printf("%d\n", STRING);
//	printf("%d\n", NONE);
//}

//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//void SetFile()
//{
//    FILE* pf = NULL;
//
//    fopen_s(&pf, "..\\test.ati", "wb");
//    {
//
//        {
//            char logo[2] = { 'M','F' };
//            unsigned short empty = 0;
//            fwrite(logo, 1, sizeof(char) * 2, pf);
//            fwrite(&empty, 1, sizeof(unsigned short), pf);
//            int dataCount = 10000;
//            fwrite(&dataCount, 1, sizeof(int), pf);
//        }
//    }
//    fclose(pf);
//}
//void IWriteData(char dtype, int ndata)
//{
//    FILE* pf = NULL;
//    fopen_s(&pf, "..\\test.ati", "ab");
//    {
//        fwrite(&dtype, 1, sizeof(char), pf);
//        fwrite(&ndata, 1, sizeof(int), pf);
//    }
//    fclose(pf);
//}
//void DWriteData(char dtype, double Ddata)
//{
//    FILE* pf = NULL;
//    fopen_s(&pf, "..\\test.ati", "ab");
//    {
//        fwrite(&dtype, 1, sizeof(char), pf);
//        fwrite(&Ddata, 1, sizeof(double), pf);
//    }
//    fclose(pf);
//}
//void SWriteData(char dtype, char* Sdata, int slen)
//{
//    FILE* pf = NULL;
//    fopen_s(&pf, "..\\test.ati", "ab");
//    {
//        fwrite(&dtype, 1, sizeof(char), pf);
//        fwrite(&slen, 1, sizeof(int), pf);
//        fwrite(Sdata, 1, slen, pf);
//    }
//    fclose(pf);
//}
//void ReadData(int dataCount)
//{
//    FILE* pf = NULL;
//    fopen_s(&pf, "..\\test.ati", "rb");
//    {
//        char header[8];
//        fread(header, 1, sizeof(header), pf);
//        if (!(header[0] == 'M' && header[1] == 'F'))
//        {
//            printf("File Format 다름");
//            abort;
//        }
//
//
//        for (int i = 0; i < dataCount; ++i)
//        {
//            char type = 0;
//            fread(&type, 1, sizeof(char), pf);
//            switch (type)
//            {
//            case 'I':
//            {
//                int data = 0;
//                fread(&data, 1, sizeof(int), pf);
//                printf("int  : %d\n", data);
//                break;
//            }
//            case 'D':
//            {
//                double data = 0;
//                fread(&data, 1, sizeof(double), pf);
//                printf("double  : %lf\n", data);
//                break;
//            }
//            case 'S':
//            {
//                int slen = 0;
//                fread(&slen, 1, sizeof(int), pf);
//                char* buf = (char*)malloc(slen);
//                fread(buf, 1, slen, pf);
//                printf("string  : %s\n", buf);
//
//                free(buf);
//                break;
//            }
//            default:
//            {
//                break;
//            }
//            }
//        }
//
//    }
//    fclose(pf);
//}
//void Menu()   /// 유틸리티 함수 혹은 헬퍼함수
//{
//    printf("============================\n");
//    printf(" 1. 데이터 입력:\n");
//    printf(" 2. 모든 데이터 출력:\n");
//    printf(" 0. 프로그램 종료\n");
//    printf("============================\n");
//    printf("매뉴를 선택하세요\n");
//}
//int main()
//{
//    int menu = 1;
//    int dataCount = 0;
//    char dtype = '0';
//    int ndata = 0;
//    double ddata = 0;
//    char sdata[100] = { 0 };
//    SetFile();
//    do
//    {
//        Menu();
//        scanf_s("%d", &menu);
//        printf("%d", menu);
//        switch (menu)
//        {
//        case 1:
//        {
//            printf(" 데이터 입력을 선택하셧습니다\n");
//            dataCount = dataCount + 1;
//            printf("추가할 데이터의 타입을 정하세요\n");
//            scanf_s(" %c", &dtype);
//            if (dtype == 'I')
//            {
//                printf("추가할 데이터를 입력하세요\n");
//                scanf_s("%d", &ndata);
//                IWriteData(dtype, ndata);
//            }
//            else if (dtype == 'D')
//            {
//                printf("추가할 데이터를 입력하세요\n");
//                scanf_s("%lf", &ddata);
//                DWriteData(dtype, ddata);
//            }
//            else if (dtype == 'S')
//            {
//                printf("추가할 데이터를 입력하세요\n");
//                scanf_s("%s", sdata, 100);
//                SWriteData(dtype, sdata, strlen(sdata) + 1);
//            }
//            break;
//        }
//        case 2:
//        {
//            printf(" 데이터 출력을 선택하셧습니다\n");
//            ReadData(dataCount);
//            break;
//        }
//        case 0:
//        {
//            printf("프로그램을 종료를 선택하셧습니다\n");
//            break;
//        }
//        }
//    } while (menu != 0);
//}


//#include <string.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <stdio.h>
//#include <Windows.h>
//
//void util(void)
//{
//    system("cls");
//    printf("1.입력\n");
//    printf("2.출력\n");
//    printf("3.프로그램 종료\n");
//    printf("===========================\n");
//}
//
//void input_util(void)
//{
//    system("cls");
//    printf("1.숫자\n");
//    printf("2.실수\n");
//    printf("3.문자열\n");
//    printf("4.뒤로\n");
//    printf("===========================\n");
//}
//
//void header_info_write(FILE* pf)
//{
//    char logo[2] = { 'H','S' };
//    unsigned short empty = 0;
//    fwrite(logo, 1, sizeof(char) * 2, pf);
//    fwrite(&empty, 1, sizeof(unsigned short), pf);
//}
//
//int judge_header(FILE* pf)
//{
//    char header[4];
//    fread(header, 1, sizeof(header), pf);
//    if (!(header[0] == 'H' and header[1] == 'S'))
//    {
//        printf("파일 포멧이 다릅니다.");
//        return 0;
//    }
//    return 1;
//}
//
//void state_write()
//{
//    FILE* pf = NULL;
//    fopen_s(&pf, "test.lhs", "wb");
//    header_info_write(pf);
//    int run = 1;
//    while (run)
//    {
//        input_util();
//        char dtype = 0;
//        switch (_getch())
//        {
//        case '1':
//        {
//            dtype = 'I';
//            int data;
//            printf("숫자 입력 : ");
//            scanf_s("%d", &data);
//            fwrite(&dtype, 1, sizeof(char), pf);
//            fwrite(&data, 1, sizeof(int), pf);
//        }
//        break;
//        case '2':
//        {
//            dtype = 'D';
//            double data;
//            printf("실수 입력 : ");
//            scanf_s("%lf", &data);
//            fwrite(&dtype, 1, sizeof(char), pf);
//            fwrite(&data, 1, sizeof(double), pf);
//        }
//        break;
//        case '3':
//        {
//            dtype = 'S';
//            char data[500];
//            printf("문자열 입력 : ");
//            scanf_s("%s", &data, 500);
//            int slen = strlen(data) + 1;
//            fwrite(&dtype, 1, sizeof(char), pf);
//            fwrite(&slen, 1, sizeof(int), pf);
//            fwrite(data, 1, slen, pf);
//        }
//        break;
//        case '4':
//        {
//            run = 0;
//            dtype = 'E';
//            fwrite(&dtype, 1, sizeof(char), pf);
//            fclose(pf);
//        }
//        break;
//        default:
//            break;
//        }
//    }
//}
//
//void state_read()
//{
//    FILE* pf = NULL;
//    int run = 1;
//    fopen_s(&pf, "test.lhs", "rb");
//    if (judge_header(pf))
//    {
//        while (run)
//        {
//            char type = 0;
//            fread(&type, 1, sizeof(char), pf);
//            switch (type)
//            {
//            case 'I':
//            {
//                int data = 0;
//                fread(&data, 1, sizeof(int), pf);
//                printf("int : %d\n", data);
//            }
//            break;
//            case 'D':
//            {
//                double data = 0;
//                fread(&data, 1, sizeof(double), pf);
//                printf("double : %g\n", data);
//            }
//            break;
//            case 'S':
//            {
//                int slen = 0;
//                fread(&slen, 1, sizeof(int), pf);
//                char* buf = (char*)malloc(slen);
//
//                fread(buf, 1, slen, pf);
//                printf("string : %s\n", buf);
//                free(buf);
//            }
//            break;
//            case 'E':
//                run = 0;
//                fclose(pf);
//                printf("아무키나 입력하세요\n");
//                _getch();
//                break;
//            default:
//                break;
//            }
//        }
//    }
//
//}
//
//int main(void)
//{
//    int loop = 1;
//    while (loop)
//    {
//        util();
//        switch (_getch())
//        {
//        case '1':
//            state_write();
//            break;
//        case '2':
//            state_read();
//            break;
//        case '3':
//            loop = 0;
//            break;
//        default:
//            break;
//        }
//    }
//
//    return 0;
//}


//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main()
//{
//	FILE* pf = NULL;
//	fopen_s(&pf, "..\\test.ati", "wb");
//	{
//		//header
//		{
//			char logo[2] = { 'M','F' };
//			unsigned short empty = 0;
//			//fwrite(logo, 2, sizeof(char), pf);
//			fwrite(logo, 1, sizeof(char) * 2, pf);
//			fwrite(&empty, 1, sizeof(unsigned short), pf);
//			int dataCount = 4;
//			fwrite(&dataCount, 1, sizeof(int), pf);
//		}
//		//body
//		{
//			char dtype = 'I';
//			int ndata = 100;
//			double ddata = 2.6;
//			const char* sdata = "Hello!";
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ndata, 1, sizeof(int), pf);
//
//			dtype = 'D';
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ddata, 1, sizeof(double), pf);
//
//			dtype = 'S';
//			int slen = strlen(sdata) + 1;
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&slen, 1, sizeof(int), pf);
//			fwrite(sdata, 1, slen, pf);
//
//			dtype = 'I';
//			ndata = 25;
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ndata, 1, sizeof(int), pf);
//		}
//	}
//	fclose(pf);
//
//	fopen_s(&pf, "..\\test.ati", "rb");
//	{
//		int dataCount = 0;
//		//file header
//		{
//			char header[8];
//			fread(header, 1, sizeof(header), pf);
//			if (!(header[0] == 'M' && header[1] == 'F'))
//			{
//				printf("파일 포멧이 다릅니다.");
//				return -1;
//			}
//			dataCount = *(int*)(header + 4);
//		}
//		//file body
//		{
//			for (int i = 0; i < dataCount; ++i)
//			{
//				char type = 0;
//				fread(&type, 1, sizeof(char), pf);
//				switch (type)
//				{
//				case 'I':
//				{
//					int data = 0;
//					fread(&data, 1, sizeof(int), pf);
//					printf("int : %d\n", data);
//				}
//				break;
//				case 'D':
//				{
//					double data = 0;
//					fread(&data, 1, sizeof(double), pf);
//					printf("double : %g\n", data);
//				}
//				break;
//				case 'S':
//				{
//					int slen = 0;
//					fread(&slen, 1, sizeof(int), pf);
//					char* buf = (char*)malloc(slen);
//					fread(buf, 1, slen, pf);
//					printf("string : %s\n", buf);
//					free(buf);
//				}
//				break;
//				default:
//					break;
//				}
//			}
//		}
//
//	}
//	fclose(pf);
//}
