# C언어 기초 강의 22 - ex22.cpp 코드를 통한 유니코드와 멀티바이트 문자 처리

이 강의는 **example/ex22.cpp**에 담긴 예제들을 바탕으로, 난수 생성, 메모리 복사, 파일 입출력, 그리고 **유니코드·멀티바이트 문자 처리**(wchar_t, TCHAR, setlocale 등)까지 점진적으로 다루는 내용입니다. 소스 파일에서 가장 아래 예제가 기초이고, 위로 올라갈수록 발전된 내용입니다.

---

## 0. 학습 목표

- `srand`와 `rand`를 이용한 난수 생성과 범위 조절을 이해한다.
- `memcpy`, `memset` 등 메모리 복사 함수를 사용할 수 있다.
- `fwrite`, `fread`, `fseek`, `ftell`을 사용한 바이너리 파일 입출력을 할 수 있다.
- **멀티바이트 문자(char)**와 **유니코드 문자(wchar_t)**의 차이를 이해한다.
- `wchar_t`와 `L""` 리터럴, `wprintf` 등 와이드 문자 함수를 사용할 수 있다.
- `TCHAR`, `_T()` 매크로를 이용한 **유니코드/ANSI 호환 코드**를 작성할 수 있다.
- `setlocale`로 **로케일**을 설정하여 한글을 올바르게 출력할 수 있다.
- `malloc`과 TCHAR를 이용한 **동적 문자열 할당**을 할 수 있다.

---

## 1. 난수 생성 (rand, srand)

### 1.1 고정 시드로 난수 생성

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//0~ 0xFFFF
	srand(265);
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand() % 1000);
}
```

**설명**
- `#include <stdlib.h>` : `srand`, `rand`, `malloc`, `free` 등을 사용하기 위한 헤더입니다.
- `srand(265)` : 난수 생성기의 **시드(seed)**를 고정값 265로 설정합니다.
- `rand()` : 0부터 `RAND_MAX`(보통 32767)까지의 **의사 난수(pseudo-random number)**를 반환합니다.
- `rand() % 1000` : 나머지 연산으로 **0~999** 범위의 난수를 만듭니다.
- 시드가 같으면 **매번 같은 순서**의 난수가 나옵니다. 디버깅·테스트에 유용합니다.

---

### 1.2 time()으로 매번 다른 난수

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//0~ 0xFFFF
	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand() % 1000);
}
```

**설명**
- `#include <time.h>` : `time`, `clock` 등 시간 관련 함수를 사용하기 위한 헤더입니다.
- `time(NULL)` : **현재 시각**을 1970년 1월 1일 기준 초 단위 정수로 반환합니다.
- `srand((unsigned int)time(NULL))` : 매 실행마다 시드가 달라지므로, **매번 다른 난수 시퀀스**가 생성됩니다.

---

### 1.3 난수 범위 조절 (-10 ~ 10)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//0~ 0xFFFF
	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand() % 21 - 10);
		//printf("%d\n", rand() % 20);
}
```

**설명**
- `rand() % 21` : **0~20** 범위의 난수를 생성합니다 (21개의 값).
- `rand() % 21 - 10` : 여기서 10을 빼서 **-10 ~ 10** 범위로 조절합니다.
- 주석 처리된 `rand() % 20`은 **0~19** 범위를 만드는 예시입니다.
- 일반 공식: **최솟값 min ~ 최댓값 max** 범위 → `rand() % (max - min + 1) + min`

---

### 1.4 랜덤 대문자 출력

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//0~ 0xFFFF
	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
	for (int i = 0; i < 10; ++i)
		printf("%c\n", rand() % 26 + 'A');
	//printf("%d\n", rand() % 21 - 10);
	//printf("%d\n", rand() % 20);
}
```

