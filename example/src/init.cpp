#include <stdio.h>
#include <locale.h> //<= 헤더 추가
int main()
{
  setlocale(LC_ALL, ""); //<= 현 운영체제에 맞게 locale 설정

  printf("안녕하세요~!\n");
}