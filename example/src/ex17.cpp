#include <stdio.h>
void PrintArray(int arr[][5]) //int (*arr)[5]
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			printf("%5d", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int arr[5][5] = { 0 };

	PrintArray(arr);
	for (int i = 0; i < 5; ++i)
	{
		arr[i][i] = 1;
		arr[i][4-i] = 1;
	}
	PrintArray(arr);
}

//#include <stdio.h>
//void PrintArray(int arr[][5]) //int (*arr)[5]
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[5][5] = { 0 };
//
//	PrintArray(arr);
//	for (int i = 0; i < 5; ++i)
//		arr[i][i] = 1;
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int arr[][5]) //int (*arr)[5]
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[5][5] = { 0 };
//
//	PrintArray(arr);
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			if (i == j)
//				arr[i][j] = 1;
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int arr[][5]) //int (*arr)[5]
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//}
//void InitArray(int pa[][5])
//{
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			pa[i][j] = i * 5 + j + 1;
//}
//int main()
//{
//	int arr[5][5] = { 0, 678 };
//
//	PrintArray(arr);
//	InitArray(arr);
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int(*arr)[5])
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//}
//void InitArray(int(*pa)[5])
//{
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			pa[i][j] = i * 5 + j + 1;
//}
//int main()
//{
//	int arr[5][5] = { 0, 678 };
//
//	PrintArray(arr);
//	InitArray(arr);
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int(*arr)[5])
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//}
//void InitArray(int(*pa)[5])
//{
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			pa[i][j] = i * 5 + j + 1;
//}
//int main()
//{
//	int arr[5][5] = { 0, 678 };
//
//	PrintArray(arr);
//	InitArray(arr);
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int (*arr)[5])
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//}
//int main()
//{
//	int arr[5][5] = { 0, 678 };
//
//	PrintArray(arr);
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			arr[i][j] = i * 5 + j + 1;
//	PrintArray(arr);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[5][5] = { 0, 678};
//
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//	for (int i = 0; i < 5; ++i)
//		for (int j = 0; j < 5; ++j)
//			arr[i][j] = i * 5 + j+1;
//
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//			printf("%5d", arr[i][j]);
//		printf("\n");
//	}
//}

//#include <stdio.h>
//int main()
//{
//	int arr[6] = { 10,20,30,40,50,60 };
//	int(*pa)[3] = (int(*)[3]) arr;
//
//	printf("\n");
//	printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
//	printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", pa, pa[0], pa[1]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[2][3] = { 10,20,30,40,50,60 };
//	int(*pa)[3] = arr;
//
//	printf("\n");
//	printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
//	printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", pa, pa[0], pa[1]);
//}


//#include <stdio.h>
//int main()
//{
//	int arr[2][3] = { 10,20,30,40,50,60 };
//
//	printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
//	printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", arr, arr[0], arr[1]);
//	
//	int(*pa)[3];
//	pa = arr;
//	printf("\n");
//	printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
//	printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", pa, pa[0], pa[1]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[2][3] = { 10,20,30,40,50,60 };
//
//	printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
//	printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
//	printf("\n");
//	printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
//	printf("%d %d %d\n", arr[0][3], arr[0][4], arr[0][5]);
//	printf("\n");
//	printf("%d %d %d\n", arr[1][-3], arr[1][-2], arr[1][-1]);
//	printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", &arr[0][0], &arr[0][1], &arr[0][2]);
//	printf("%p %p %p\n", &arr[1][0], &arr[1][1], &arr[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", arr, arr[0], arr[1]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[2][3] = { 10,20,30,40,50,60 };
//
//	printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
//	printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", &arr[0][0], &arr[0][1], &arr[0][2]);
//	printf("%p %p %p\n", &arr[1][0], &arr[1][1], &arr[1][2]);
//	printf("\n");
//	printf("%p %p %p\n", arr, arr[0], arr[1]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[2][3] = { 10,20,30,40,50,60 };
//
//	printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
//	printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char** buf;
//	int count;
//	int capacity;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	if (psa->count >= psa->capacity)
//		return; //로그 남기기.
//
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			free(psa->buf[i]); ///////////////
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//void InitString(StringArray* psa, int capacity)
//{
//	psa->buf = (char**)malloc(sizeof(char*) * capacity);
//	psa->count = 0;
//	psa->capacity = capacity;
//}
//void UninitString(StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		free(psa->buf[i]);
//}
//int main()
//{
//	StringArray sa;
//	int run = 1;
//
//	InitString(&sa, 1000);
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//
//	UninitString(&sa);
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char** buf;
//	int count;
//	int capacity;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	if (psa->count >= psa->capacity)
//		return; //로그 남기기.
//	
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			free(psa->buf[i]); ///////////////
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//void InitString(StringArray* psa, int capacity)
//{
//	psa->buf = (char**)malloc(sizeof(char*) * capacity);
//	psa->count = 0;
//	psa->capacity = capacity;
//}
//void FreeString(StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		free(psa->buf[i]);
//}
//int main()
//{
//	StringArray sa;
//	int run = 1;
//
//	InitString(&sa, 1000);
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//
//	FreeString(&sa);
//}