**설명**
- `rand() % 26` : **0~25**의 난수를 생성합니다 (알파벳 26글자).
- `+ 'A'` : ASCII 코드에서 `'A'`는 65이므로, 65~90 범위 → **'A'~'Z'** 중 하나의 대문자가 됩니다.
- `%c`로 출력하면 숫자가 아닌 **문자**로 표시됩니다.

---

### 1.5 랜덤 대소문자 출력 (삼항 연산자)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//0~ 0xFFFF
	srand((unsigned int)time(NULL)); //1970년1월1일 ms 값
	for (int i = 0; i < 10; ++i) {
		rand() % 2 ?
			printf("%c\n", rand() % 26 + 'a'):
			printf("%c\n", rand() % 26 + 'A');
	}

	//printf("%c\n", rand() % 26 + 'A');
	//printf("%d\n", rand() % 21 - 10);
	//printf("%d\n", rand() % 20);
}
```

**설명**
- `rand() % 2` : **0 또는 1**을 생성합니다 (50% 확률).
- **삼항 연산자** `조건 ? A : B` : 조건이 참(1)이면 A, 거짓(0)이면 B를 실행합니다.
  - 1(참)이면 `rand() % 26 + 'a'` → **소문자** ('a'~'z')
  - 0(거짓)이면 `rand() % 26 + 'A'` → **대문자** ('A'~'Z')
- 결과적으로 랜덤한 **대소문자 영문자**를 출력합니다.

---

## 2. 메모리 복사 (memcpy, memset)

### 2.1 변수 간 메모리 복사

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

int main()
{
	int n = 10;
	int k = n;
	int t = 0;

	memcpy(&t, &n, sizeof(int));

	printf("%d %d %d\n", n, k, t);
}
```

**설명**
- `#include <memory.h>` : `memcpy`, `memset` 등 메모리 관련 함수를 사용하기 위한 헤더입니다.
- `int k = n;` : 일반적인 **대입 연산**으로 값을 복사합니다.
- `memcpy(&t, &n, sizeof(int))` : `n`의 메모리 내용을 `t`로 **바이트 단위**로 복사합니다.
  - 첫 번째 인자 : 복사 **대상(destination)**의 주소
  - 두 번째 인자 : 복사 **원본(source)**의 주소
  - 세 번째 인자 : 복사할 **바이트 수**

**예상 출력**
```
10 10 10
```

---

### 2.2 배열 복사

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

int main()
{
	int arr[5] = { 10, 20, 30, 40, 50 };
	int buf[5];

	memcpy(buf, arr, sizeof(int) * 5);

	for (int i = 0; i < 5; ++i)
		printf("%d %d\n", arr[i], buf[i]);
}
```

**설명**
- `memcpy(buf, arr, sizeof(int) * 5)` : `arr` 배열의 전체 내용(**20바이트**)을 `buf`로 복사합니다.
- 배열은 `=` 연산자로 직접 복사할 수 없으므로, `memcpy`가 유용합니다.

**예상 출력**
```
10 10
20 20
30 30
40 40
50 50
```

---

### 2.3 대용량 복사와 성능 측정 (clock)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define MB	1024*1024
int main()
{
	int* arr = (int*)malloc(sizeof(int) * MB * 100);
	int* buf = (int*)malloc(sizeof(int) * MB * 100);
	unsigned long startTime = 0;
	unsigned long endTime = 0;

	for (int i = 0; i < 200 * MB; ++i)
		arr[i] = i;

	startTime = (unsigned long)clock();
	//for (int i = 0; i < 200 * MB; ++i)
	//	buf[i] = arr[i];
	memcpy(buf, arr, sizeof(int) * 200 * MB);

	endTime = (unsigned long)clock();

	printf("%d clock\n", endTime - startTime);

	free(arr);
	free(buf);
}
```

