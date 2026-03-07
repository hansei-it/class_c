#include <stdio.h>
void f2()
{
  int b = 20;
}
void f1()
{
  int a = 10;

  f2();
}
int main()
{
  int m = 10;

  f1();
  f2();
}
//#include <stdio.h>
//int main()
//{
//  //메모리 저장소
//  // Code/Data Area
//  // 1. Global Data/ 2. Stack/ 3. Heap
//  int n = 10;
//  double d = 1.5;
//
//  int* pn = &n;
//  double* pd = &d;
//
//
//}

//#include <stdio.h>
//void PrintString(const char* s)
//{
//  printf("string : %s\n", s);
//}
//int main()
//{
//  const char* s = "ABC";
//
//  PrintString(s);
//}

//#include <stdio.h>
//int main()
//{
//  const char* s = "ABC";
//
//  printf("string : %s\n", s);
//  printf("string : %c\n", s[1]);
//  printf("string : %s\n", s + 1);
//  printf("string : %s\n", &s[1]);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "Hello!!";
//  char* s = arr;
//
//  printf("%s %s\n", s, arr);
//  s[1] = 'E';
//  printf("%s %s\n", s, arr);
//
//  for (int i = 0; s[i] ; ++i)
//    printf("%d %c\n", s[i], s[i]);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "Hello!!";
//  char* s = arr;
//
//  printf("%s %s\n", s, arr);
//  s[1] = 'E';
//  printf("%s %s\n", s, arr);
//
//  for (int i = 0; s[i] != '\0'; ++i)
//    printf("%d %c\n", s[i], s[i]);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[] = "Hello";
//  char* s = arr;
//
//  printf("%s %s\n", s, arr);
//  s[1] = 'E';
//  printf("%s %s\n", s, arr);
//
//  for (int i = 0; i < 5; ++i)
//    printf("%d %c\n", s[i], s[i]);
//}

//#include <stdio.h>
//int main()
//{
//  const char* s = "ABC";
//  char a[] = "ABC";
//
//  //s[0] = 'Z'; // X
//  a[0] = 'Z'; // O
//  printf("%p %p\n", s, a);
//  printf("%s %s\n", s, a);
//}

//#include <stdio.h>
//int main()
//{
//  const char* s = "ABC";
//  char a[] = "ABC";
//
//  s[0] = 'Z'; // X
//  a[0] = 'Z'; // O
//  printf("%p %p\n", s, a);
//  printf("%s %s\n", s, a);
//}

//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";
//  char a[] = "ABC";
//
//  s[0] = 'Z'; // X
//  a[0] = 'Z'; // O
//  printf("%p %p\n", s, a);
//  printf("%s %s\n", s, a);
//}

//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";
//  char a[] = "ABC";
//
//  printf("%p %p\n", s, a);
//  printf("%s %s\n", s, a);
//}

//#include <stdio.h>
//int main()
//{
//  //char arr[3] = "ABC";
//  char arr[3] = { 'A','B','C' };
//
//  printf("%s\n", arr);
//  printf("%s\n", &arr[0]);
//}


//#include <stdio.h>
//int main()
//{
//  char arr[] = "ABC";
//  //char arr[] = { 'A','B','C','\0' };
//
//  printf("%s\n", arr);
//  printf("%s\n", &arr[0]);
//}

//#include <stdio.h>
//int main()
//{
//  char arr[4] = "ABC";
//  //char arr[4] = { 'A','B','C','\0' };
//
//  printf("%s\n", arr);
//  printf("%s\n", &arr[0]);
//}

//#include <stdio.h>
//int main()
//{
//  //char arr[] = "ABC";
//  char arr[4] = { 'A','B','C','\0' };
//
//  printf("%s\n", arr);
//  printf("%s\n", &arr[0]);
//}

//#include <stdio.h>
//int main()
//{
//  //char arr[] = "ABC";
//  char arr[4] = {'A','B','C','\0'};
//
//  printf("%s\n", arr);
//}

//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";   //포인터
//  char arr[] = "ABC";//배열
//
//  printf("%s %s\n", s, arr);
//}


//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";
//
//  printf("%s %s\n", s, "ABC");
//  printf("%c %c\n", s[0], "ABC"[0]);
//  printf("%c %c\n", s[1], "ABC"[1]);
//}


//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";
//
//  printf("%s %s\n", s, "ABC");
//  printf("%c %c\n", s[0], "ABC"[0]);
//  printf("%c %c\n", s[1], "ABC"[1]);
//}

//#include <stdio.h>
//int main()
//{
//  char* s = "ABC";
//
//  printf("%p %p\n", s, "ABC");
//  printf("%s %s\n", s, "ABC");
//  printf("%p %p\n", s+1, "ABC"+1);
//  printf("%s %s\n", s+1, "ABC"+1);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 10;
//  int* p = &n;
//
//  printf("%d %d\n", n, *p); // 10 10
//  printf("%p %p\n", &n, &*p); // 10 10
//  printf("%d %d\n", *&n, *&*p); // 10 10
//}
