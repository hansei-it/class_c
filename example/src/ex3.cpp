//#include <stdio.h>
//int main()
//{
//  int a = 10;
//  int b = a++;
//
//  printf("a = %d\n", a);
//  printf("b = %d\n", b);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//  int r = 0;
//
//  r = --n;
//  printf("%d %d\n", n, r);
//  r = n--;
//  printf("%d %d\n", n, r);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//  int r = 0;
//
//  r = ++n;
//  printf("%d %d\n", n, r);
//  r = n++;
//  printf("%d %d\n", n, r);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//
//  ++n;
//  printf("%d\n", n);
//  n++;
//  printf("%d\n", n);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//
//  ++n;
//  printf("%d\n", n);
//  n++;
//  printf("%d\n", n);
//}


#include <stdio.h>
int main()
{
  // ++ , -- 연산자
  int n = 0;

  ++n;
  printf("%d\n", n);
}

//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  for (int i = 0; i < 5; ++i)
//    sum += i+1;
//
//  printf("sum = %d\n", sum);
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  for(int i = 1 ; i <= 5 ; ++i)
//    sum += i;
//
//  printf("sum = %d\n", sum);
//  printf("\n");
//}


//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  sum += 1;
//  sum += 2;
//  sum += 3;
//  sum += 4;
//  sum += 5;
//
//  printf("sum = %d\n", sum);
//  printf("\n");
//}


//#include <stdio.h>
//int main()
//{
//  int sum = 0;
//
//  sum = sum + 1;
//  sum = sum + 2;
//  sum = sum + 3;
//  sum = sum + 4;
//  sum = sum + 5;
//
//  printf("sum = %d\n", sum);
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 1; i <= 10; ++i)
//  {
//    if (i % 2 == 0)
//      continue; //break;
//
//
//
//
//
//
//    printf("%5d", i);
//  }
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 1; i <= 10; ++i)
//  {
//    if( i % 2 == 0)
//      printf("%5d", i);
//  }
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 1; i <= 10; ++i)
//  {
//    printf("%5d", i);
//  }
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 1; i <= 10; ++i)
//  {
//    printf("%d ", i);
//  }
//  printf("\n");
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//  do
//  {
//    printf("%d\n", n);
//  } while (n > 0);
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//  while (n > 0)
//  {
//    printf("%d\n", n);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  while (1)
//  {
//    int n = 0;
//    printf("정수 입력:");
//    scanf_s("%d", &n);
//    if (n > 0)
//    {
//      printf("Hello : %d\n", n);
//    }
//    else
//    {
//      break;
//    }
//  }
//}

//#include <stdio.h>
//int main()
//{
//  int n = 0;
//  while ( n < 5 )
//  {
//    printf("Hello\n");
//    n++;
//  }
//}

//#include <stdio.h>
//int main()
//{
//  while (1)
//  {
//    printf("Hello\n");
//  }
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 0; i < 10; i += 2 ) // i = i + 2;
//  {
//    printf("Hello! : %d\n", i + 1);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 0; i < 10; ++i )
//  {
//    printf("Hello! : %d\n", i + 1);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 0; i < 10; i = i + 1)
//  {
//    printf("Hello! : %d\n", i+1);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  for (int i = 0; i < 10; i = i + 1)
//  {
//    printf("Hello! : %d\n", i);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  //루프문 : for(), while(), do-while()
//
//  for (int i = 1; i <= 100; i = i + 1)
//  {
//    printf("Hello! : %d\n", i);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  //루프문 : for(), while(), do-while()
//
//  for (int i = 1; i <= 10; i = i + 1)
//  {
//    printf("Hello! : %d\n", i);
//  }
//}

//#include <stdio.h>
//int main()
//{
//  //루프문 : for(), while(), do-while()
//
//  for (int i = 1; i <= 10; i = i+1)
//  {
//    printf("Hello!\n");
//  }
//
//}

//#include <stdio.h>
//int main()
//{
//  printf("Hello!\n");
//}

//#include <stdio.h>
//#include <conio.h> // _getch()
//
//int main()
//{
//  switch ( _getch() ) //getchar()
//  {
//  case 49:
//    printf("case 1\n");
//    break;
//  case '2': //50
//    printf("case 2\n");
//    break;
//  case '3': //51
//    printf("case 3\n");
//    break;
//  default:
//    printf("default \n");
//    break;
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 0;
//  printf("정수 입력: ");
//  scanf_s("%d", &n);
//
//  switch ( n )
//  {
//  case 1:
//    printf("case 1\n");
//    break;
//  case 2:
//    printf("case 2\n");
//    break;
//  case 3:
//    printf("case 3\n");
//    break;
//  default:
//    printf("default \n");
//    break;
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  switch (1)
//  {
//  case 1:
//    printf("case 1\n");
//    break;
//  case 2:
//    printf("case 2\n");
//    break;
//  case 3:
//    printf("case 3\n");
//    break;
//  default:
//    printf("default \n");
//    break;
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  if ( n == 10)
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//  else
//  {
//    printf("4. Hello\n");
//    printf("5. Hello\n");
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  //제어문 if/ if-else / switch-case
//  if ( 0 )
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//  else
//  {
//    printf("4. Hello\n");
//    printf("5. Hello\n");
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  //제어문 if/ if-else / switch-case
//  if ( 1 )
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//  else
//  {
//    printf("4. Hello\n");
//    printf("5. Hello\n");
//  }
//}


//#include <stdio.h>
//
//int main()
//{
//  //제어문 if/ if-else / switch-case
//  if (100 > 50)
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//  else
//  {
//    printf("4. Hello\n");
//    printf("5. Hello\n");
//  }
//}

//#include <stdio.h>
//
//int main()
//{
//  //제어문 if/ if-else / switch-case
//
//  if (100 < 50)
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//
//  printf("4. Hello\n");
//  printf("5. Hello\n");
//}

//#include <stdio.h>
//
//int main()
//{
//  //제어문 if/ if-else / switch-case
//
//  if (100 > 5)
//  {
//    printf("1. Hello\n");
//    printf("2. Hello\n");
//    printf("3. Hello\n");
//  }
//
//  printf("4. Hello\n");
//  printf("5. Hello\n");
//}


//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  printf("%d\n", n);
//  printf("%p\n", &n);
//  printf("%d\n", (&n)[0]);
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  *&n = 20;
//
//  printf("%d\n", n);
//  printf("%p\n", &n);
//  printf("%d\n", *&n);
//  printf("%p\n", &*&n);
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  printf("%d\n", n);
//  printf("%p\n", &n);
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  printf("%d\n", n);
//  printf("%p\n", &n);
//}


//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  printf("%d\n", n);
//}

//#include <stdio.h>
//
//int main()
//{
//  int n = 2;
//
//  printf("%d\n", n  );// n
//  printf("%d\n", n << 1);// n*2
//  printf("%d\n", n << 2);// n*4
//  printf("%d\n", n << 3);// n*8
//}


//#include <stdio.h>
//
//int main()
//{
//  int n = 10;
//
//  printf("%d, %p", n, &n); //10 0x3F4570
//}