**설명**
- `#define MB 1024*1024` : 1MB(1,048,576)를 나타내는 매크로입니다.
- `malloc(sizeof(int) * MB * 100)` : 약 **400MB**의 메모리를 동적 할당합니다.
- `clock()` : 프로그램 실행 이후의 **CPU 클럭 수**를 반환합니다.
- `endTime - startTime` : 복사에 걸린 시간을 **클럭 단위**로 측정합니다.
- 주석 처리된 `for` 반복문(원소 하나씩 복사)과 `memcpy`(한 번에 복사)의 **성능 차이**를 비교하는 예제입니다.
- `memcpy`는 내부적으로 최적화되어 있어, 반복문으로 하나씩 복사하는 것보다 **훨씬 빠릅니다**.

---

### 2.4 버퍼에 여러 자료형 묶어 넣기 (memset + memcpy)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>

int main()
{
	char buf[100];
	int n = 10;
	double d = 5.5;
	const char* s = "Hello!";

	memset(buf, 0, sizeof(char) * 100);

	memcpy(buf, &n, sizeof(int));
	memcpy(buf + 4, &d, sizeof(double));
	memcpy(buf + 12, s, strlen(s) + 1);

	printf("%d %g %s\n", *(int*)buf, *(double*)(buf + 4), (char*)(buf + 12));
}
```

**설명**
- `memset(buf, 0, sizeof(char) * 100)` : 버퍼 100바이트를 **모두 0**으로 초기화합니다.
- 하나의 `char buf[100]` 배열에 **서로 다른 자료형**의 데이터를 순서대로 넣습니다.
  - `buf[0~3]` : `int n` → 4바이트
  - `buf[4~11]` : `double d` → 8바이트
  - `buf[12~]` : 문자열 `s` → 7바이트 (널 문자 포함)
- 읽을 때는 **포인터 캐스팅**으로 원래 자료형에 맞게 해석합니다.
  - `*(int*)buf` : buf 시작 위치를 int 포인터로 해석
  - `*(double*)(buf + 4)` : buf+4 위치를 double 포인터로 해석
  - `(char*)(buf + 12)` : buf+12 위치를 문자열로 해석

**예상 출력**
```
10 5.5 Hello!
```

---

## 3. 바이너리 파일 입출력 (fwrite, fread, fseek, ftell)

### 3.1 바이너리 파일 쓰기와 ftell

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wb");

	int n = 10;
	double d = 5.5;
	const char* s = "Hello!";
	fwrite(&n, sizeof(int), 1, pf);
	fwrite(&d, sizeof(double), 1, pf);
	fwrite(s, strlen(s) + 1, 1, pf); //전체 19byte

	fclose(pf);

	fopen_s(&pf, "test.txt", "rb");

	int size = 0;
	size = ftell(pf); //file position
	printf("size : %d\n", size);

	fclose(pf);
}
```

**설명**
- `fopen_s(&pf, "test.txt", "wb")` : 파일을 **바이너리 쓰기 모드**(`"wb"`)로 엽니다.
- `fwrite(데이터주소, 크기, 개수, 파일포인터)` : 데이터를 바이너리로 파일에 씁니다.
  - `&n` : int → 4바이트
  - `&d` : double → 8바이트
  - `s` : 문자열 → 7바이트 (`strlen("Hello!") + 1`, 널 문자 포함)
  - 총 **19바이트**가 기록됩니다.
- `ftell(pf)` : 현재 **파일 위치(file position)**를 반환합니다.
  - 파일을 열자마자 호출하면 아직 읽기 전이므로 **0**이 나옵니다.

**예상 출력**
```
size : 0
```

---

