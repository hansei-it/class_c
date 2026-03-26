#include <stdio.h>
int Find(int list[], int size, int (*cbCompare)(int))
{
	for (int i = 0; i < size; ++i)
		if (cbCompare(list[i]))
			return i;

	return -1;
}
/////////////////
int cmp(int key)
{
	return key % 5 == 0 && key > 50;
}
int cmp2(int key)
{
	return 90 == key;
}
int main()
{
	int list[8] = { 59,40,60,69,32,51,74,90 };
	int size = 8;

	int idx = Find(list, size, cmp2);
	if (idx != -1)
		printf("[%d] : %d \n", idx, list[idx]);
	else
		printf("원소가 없다!\n");
}
//#include <stdio.h>
//int Find(int list[], int size, int (*cbCompare)(int) )
//{
//	for (int i = 0; i < size; ++i)
//		if ( cbCompare(list[i]) )
//			return i;
//
//	return -1;
//}
///////////////////
//int cmp(int key)
//{
//	return key % 5 == 0 && key > 50;
//}
//int main()
//{
//	int list[8] = { 59,40,60,69,32,51,74,90 };
//	int size = 8;
//
//	int idx = Find(list, size, cmp);
//	if (idx != -1)
//		printf("[%d] : %d \n", idx, list[idx]);
//	else
//		printf("원소가 없다!\n");
//}

//#include <stdio.h>
//int Find(int list[], int size, int key)
//{
//	for (int i = 0; i < size; ++i)
//		if (list[i] == key)
//			return i;
//
//	return -1;
//}
//int main()
//{
//	int list[8] = { 59,40,60,69,32,51,74,90 };
//	int size = 8;
//
//	int idx = Find(list, size, 51);
//	if (idx != -1)
//		printf("[%d] : %d \n", idx, list[idx]);
//	else
//		printf("원소가 없다!\n");
//}

//#include <stdio.h>
//int Find(int list[], int size, int key)
//{
//	for (int i = 0; i < size; ++i)
//		if (list[i] == key)
//			return i;
//	
//	return -1;
//}
//int main()
//{
//	int list[8] = { 59,40,60,69,32,51,74,90 };
//	int size = 8;
//
//	int idx = Find(list, size, 51);
//	if (idx != -1)
//		printf("[%d] : %d \n", idx, list[idx]);
//	else
//		printf("원소가 없다!\n");
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//	return a + b;
//}
//int Sub(int a, int b)
//{
//	return a - b;
//}
//int main()
//{
//	int (*pf)(int a, int b);
//	pf = Add;
//
//	printf("\n");
//	printf("%d\n", pf(2, 3));
//	pf = Sub;
//	printf("%d\n", pf(2, 3));
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//	return a+b;
//}
//int Sub(int a, int b)
//{
//	return a - b;
//}
//int main()
//{
//	int (*pf)(int a, int b);
//	pf = Add;
//	
//	printf("\n");
//	printf("%d\n", pf(2, 3));
//	printf("%d\n", pf(2, 3));
//}


////#include <stdio.h>
////int Add(int a, int b)
////{
////	return a+b;
////}
////int Sub(int a, int b)
////{
////	return a - b;
////}
////int main()
////{
////	printf("Add : %p\n", Add);
////	printf("Sub : %p\n", Sub);
////	printf("printf : %p\n", printf);
////	printf("main : %p\n", main);
////
////	printf("\n");
////	printf("%d\n", Add(2, 3));
////	printf("%d\n", Sub(2, 3));
////}

//
//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	double d = 5.5;
//	char c = 'A';
//
//	void* pv = (void*)(int*)&n;
//	printf("%d\n", *(int*)(void*)pv);
//
//	pv = (void*)&d;
//	printf("%g\n", *(double*)pv);
//
//	pv = (void*)&c;
//	printf("%c\n", *(char*)pv);
//}

//
//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	double d = 5.5;
//	char c = 'A';
//
//	void* pv = (void*)(int*)&n;
//	printf("%d\n", *(int*)(void*)pv);
//
//	pv = (void*)&d;
//	printf("%g\n", *(double*)pv);
//
//	pv = (void*)&c;
//	printf("%c\n", *(char*)pv);
//}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	double d = 5.5;
//	char c = 'A';
//
//	void* pv = &n;
//	printf("%d\n", *(int*)(void*)pv);
//
//	pv = &d;
//	printf("%g\n", *(double*)pv);
//
//	pv = &c;
//	printf("%c\n", *(char*)pv);
//}

//#include <stdio.h>
//
//void PrintArray(const char** pa)
//{
//	printf("%s %s %s %s\n", pa[0], pa[1], pa[2], pa[3]);
//}
//int main()
//{
//	const char* arr[4] = { "10","20","30","40" };
//	printf("%s %s %s %s\n", arr[0], arr[1], arr[2], arr[3]);
//
//	const char** pa;
//	pa = arr;
//	printf("%s %s %s %s\n", pa[0], pa[1], pa[2], pa[3]);
//	printf("%s\n", *pa);
//	printf("%c%c\n", **pa, (*pa)[1]);
//
//	PrintArray(arr);
//}

