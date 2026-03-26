#include <stdio.h>
int main()
{
	int s1[] = { 'A','B','C','D','E','\0' };

	printf("%s\n", s1);
}

//#include <stdio.h>
//int main()
//{
//	int* s1 = "ABCDE";
//
//	printf("%s\n", s1);
//}

//#include <stdio.h>
//int main()
//{
//	char* s1 = "ABCDE";
//	//char* s2 = "ABCDE";
//	char s2[] = "ABCDE";
//
//	printf("%d\n", s1 == s2);
//}

//#include <stdio.h>
//#include <string.h>
//void ustrcpy(char dest[], char* src)
//{
//	int slen = strlen(src); //sizeof(s);
//	for (int i = 0; i < slen + 1; ++i)
//		dest[i] = src[i];
//}
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//	char cs[100];
//	//strcpy_s(cs, strlen(s)+1, s);
//	ustrcpy(cs, s);
//
//	printf("%s, %s\n", s, cs);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//	char cs[100];
//	int slen = strlen(s); //sizeof(s);
//	for (int i = 0; i < slen + 1; ++i)
//		cs[i] = s[i];
//
//	printf("length : %d\n", slen);
//	printf("%s, %s\n", s, cs);
//}

//#include <stdio.h>
//int main()
//{
//	int* p = NULL; //널 포인터
//	char c = '\0'; //널 문자
//	char* s = "";  //널 문자열
//
//
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "";
//	char cs[100];
//
//	int i = 0;
//	do {
//		cs[i] = s[i++];
//	} while (s[i-1]);
//
//	printf("%s %s\n", cs, s);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//	char cs[100];
//
//	for (int i = 0; cs[i] = s[i]; ++i)
//		; //empty...
//
//	printf("%s %s\n", cs, s);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//
//	int smallAlpha = 0;
//	int largeAlpha = 0;
//	for (int i = 0; s[i]; ++i)
//	{
//		if ('A' <= s[i] && s[i] <= 'Z')
//			++largeAlpha;
//		else if ('a' <= s[i] && s[i] <= 'z')
//			++smallAlpha;
//	}
//
//	printf("소문자는 %d개입니다.\n", smallAlpha);
//	printf("대문자는 %d개입니다.\n", largeAlpha);
//}


//#include <stdio.h>
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//
//	int largeAlpha = 0;
//	for (int i = 0; s[i]; ++i)
//		if ('A' <= s[i] && s[i] <= 'Z')
//		{
//			++largeAlpha;
//		}
//
//	printf("대문자는 %d개입니다.\n", largeAlpha);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABCsefsafeDEF*(34";
//
//	int largeAlpha = 0;
//	for(int i = 0 ; s[i] ; ++i)
//		if (s[i] == "대문자")
//		{
//			++largeAlpha;
//		}
//
//	printf("대문자는 %d개입니다.\n", largeAlpha);
//}


//#include <stdio.h>
//int main()
//{
//	printf("%c %c\n", '0', '1');
//	printf("%d %d\n", '0', '1');
//	printf("%d\n", '1' - '0');
//	printf("%d\n", '0'+1);
//}

//#include <stdio.h>
//int main()
//{
//	printf("%c %c\n", 'A', 'a');
//	printf("%d %d\n", 'A', 'a');
//	printf("%d\n", 'A'-'a');
//}

//#include <stdio.h>
//int main()
//{
//	int n = 65;
//	printf("%d %c\n", n, n); //%x, %o
//
//	n = 0x41;
//	printf("%d %c\n", n, n);
//
//	n = 0101;
//	printf("%d %c\n", n, n);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//	char a[4] = "ABC";
//
//	s = "DEH";
//	//a = "DEH";
//	a[0] = 'D';
//	a[1] = 'E';
//	a[2] = 'H';
//	a[3] = 'Z';
//	printf("%s\n", s);
//	printf("%s\n", a);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//	char a[] = "ABC";
//	
//	//s[0] = 'Z';
//	a[0] = 'Z';
//	printf("%s\n", s);
//	printf("%s\n", a);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//	char a[] = "ABC";
//	char b[4] = { 'A','B','C','\0' };
//	char c[4] = { 65,66,67,0 };
//	
//	printf("%s\n", s);
//	printf("%s\n", a);
//	printf("%s\n", b);
//	printf("%s\n", c);
//}