### 3.2 fseek로 원하는 위치 읽기

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wb");

	int n = 10;
	double d = 5.5;
	const char* s = "Hello!";
	fwrite(&n, sizeof(int), 1, pf);
	fwrite(&d, sizeof(double), 1, pf);
	fwrite(s, strlen(s) + 1, 1, pf); //전체 19byte

	fclose(pf);

	fopen_s(&pf, "test.txt", "rb");

	fseek(pf, 4, SEEK_SET);
	fread(&d, sizeof(double), 1, pf);
	printf("double : %g\n", d);

	char buf[100];
	fseek(pf, -7, SEEK_END);
	fread(buf, strlen("Hello!") + 1, 1, pf);
	printf("string : %s\n", buf);

	int size = 0;
	fseek(pf, 0, SEEK_END);
	size = ftell(pf); //file position
	printf("size : %d\n", size);

	fclose(pf);
}
```

**설명**
- `fseek(pf, 오프셋, 기준)` : 파일 읽기/쓰기 위치를 이동합니다.

| 기준 상수 | 의미 |
|-----------|------|
| `SEEK_SET` | 파일 **처음**부터 |
| `SEEK_CUR` | **현재 위치**부터 |
| `SEEK_END` | 파일 **끝**부터 |

- `fseek(pf, 4, SEEK_SET)` : 시작에서 4바이트 뒤(int를 건너뜀)로 이동하여 **double**을 읽습니다.
- `fseek(pf, -7, SEEK_END)` : 끝에서 7바이트 앞으로 이동하여 **문자열**을 읽습니다.
- `fseek(pf, 0, SEEK_END)` 후 `ftell(pf)` : 파일 끝으로 이동하면 **파일 전체 크기**(19바이트)를 알 수 있습니다.

**예상 출력**
```
double : 5.5
string : Hello!
size : 19
```

---

### 3.3 fwrite/fread로 여러 값 쓰고 배열로 읽기

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wb");

	int n = 10;
	double d = 5.5;
	const char* s = "Hello!";
	fwrite(&n, sizeof(int), 1, pf);
	fwrite(&n, sizeof(int), 1, pf);
	fwrite(&d, sizeof(double), 1, pf);
	fwrite(s, strlen(s) + 1, 1, pf); //전체 19byte

	fclose(pf);

	fopen_s(&pf, "test.txt", "rb");
	int arr[2];
	fread(arr, sizeof(int) * 2, 1, pf);
	printf("int %d %d\n", arr[0], arr[1]);

	fclose(pf);
}
```

**설명**
- 이 예제에서는 같은 `int n = 10`을 **두 번** 연속으로 파일에 씁니다.
- `fread(arr, sizeof(int) * 2, 1, pf)` : 파일에서 **int 2개 분량**(8바이트)을 한 번에 읽어 `arr` 배열에 저장합니다.
- 바이너리 파일에서는 **연속된 바이트**를 원하는 크기 단위로 묶어서 읽을 수 있습니다.

**예상 출력**
```
int 10 10
```

---

## 4. 멀티바이트 문자와 char의 한계

### 4.1 char로 한글 다루기

```c
#include <stdio.h>

int main()
{
	char c = 'A';
	char c2 = '가';
	const char* s = "ABC";
	const char* s2 = "가나다";

	printf("%c %c\n", c, c2);
	printf("%s %s\n", s, s2);
}
```

**설명**
- `char c = 'A'` : 영문 1글자는 `char`(1바이트)에 정상적으로 저장됩니다.
- `char c2 = '가'` : 한글은 **2바이트 이상**(멀티바이트 문자)이므로, 1바이트 `char`에 제대로 저장할 수 **없습니다**. 컴파일 경고가 발생하거나 잘못된 값이 저장됩니다.
- `const char* s2 = "가나다"` : 문자열 포인터로는 멀티바이트 문자를 담을 수 있지만, `%c`로 **한 글자씩 접근**할 때 문제가 생깁니다.
- `%s`로 문자열 전체를 출력하면 환경에 따라 정상 출력될 수도 있습니다.

**예상 출력 (환경에 따라 다름)**
```
A (깨진 문자)
ABC 가나다
```

> **핵심**: `char`는 1바이트로 **영문·숫자·기호**에는 충분하지만, **한글 등 다국어 문자**를 개별 문자로 다루기에는 부족합니다. 이 문제를 해결하기 위해 **wchar_t**와 **유니코드**를 사용합니다.

