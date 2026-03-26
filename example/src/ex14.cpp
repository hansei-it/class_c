#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
void Menu()
{
	puts("1. 정수 입력");
	puts("2. 모든 정수 출력");
	puts("3. 정수 찾기");
	puts("4. 정수 삭제");
	puts("===============");
}
void InputInteger(int arr[], int* pcount)
{
	int data = 0;
	printf("정수입력:");
	scanf_s("%d", &data);
	arr[(*pcount)++] = data;
}
void PrintInteger(const int arr[], int count)
{
	for (int i = 0; i < count; ++i)
		printf("[%d] : %d\n", i, arr[i]);
}
void SearchInteger(const int arr[], int count)
{
	int data = 0;
	printf("찾을 정수 입력:");
	scanf_s("%d", &data);
	for (int i = 0; i < count; ++i)
		if (data == arr[i])
		{
			printf("%d의 원소는 %d\n", i, arr[i]);
			break;
		}
}
void RemoveInteger(int arr[], int* pcount)
{
	int data = 0;
	printf("삭제할 정수 입력:");
	scanf_s("%d", &data);
	for (int i = 0; i < *pcount; ++i)
		if (data == arr[i])
		{
			for (int j = i; j < *pcount - 1; ++j)
				arr[j] = arr[j + 1];
			--*pcount;
			break;
		}
}
int main()
{
	int* arr = (int*)malloc(sizeof(int) * 1000);
	int count = 0;
	int run = 1;

	while (run)
	{
		Menu();
		switch (_getch())
		{
		case '1':
			InputInteger(arr, &count);
			break;
		case '2':
			PrintInteger(arr, count);
			break;
		case '3':
			SearchInteger(arr, count);
			break;
		case '4':
			RemoveInteger(arr, &count);
			break;
		default:
			printf("프로그램 종료!");
			run = 0;
			break;
		}
	}
	free(arr);
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <conio.h>
//void Menu()
//{
//	puts("1. 정수 입력");
//	puts("2. 모든 정수 출력");
//	puts("3. 정수 찾기");
//	puts("4. 정수 삭제");
//	puts("===============");
//}
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int) * 1000);
//	int count = 0;
//	int run = 1;
//
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			{
//				int data = 0;
//				printf("정수입력:");
//				scanf_s("%d", &data);
//				arr[count++] = data;
//			}
//			break;
//		case '2':
//			for (int i = 0; i < count; ++i)
//				printf("[%d] : %d\n", i, arr[i]);
//			break;
//		case '3':
//			{
//				int data = 0;
//				printf("찾을 정수 입력:");
//				scanf_s("%d", &data);
//				for (int i = 0; i < count; ++i)
//					if (data == arr[i])
//					{
//						printf("%d의 원소는 %d\n", i, arr[i]);
//						break;
//					}
//			}
//			break;
//		case '4':
//			{
//				int data = 0;
//				printf("삭제할 정수 입력:");
//				scanf_s("%d", &data);
//				for (int i = 0; i < count; ++i)
//					if (data == arr[i])
//					{
//						for (int j = i; j < count - 1; ++j)
//							arr[j] = arr[j + 1];
//						--count;
//						break;
//					}
//			}
//			break;
//		default:
//			printf("프로그램 종료!");
//			run = 0;
//			break;
//		}
//	}
//	free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <conio.h>
//void Menu()
//{
//	puts("1. 정수 입력");
//	puts("2. 모든 정수 출력");
//	puts("3. 정수 찾기");
//	puts("4. 정수 삭제");
//	puts("===============");
//}
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int) * 1000);
//	int count=0;
//	int run = 1;
//
//	while (run)
//	{
//		Menu();
//		switch (_getch())
//		{
//		case '1':
//			printf("메뉴1");
//			break;
//		case '2':
//			printf("메뉴2");
//			break;
//		case '3':
//			printf("메뉴3");
//			break;
//		case '4':
//			printf("메뉴4");
//			break;
//		default:
//			printf("프로그램 종료!");
//			run = 0;
//			break;
//		}
//	}
//	free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//int main()
//{
//	const char* s = "ABCDE";
//	char* buf = NULL;
//
//	buf = (char*)malloc(strlen(s) + 1);
//	strcpy_s(buf, strlen(s) + 1, s);
//	printf("string: %s\n", buf);
//
//	free(buf);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//int main()
//{
//	const char* s = "ABCDE";
//	char buf[100];
//
//	strcpy_s(buf, strlen(s) + 1, s);
//	printf("string: %s\n", buf);
//}