//#include <stdio.h>
//
//void PrintArray(const char** pa)
//{
//	printf("%s %s %s %s\n", pa[0], pa[1], pa[2], pa[3]);
//}
//int main()
//{
//	const char* arr[4] = { "10","20","30","40" };
//	printf("%s %s %s %s\n", arr[0], arr[1], arr[2], arr[3]);
//
//	const char** pa;
//	pa = arr;
//	printf("%s %s %s %s\n", pa[0], pa[1], pa[2], pa[3]);
//
//	PrintArray(arr);
//}

//#include <stdio.h>
//void PrintArray(int* pa)
//{
//	printf("%d %d %d %d\n", pa[0], pa[1], pa[2], pa[3]);
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//
//	int* pa;
//	pa = arr;
//	printf("%d %d %d %d\n", pa[0], pa[1], pa[2], pa[3]);
//
//	PrintArray(arr);
//
//}

//#include <stdio.h>
//void PrintDataArray(int** parr)
//{
//	printf("%p %p %p\n", parr[0], parr[1], parr[2]);
//}
//int main()
//{
//	int a = 10;
//	int b = 20;
//	int c = 30;
//
//	int* parr[3] = { &a, &b, &c };
//
//	printf("%d %d %d\n", a, b, c);
//	printf("%d %d %d\n", *parr[0], *parr[1], *parr[2]);
//
//	int** pparr = parr;
//	printf("%p %p %p\n", parr[0], parr[1], parr[2]);
//	PrintDataArray(parr);
//}

//#include <stdio.h>
//typedef int* INT;
//int main()
//{
//	int a = 10;
//	int b = 20;
//	int c = 30;
//
//	INT parr[3] = { &a, &b, &c };
//
//	printf("%d %d %d\n", a, b, c);
//	printf("%d %d %d\n", *parr[0], *parr[1], *parr[2]);
//
//	INT* pparr = parr;
//	printf("%p %p %p\n", parr[0], parr[1], parr[2]);
//	printf("%p %p %p\n", pparr[0], pparr[1], pparr[2]);
//}

//#include <stdio.h>
//int main()
//{
//	int a = 10;
//	int b = 20;
//	int c = 30;
//
//	int* parr[3] = { &a, &b, &c };
//
//	printf("%d %d %d\n", a, b, c);
//	printf("%d %d %d\n", *parr[0], *parr[1], *parr[2]);
//
//	int** pparr = parr;
//	printf("%p %p %p\n", parr[0], parr[1], parr[2]);
//	printf("%p %p %p\n", pparr[0], pparr[1], pparr[2]);
//}

//#include <stdio.h>
//void AddData(int* pscount)
//{
//	//(*pscount++);
//	//*(pscount = pscount + 1);
//	(*pscount)++;
//}
//int main()
//{
//	int scount = 0;
//
//	AddData(&scount); //pass by value
//
//	printf("%d\n", scount);
//}

//
//#include <stdio.h>
//void AddData(int* pscount)
//{
//	*pscount = *pscount + 1;
//}
//int main()
//{
//	int scount = 0;
//
//	AddData(&scount); //pass by value
//
//	printf("%d\n", scount);
//}

//#include <stdio.h>
//void AddData(int scount)
//{
//	scount++;
//}
//int main()
//{
//	int scount = 0;
//
//	AddData(scount); //pass by value
//
//	printf("%d\n", scount);
//}