//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char** buf;
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			free(psa->buf[i]); ///////////////
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//void InitString(StringArray* psa, int capacity)
//{
//	psa->buf = (char**) malloc (sizeof(char*)*capacity);
//	psa->count=0;
//}
//void FreeString(StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		free(psa->buf[i]);
//}
//int main()
//{
//	StringArray sa;
//	int run = 1;
//
//	InitString(&sa, 1000);
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//
//	FreeString(&sa);
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char* buf[100];
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			free(psa->buf[i]); ///////////////
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//void FreeString(StringArray* psa)
//{
//	for(int i = 0 ; i < psa->count ; ++i)
//		free(psa->buf[i]);
//}
//int main()
//{
//	StringArray sa = { 0 };
//	int run = 1;
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//
//	FreeString(&sa);
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char* buf[100];
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			free(psa->buf[i]); ///////////////
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//int main()
//{
//	StringArray sa = { 0 };
//	int run = 1;
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char* buf[100];
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//	char str[500];
//	printf("검색할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			printf("[%d] : %s 있습니다.\n", i, str);
//			break;
//		}
//	}
//}
//void RemoveString(StringArray* psa)
//{
//	char str[500];
//	printf("삭제할 문자열 입력:");
//	gets_s(str, 500);
//	for (int i = 0; i < psa->count; ++i)
//	{
//		if (strcmp(str, psa->buf[i]) == 0)
//		{
//			for (int j = i; j < psa->count - 1; ++j)
//				psa->buf[j] = psa->buf[j + 1];
//			--psa->count;
//			break;
//		}
//	}
//}
//int main()
//{
//	StringArray sa = { 0 };
//	int run = 1;
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//}

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct _stringArray
//{
//	char* buf[100];
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//	printf("문자열 입력:");
//	char str[500];
//	gets_s(str, 500);
//	char* s = (char*)malloc(strlen(str) + 1);
//	strcpy_s(s, strlen(str) + 1, str);
//
//	psa->buf[psa->count] = s;
//	++psa->count;
//}
//void PrintString(const StringArray* psa)
//{
//	for (int i = 0; i < psa->count; ++i)
//		printf("[%d] : %s\n", i, psa->buf[i]);
//}
//void SearchString(const StringArray* psa)
//{
//
//}
//void RemoveString(StringArray* psa)
//{
//
//}
//int main()
//{
//	StringArray sa = { 0 };
//	int run = 1;
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//}

//#include <stdio.h>
//#include <conio.h>
//
//typedef struct _stringArray
//{
//	char* buf[100];
//	int count;
//}StringArray;
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//void AddString(StringArray* psa)
//{
//
//}
//void PrintString(const StringArray* psa)
//{
//
//}
//void SearchString(const StringArray* psa)
//{
//
//}
//void RemoveString(StringArray* psa)
//{
//
//}
//int main()
//{
//	StringArray sa = { 0 };
//	int run = 1;
//	while (run)
//	{
//		switch (_getch())
//		{
//		case '1':
//			AddString(&sa);
//			break;
//		case '2':
//			PrintString(&sa);
//			break;
//		case '3':
//			SearchString(&sa);
//			break;
//		case '4':
//			RemoveString(&sa);
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//}


//#include <stdio.h>
//#include <conio.h>
//
//void Menu()
//{
//	puts("1. 문자열 입력:");
//	puts("2. 모든 문자열 출력:");
//	puts("3. 문자열 검색:");
//	puts("4. 문자열 삭제:");
//	puts("0. 프로그램 종료");
//}
//int main()
//{
//	int run = 1;
//	while (run)
//	{
//		switch (_getch())
//		{
//		case '1':
//			printf("입력");
//			break;
//		case '2':
//			printf("출력");
//			break;
//		case '3':
//			printf("검색");
//			break;
//		case '4':
//			printf("삭제");
//			break;
//		case '0':
//			run = 0;
//			break;
//		}
//	}
//}