//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int) * 10);
//
//	for (int i = 0; i < 10; ++i)
//		arr[i] = i + 1;
//
//	for (int i = 0; i < 10; ++i)
//		printf("%d ", arr[i]);
//
//	free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int) * 10);
//
//	for (int i = 0; i < 10; ++i)
//		arr[i] = i+1;
//
//	for (int i = 0; i < 10; ++i)
//		printf("%d ", arr[i]);
//
//	free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int)*1000000);
//	for (int i = 0; i < 1000000; ++i)
//		arr[i] = i;
//
//	for (int i = 0; i < 1000000; ++i)
//		if( i%100000 == 0 )
//			printf("%d ", arr[i]);
//
//	free(arr);
//}


//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	int arr[1000000];
//	for (int i = 0; i < 1000000; ++i)
//		arr[i] = i;
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main() //함수
//{
//	double d=6.6;
//	printf("%g\n", d);
//
//	double* pd = (double*)malloc(sizeof(double));
//	*pd = 6.6;
//	printf("%g\n", *pd);
//	free(pd);
//}


//#include <stdio.h>
//#include <stdlib.h>
//int main() //함수
//{
//	double d = 6.6;
//	printf("%g\n", d);
//
//	double* pd = (double*)malloc(8);
//	*pd = 6.6;
//	printf("%g\n", *pd);
//	free(pd);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int main() //함수
//{
//	int* p = (int*)malloc(4);
//
//	*p = 100;
//	printf("%d\n", *p);
//
//	free(p);
//}

//#include <stdio.h>
//#include <string.h>
//int global_n = 100;// 전역변수
//void a() { } //함수
//int main() //함수
//{
//	int local_n = 10; //지역변수, stack변수
//	static int static_n = 20; //지역변수, static변수
//	const char* s = "ABC"; //"ABC" 상수문자열
//	int* p = malloc(sizeof(int)); //동적메모리(heap 메모리)
//
//	printf("%p\n", &global_n);
//	printf("%p\n", &static_n);
//	printf("%p\n", s);
//	printf("\n");
//	printf("%p\n", &local_n);
//	printf("%p\n", &s);
//	printf("%p\n", &p);
//	printf("\n");
//	printf("%p\n", p);
//	printf("\n");
//	printf("%p\n", main);
//	printf("%p\n", a);
//
//	free(p);
//}

//#include <stdio.h>
//#include <string.h>
//void PrintArray(const int arr[], int size)//*
//{
//	for (int i = 0; i < size; ++i)
//		printf("%d ", arr[i]);
//	printf("\n");
//}
//void ResetArray(int arr[], int size)//*
//{
//	for (int i = 0; i < size; ++i)
//		arr[i] = 0;
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	ResetArray(arr, 4);
//	PrintArray(arr, 4);
//}

//#include <stdio.h>
//#include <string.h>
//void PrintArray(const int arr[], int size)
//{
//	for (int i = 0; i < size; ++i)
//		printf("%d ", arr[i]);
//	printf("\n");
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	PrintArray(arr, 4);
//	printf("%d\n", arr[0]);
//}

//#include <stdio.h>
//#include <string.h>
//void PrintString(const char* s)
//{
//	printf("string: %s\n", s);
//}
//int main()
//{
//	char* s = "ABC";
//
//	PrintString(s);
//	PrintString("12345");
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	const char* s = "ABC";
//
//	printf("%c\n", *s); //Read
//	*s = 'Z';//Write
//
//	printf("string: %s\n", s);
//}