//#include <stdio.h>
//int main()
//{
//	const char* s = "ABC";
//
//	printf("%c\n", s[0]);
//	s[0] = 'Z';
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//
//	printf("%c\n", s[0]);
//	s[0] = 'Z';
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//
//	printf("NULL '\\0' : %d\n", '\0');
//
//	for (int i = 0; s[i] ; ++i)
//	//for (int i = 0; s[i] != '\0'; ++i)
//		printf("%d %c\n", s[i], s[i]);
//}


//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//
//	for(int i = 0 ; i < 3 ; ++i)
//		printf("%d %c\n", s[i], s[i]);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABC";
//
//	printf("%d %c\n", s[0], s[0]);
//	printf("%d %c\n", s[1], s[1]);
//	printf("%d %c\n", s[2], s[2]);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "Hello!";
//
//	printf("%s %p\n", s, s);
//	printf("%s %p\n", s + 1, s + 1);
//	printf("%c %c\n", *s, s[0]);
//}

//#include <stdio.h>
//int main()
//{
//	const char* s = "Hello!";
//
//	printf("%s\n", s);
//	printf("%s\n", "Hello!");
//	printf("%p\n", s);
//	printf("%p\n", "Hello!");
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "Hello!";
//
//	printf("%s\n", s);
//	printf("%s\n", "Hello!");
//	printf("%p\n", s);
//	printf("%p\n", "Hello!");
//}

//#include <stdio.h>
//int Min(int arr[], int size) //int* arr, int arr[100]
//{
//	if (size <= 0)
//		return -1;
//
//	int minIndex = 0;
//	for (int i = 1; i < size; ++i)
//		if (arr[minIndex] > arr[i])
//			minIndex = i;
//	return minIndex;
//}
//int main()
//{
//	int arr[] = { 54,70,32,20,15,68,90,94 };
//	int size = 8;
//
//	int idx = Min(arr, size);
//	if (idx != -1)
//		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
//}

//#include <stdio.h>
//int Min(int* arr, int size)
//{
//	if (size <= 0)
//		return -1;
//
//	int minIndex = 0;
//	for (int i = 1; i < size; ++i)
//		if (arr[minIndex] > arr[i])
//			minIndex = i;
//	return minIndex;
//}
//int main()
//{
//	int arr[] = { 54,70,32,20,15,68,90,94 };
//	int size = 8;
//
//	int idx = Min(arr, size);
//	if (idx != -1)
//		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
//}

//#include <stdio.h>
//int Min(int* arr, int size)
//{	
//	return 3;
//}
//int main()
//{
//	int arr[] = { 54,70,32,20,15,68,90,94 };
//	int size = 8;
//
//	int idx = Min(arr, size);
//	if( idx != -1)
//		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
//}

//#include <stdio.h>
//int Min(int* arr, int size)
//{
//	int minValue = 0xfffffff;
//	for (int i = 0; i < size; ++i)
//		if( minValue > arr[i])
//			minValue = arr[i];
//
//	return minValue;
//}
//int main()
//{
//	int arr[] = { 54,70,32,20,15,68,90,94 };
//	int size = 8;
//
//	int value = Min(arr, size);
//	printf("가장 작은 원소 : %d\n", value);
//}

