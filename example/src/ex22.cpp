#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <tchar.h>
int main()
{
	setlocale(LC_ALL, "Korean");

	const TCHAR* str = _T("Hello!");
	TCHAR* s = (TCHAR*)malloc(sizeof(TCHAR) * ((int)_tcslen(str))+sizeof(TCHAR));

	int slen = (int)_tcslen(str) + 1;
	if( s != NULL )
		_tcscpy_s(s, slen, str);

	_tprintf(_T("string: %s\n"), s);

	free(s);
}

//#include <stdio.h>
//#include <locale.h>
//#include <string.h>
//#include <tchar.h>
//int main()
//{
//#ifdef _UNICODE
//	_wsetlocale(LC_ALL, L"Korean");
//#else
//	setlocale(LC_ALL, "Korean");
//#endif
//
//	TCHAR c = _T('A');
//	TCHAR c2 = _T('가');
//	const TCHAR* s = _T("ABC");
//	const TCHAR* s2 = _T("가나다");
//
//	_tprintf(_T("%c %c\n"), c, c2);
//	_tprintf(_T("%s %s\n"), s, s2);
//
//	int n = 10;
//	_tprintf(_T("정수 입력:"));
//	_tscanf_s(_T("%d"), &n);
//
//	_tprintf(_T("정수 : %d\n"), n);
//
//	_tprintf(_T("문자열의 길이:%d\n"), (int)_tcslen(s2));
//}

//#include <stdio.h>
//#include <locale.h>
//int main()
//{
//	setlocale(LC_ALL, "Korean");
//	wchar_t c = L'A';
//	wchar_t c2 = L'가';
//	const wchar_t* s = L"ABC";
//	const wchar_t* s2 = L"가나다";
//
//	wprintf(L"%c %c\n", c, c2);
//	wprintf(L"%s %s\n", s, s2);
//}

//#include <stdio.h>
//#include <locale.h>
//int main()
//{
//	setlocale(LC_ALL, "Korean");
//	wchar_t c = L'A';
//	wchar_t c2 = L'가';
//	const wchar_t* s = L"ABC";
//	const wchar_t* s2 = L"가나다";
//
//	wprintf(L"%c %c\n", c, c2);
//	wprintf(L"%s %s\n", s, s2);
//}


//#include <stdio.h>
//
//int main()
//{
//	char c = 'A';
//	char c2 = '가';
//	const char* s = "ABC";
//	const char* s2 = "가나다";
//
//	printf("%c %c\n", c, c2);
//	printf("%s %s\n", s, s2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//#include <string.h>
//
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//
//	int n = 10;
//	double d = 5.5;
//	const char* s = "Hello!";
//	fwrite(&n, sizeof(int), 1, pf);
//	fwrite(&n, sizeof(int), 1, pf);
//	fwrite(&d, sizeof(double), 1, pf);
//	fwrite(s, strlen(s) + 1, 1, pf); //전체 19byte
//
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "rb");
//	int arr[2];
//	fread(arr, sizeof(int)*2, 1, pf);
//	printf("int %d %d\n", arr[0], arr[1]);
//
//	fclose(pf);
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//#include <string.h>
//
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//
//	int n = 10;
//	double d = 5.5;
//	const char* s = "Hello!";
//	fwrite(&n, sizeof(int), 1, pf);
//	fwrite(&d, sizeof(double), 1, pf);
//	fwrite(s, strlen(s) + 1, 1, pf); //전체 19byte
//
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "rb");
//
//	fseek(pf, 4, SEEK_SET);
//	fread(&d, sizeof(double), 1, pf);
//	printf("double : %g\n", d);
//
//	char buf[100];
//	fseek(pf, -7, SEEK_END);
//	fread(buf, strlen("Hello!") + 1, 1, pf);
//	printf("string : %s\n", buf);
//
//	int size = 0;
//	fseek(pf, 0, SEEK_END);
//	size = ftell(pf); //file position
//	printf("size : %d\n", size);
//
//	fclose(pf);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//#include <string.h>
//
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//	
//	int n = 10;
//	double d = 5.5;
//	const char* s = "Hello!";
//	fwrite(&n, sizeof(int), 1, pf);
//	fwrite(&d, sizeof(double), 1, pf);
//	fwrite(s, strlen(s)+1, 1, pf); //전체 19byte
//
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "rb");
//	
//	int size = 0;
//	size = ftell(pf); //file position
//	printf("size : %d\n", size);
//
//	fclose(pf);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//#include <string.h>
//
//int main()
//{
//	char buf[100];
//	int n = 10;
//	double d = 5.5;
//	const char* s = "Hello!";
//
//	memset(buf, 0, sizeof(char) * 100);
//
//	memcpy(buf, &n, sizeof(int));
//	memcpy(buf + 4, &d, sizeof(double));
//	memcpy(buf + 12, s, strlen(s)+1);
//
//	printf("%d %g %s\n", *(int*)buf, *(double*)(buf + 4), (char*)(buf + 12));
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//
//#define MB	1024*1024
//int main()
//{
//	int* arr = (int*)malloc(sizeof(int) * MB * 100);
//	int* buf = (int*)malloc(sizeof(int) * MB * 100);
//	unsigned long startTime = 0;
//	unsigned long endTime = 0;
//
//	for (int i = 0; i < 200 * MB; ++i)
//		arr[i] = i;
//
//	startTime = (unsigned long)clock();
//	//for (int i = 0; i < 200 * MB; ++i)
//	//	buf[i] = arr[i];
//	memcpy(buf, arr, sizeof(int) * 200*MB);
//
//	endTime = (unsigned long)clock();
//
//	printf("%d clock\n", endTime - startTime);
//
//	free(arr);
//	free(buf);
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	int buf[5];
//
//	memcpy(buf, arr, sizeof(int)*5);
//
//	for (int i = 0; i < 5; ++i)
//		printf("%d %d\n", arr[i], buf[i]);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <memory.h>
//
//int main()
//{
//	int n = 10;
//	int k = n;
//	int t = 0;
//
//	memcpy(&t, &n, sizeof(int));
//
//	printf("%d %d %d\n", n, k, t);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//int main()
//{
//	//0~ 0xFFFF
//	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
//	for (int i = 0; i < 10; ++i) {
//		rand()%2 ? 
//			printf("%c\n", rand() % 26 + 'a'):
//			printf("%c\n", rand() % 26 + 'A');
//	}
//
//	//printf("%c\n", rand() % 26 + 'A');
//	//printf("%d\n", rand() % 21 - 10);
//	//printf("%d\n", rand() % 20);
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//int main()
//{
//	//0~ 0xFFFF
//	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
//	for (int i = 0; i < 10; ++i)
//		printf("%c\n", rand() % 26 +'A');
//	//printf("%d\n", rand() % 21 - 10);
//	//printf("%d\n", rand() % 20);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//int main()
//{
//	//0~ 0xFFFF
//	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
//	for (int i = 0; i < 10; ++i)
//		printf("%d\n", rand() % 21-10);
//		//printf("%d\n", rand() % 20);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//int main()
//{
//	//0~ 0xFFFF
//	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
//	for (int i = 0; i < 10; ++i)
//		printf("%d\n", rand() % 1000);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//	//0~ 0xFFFF
//	srand(265);
//	for (int i = 0; i < 10; ++i)
//		printf("%d\n", rand() % 1000);
//}
