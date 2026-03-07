#include <stdio.h>
void PrintHello(int size)
{
  for (int i = 0; i < size; ++i)
    printf("%d.Hello!\n", i + 1);
}
int main()
{
  PrintHello(5);
  PrintHello(3);
  PrintHello(10);
}

//#include <stdio.h>
//void PrintHello(int size)
//{
//  for(int i = 0 ; i < size ; ++i)
//    printf("%d.Hello!\n", i+1);
//}
//int main()
//{
//  PrintHello(5);
//  PrintHello(3);
//}

//#include <stdio.h>
//void PrintHello()
//{
//  printf("1.Hello!\n");
//  printf("2.Hello!\n");
//  printf("3.Hello!\n");
//  printf("4.Hello!\n");
//  printf("5.Hello!\n");
//}
//int main()
//{
//  PrintHello();
//  PrintHello();
//}


//#include <stdio.h>
//int main()
//{
//  printf("1.Hello!\n");
//  printf("2.Hello!\n");
//  printf("3.Hello!\n");
//  printf("4.Hello!\n");
//  printf("5.Hello!\n");
//}

//#include <stdio.h>
//int main()
//{
//  double arr[4] = { 10,20,30,40 };
//
//  for(int i = 0 ; i < 4 ; ++i)
//    printf("%p %g\n", &arr[i], arr[i]);
//}

//#include <stdio.h>
//int main()
//{
//  double arr[4] = { 10,20,30,40 };
//
//  printf("%p %g\n", &arr[0], arr[0]);
//  printf("%p %g\n", &arr[1], arr[1]);
//  printf("%p %g\n", &arr[2], arr[2]);
//  printf("%p %g\n", &arr[3], arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  double arr[4] = { 10,20,30,40 };
//
//  printf("%d %d\n", sizeof(arr), sizeof(arr[0]));
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %d\n", sizeof(arr), sizeof(arr[0]));
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d\n", *&arr[0]);
//  printf("%d\n", *&arr[1]);
//  printf("%d\n", *&arr[2]);
//  printf("%d\n", *&arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%p\n", &arr[0]);
//  printf("%p\n", &arr[1]);
//  printf("%p\n", &arr[2]);
//  printf("%p\n", &arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d\n", arr[0]);
//  printf("%d\n", arr[1]);
//  printf("%d\n", arr[2]);
//  printf("%d\n", arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int c = 30;
//  int d = 40;
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %d %d %d\n", a, b, c, d);
//  
//  for(int i = 0 ; i < 4 ; ++i)
//    printf("%d ", arr[i]);
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int c = 30;
//  int d = 40;
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %d %d %d\n", a, b, c, d);
//  printf("%d ", arr[0]);
//  printf("%d ", arr[1]);
//  printf("%d ", arr[2]);
//  printf("%d ", arr[3]);
//  printf("\n");
//}



//#include <stdio.h>
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int c = 30;
//  int d = 40;
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %d %d %d\n", a, b, c, d);
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//}
//

//#include <stdio.h>

//int main()
//{
//  int a = 10;
//  int b = 20;
//  int c = 30;
//  int d = 40;
//
//  printf("%d %d %d %d\n", a, b, c, d);
//}

//#include <stdio.h>
//int main()
//{
//  double d = 4.55;
//  double* pd = NULL;
//
//  pd = &d;
//
//  *pd = 3.14;
//
//  printf("%p %p\n", &d, pd);
//  printf("%g %g\n", *&d, *pd);
//  printf("%g %g\n", d, *pd);
//}


//#include <stdio.h>
//int main()
//{
//  double d = 4.55;
//  double* pd = NULL;
//
//  pd = &d;
//
//  printf("%p %p\n", &d, pd);
//  printf("%g %g\n", *&d, *pd);
//  printf("%g %g\n", d, *pd);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 100;
//  int* pa = &n;
//
//  printf("%d %p\n", n, pa);
//  printf("%d %p\n", n, &n);
//  printf("%d %d\n", n, *pa);
//}


//#include <stdio.h>
//int main()
//{
//  int n = 100;
//  int* pa = &n;
//
//  printf("%d %p\n", n, pa);
//  printf("%d %p\n", n, &n);
//}


//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  for (int i = 1; i <= 10; i += 1)
//  {
//    if (i % 5 == 0)
//      sum += i;
//  }
//
//  printf("Sum = %d\n", sum);
//}

//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  for (int i = 1; i <= 10; i += 1)
//  {
//    if (i % 2 == 0)
//      sum += i;
//  }
//
//  printf("Sum = %d\n", sum);
//}

//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  for (int i = 2; i <= 10; i += 2)
//  {
//    sum += i;
//  }
//
//  printf("Sum = %d\n", sum);
//}

//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//  
//  for (int i = 1; i <= 10; ++i)
//  {
//    sum += i;
//  }
//
//  printf("Sum = %d\n", sum);
//}


//#include <stdio.h>

//int main()
//{
//  int sum = 0;
//  int i = 1;
//
//  for (; i <= 10; ++i)
//  {
//    sum += i;
//  }
//
//  printf("Sum = %d\n", sum);
//}
