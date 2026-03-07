#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char* s = (char*)malloc(sizeof(char) * 7);
  char arr[] = "Hello!";

  strcpy_s(s, 7, arr);

  printf("%s %s\n", s, arr);
  printf("%p %p\n", s, arr);

  free(s);
}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  char* s = (char*)malloc(sizeof(char) * 7);
//  char arr[] = "Hello!";
//
//  for (int i = 0; s[i] = arr[i] ; ++i)
//    ; //empty
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  char* s = (char*)malloc(sizeof(char) * 7);
//  char arr[] = "Hello!";
//
//  for (int i = 0; arr[i] != '\0'; ++i)
//    s[i] = arr[i];
//  s[6] = arr[6];
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  char* s = (char*)malloc(sizeof(char) * 7);
//  char arr[] = "Hello!";
//
//  for(int i = 0 ; i < 7 ; ++i)
//    s[i] = arr[i];
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  char* s = (char*)malloc(sizeof(char) * 7);
//  char arr[] = "Hello!";
//
//  s[0] = arr[0];
//  s[1] = arr[1];
//  s[2] = arr[2];
//  s[3] = arr[3];
//  s[4] = arr[4];
//  s[5] = arr[5];
//  s[6] = arr[6];
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  char* s = (char*)malloc(sizeof(char)*7);
//  char arr[] = "Hello!";
//  
//  ///////////////
//  //s = "Hello!";
//  s[0] = 'H';
//  s[1] = 'e';
//  s[2] = 'l';
//  s[3] = 'l';
//  s[4] = '0';
//  s[5] = '!';
//  s[6] = '\0';
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//
//  free(s);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  const char* s = "Hello!";
//  char arr[] = "Hello!";
//
//  printf("%s %s\n", s, arr);
//  printf("%p %p\n", s, arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//  printf("Hello!\n");
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int* p1 = (int*)malloc(sizeof(int));
//  int* p2 = (int*)malloc(sizeof(int)*5);
//
//  *p1 = 10; //p1[0] = 10;
//  *(p2 + 0) = 10;
//  *(p2 + 1) = 20;
//  *(p2 + 2) = 30;
//  *(p2 + 3) = 40;
//  *(p2 + 4) = 50;
//
//  printf("data : %d\n", p1[0]);
//  for (int i = 0; i < 5; ++i)
//    printf("%5d", p2[i]);
//  printf("\n");
//
//  free(p1);
//  free(p2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int* arr = (int*)malloc(sizeof(int) * 1024 * 1024);
//
//  for (int i = 0; i < 1024 * 1024; ++i)
//    arr[i] = i;
//
//  for (int i = 0; i < 10; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//
//  free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int* arr =(int*) malloc(sizeof(int)*1024*1024);
//
//  for (int i = 0; i < 1024 * 1024; ++i)
//    arr[i] = i ;
//
//  for (int i = 0; i < 10; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//
//  free(arr);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int arr[10] = { 0 };
//
//  for (int i = 0; i < 10; ++i)
//    printf("%5d", arr[i]);
//  printf("\n");
//}


//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  double* p = (double*)malloc(sizeof(double)); //1.     
//  if (p != NULL)
//  {
//    *p = 10.12345; //2.    (W)
//    printf("%g\n", *p); //2.    (R)
//    free(p); //3.     
//  }
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  double* p = (double*)malloc(sizeof(double)); //1.     
//  *p = 10.12345; //2.    (W)
//  printf("%g\n", *p); //2.    (R)
//  free(p); //3.     
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int* p = (int*)malloc(sizeof(int));
//  *p = 10;
//  printf("%d\n", *p);
//  free(p);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  int n = 10;
//  int* p1 = &n;
//  int* p2 = (int*)(void*)malloc(4);//1.
//  *p2 = 10;
//
//  printf("%d %d\n", *p1, *p2);
//
//  free(p2);//2.
//}


//#include <stdio.h>
//
//int main()
//{
//  //stack area
//  int n = 10;
//  int* p = &n;
//  const char* s = "Hello";
//  int arr[5] = { 10,20,30,40,50 };
//
//  printf("%d %d\n", n, *p);
//  printf("string : %s\n", s);
//
//  for (int i = 0; i < 5; ++i)
//    printf("%d\n", arr[i]);
//}
