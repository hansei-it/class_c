#include <stdio.h>
void PrintArray(char* pa, int size)
{
  printf("size: %d\n", size);
  for (int i = 0; i < size; ++i)
    printf("%d : %c\n", pa[i], pa[i]);
}
void main()
{
  char arr[5] = { 'A', 'B', 'C', 'D', 'E' };
  PrintArray(arr, 5);

  char arr2[3] = { 'a', 'b', 'c' };
  PrintArray(arr2, 3);
}

//#include <stdio.h>
//void PrintArray(char* pa, int size)
//{
//  printf("size: %d\n", size);
//  for (int i = 0; i < size; ++i)
//    printf("%d : %c\n", pa[i], pa[i]);
//}
//void main()
//{
//  char arr[5] = { 'A', 'B', 'C', 'D', 'E'};
//  PrintArray(arr, 5);
//
//  char arr2[3] = { 'a', 'b', 'c'};
//  PrintArray(arr2, 3);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//  printf("size: %d\n", size);
//  for (int i = 0; i < size; ++i)
//    printf("%d\n", pa[i]);
//}
//void main()
//{
//  int arr[5] = { 10,20,30,40,50 };
//  PrintArray(arr, 5);
//
//  int arr2[3] = { 100,200,300 };
//  PrintArray(arr2, 3);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//  printf("size: %d\n", size);
//  for (int i = 0; i < size; ++i)
//    printf("%d\n", pa[i]);
//}
//void main()
//{
//  int arr[5] = { 10,20,30,40,50 };
//
//  PrintArray(arr, 5);
//}

//#include <stdio.h>
//void PrintArray(int* pa, int size)
//{
//  printf("size: %d\n", size);
//  printf("%d\n", pa[0]);
//  printf("%d\n", pa[1]);
//  printf("%d\n", pa[2]);
//  printf("%d\n", pa[3]);
//  printf("%d\n", pa[4]);
//}
//void main()
//{
//  int arr[5] = { 10,20,30,40,50 };
//
//  PrintArray( arr , 5);
//}

//#include <stdio.h>
//void PrintInteger(int* p)
//{
//  printf("%p : %d\n", p, *p);
//}
//void main()
//{
//  int n = 100;
//
//  PrintInteger(&n); // 100
//  printf("%p\n", &n);
//}

//#include <stdio.h>
//void PrintInteger(int* p)
//{
//  printf("%d\n", *p);
//}
//void main()
//{
//  int n = 100;
//
//  PrintInteger(&n); // 100
//}

//#include <stdio.h>
//void PrintInteger(int n)
//{
//  printf("%d\n", n);
//}
//void main()
//{
//  int n = 100;
//
//  PrintInteger(n); // 100
//}

//#include <stdio.h>
//void PrintPerson(const char* name, int age, const char* phone)
//{
//  printf(" ̸ : %s\n", name);
//  printf("    : %d\n", age);
//  printf("  ȭ  ȣ: %s\n", phone);
//  printf("\n");
//}
//int main()
//{
//  PrintPerson("ȫ 浿", 25, "010-1234-1212");
//  PrintPerson(" ̸   ", 30, "010-5678-1212");
//  PrintPerson(" Ӳ   ", 29, "010-1234-3456");
//}

//#include <stdio.h>
//void PrintPerson(const char* name, int age, const char* phone)
//{
//  printf(" ̸ : %s\n", name);
//  printf("    : %d\n", age);
//  printf("  ȭ  ȣ: %s\n", phone);
//  printf("\n");
//}
//int main()
//{
//  PrintPerson("ȫ 浿", 25, "010-1234-1212");
//}

//#include <stdio.h>
//void PrintHong(void)
//{
//  printf(" ̸ : ȫ 浿\n");
//  printf("    : 25\n");
//  printf("  ȭ  ȣ: 010-1234-1212\n");
//  printf("\n");
//}
//int main()
//{
//  PrintHong();
//  PrintHong();
//  PrintHong();
//}

//#include <stdio.h>
//void PrintHong(void)
//{
//  printf(" ̸ : ȫ 浿\n");
//  printf("    : 25\n");
//  printf("  ȭ  ȣ: 010-1234-1212\n");
//  printf("\n");
//}
//int main()
//{
//  PrintHong();
//}

