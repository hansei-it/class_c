#include <stdio.h>
struct Data
{
	int n;
	double d;
};
void PrintData(const Data* pd) {
	printf("%d, %g\n", pd->n, pd->d);
}
void SetData(Data* pd, int n, double d) {
	pd->n = n;
	pd->d = d;
}
int main()
{
	Data darr[5] = { 0 };
	int arr[5] = { 10,20,30,40,50 };

	for (int i = 0; i < 5; ++i)
		SetData(&darr[i], i + 1, i + 10);

	for (int i = 0; i < 5; ++i)
		PrintData(&darr[i]);

	int* pa = arr;
	for (int i = 0; i < 5; ++i)
	{
		printf("int [%d] : %d\n", i, arr[i]);
	}
}

//#include <stdio.h>
////#define _WINDOWS_
//
//int main()
//{
//#ifdef _WINDOWS_
//	printf("windows OS Logo!\n");
//#else
//	printf("linux OS Logo!\n");
//#endif
//
//	int n = 100;
//
//	printf("int : %d\n", n);
//}

//
//#include <stdio.h>
//
////int Max(int a, int b)
////{
////	return a > b ? a : b;
////}
//#define Max(a, b) (((a)>(b)) ? (a) : (b))
//int main()
//{
//	int n1 = 10;
//	int n2 = 20;
//
//	printf("%d\n", Max(n1, n2));
//	printf("%d\n", Max(++n1, ++n2));
//	printf("%d, %d\n", n1, n2);
//}

//#include <stdio.h>
//
////int Max(int a, int b)
////{
////	return a > b ? a : b;
////}
//#define Max(a, b) (((a)>(b)) ? (a) : (b))
//int main()
//{
//	int n1 = 10;
//	int n2 = 20;
//
//	printf("%d\n", Max(n1, n2));
//	printf("%d\n", Max(++n1, ++n2));
//	printf("%d, %d\n", n1, n2);
//}


//#include <stdio.h>
//
//int Max(int a, int b)
//{
//	return a > b ? a : b;
//}
//int main()
//{
//	int n1 = 10;
//	int n2 = 20;
//
//	printf("%d\n", Max(n1, n2));
//
//	int result = n1 > n2 ? n1 : n2;
//	printf("%d\n", result);
//
//	n1 < n2 ? printf("Good!\n") : printf("Bad!\n");
//}

//#include <stdio.h>
//
//#define MAX		100
//#define Mul(a, b) ((a)*(b))
//int Multi(int a, int b)
//{
//	return a * b;
//}
//
//int main()
//{
//	int n1 = 2;
//	int n2 = 3;
//
//	printf("%d\n", Mul(n1 + n2, n1 + n2));
//	printf("%d\n", (n1 + n2 * n1 + n2));
//	printf("%d\n", Multi(n1 + n2, n1 + n2));
//}


//#include <stdio.h>
//
//#define MAX		100
//#define Mul(a, b) (a*b)
//int Multi(int a, int b)
//{
//	return a * b;
//}
//
//int main()
//{
//	int n1 = 2;
//	int n2 = 3;
//
//	printf("%d\n", Mul(n1 + n2, n1 + n2));
//	printf("%d\n", (n1 + n2 * n1 + n2));
//	printf("%d\n", Multi(n1 + n2, n1 + n2));
//}

//#include <stdio.h>
//
//#define MAX		100
//#define Add(a, b) (a+b)
//int Adder(int a, int b)
//{
//	return a + b;
//}
//
//int main()
//{
//	printf("%d\n", MAX);
//	printf("%d\n", 100);
//	printf("add : %d\n", Add(2, 3));
//	printf("add : %d\n", (2 + 3));
//}


//#include <stdio.h>
//
//#define MAX		100
//#define Add(a, b) (a+b)
//
//int main()
//{
//	printf("%d\n", MAX);
//	printf("%d\n", 100);
//	printf("add : %d\n", Add(2, 3));
//	printf("add : %d\n", (2+3));
//}

//#include <stdio.h>
//#include <string.h>
//
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wt");
//	fprintf(pf, "10 2.5 H ABC\n");
//	fclose(pf);
//
//	int n;
//	double d;
//	char c;
//	char s[100];
//
//	fopen_s(&pf, "test.txt", "rt");
//	fscanf_s(pf, "%d %lf %c %s", &n, &d, &c, 1, s, 100 );
//	fclose(pf);
//
//	printf("%d\n", n);
//	printf("%g\n", d);
//	printf("%c\n", c);
//	printf("%s\n", s);
//}

//#include <stdio.h>
//#include <string.h>
//
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wt");
//	fprintf(pf, "10 2.5 H ABC\n");
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "rt");
//	char buf[100];
//	fgets(buf, sizeof(buf), pf);
//	printf("size: %d, %s", strlen(buf), buf);
//	fclose(pf);
//
//	int n;
//	double d;
//	char c;
//	char s[100];
//	sscanf_s(buf, "%d %lf %c %s", &n, &d, &c, 1, s, 100);
//	printf("%d\n", n);
//	printf("%g\n", d);
//	printf("%c\n", c);
//	printf("%s\n", s);
//}
