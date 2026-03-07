#include <stdio.h>
void PrintString(const char* s)
{
  printf("string : %s\n", s);
}
int main()
{
  
  PrintString("Hello!"); // string : Hello!
  void (*pf)(const char* s);
  pf = PrintString;
  pf("Hello!");          // string : Hello!

}

//#include <stdio.h>
//int main()
//{
//  int a = 10, b = 20;
//  int result = a + b;
//
//  printf("result = %d\n", result);
//  printf("result = %d\n", result);
//  printf("result = %d\n", result);
//}

//#include <stdio.h>
//void PrintArray(int arr[], int size)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//}
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//  PrintArray(arr, 10);
//
//  int a = 10, b = 20;
//  int result = a + b;
//  printf("result = %d\n", result);
//  printf("result = %d\n", result);
//  printf("result = %d\n", result);
//}

//#include <stdio.h>
/////////////////////server code
//void PrintArray(int arr[], int size, void (*pf)(int))
//{
//  for (int i = 0; i < size; ++i)
//    pf(arr[i]); // ݹ (callback)
//  printf("\n");
//}
////////////////////client code
//void PrintPattern(int data)//callback function
//{
//  printf("%d\n", data);
//}
//void PrintPattern2(int data)
//{
//  printf("int : %d\n", data);
//}
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//
//  PrintArray(arr, 10, PrintPattern); //ȣ  (call)
//  PrintArray(arr, 10, PrintPattern2); //ȣ  (call)
//}

//#include <stdio.h>
/////////////////////server code
//void PrintArray(int arr[], int size, void (*pf)(int) )
//{
//  for (int i = 0; i < size; ++i)
//    pf(arr[i]);
//  printf("\n");
//}
////////////////////client code
//void PrintPattern(int data)
//{
//  printf("%d\n", data);
//}
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//
//  PrintArray(arr, 10, PrintPattern);
//}

//#include <stdio.h>
//void PrintArray(int arr[], int size)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//}
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//
//  PrintArray(arr, 10);
//  PrintArray(arr + 5, 3);
//  PrintArray(arr, 5);
//}

//#include <stdio.h>
//void PrintArray(int arr[], int size)
//{
//  for (int i = 0; i < size; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//}
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//
//  PrintArray(arr, 10);
//}

//#include <stdio.h>
//int main()
//{
//  int arr[10] = { 5,7,3,4,6,2,1,9,7,3 };
//
//  for (int i = 0; i < 10; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//  return a + b;
//}
//int Sub(int a, int b)
//{
//  return a - b;
//}
//int main()
//{
//  int (*pf)(int, int) = NULL;
//
//  pf = Add;
//  //or
//  //pf = Sub;
//
//  printf("%d\n", pf(5, 5));
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//  return a + b;
//}
//int Sub(int a, int b)
//{
//  return a - b;
//}
//int main()
//{
//  printf("main : %p\n", main);
//  printf("Add : %p\n", Add);
//  printf("Sub : %p\n", Sub);
//
//  void* pv = Add;
//  int (*pfunc)(int a, int b) = Add;
//  pfunc = Sub;
//
//  printf("%d\n", Sub(1, 2));
//  printf("%d\n", pfunc(1, 2));
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//  return a + b;
//}
//int Sub(int a, int b)
//{
//  return a - b;
//}
//int main()
//{
//  printf("main : %p\n", main);
//  printf("Add : %p\n", Add);
//  printf("Sub : %p\n", Sub);
//
//  printf("%d\n", Add(1, 2));
//}

//#include <stdio.h>
//int Add(int a, int b)
//{
//  return a + b;
//}
//int Sub(int a, int b)
//{
//  return a - b;
//}
//int main()
//{
//  int result = Add(10, 20);
//  printf("result : %d\n", result);
//
//  result = Sub(10, 20);
//  printf("result : %d\n", result);
//}



//#include <stdio.h>
//void PrintString(const char* str); //  Լ      
//int main()
//{
//  PrintString("Hello");
//
//  const char* s = "Hello";
//  PrintString(s);
//
//  char a[] = "Hello";
//  PrintString(a);
//}
//void PrintString(const char* str) //  Լ      (    )
//{
//  printf("%s", str);
//}

//#include <stdio.h>
//void PrintString(const char* str); //  Լ      
//void PrintString(const char* str) //  Լ      (    )
//{
//  printf("%s", str);
//}
//int main()
//{
//  PrintString("Hello");
//
//  const char* s = "Hello";
//  PrintString(s);
//
//  char a[] = "Hello";
//  PrintString(a);
//}



//#include <stdio.h>
//void PrintString(const char* str)
//{
//  printf("%s", str);
//}
//int main()
//{
//  PrintString("Hello");
//
//  const char* s = "Hello";
//  PrintString(s);
//
//  char a[] = "Hello";
//  PrintString(a);
//}

//#include <stdio.h>
//int main()
//{
//  printf("%s", "Hello");
//
//  const char* s = "Hello";
//  printf("%s", s);
//
//  char a[] = "Hello";
//  printf("%s", a);
//}

//#include <stdio.h>
//int main() // <= system(os)   ȣ   ϴ   Լ 
//{
//
//  return 0;
//}