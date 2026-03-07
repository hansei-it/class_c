#include <stdio.h>
int TotalSum(int arr[], int size)
{
  int sum = 0;
  for (int i = 1; i < size; ++i)
    sum += arr[i];

  return sum;
}
int main()
{
  int a = 10;
  int b = 20;
  int c = a + b;

  printf("%d + %d = %d\n", a, b, c);

  int arr[5] = { 4,5,2,3,100 };
  int result = TotalSum(arr, 5);

  printf("total = %d\n", result);
  
}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//char* InputString()
//{
//  char buffer[500];
//  printf("문자열 입력:");
//  gets_s(buffer, 500);
//
//  char* m = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(m, strlen(buffer) + 1, buffer);
//
//  return m;
//}
//int main()
//{
//  char* sArray[100] = { NULL };
//  int index = 0; 
//  while (1)
//  {
//    char* data = InputString();
//    if ( strcmp(data,"exit") == 0 )// data가 "exit" 라면..
//    {
//      free(data);
//      break;
//    }
//
//    sArray[index++] = data;
//  } 
//
//  for (int i = 0; i < index; ++i)
//    printf("string[%d] : %s\n", i, sArray[i]);
//
//  for (int i = 0; i < index; ++i)
//    free(sArray[i]);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//char* InputString()
//{
//  char buffer[500];
//  printf("문자열 입력:");
//  gets_s(buffer, 500);
//
//  char* m = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(m, strlen(buffer) + 1, buffer);
//
//  return m;
//}
//int main()
//{
//  char* sArray[100] = { NULL };
//
//  sArray[0] = InputString();
//  sArray[1] = InputString();
//  sArray[2] = InputString();
//
//  printf("string : %s\n", sArray[0]);
//  printf("string : %s\n", sArray[1]);
//  printf("string : %s\n", sArray[2]);
//
//  free(sArray[0]);
//  free(sArray[1]);
//  free(sArray[2]);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//char* InputString()
//{
//  char buffer[500];
//  printf("문자열 입력:");
//  gets_s(buffer, 500);
//
//  char* m = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(m, strlen(buffer) + 1, buffer);
//
//  return m;
//}
//int main()
//{
//  char* sArray[100] = { NULL };
//
//  sArray[0] = InputString();
//
//  printf("string : %s\n", sArray[0]);
//
//  free(sArray[0]);
//}

//#include <stdio.h>
//void PrintAddress(const char* s)
//{
//  //s[0] = 'a';
//  printf("pointer : %p\n", s);
//}
//void PrintString(const char* s)
//{
//  printf("string : %s\n", s);
//}
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//  char* s1 = arr;
//  char* s2 = s1;
//
//  PrintAddress(arr);
//  PrintString(arr);
//}


//#include <stdio.h>
//int main()
//{
//  char arr[] = "ABCDEF";
//  char* s1 = arr;
//  const char* s2 = arr;
//  const char* const s3 = arr;
//
//  s1[0] = 'Z'; //O
//  s1 = arr;    //O
//
//  s2[0] = 'Z'; //X
//  s2 = arr;    //O
//
//  s3[0] = 'Z'; //X
//  s3 = arr;    //X
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "ABCDEF";
//  char* s1 = arr;
//  const char* s2 = arr;
//
//  s1[0] = 'T'; //arr[0] = 'T';
//  s2[0];
//  printf("%s %s %s\n", arr, s1, s2);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "ABCDEF";
//  char* s1 = arr;
//  char* s2 = arr;
//
//  s1[0] = 'T'; //arr[0] = 'T';
//  printf("%s %s %s\n", arr, s1, s2);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "ABCDEF";
//  char* s1 = arr;
//  char* s2 = arr;
//
//  printf("%s %s %s\n", arr, s1, s2);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//  const int cn = 10;
//
//  printf("%d %d\n", n, cn);
//  n = 20;
//  cn = 20;
//  printf("%d %d\n", n, cn);
//}

//#include <stdio.h>
//void PrintAddress(const char* s)
//{
//  printf("pointer : %p\n", s);
//}
//void PrintString(const char* s)
//{
//  printf("string : %s\n", s);
//}
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//  char* s1 = arr;
//  char* s2 = s1;
//
//  PrintAddress(arr);
//  PrintString(arr);
//}

//#include <stdio.h>
//void PrintAddress(char* s)
//{
//  printf("pointer : %p\n", s);
//}
//void PrintString(char* s)
//{
//  printf("string : %s\n", s);
//}
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//  char* s1 = arr;
//  char* s2 = s1;
//
//  PrintAddress(arr);
//  PrintString(arr);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//  char* s1 = arr;
//  char* s2 = s1;
//
//  printf("%p %p %p\n", arr, s1, s2);
//  printf("%s %s %s\n", arr, s1, s2);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//
//  printf("%p %s\n", arr, arr);
//  printf("%p %s\n", arr+2, arr+2);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[5] = { 'A','B','C','D' };
//
//  printf("%p %s\n", arr, arr);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[4] = { 'A','B','C','D' };
//
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%c %c %c %c\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%p %p %p %p\n", &arr[0], &arr[1], &arr[2], &arr[3]);
//  printf("%p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3);
//  printf("%c %c %c %c\n", *arr, *(arr + 1), *(arr + 2), *(arr + 3));
//}

//#include <stdio.h>
//int main()
//{
//  char arr[4] = { 'A','B','C','D' };
//
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%c %c %c %c\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%p %p %p %p\n", &arr[0], &arr[1], &arr[2], &arr[3]);
//  printf("%p %p %p %p\n", arr, arr+1, arr+2, arr+3);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[4] = { 'A','B','C','D' };
//
//  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//  printf("%c %c %c %c\n", arr[0], arr[1], arr[2], arr[3]);
//}

//#include <stdio.h>
//int main()
//{
//  char c = 255;
//  int n = 255;
//
//  printf("%d %d\n", c, n);
//}

//#include <stdio.h>
//int main()
//{
//  char c = 128;
//  int n = 128;
//
//  printf("%d %d\n", c, n);
//}

//#include <stdio.h>
//int main()
//{
//  char c = 0x41;
//  int n = 0x41;
//
//  printf("%d %d\n", c, n);
//  printf("%c %c\n", c, n);
//  printf("char : %d, int : %d\n", sizeof(char), sizeof(int));
//  printf("char : %d, int : %d\n", sizeof(c), sizeof(n));
//}

//#include <stdio.h>
//int main()
//{
//  char c = 0x41;
//  int n = 0x41;
//
//  printf("%d %d\n", c, n);
//  printf("%c %c\n", c, n);
//}

//#include <stdio.h>
//int main()
//{
//  char c = 65;
//  int n = 65;
//
//  printf("%d %d\n", c, n);
//  printf("%c %c\n", c, n);
//}

//#include <stdio.h>
//int main()
//{
//  char c = 'A';
//  int n = 'A';
//
//  printf("%d %d\n", c, n);
//  printf("%c %c\n", c, n);
//}