//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	int n = 10;
//	const int* const p = &n; //**
//
//	n = 100;
//	*p = 100;
//	int k = 20;
//	p = &k;
//	printf("%d %d\n", n, *p);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	int n = 10;
//	int* const p = &n; //**
//
//	n = 100;
//	*p = 100;     
//	int k = 20;
//	p = &k;
//	printf("%d %d\n", n, *p);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	int n = 10;
//	const int* p = &n; //**
//
//	n = 100;
//	//*p = 100;     X
//	int k = 20;
//	p = &k;
//	printf("%d %d\n", n, *p);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	int n = 10;
//	const int cn = 10;
//
//	printf("%d %d\n", n, cn);
//	n = 20;
//	cn = 30;
//	printf("%d %d\n", n, cn);
//}

// 
//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	//strcpy_s(); 복사
//	//strcat_s(); 붙이기
//	//strcmp();   비교
//	//strlen();   길이
//
//	char* a = "abc";
//	char* b = "ABCD";
//	char buf[100];
//
//	printf("%d %d\n", strlen(a), strlen(b));
//	strcpy_s(buf, strlen(a) + 1, a);
//	printf("%s\n", buf);
//	strcat_s(buf, strlen(a)+strlen(b) + 1, b);
//	printf("%s\n", buf);
//	printf("\n");
//	printf("%d\n", strcmp("ABC", "BAC"));
//	printf("%d\n", strcmp("ABC", "ABC"));
//	printf("%d\n", strcmp("ABC","AAAA"));
//}

//#include <stdio.h>
//#include <string.h>
//
//int ustrcmp(char* a, char* b)
//{
//	int na = strlen(a);// "AB";
//	int nb = strlen(b);// "AB";
//	if (na > nb)
//	{
//		na = nb;
//	}
//
//	int i = 0;
//	for (i = 0; i < na; ++i)
//	{
//		if (a[i] > b[i])
//			return 1;
//		else if (a[i] < b[i])
//			return -1;
//	}
//	if (a[i] == b[i])
//		return 0;
//	else if (a[i] == '\0')
//		return -1;
//	else
//		return 1;
//}
//int main()
//{
//	char* a = "abc";
//	char* b = "abc";
//	char* c = "abcd";
//	char* d = "BBC";
//
//	printf("%d\n", strcmp(a, b)); // 0
//	printf("%d\n", strcmp(a, c)); // -1
//	printf("%d\n", strcmp(a, d)); // 1
//}

//#include <stdio.h>
//#include <string.h>
//
//int ustrcmp(char* a, char* b)
//{
//	int na = strlen(a);// "AB";
//	int nb = strlen(b);// "AB";
//	if (na > nb)
//	{
//		na = nb;
//	}
//
//	int i=0;
//	for (i = 0; i < na; ++i)
//	{
//		if (a[i] > b[i])
//			return 1;
//		else if (a[i] < b[i])
//			return -1;
//	}
//	if (a[i] == b[i])
//		return 0;
//	else if (a[i] == '\0')
//		return -1;
//	else
//		return 1;
//}
//int main()
//{
//	char* a = "abc";
//	char* b = "abc";
//	char* c = "abcd";
//	char* d = "BBC";
//
//	printf("%d\n", strcmp(a, b)); // 0
//	printf("%d\n", strcmp(a, c)); // -1
//	printf("%d\n", strcmp(a, d)); // 1
//}

//#include <stdio.h>
//#include <string.h>
//
//int ustrcmp(char* a, char* b)
//{
//	return 0;
//}
//int main()
//{
//	char* a = "abc";
//	char* b = "abc";
//	char* c = "abcd";
//	char* d = "BBC";
//
//	printf("%d\n", strcmp(a, b)); // 0
//	printf("%d\n", strcmp(a, c)); // -1
//	printf("%d\n", strcmp(a, d)); // 1
//}

//#include <stdio.h>
//#include <string.h>
//
//int ustrcmp(char* a, char* b)
//{
//	if (strlen(a) != strlen(b))
//		return 0;
//
//	for (int i = 0; a[i]; ++i)
//		if (a[i] != b[i])
//			return 0;
//
//	return 1;
//}
//int main()
//{
//	char* a = "abc";
//	char* b = "abc";
//	char* c = "abcd";
//
//	printf("%d\n", ustrcmp(a, b));// 1
//	printf("%d\n", ustrcmp(a, c));// 0
//}
