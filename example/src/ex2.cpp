#include <stdio.h>

int main()
{
  int n = 10;

  printf("%d %p\n", n, &n);
  printf("%d %p\n", n+1, &n+1);
}

//#include <stdio.h>
//
//int main()
//{
//  //쉬프트(shift) 연산자
//  int a = 10;
//
//  printf("%d\n", a >> 0);
//  printf("%d\n", a >> 1);
//  printf("%d\n", a >> 2);
//  printf("%d\n", a >> 3);
//  printf("%d\n", a >> 4);
//}

//#include <stdio.h>
//
//int main()
//{
//  //쉬프트(shift) 연산자
//  int a = 3;
//
//  printf("%d\n", a << 0);
//  printf("%d\n", a << 1);
//  printf("%d\n", a << 2);
//}

//#include <stdio.h>
//
//int main()
//{
//  int a = 0;
//  int b = 3;
//  int c = 100;
//
//  if ((a == b) && (c == 100))
//    printf(" a == b\n");
//  else
//    printf(" a != b\n");
//}

//#include <stdio.h>
//
//int main()
//{
//  int a = 0;
//  int b = 3;
//  int c = 100;
//
//  if ( (a == b) || (c == 100) )
//    printf(" a == b\n");
//  else
//    printf(" a != b\n");
//}

//#include <stdio.h>
//
//int main()
//{
//  int a = 0;
//  int b = 3;
//
//  if (a == b)
//    printf(" a == b\n");
//  else
//    printf(" a != b\n");
//}

//#include <stdio.h>
//
//int main()
//{
//  //논리 연산자
//  //비트 (논리) 연산자 : AND(&) OR(|) XOR(^) NOT(~)
//  //(값) 논리 연산자   : AND(&&) OR(||) NOT(!)
//  int a = 0;
//  int b = 3;
//
//  printf("%d\n", a && b);
//  printf("%d\n", a || b);
//  printf("%d\n", !a);
//  printf("%d\n", !b );
//}

//#include <stdio.h>
//
//int main()
//{
//  //논리 연산자
//  //비트 (논리) 연산자 : AND(&) OR(|) XOR(^) NOT(~)
//  //(값) 논리 연산자   : AND(&&) OR(||) NOT(!)
//  int a = 5;
//  int b = 3;
//
//  printf("%d\n", a & b);
//  printf("%d\n", a | b);
//  printf("%d\n", a ^ b);
//  printf("%d\n", ~a);
//  printf("%08X\n", ~a);
//  printf("%d\n", ~b);
//  printf("%08X\n", ~b);
//}

//#include <stdio.h>
//
//int main()
//{
//  //대입 연산자
//  // = += -= <<= %= ...
//  int a = 5;
//  int b = 3;
//
//  a += b;
//  printf("%d %d\n", a, b);
//  a -= b;
//  printf("%d %d\n", a, b);
//  a <<= b;
//  printf("%d %d\n", a, b);  
//  a %= b;
//  printf("%d %d\n", a, b);
//}

//#include <stdio.h>
//
//int main()
//{
//  //대입 연산자
//  //
//  int a = 5;
//  int b = 3;
//
//  a = b;
//  printf("%d %d\n", a, b);
//}

//#include <stdio.h>
//
//int main()
//{
//  //비교 연산자
//  // == != < > <= >= (true:1, false:0)
//
//  int a = 5;
//  int b = 3;
//
//  printf("%d\n", a == b);
//  printf("%d\n", a != b);
//  printf("%d\n", a < b);
//  printf("%d\n", a > b);
//}

//#include <stdio.h>
//
//int main()
//{
//  //산술 연산자
//  // + - / * &
//
//  int a = 5;
//  int b = 3;
//
//  printf("%d\n", a + b);
//  printf("%d\n", a - b);
//  printf("%d\n", a / b);
//  printf("%d\n", a * b);
//  printf("%d\n", a % b);
//}

//#include <stdio.h>
//
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int result = a + b;
//
//  printf("%p\n", &a);
//  printf("%p\n", &b);
//  printf("%p\n", &result);
//}

//#include <stdio.h>
//
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int result = a + b;
//
//  printf("%p\n", &a);
//}


//#include <stdio.h>
//
//int main()
//{
//  int a = 10;
//  int b = 20;
//  int result = a + b;
//
//  printf("%d\n", result);
//  printf("%d\n", a+b );
//}

//#include <stdio.h>
//
//int main()
//{
//  printf("Hello\n");
//}