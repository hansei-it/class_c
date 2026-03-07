#include <stdio.h>
int main()
{
  int arr[4] = { 10,20,30,40 };

  int* p = &arr[0];
  printf("%d\n", *(p + 0));
  printf("%d\n", *(p + 1));
  printf("%d\n", *(p + 2));
  printf("%d\n", *(p + 3));
  printf("\n");
  printf("%d\n", p[0]);
  printf("%d\n", p[1]);
  printf("%d\n", p[2]);
  printf("%d\n", p[3]);
  printf("\n");
}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d\n", arr[0]);
//  printf("%d\n", arr[1]);
//  printf("%d\n", arr[2]);
//  printf("%d\n", arr[3]);
//  printf("\n");
//  printf("%p\n", &arr[0]);
//  printf("%p\n", &arr[1]);
//  printf("%p\n", &arr[2]);
//  printf("%p\n", &arr[3]);
//  printf("\n");
//  int* p = &arr[0];
//  printf("%p\n", p+0);
//  printf("%p\n", p+1);
//  printf("%p\n", p+2);
//  printf("%p\n", p+3);
//  printf("\n");
//  printf("%d\n", *(p+0));
//  printf("%d\n", *(p+1));
//  printf("%d\n", *(p+2));
//  printf("%d\n", *(p+3));
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//
//  printf("%d %p", n, &n);
//  printf("%d %p", n - 1, &n - 1);
//  printf("%d %p", n - 2, &n - 2);
//  printf("%d %p", n - 3, &n - 3);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//
//  printf("%d %p", n, &n);
//  printf("%d %p", n + 1, &n + 1);
//  printf("%d %p", n + 2, &n + 2);
//  printf("%d %p", n + 3, &n + 3);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%p %p %p %p\n", &arr[0], &arr[1], &arr[2], &arr[3]);
//
//  // int* p;
//  // p = &arr[0];
//  int* p = &arr[0];
//  printf("%d\n", *p);
//
//  p = &arr[2];
//  printf("%d\n", *p);
//
//  *p = 100;
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//  int m = 20;
//  int* pn = &n;
//
//  printf("%d %p\n", *pn, pn);
//  pn = &m;
//  printf("%d %p\n", *pn, pn);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//  int* pn = &n;
//
//  printf("%d %d\n", n, *pn);
//  printf("%p %p\n", &n, pn);
//
//  printf("%d %d\n", sizeof(n), sizeof(pn));
//}

//#include <stdio.h>
//int TotalInteger(int a, int b)
//{
//  int sum = 0;
//  for (int i = a; i <= b; ++i)
//    sum += i;
//  return sum;
//}
//int main()
//{
//  int sum = 0;
//
//  sum = TotalInteger(1, 5);
//
//  printf("sum = %d\n", sum);
//  printf("sum = %d\n", TotalInteger(20,30) );
//}

//#include <stdio.h>
//int TotalInteger(int a, int b)
//{
//  int sum = 0;
//  for (int i = a; i <= b; ++i)
//    sum += i;
//  return sum;
//}
//int main()
//{
//  int sum = 0;
//
//  sum = TotalInteger(5, 1);
//
//  printf("sum = %d\n", sum);
//}

//#include <stdio.h>
//int TotalInteger()
//{
//  int sum = 0;
//  for (int i = 1; i <= 10; ++i)
//    sum += i;
//  return sum;
//}
//int main()
//{
//  int sum = 0;
//
//  sum = TotalInteger();
//
//  printf("sum = %d\n", sum);
//}

//#include <stdio.h>
//int TotalInteger()
//{
//  return 55;
//}
//int main()
//{
//  int sum = 0;
//  
//  sum = TotalInteger();
//
//  printf("sum = %d\n", sum);
//}

//#include <stdio.h>
//int main()
//{
//  int sum=0;
//  for (int i = 1; i <= 10; ++i)
//    sum += i;
//
//  printf("sum = %d\n", sum);
//}

//#include <stdio.h>
//int Sum(int a, int b)
//{
//  return a + b;
//}
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int sum = Sum(a, b);
//
//  printf("sum = %d\n", sum);
//  printf("sum = %d\n", Sum(1, 2));
//  printf("sum = %d\n", Sum(15, 15));
//}

//#include <stdio.h>
//int Sum(int _a, int _b)
//{
//  return _a + _b;
//}
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int sum = Sum(a, b);
//
//  printf("sum = %d\n", sum);
//  printf("sum = %d\n", Sum(1,2));
//  printf("sum = %d\n", Sum(15,15));
//}

//#include <stdio.h>
//int Sum(int _a, int _b)
//{
//  return _a + _b;
//}
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int sum = Sum(a,b);
//
//  printf("sum = %d\n", sum);
//}

//#include <stdio.h>
//void Print(int size,const char* s)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%d.%s\n", i + 1, s);
//}
//void main()
//{
//  Print(2,"ABC");
//  Print(3,"12345");
//  Print(5,"Hello~");
//}

//#include <stdio.h>
//void Print(int size)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%d.%s\n", i + 1, "Hello!");
//}
//void main()
//{
//  Print(2);
//  Print(3);
//  Print(5);
//}

//#include <stdio.h>
//void PrintHello(int size)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%d.Hello!\n", i + 1);
//}
//void main()
//{
//  PrintHello(2);
//  PrintHello(3);
//  PrintHello(5);
//}

//#include <stdio.h>
//void PrintHello(int size)
//{
//  for (int i = 0; i < 10; ++i)
//    printf("%d.Hello!\n", i + 1);
//}
//void main()
//{
//  PrintHello(2);
//  PrintHello(3);
//  PrintHello(5);
//}

//#include <stdio.h>
//void PrintHello()
//{
//  for (int i = 0; i < 10; ++i)
//    printf("%d.Hello!\n", i + 1);
//}
//void main()
//{
//  PrintHello();
//  PrintHello();
//  PrintHello();
//}

//#include <stdio.h>
//void PrintHello()
//{
//  for (int i = 0; i < 10; ++i)
//    printf("%d.Hello!\n", i + 1);
//}
//void main()
//{
//  PrintHello();
//}

//#include <stdio.h>
//
//void main()
//{
//  for (int i = 0; i < 10; ++i)
//    printf("%d.Hello!\n", i+1);
//}

//#include <stdio.h>
//
//void main()
//{
//  for (int i = 0; i < 10; ++i)
//    printf("%d.Hello!\n", i);
//}

//#include <stdio.h>
//
//void main()
//{
//  for (int i = 0; i < 10; ++i)
//    printf("Hello!\n");
//}