////#pragma warning(disable:6387)
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//void InputString(char* buf)
//{
//	printf("문자열 입력:");
//	gets_s(buf, 1000);
//}
//char* AllocateString(char buf[])
//{
//	char* s = (char*)malloc(strlen(buf) + 1);
//	strcpy_s(s, strlen(buf) + 1, buf);
//
//	return s;
//}
//int IsExit(char* s)
//{
//	return strcmp("exit", s) == 0;
//}
//void FreeString(char* s)
//{
//	free(s);
//}
//void AddStringArray(char* sarray[], int* pscount, char* s)
//{
//	sarray[(*pscount)++] = s;
//}
//void PrintStringArray(char* sarray[], int scount)
//{
//	printf("===================\n");
//	for (int i = 0; i < scount; ++i)
//		printf("[%d] : %s\n", i, sarray[i]);
//}
//void FreeStringArray(char* sarray[], int scount)
//{
//	for (int i = 0; i < scount; ++i)
//		FreeString(sarray[i]);
//}
//int main()
//{
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		InputString(buf);
//		char* s = AllocateString(buf);
//
//		if (IsExit(s))
//		{
//			FreeString(s);
//			break;
//		}
//
//		AddStringArray(sarray, &scount, s);
//	}
//
//	PrintStringArray(sarray, scount);
//	FreeStringArray(sarray, scount);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//void InputString(char* buf)
//{
//	printf("문자열 입력:");
//	gets_s(buf, 1000);
//}
//char* AllocateString(char buf[])
//{
//	char* s = (char*)malloc(strlen(buf) + 1);
//	strcpy_s(s, strlen(buf) + 1, buf);
//
//	return s;
//}
//int IsExit(char* s)
//{
//	return strcmp("exit", s) == 0;
//}
//void FreeString(char* s)
//{
//	free(s);
//}
//void AddStringArray(char* sarray[], int* pscount, char* s)
//{
//	sarray[(*pscount)++] = s;
//}
//void PrintStringArray(char* sarray[], int scount)
//{
//	printf("===================\n");
//	for (int i = 0; i < scount; ++i)
//		printf("[%d] : %s\n", i, sarray[i]);
//}
//void FreeStringArray(char* sarray[], int scount)
//{
//	for (int i = 0; i < scount; ++i)
//		FreeString(sarray[i]);
//}
//int main()
//{
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		InputString(buf);
//		char* s = AllocateString(buf);
//
//		if ( IsExit(s) )
//		{
//			FreeString(s);
//			break;
//		}		
//
//		AddStringArray(sarray, &scount, s);
//	}
//
//	PrintStringArray(sarray, scount);
//	FreeStringArray(sarray, scount);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	//char* s = (char*)malloc(1);
//	//printf(" %p %p\n", s, "exit");
//	//printf("%d\n", s == "exit");
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		printf("문자열 입력:");
//		gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//		char* s = (char*)malloc(strlen(buf) + 1);
//		strcpy_s(s, strlen(buf) + 1, buf);
//
//		if (strcmp("exit", s) == 0)
//		{
//			free(s);
//			break;
//		}
//		else
//		{
//			sarray[scount++] = s;
//			printf("string : %s\n", s);
//		}
//	}
//
//	printf("===================\n");
//	for (int i = 0; i < scount; ++i)
//		printf("[%d] : %s\n", i, sarray[i]);
//
//	for (int i = 0; i < scount; ++i)
//		free(sarray[i]);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	//char* s = (char*)malloc(1);
//	//printf(" %p %p\n", s, "exit");
//	//printf("%d\n", s == "exit");
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		printf("문자열 입력:");
//		gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//		char* s = (char*)malloc(strlen(buf) + 1);
//		strcpy_s(s, strlen(buf) + 1, buf);
//
//		if (strcmp("exit", s) == 0)
//		{
//			free(s);
//			break;
//		}
//		else
//		{
//			sarray[scount++] = s;
//			printf("string : %s\n", s);
//		}
//	}
//
//	printf("===================\n");
//	for (int i = 0; i < scount; ++i)
//		printf("[%d] : %s\n", i, sarray[i]);
//
//	for (int i = 0; i < scount; ++i)
//		free(sarray[i]);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	//char* s = (char*)malloc(1);
//	//printf(" %p %p\n", s, "exit");
//	//printf("%d\n", s == "exit");
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		printf("문자열 입력:");
//		gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//		char* s = (char*)malloc(strlen(buf) + 1);
//		strcpy_s(s, strlen(buf) + 1, buf);
//
//		if (s[0] == "exit"[0] &&
//			s[1] == "exit"[1] &&
//			s[2] == "exit"[2] &&
//			s[3] == "exit"[3] &&
//			s[4] == "exit"[4]) //s == "exit" 주소 비교
//			break;
//		else
//		{
//			sarray[scount++] = s;
//			printf("string : %s\n", s);
//		}
//	}
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	char* sarray[1000] = { NULL };
//	int scount = 0;
//
//	while (1)
//	{
//		char buf[1000];
//		printf("문자열 입력:");
//		gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//		char* s = (char*)malloc(strlen(buf) + 1);
//		strcpy_s(s, strlen(buf) + 1, buf);
//
//		if (1)
//		{
//			sarray[scount++] = s;
//			printf("string : %s\n", s);
//		}
//	}
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	char buf[1000];
//	printf("문자열 입력:");
//	gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//	char* s = (char*)malloc(strlen(buf) + 1);
//	strcpy_s(s, strlen(buf) + 1, buf);
//
//	printf("string : %s\n", s);
//}

//#include <stdio.h>
//
//int main()
//{
//	char buf[1000];
//	printf("문자열 입력:");
//	gets_s(buf, 1000); //scanf_s() : "hello world!"
//
//	printf("string : %s\n", buf);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//
//int main()
//{
//	int* p = (int*)malloc(sizeof(int) * 100);
//	memset(p, 0, sizeof(int) * 100); // 400byte => 0
//
//	for (int i = 0; i < 100; ++i)
//		printf("%d ", p[i]);
//
//	free(p);
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//
//int main()
//{
//	int* p =(int*) malloc(sizeof(int) * 100);
//	memset(p, 0, sizeof(int) * 100); // 400byte => 0
//
//	for (int i = 0; i < 100; ++i)
//		printf("%d ", p[i]);
//
//	free(p);
//}