//#include <stdio.h>
//int main()
//{
//  printf(" ̸ : ȫ 浿\n");
//  printf("    : 25\n");
//  printf("  ȭ  ȣ: 010-1234-1212\n");
//}

//#include <stdio.h>
//
//int main()
//{
//  int arr[4] = { 100 };
//
//  printf("%p %p\n", &arr[0], arr);
//
//  int* p1 = &arr[0];
//  int* p2 = arr;
//
//  printf("%d %d\n", p1[0], p2[0]);
//  printf("%d %d\n", *p1, *p2);
//}

//#include <stdio.h>
//
//int main()
//{
//  int arr[4] = { 0 };
//
//  printf("%d\n", arr[0]);
//  printf("%d\n", arr[1]);
//  printf("%d\n", arr[2]);
//  printf("%d\n", arr[3]);
//}

//#include <stdio.h>
//
//int main()
//{
//  //int arr[4] = { 1,2,3,4 };
//  //int arr[] = { 1,2,3,4 };
//  int arr[ 4 ] = { 1,2 };
//
//  printf("%d\n", arr[0]);
//  printf("%d\n", arr[1]);
//  printf("%d\n", arr[2]);
//  printf("%d\n", arr[3]);
//}

//#include <stdio.h>
//#define SIZE 10
//
//int main()
//{
//  int arr[SIZE] = { 10,20,30,40 };
//  int* p = &arr[SIZE - 1];
//
//  for (int i = 0; i < SIZE; ++i)
//  {
//    printf("%d\n", p[-(SIZE - 1 - i)]);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[4 - 1];
//
//  for (int i = 0; i < 4; ++i)
//  {
//    printf("%d\n", p[-(4-1-i)] );
//  }
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[4-1];
//
//  for (int i = 0; i < 4; ++i)
//  {
//    printf("%d %d\n", i, 4 - 1 - i);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[3];
//
//  for (int i = 0; i < 4; ++i)
//  {
//    printf("%d %d\n", i, 4-1-i);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[3];
//
//  for(int i = 3 ; i >= 0 ; --i)
//    printf("%d\n", p[-i]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[3];
//
//  printf("%d\n", p[-3]);
//  printf("%d\n", p[-2]);
//  printf("%d\n", p[-1]);
//  printf("%d\n", p[-0]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[3];
//
//  printf("%d %d %d %d\n",
//    p[-3], p[-2], p[-1], p[0]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[2];
//
//  printf("%d %d %d %d\n",
//    p[-2], p[-1], p[0], p[1]);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[2];
//
//  printf("%d %d %d %d\n",
//    p[-2], p[-1], p[0], p[1]);
//}

//#include <stdio.h>
//int main()
//{
//  /////////////
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[0];
//
//  for (int i = 0; i < 4; ++i)
//    printf("%d %d\n", arr[i], p[i]);
// 
//}

//#include <stdio.h>
//int main()
//{
//  /////////////
//  int arr[4] = { 10,20,30,40 };
//  int* p = &arr[0];
//  printf("%d %d\n", arr[0], p[0]);// 10
//  printf("%d %d\n", arr[1], p[1]);// 20
//  printf("%d %d\n", arr[2], p[2]);// 30
//  printf("%d %d\n", arr[3], p[3]);// 40
//}


//#include <stdio.h>
//int main()
//{
//  /////////////
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %p\n", arr[0], &arr[0]);// 10
//  printf("%d %p\n", arr[1], &arr[1]);// 20
//  printf("%d %p\n", arr[2], &arr[2]);// 30
//  printf("%d %p\n", arr[3], &arr[3]);// 40
//}

//#include <stdio.h>
//int main()
//{
//  /////////////
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d %p\n", arr[0]);// 10
//  printf("%d %p\n", arr[1]);// 20
//  printf("%d %p\n", arr[2]);// 30
//  printf("%d %p\n", arr[3]);// 40
//}

//#include <stdio.h>
//int main()
//{
//  /////////////
//  int arr[4] = { 10,20,30,40 };
//
//  printf("%d\n", arr[0]);// 10
//  printf("%d\n", arr[1]);// 20
//  printf("%d\n", arr[2]);// 30
//  printf("%d\n", arr[3]);// 40
//}