---

## 5. 유니코드와 wchar_t

### 5.1 wchar_t와 L"" 리터럴

```c
#include <stdio.h>
#include <locale.h>
int main()
{
	setlocale(LC_ALL, "Korean");
	wchar_t c = L'A';
	wchar_t c2 = L'가';
	const wchar_t* s = L"ABC";
	const wchar_t* s2 = L"가나다";

	wprintf(L"%c %c\n", c, c2);
	wprintf(L"%s %s\n", s, s2);
}
```

**설명**
- `wchar_t` : **와이드 문자(wide character)** 자료형으로, Windows에서는 보통 **2바이트(UTF-16)**입니다. 한글 한 글자를 온전히 저장할 수 있습니다.
- `L'가'`, `L"가나다"` : 문자/문자열 앞에 **`L`**을 붙이면 **와이드 문자(wchar_t)** 리터럴이 됩니다.
- `#include <locale.h>` : `setlocale` 함수를 사용하기 위한 헤더입니다.
- `setlocale(LC_ALL, "Korean")` : **로케일(locale)**을 한국어로 설정합니다. 이 설정이 없으면 `wprintf`로 한글을 출력할 때 **아무것도 나오지 않거나 깨질** 수 있습니다.
- `wprintf` : `printf`의 와이드 문자 버전입니다. 서식 문자열도 `L"..."`로 작성해야 합니다.

**예상 출력**
```
A 가
ABC 가나다
```

> **주의**: `setlocale`을 호출하지 않으면 한글이 출력되지 않습니다. 반드시 로케일 설정을 먼저 해야 합니다.

---

## 6. TCHAR과 _T() 매크로 (유니코드/ANSI 호환)

### 6.1 TCHAR 기본 사용

```c
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <tchar.h>
int main()
{
#ifdef _UNICODE
	_wsetlocale(LC_ALL, L"Korean");
#else
	setlocale(LC_ALL, "Korean");
#endif

	TCHAR c = _T('A');
	TCHAR c2 = _T('가');
	const TCHAR* s = _T("ABC");
	const TCHAR* s2 = _T("가나다");

	_tprintf(_T("%c %c\n"), c, c2);
	_tprintf(_T("%s %s\n"), s, s2);

	int n = 10;
	_tprintf(_T("정수 입력:"));
	_tscanf_s(_T("%d"), &n);

	_tprintf(_T("정수 : %d\n"), n);

	_tprintf(_T("문자열의 길이:%d\n"), (int)_tcslen(s2));
}
```

**설명**
- `#include <tchar.h>` : **TCHAR** 관련 매크로와 함수를 사용하기 위한 헤더입니다.
- **TCHAR** : 프로젝트 설정에 따라 자동으로 **char 또는 wchar_t**로 변환되는 매크로 자료형입니다.
  - **유니코드 빌드**(`_UNICODE` 정의됨) → `TCHAR` = `wchar_t`
  - **멀티바이트 빌드**(기본) → `TCHAR` = `char`
- **_T("문자열")** : 유니코드 빌드에서는 `L"문자열"`로, 멀티바이트 빌드에서는 `"문자열"`로 자동 변환됩니다.
- `#ifdef _UNICODE ... #else ... #endif` : 빌드 환경에 따라 **다른 코드를 실행**하는 조건부 컴파일입니다.
  - 유니코드 → `_wsetlocale(LC_ALL, L"Korean")`
  - 멀티바이트 → `setlocale(LC_ALL, "Korean")`

**TCHAR 대응 함수 표**

| 일반 함수 | TCHAR 대응 함수 | 설명 |
|-----------|-----------------|------|
| `printf` | `_tprintf` | 화면 출력 |
| `scanf_s` | `_tscanf_s` | 키보드 입력 |
| `strlen` | `_tcslen` | 문자열 길이 |
| `strcpy_s` | `_tcscpy_s` | 문자열 복사 |
| `setlocale` | `_tsetlocale` | 로케일 설정 |