//#include <stdio.h>
//int Min(int* arr, int size)
//{
//	int minValue = -0xfffffff;
//	return minValue;
//}
//int main()
//{
//	int arr[] = { 54,70,32,20,15,68,90,94 };
//	int size = 8;
//
//	int value = Min(arr, size);
//	printf("가장 작은 원소 : %d\n", value);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[ ] = { 10,20,30,40,50 };
//	printf("array size : %d\n", sizeof(arr));
//	printf("element size : %d\n", sizeof(arr[0]));
//	printf("array count : %d\n", sizeof(arr) / sizeof(int));
//
//	int* pa = arr;
//	printf("%p %p\n", pa, arr);
//	printf("%d %d\n", pa[0], arr[0]);
//	printf("%d %d\n", sizeof(pa), sizeof(arr));
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	printf("array size : %d\n", sizeof(arr));
//	printf("element size : %d\n", sizeof(arr[0]));
//	printf("array count : %d\n", sizeof(arr)/sizeof(int));
//
//	int* pa = arr;
//	printf("%p %p\n", pa, arr);
//	printf("%d %d\n", pa[0], arr[0]);
//	printf("%d %d\n", sizeof(pa), sizeof(arr));
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	int* pa = arr;
//
//	for (int i = 0; i < 4; ++i)
//		printf("%d %d\n", pa[i], pa[3 - i]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	int* pa = arr + 3;
//
//	printf("%d\n", pa[0]);
//	printf("%d\n", pa[-1]);
//	printf("%d\n", pa[-2]);
//	printf("%d\n", pa[-3]);
//	printf("\n");
//	printf("%d\n", pa[3-0]);
//	printf("%d\n", pa[3-1]);
//	printf("%d\n", pa[3-2]);
//	printf("%d\n", pa[3-3]);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//	for (int i = 0; i < size; ++i)
//		printf("%d\n", pa[i]);
//	printf("\n");
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	PrintArray(arr, 2);
//	PrintArray(arr + 2, 2);
//	PrintArray(arr+1, 3);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//	for(int i = 0 ; i < size ; ++i)
//		printf("%d\n", pa[i]);
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	PrintArray(arr, 4);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//	printf("%d\n", pa[0]);
//	printf("%d\n", pa[1]);
//	printf("%d\n", pa[2]);
//	printf("%d\n", pa[3]);
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	PrintArray(arr, 4);
//}


//#include <stdio.h>
//void PrintArray(int* pa)
//{
//	printf("%d\n", pa[0]);
//	printf("%d\n", pa[1]);
//	printf("%d\n", pa[2]);
//	printf("%d\n", pa[3]);
//
//}
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	PrintArray(arr);
//}

//#include <stdio.h>
//int main()
//{
//	int n = 100;
//	int arr[4] = { 10,20,30,40 };
//
//	int* pa = &n;
//	int* pb = arr;
//
//	printf("%p %p\n", pa, pb);
//}


//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	
//	printf("%p %p\n", &arr[0], arr);
//	printf("%p %p\n", &arr[0]+1, arr+1);
//}
//
//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	int* p = &arr[0];
//
//	printf("%d %d\n", *p, p[0]);
//	printf("%d %d\n", *(p+1), p[1]);
//	printf("%d %d\n", *(p+2), p[2]);
//	printf("%d %d\n", *(p+3), p[3]);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	int* p = &arr[0];
//
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr[1]);
//	printf("%p\n", &arr[2]);
//	printf("%p\n", &arr[3]);
//	printf("\n");
//	printf("%p %d\n", p, *(p+0));
//	printf("%p %d\n", p + 1, *(p+1));
//	printf("%p %d\n", p + 2, *(p+2));
//	printf("%p %d\n", p + 3, *(p+3));
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//	int* p = &arr[0];
//
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr[1]);
//	printf("%p\n", &arr[2]);
//	printf("%p\n", &arr[3]);
//	printf("\n");
//	printf("%d\n", *p);
//}

//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr[1]);
//	printf("%p\n", &arr[2]);
//	printf("%p\n", &arr[3]);
//	printf("\n");
//	printf("%p\n", &arr[0]+1);
//	printf("%p\n", &arr[1]+1);
//	printf("%p\n", &arr[2]+1);
//	printf("%p\n", &arr[3]+1);
//}

//#include <stdio.h>
//int main()
//{
//	short n = 100;
//	short* p = &n;
//
//	printf("%p %p\n", &n, p);
//	printf("%p %p\n", &n + 1, p+1);
//	printf("%p %p\n", &n - 1, p-1);
//}

//#include <stdio.h>
//int main()
//{
//	short n = 100;
//
//	printf("%p \n", &n);
//	printf("%p \n", &n+1);
//	printf("%p \n", &n-1);
//}
