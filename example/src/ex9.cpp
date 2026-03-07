#include <stdio.h>

int main()
{
  //주소의 형식 변환
  char c = 'A';
  int n = 10;
  double d = 4.5;
  
  void* pv = NULL;
  pv = &c;
  printf("%c", *(char*)pv);

  pv = &n;
  printf("%d", *(int*)pv);

  pv = &d;
  printf("%g", *(double*)pv);
}

//#include <stdio.h>
//
//int main()
//{
//  //주소의 형식 변환
//  char c = 'A';
//  int n = 10;
//  double d = 4.5;
//
//  printf("%c %d %g\n", c, n, d);
//  printf("%p %p %p\n", &c, &n, &d);
//  printf("%p %p %p\n", &c + 1, &n + 1, &d + 1);
//  printf("%p %p %p\n", 
//    (char*) & c + 1, (int*) & n + 1, (double*) & d + 1);
//  printf("%p %p %p\n", 
//    (int*) & c + 1, (double*) & n + 1, (char*) & d + 1);
//
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//void InputString(char** ps)
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  char* s = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(s, strlen(buffer) + 1, buffer);
//
//  *ps = s; //return s;
//}
//int main()
//{
//  char* s = NULL;
//   
//  InputString(&s);
//
//  printf("string: %s\n", s);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//char* InputString()
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  char* s = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(s, strlen(buffer) + 1, buffer);
//
//  return s;
//}
//int main()
//{
//  char* s = InputString();
//
//  printf("string: %s\n", s);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main()
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  char* s = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(s, strlen(buffer) + 1, buffer);
//
//  printf("string: %s , %s\n", buffer, s);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main()
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  char* s = (char*)malloc(strlen(buffer) + 1);
//  strcpy_s(s, strlen(buffer)+1, buffer);
//
//  printf("string: %s , %s\n", buffer, s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//char* InputString()
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  return buffer ;
//}
//int main()
//{
//  char* s = InputString();
//
//  printf("string: %s\n", s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main()
//{
//  char buffer[100];
//  printf("문자열 입력:");
//  gets_s(buffer, 100);
//
//  printf("string: %s\n", buffer);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//#include <string.h> //strcpy_s() 선언
//
//void CopyString(char* dst, const char* src)
//{
//  strcpy_s(dst, strlen(src)+1, src);
//}
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  CopyString(s2, s1);
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//#include <string.h> //strcpy_s() 선언
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  strcpy_s(s2, 7, s1);
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//#include <string.h> //strcpy_s() 선언
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  strcpy_s(s2, 7, s1);
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  s2[0] = s1[0];
//  s2[1] = s1[1];
//  s2[2] = s1[2];
//  s2[3] = s1[3];
//  s2[4] = s1[4];
//  s2[5] = s1[5];
//  s2[6] = s1[6];
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  s2[0] = s1[0];
//  s2[1] = '\0';
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//int main()
//{
//  const char* s1 = "Hello!";
//  char* s2 = (char*)malloc(7);
//
//  //s2 = s1;
//  s2[0] = s1[0];
//  s2[1] = '\0';
//
//  printf("%s %s\n", s1, s2);
//
//  free(s2);
//}

//#include <stdio.h> //printf() 선언
//#include <stdlib.h> //malloc(), free() 선언
//int main()
//{
//  int* pn = (int*)malloc(sizeof(int));
//  *pn = 10; //Write
//  printf("int : %d\n", *pn); //Read
//  free(pn);
//}