- `_tcslen(s2)` : 문자열 `s2`(`"가나다"`)의 **글자 수**를 반환합니다 → **3**.

---

### 6.2 동적 문자열 할당과 TCHAR (최종 예제)

```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <tchar.h>
int main()
{
	setlocale(LC_ALL, "Korean");

	const TCHAR* str = _T("Hello!");
	TCHAR* s = (TCHAR*)malloc(sizeof(TCHAR) * ((int)_tcslen(str)) + sizeof(TCHAR));

	int slen = (int)_tcslen(str) + 1;
	if (s != NULL)
		_tcscpy_s(s, slen, str);

	_tprintf(_T("string: %s\n"), s);

	free(s);
}
```

**설명**
- `_tcslen(str)` : 문자열 `str`의 **글자 수**를 반환합니다 (널 문자 제외, `"Hello!"` → 6).
- `malloc(sizeof(TCHAR) * _tcslen(str) + sizeof(TCHAR))` : 문자열 길이 + 널 문자(1개) 만큼의 메모리를 **동적 할당**합니다.
  - `sizeof(TCHAR)` : 유니코드면 2바이트, 멀티바이트면 1바이트
  - 유니코드 빌드: `2 * 6 + 2 = 14`바이트
  - 멀티바이트 빌드: `1 * 6 + 1 = 7`바이트
- `_tcscpy_s(s, slen, str)` : `strcpy`의 TCHAR 안전 버전. `str`의 내용을 `s`로 복사합니다.
  - `slen` : 대상 버퍼의 **문자 수** (글자 수 + 1, 널 문자 포함)
- `if (s != NULL)` : `malloc`이 **실패할 수 있으므로** 반드시 NULL 체크를 합니다.
- `free(s)` : 사용이 끝난 동적 메모리를 **해제**합니다. 해제하지 않으면 **메모리 누수(memory leak)**가 발생합니다.

**예상 출력**
```
string: Hello!
```

---

## 7. 보충 학습

### 7.1 char, wchar_t, TCHAR 비교

| 항목 | char | wchar_t | TCHAR |
|------|------|---------|-------|
| **크기** | 1바이트 | 2바이트 (Windows) | 빌드에 따라 1 또는 2바이트 |
| **한글 저장** | 멀티바이트(2~3바이트 필요) | 한 글자 = 1개 wchar_t | 빌드에 따라 다름 |
| **문자 리터럴** | `'A'` | `L'A'` | `_T('A')` |
| **문자열 리터럴** | `"Hello"` | `L"Hello"` | `_T("Hello")` |
| **출력 함수** | `printf` | `wprintf` | `_tprintf` |
| **문자열 길이** | `strlen` | `wcslen` | `_tcslen` |
| **문자열 복사** | `strcpy_s` | `wcscpy_s` | `_tcscpy_s` |

---

### 7.2 setlocale이 필요한 이유

- C 라이브러리의 와이드 문자 출력 함수(`wprintf` 등)는 **로케일 설정**에 따라 문자를 변환합니다.
- 기본 로케일은 `"C"`(영문만 지원)이므로, 한글을 출력하려면 반드시 다음 중 하나를 호출해야 합니다.
  - `setlocale(LC_ALL, "Korean")` : 한국어 로케일 명시
  - `setlocale(LC_ALL, "")` : 시스템 기본 로케일 사용

---

### 7.3 _UNICODE 매크로와 프로젝트 설정

- Visual Studio에서 **프로젝트 속성 → 일반 → 문자 집합**을 변경할 수 있습니다.
  - **유니코드 문자 집합 사용** → `_UNICODE`, `UNICODE` 매크로가 자동 정의됨
  - **멀티바이트 문자 집합 사용** → 해당 매크로가 정의되지 않음
- TCHAR과 `_T()`를 사용하면, 이 설정을 바꿔도 **코드 수정 없이** 양쪽 모두에서 빌드할 수 있습니다.

