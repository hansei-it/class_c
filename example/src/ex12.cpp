#include <stdio.h>
int main()
{
	int n = 10;

	printf("%p\n", &n);
	printf("%p\n", &n + 1);
	printf("%p\n", &n + 2);
	printf("%p\n", &n + 3);
	printf("\n");
	printf("%p\n", &n);
	printf("%p\n", &n - 1);
	printf("%p\n", &n - 2);
	printf("%p\n", &n - 3);
}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//
//	printf("%d %p\n", n, &n);
//	printf("%d %p\n", n+1, &n+1);
//}


//#include <stdio.h>
//int main()
//{
//	int arr[4] = { 10,20,30,40 };
//
//	printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//	for (int i = 0; i < 4; ++i)
//		printf("%d ", arr[i]);
//	printf("\n");
//}

//#include <stdio.h>
//void PrintDataValue(char c, int n, double d)
//{
//	printf("%d %d %g\n", c, n, d);
//}
//void PrintDataAddress(const char* pc,const int* pn,const double* pd)
//{
//	printf("%d %d %g\n", *pc, *pn, *pd);
//}
//int main()
//{
//	char c = 10;
//	int n = 10;
//	double d = 10;
//
//	PrintDataValue(c, n, d);
//	PrintDataAddress(&c, &n, &d);
//}

//#include <stdio.h>
//int Swap(int* pa, int* pb)
//{
//	int t = *pa;
//	*pa = *pb;
//	*pb = t;
//
//	return 203;
//}
//int main()
//{
//	int a = 10;
//	int b = 20;
//
//	printf("%d %d\n", a, b);
//	Swap(&a, &b);
//	printf("%d %d\n", a, b);
//}

//#include <stdio.h>
//int main()
//{
//	int a = 10;
//	int b = 20;
//
//	printf("%d %d\n", a, b);
//	int t = a;
//	a = b;
//	b = t;
//	printf("%d %d\n", a, b);
//}

//#include <stdio.h>
//void TotalInteger(int a, int b, int* psum)
//{
//	int sum = 0;
//	for (int i = a; i <= b; ++i)
//		sum += i;
//
//	*psum = sum;
//}
//int main()
//{
//	int sum = 0;
//	
//	TotalInteger(1, 10, &sum);
//	printf("sum : %d\n", sum);
//}

//#include <stdio.h>
//double TotalInteger(int a, int b)
//{
//	int sum = 0;
//	for (int i = a; i <= b; ++i)
//		sum += i;
//
//	return (double)sum;
//}
//int main()
//{
//	int sum = TotalInteger(1, 10);
//
//	printf("sum : %d\n", sum);
//}


//#include <stdio.h>
//
//int TotalInteger(int a, int b)
//{
//	int sum = 0;
//	for (int i = a; i <= b; ++i)
//		sum += i;
//	
//	return sum;
//}
//
//int main()
//{
//	int sum = TotalInteger(1, 10);
//
//	printf("sum :%d\n", sum);
//	printf("sum :%d\n", TotalInteger(1,10) );
//	printf("sum*2 : %d\n", sum * 2);
//}

//#include <stdio.h>
//// server
//void PrintHello(int size) //매개변수(parameter)
//{
//	for(int i = 0 ; i< size ; ++i)
//		printf("Hello! : %d\n", i+1);
//}
//// client
//int main()
//{
//	PrintHello( 10 ); //함수의 인수(arguments)
//}

//#include <stdio.h>
//
//void PrintHello()
//{
//	printf("Hello!\n");
//	printf("Hello!\n");
//	printf("Hello!\n");
//}
//int main()
//{
//	PrintHello();
//	PrintHello();
//}

//#include <stdio.h>
//int main()
//{
//	printf("Hello!\n");
//	printf("Hello!\n");
//	printf("Hello!\n");
//}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	int* p = &n;
//	int** pp = &p;
//
//	printf("%d %d %d\n", n, *p, **pp);
//	printf("%p %p %p\n", &n, p, *pp);
//}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	int* p = &n;
//
//	printf("%d %p\n", n, &n);
//	printf("%d %p\n", *p, p);
//
//	printf("size : %d\n", sizeof(p));
//}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	do
//	{
//		printf("int : %d\n", n);
//		++n;
//	} while (n < 5);
//}

//#include <stdio.h>
//int main()
//{
//	int n = 10;
//	while (n < 5)
//	{
//		printf("int : %d\n", n);
//		++n;
//	}
//}


//#include <stdio.h>
//int main()
//{
//	int size = 10;
//
//	for (int i = 0; i < size; ++i)
//	{
//		if (i % 3)
//			continue;
//
//		printf("%d\n", i);
//	}
//}

//#include <stdio.h>
//int main()
//{
//	int size = 10;
//
//	for (int i = 0; i < size; ++i)
//	{
//		if (i % 3)
//			continue;
//			
//		printf("%d\n", i);
//	}
//}


//#include <stdio.h>
//int main()
//{
//	int size = 10;
//
//	for (int i = 0; i < size; ++i)
//	{
//		if (i % 2 == 0)
//			printf("%d\n", i);
//	}
//}

//#include <stdio.h>
//int main()
//{
//	int flag = 1;
//
//	while (flag)
//	{
//		int data = 0;
//		printf("정수 입력: ");
//		scanf_s("%d", &data);
//
//		if (data >= 0)
//			printf("int : %d\n", data);
//		else
//			flag = 0;
//	}
//}

//#include <stdio.h>
//int main()
//{
//	while (1)
//	{
//		int data = 0;
//		printf("정수 입력: ");
//		scanf_s("%d", &data);
//
//		if (data >= 0)
//			printf("int : %d\n", data);
//		else
//			break;
//	}
//}

//#include <stdio.h>
//int main()
//{
//	for (int i = 0; i < 5; ++i)
//		printf("int : %d\n", i+1);
//}

//#include <stdio.h>
//int main()
//{
//	for(int i = 1 ; i <= 5 ; ++i)
//		printf("int : %d\n", i);
//}

//#include <stdio.h>
//int main()
//{
//	printf("int : %d\n", 1);
//	printf("int : %d\n", 2);
//	printf("int : %d\n", 3);
//	printf("int : %d\n", 4);
//	printf("int : %d\n", 5);
//}


//#include <stdio.h>
//int main()
//{
//	int score = 95;
//
//	switch (score / 10)
//	{
//	case 9:
//		printf("A\n");
//		break;
//	case 8:
//		printf("B\n");
//		break;
//	case 7:
//		printf("C\n");
//		break;
//	default:
//		printf("F\n");
//		break;
//	}
//}

//#include <stdio.h>
//int main()
//{
//	int score = 10;
//
//	if (score >= 90)
//		printf("A\n");
//	else if (score >= 80)
//		printf("B\n");
//	else if (score >= 70)
//		printf("C\n");
//	else
//		printf("F\n");
//}

//#include <stdio.h>
//int main()
//{
//	const char* s = "Hello!";
//
//	printf("%s\n", s);
//}