---

### 7.4 동적 할당 시 주의사항

- `malloc` 후에는 반드시 **NULL 체크**를 합니다.
- 사용이 끝나면 반드시 `free`로 **해제**합니다.
- 유니코드에서는 `sizeof(TCHAR)`이 2이므로, 바이트 수 계산 시 **글자 수 × sizeof(TCHAR)**로 해야 합니다.
- `_tcscpy_s`의 두 번째 인자는 **바이트 수가 아니라 문자 수**(널 포함)입니다.

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| 난수 시드 설정 | `srand(시드값)`, `srand((unsigned int)time(NULL))` |
| 난수 생성 | `rand()`, `rand() % 범위 + 최솟값` |
| 메모리 복사 | `memcpy(대상, 원본, 바이트수)` |
| 메모리 초기화 | `memset(대상, 값, 바이트수)` |
| 파일 열기 | `fopen_s(&fp, 파일명, 모드)` |
| 바이너리 쓰기 | `fwrite(주소, 크기, 개수, fp)` |
| 바이너리 읽기 | `fread(주소, 크기, 개수, fp)` |
| 파일 위치 이동 | `fseek(fp, 오프셋, 기준)` — `SEEK_SET`, `SEEK_CUR`, `SEEK_END` |
| 파일 위치 확인 | `ftell(fp)` |
| 멀티바이트 한계 | `char`는 1바이트 → 한글 개별 문자 저장 불가 |
| 와이드 문자 | `wchar_t`, `L'문자'`, `L"문자열"` |
| 와이드 출력 | `wprintf(L"서식", ...)` |
| 로케일 설정 | `setlocale(LC_ALL, "Korean")` |
| TCHAR 헤더 | `#include <tchar.h>` |
| TCHAR 매크로 | `TCHAR`, `_T('문자')`, `_T("문자열")` |
| TCHAR 출력/입력 | `_tprintf`, `_tscanf_s` |
| TCHAR 문자열 길이 | `_tcslen(문자열)` |
| TCHAR 문자열 복사 | `_tcscpy_s(대상, 문자수, 원본)` |
| 동적 할당 (TCHAR) | `(TCHAR*)malloc(sizeof(TCHAR) * 길이)` + `free` |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `srand`와 `time`을 사용하여 **1~100 사이의 랜덤 정수** 5개를 출력하는 프로그램을 작성하세요.
2. `int arr[10]`에 1~10을 넣고, `memcpy`로 다른 배열에 복사한 뒤 두 배열을 나란히 출력하세요.
3. 정수와 실수를 `fwrite`로 바이너리 파일에 쓰고, `fseek`와 `fread`로 실수만 골라 읽어서 출력해 보세요.
4. `wchar_t` 변수에 자신의 이름(한글)을 넣고 `wprintf`로 출력해 보세요. `setlocale`을 빼면 어떻게 되는지도 확인하세요.
5. `TCHAR`과 `_T()`를 사용하여 `"안녕하세요"`를 출력하는 프로그램을 작성하세요. Visual Studio에서 유니코드/멀티바이트 빌드 설정을 바꿔 가며 테스트해 보세요.
6. `TCHAR*`로 동적 할당한 문자열에 `_tcscpy_s`로 `"C언어"`를 복사하고 출력한 뒤, `free`로 메모리를 해제하는 프로그램을 작성하세요.

---

이 강의 자료는 **example/ex22.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. **1~3장**은 이전 수업 내용(난수, 메모리 복사, 파일 입출력)의 복습이고, **4~6장**이 이번 수업의 핵심(멀티바이트 문자의 한계, wchar_t와 유니코드, TCHAR 매크로)입니다. 각 예제를 직접 타이핑하고 실행해 보면서, 특히 `setlocale` 유무에 따른 출력 차이와 유니코드/멀티바이트 빌드 설정에 따른 차이를 실험해 보세요.
