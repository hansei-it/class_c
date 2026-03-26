# C언어 기초 강의 14 - ex14.cpp 코드를 통한 동적 메모리·문자열·const·메뉴 프로그램

이 강의는 **example/ex14.cpp**에 담긴 예제들을 바탕으로, 동적 메모리 할당(malloc/free), 문자열 함수, const 포인터, 배열을 함수에 전달하는 방법, 그리고 메뉴 기반 정수 관리 프로그램까지를 다루는 강의 자료입니다.

---

## 0. 학습 목표

- `malloc`과 `free`를 사용하여 **동적 메모리 할당과 해제**를 할 수 있다.
- **동적 배열**을 만들고, 스택 배열과 힙 배열의 차이를 이해한다.
- 문자열 함수(`strcpy_s`, `strcat_s`, `strcmp`, `strlen`)를 사용할 수 있다.
- `const` 변수와 **const 포인터**(`const int*`, `int* const`, `const int* const`)의 차이를 안다.
- 배열과 문자열을 **함수의 매개변수**로 전달하는 방법을 이해한다.
- `_getch`와 `switch`를 활용한 **메뉴 기반 프로그램**을 작성할 수 있다.

---

## 1. 동적 메모리 할당 기초 (malloc / free)

C에서는 `malloc` 함수로 **실행 중에 필요한 만큼** 메모리를 할당하고, 다 쓴 뒤 `free`로 반환합니다. `malloc`은 `<stdlib.h>`에 선언되어 있습니다.

### 1.1 int 하나를 동적 할당

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int* p = (int*)malloc(4);

	*p = 100;
	printf("%d\n", *p);

	free(p);
}
```

**설명**
- `malloc(4)` : 4바이트(int 하나 크기)를 **힙(heap) 메모리**에서 할당합니다.
- 반환 타입이 `void*`이므로, `(int*)`로 **캐스팅**해서 정수 포인터에 저장합니다.
- `*p = 100` : 할당받은 메모리에 100을 저장합니다.
- `free(p)` : 사용이 끝난 메모리를 **반환**합니다. 반드시 해 주어야 **메모리 누수**가 없습니다.

**예상 출력**
```
100
```

---

### 1.2 malloc(8)로 double 할당

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	double d = 6.6;
	printf("%g\n", d);

	double* pd = (double*)malloc(8);
	*pd = 6.6;
	printf("%g\n", *pd);
	free(pd);
}
```

**설명**
- `double`은 보통 **8바이트**이므로 `malloc(8)`로 할당합니다.
- 스택 변수 `d`와 힙 메모리 `*pd` 모두 같은 값을 저장·출력할 수 있습니다.
- 스택 변수는 함수가 끝나면 자동으로 사라지지만, `malloc`으로 할당한 메모리는 **`free`를 호출해야** 해제됩니다.

**예상 출력**
```
6.6
6.6
```

---

### 1.3 sizeof를 활용한 안전한 malloc

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	double d=6.6;
	printf("%g\n", d);

	double* pd = (double*)malloc(sizeof(double));
	*pd = 6.6;
	printf("%g\n", *pd);
	free(pd);
}
```

**설명**
- `malloc(sizeof(double))`을 쓰면 **타입 크기를 직접 숫자로 쓰지 않아도** 됩니다.
- 환경에 따라 자료형의 크기가 다를 수 있으므로, `sizeof`를 쓰는 것이 **더 안전하고 이식성이 좋습니다**.
- `malloc(8)`과 `malloc(sizeof(double))`은 같은 결과이지만, `sizeof`를 쓰는 습관을 들이는 것이 좋습니다.

---

## 2. 동적 배열과 대규모 배열 (스택 vs 힙)

### 2.1 동적 배열 만들기

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int* arr = (int*)malloc(sizeof(int) * 10);

	for (int i = 0; i < 10; ++i)
		arr[i] = i + 1;

	for (int i = 0; i < 10; ++i)
		printf("%d ", arr[i]);

	free(arr);
}
```

**설명**
- `malloc(sizeof(int) * 10)` : int 10개 분량(40바이트)을 힙에 할당합니다.
- `arr[i]`처럼 **일반 배열과 동일한 문법**으로 접근합니다. 포인터에 `[]`를 쓸 수 있는 이유는 `arr[i]`가 `*(arr + i)`와 같기 때문입니다.
- 1부터 10까지 저장한 뒤 출력합니다.

**예상 출력**
```
1 2 3 4 5 6 7 8 9 10
```

---

### 2.2 대규모 스택 배열의 문제점 (스택 오버플로우)

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int arr[1000000];
	for (int i = 0; i < 1000000; ++i)
		arr[i] = i;
}
```

**설명**
- `int arr[1000000]` : 100만 개의 int(약 **4MB**)를 **스택**에 할당하려고 합니다.
- 일반적으로 스택 크기는 **1~2MB** 정도이므로, 이 코드는 **스택 오버플로우(Stack Overflow)**를 일으킵니다.
- 프로그램이 **비정상 종료**되거나 오류가 발생합니다.

> **핵심**: 큰 배열은 스택이 아닌 **힙(malloc)**에 할당해야 합니다.

---

### 2.3 힙 메모리로 대규모 배열 사용

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int* arr = (int*)malloc(sizeof(int)*1000000);
	for (int i = 0; i < 1000000; ++i)
		arr[i] = i;

	for (int i = 0; i < 1000000; ++i)
		if( i%100000 == 0 )
			printf("%d ", arr[i]);

	free(arr);
}
```

**설명**
- `malloc(sizeof(int)*1000000)` : 100만 개의 int(약 4MB)를 **힙**에 할당합니다. 힙은 스택보다 훨씬 큰 공간을 사용할 수 있습니다.
- 출력 시 `i % 100000 == 0` 조건을 걸어, 10만 번째마다 하나씩만 출력합니다 (100만 개를 전부 출력하면 너무 길기 때문).
- 사용 후 반드시 `free(arr)`로 해제합니다.

**예상 출력**
```
0 100000 200000 300000 400000 500000 600000 700000 800000 900000
```

---

### 2.4 스택 vs 힙 비교

| 구분 | 스택 (Stack) | 힙 (Heap) |
|------|-------------|-----------|
| **할당 방법** | `int arr[10];` (선언) | `malloc(sizeof(int)*10)` |
| **해제** | 함수 종료 시 자동 | `free()`로 직접 해제 |
| **크기 제한** | 보통 1~2MB | 수 GB까지 가능 |
| **속도** | 빠름 | 상대적으로 느림 |
| **용도** | 작은 지역 변수 | 큰 배열, 실행 중 크기 결정 |

---

## 3. 메모리 레이아웃 이해 (보충)

### 3.1 메모리 영역별 주소 확인

```c
#include <stdio.h>
#include <string.h>
int global_n = 100;
void a() { }
int main()
{
	int local_n = 10;
	static int static_n = 20;
	const char* s = "ABC";
	int* p = malloc(sizeof(int));

	printf("%p\n", &global_n);
	printf("%p\n", &static_n);
	printf("%p\n", s);
	printf("\n");
	printf("%p\n", &local_n);
	printf("%p\n", &s);
	printf("%p\n", &p);
	printf("\n");
	printf("%p\n", p);
	printf("\n");
	printf("%p\n", main);
	printf("%p\n", a);

	free(p);
}
```

**설명**
- 이 코드는 C 프로그램의 **메모리 영역**을 확인하기 위한 예제입니다.
- `%p`는 **주소(포인터)**를 16진수로 출력하는 형식 지정자입니다.

| 변수/대상 | 메모리 영역 | 설명 |
|-----------|------------|------|
| `global_n` | **데이터(Data) 영역** | 전역 변수 |
| `static_n` | **데이터(Data) 영역** | static 지역 변수 |
| `"ABC"` | **데이터(읽기 전용) 영역** | 상수 문자열 |
| `local_n`, `s`, `p` | **스택(Stack) 영역** | 지역 변수 |
| `malloc` 결과 | **힙(Heap) 영역** | 동적 할당 메모리 |
| `main`, `a` | **코드(Code) 영역** | 함수 코드 |

- 실행해 보면 같은 영역의 변수들은 **주소가 비슷한 범위**에 있고, 다른 영역은 주소가 크게 다른 것을 확인할 수 있습니다.

---

## 4. 문자열 함수 (strcpy_s, strcat_s, strcmp, strlen)

문자열 관련 함수들은 `<string.h>`에 선언되어 있습니다.

### 4.1 주요 문자열 함수 사용법

```c
#include <stdio.h>
#include <string.h>
int main()
{
	//strcpy_s(); 복사
	//strcat_s(); 붙이기
	//strcmp();   비교
	//strlen();   길이

	char* a = "abc";
	char* b = "ABCD";
	char buf[100];

	printf("%d %d\n", strlen(a), strlen(b));
	strcpy_s(buf, strlen(a) + 1, a);
	printf("%s\n", buf);
	strcat_s(buf, strlen(a)+strlen(b) + 1, b);
	printf("%s\n", buf);
	printf("\n");
	printf("%d\n", strcmp("ABC", "BAC"));
	printf("%d\n", strcmp("ABC", "ABC"));
	printf("%d\n", strcmp("ABC","AAAA"));
}
```

**설명**

| 함수 | 기능 | 사용 예 |
|------|------|---------|
| `strlen(s)` | 문자열 길이 반환 (널 문자 제외) | `strlen("abc")` → 3 |
| `strcpy_s(dest, size, src)` | src를 dest에 **복사** | `strcpy_s(buf, 4, "abc")` |
| `strcat_s(dest, size, src)` | dest 뒤에 src를 **이어 붙임** | `strcat_s(buf, 8, "ABCD")` |
| `strcmp(a, b)` | 두 문자열을 **사전순 비교** | 같으면 0, a<b면 음수, a>b면 양수 |

- `strlen(a) + 1` : 문자열 길이 + 널 문자(`'\0'`) 1바이트를 포함한 크기입니다.
- `strcpy_s`로 `"abc"`를 buf에 복사한 뒤, `strcat_s`로 `"ABCD"`를 이어 붙이면 `"abcABCD"`가 됩니다.
- `strcmp("ABC", "BAC")` : 'A' < 'B'이므로 **음수** 반환.
- `strcmp("ABC", "ABC")` : 같으므로 **0** 반환.
- `strcmp("ABC", "AAAA")` : 두 번째 문자 'B' > 'A'이므로 **양수** 반환.

**예상 출력**
```
3 4
abc
abcABCD

-1
0
1
```

---

### 4.2 strcpy_s로 문자열 복사 (스택 버퍼)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	const char* s = "ABCDE";
	char buf[100];

	strcpy_s(buf, strlen(s) + 1, s);
	printf("string: %s\n", buf);
}
```

**설명**
- `char buf[100]` : 스택에 100바이트짜리 배열을 선언합니다.
- `strcpy_s(buf, strlen(s) + 1, s)` : 문자열 `"ABCDE"`(5글자 + 널 문자 = 6바이트)를 buf에 복사합니다.
- 두 번째 인자 `strlen(s) + 1`은 복사할 **최대 크기**(널 문자 포함)입니다.

**예상 출력**
```
string: ABCDE
```

---

### 4.3 strcpy_s로 문자열 복사 (동적 버퍼)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	const char* s = "ABCDE";
	char* buf = NULL;

	buf = (char*)malloc(strlen(s) + 1);
	strcpy_s(buf, strlen(s) + 1, s);
	printf("string: %s\n", buf);

	free(buf);
}
```

**설명**
- `malloc(strlen(s) + 1)` : 문자열 길이 + 널 문자 크기만큼 **힙에 동적 할당**합니다.
- 스택 버퍼(`char buf[100]`)와 달리, **필요한 만큼만** 메모리를 사용할 수 있습니다.
- 동적 할당한 버퍼는 반드시 `free(buf)`로 해제합니다.

**예상 출력**
```
string: ABCDE
```

---

### 4.4 strcmp 직접 구현하기 (1단계: 뼈대)

```c
#include <stdio.h>
#include <string.h>

int ustrcmp(char* a, char* b)
{
	return 0;
}
int main()
{
	char* a = "abc";
	char* b = "abc";
	char* c = "abcd";
	char* d = "BBC";

	printf("%d\n", strcmp(a, b)); // 0
	printf("%d\n", strcmp(a, c)); // -1
	printf("%d\n", strcmp(a, d)); // 1
}
```

**설명**
- `ustrcmp`(사용자 정의 strcmp)의 **뼈대**입니다. 아직 구현이 없고 항상 0을 반환합니다.
- `main`에서는 표준 `strcmp`를 사용해 **기대하는 결과**를 먼저 확인합니다.
- 이 결과를 목표로 `ustrcmp`를 단계적으로 구현해 나갑니다.

**예상 출력 (strcmp 사용)**
```
0
-1
1
```

---

### 4.5 strcmp 직접 구현하기 (2단계: 같음 비교)

```c
#include <stdio.h>
#include <string.h>

int ustrcmp(char* a, char* b)
{
	if (strlen(a) != strlen(b))
		return 0;

	for (int i = 0; a[i]; ++i)
		if (a[i] != b[i])
			return 0;

	return 1;
}
int main()
{
	char* a = "abc";
	char* b = "abc";
	char* c = "abcd";

	printf("%d\n", ustrcmp(a, b));// 1
	printf("%d\n", ustrcmp(a, c));// 0
}
```

**설명**
- 먼저 **길이가 다르면** 다른 문자열이므로 0을 반환합니다.
- 길이가 같으면 **한 글자씩 비교**합니다. 다른 글자가 있으면 0(다름), 모두 같으면 1(같음)을 반환합니다.
- 이 버전은 "같다/다르다"만 판별하며, 표준 `strcmp`처럼 **대소 비교(-1, 0, 1)**는 하지 않습니다.

**예상 출력**
```
1
0
```

---

### 4.6 strcmp 직접 구현하기 (3단계: 완전한 비교)

```c
#include <stdio.h>
#include <string.h>

int ustrcmp(char* a, char* b)
{
	int na = strlen(a);
	int nb = strlen(b);
	if (na > nb)
	{
		na = nb;
	}

	int i = 0;
	for (i = 0; i < na; ++i)
	{
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	if (a[i] == b[i])
		return 0;
	else if (a[i] == '\0')
		return -1;
	else
		return 1;
}
int main()
{
	char* a = "abc";
	char* b = "abc";
	char* c = "abcd";
	char* d = "BBC";

	printf("%d\n", strcmp(a, b)); // 0
	printf("%d\n", strcmp(a, c)); // -1
	printf("%d\n", strcmp(a, d)); // 1
}
```

**설명**
- 두 문자열 중 **짧은 쪽 길이**만큼 한 글자씩 비교합니다.
- 비교 도중 `a[i] > b[i]`이면 1, `a[i] < b[i]`이면 -1을 반환합니다.
- 짧은 쪽 길이까지 모두 같으면:
  - 두 문자열 길이가 같으면 (`a[i] == b[i]`, 둘 다 `'\0'`) → **0** (같음)
  - a가 더 짧으면 (`a[i] == '\0'`) → **-1** (a가 앞)
  - b가 더 짧으면 → **1** (a가 뒤)
- 이제 표준 `strcmp`와 동일한 동작을 합니다.

**예상 출력**
```
0
-1
1
```

---

## 5. const와 const 포인터

`const`는 **값을 변경할 수 없게** 만드는 키워드입니다. 포인터와 함께 사용하면 다양한 조합이 가능합니다.

### 5.1 const 변수

```c
#include <stdio.h>
#include <string.h>
int main()
{
	int n = 10;
	const int cn = 10;

	printf("%d %d\n", n, cn);
	n = 20;
	cn = 30;    // 컴파일 오류! const 변수는 값 변경 불가
	printf("%d %d\n", n, cn);
}
```

**설명**
- `const int cn = 10` : 상수 변수입니다. 선언 시 초기화한 값을 **변경할 수 없습니다**.
- `n = 20` : 일반 변수이므로 값 변경이 가능합니다.
- `cn = 30` : **컴파일 오류**가 발생합니다. const 변수에 새 값을 대입할 수 없습니다.

---

### 5.2 const int* — 포인터를 통한 값 변경 금지

```c
#include <stdio.h>
#include <string.h>
int main()
{
	int n = 10;
	const int* p = &n;

	n = 100;
	//*p = 100;     // X — const int*를 통해 값을 변경할 수 없음
	int k = 20;
	p = &k;         // OK — 포인터가 가리키는 대상은 변경 가능
	printf("%d %d\n", n, *p);
}
```

**설명**
- `const int* p` : p가 가리키는 **값을 읽기만** 할 수 있습니다.
- `*p = 100` : **컴파일 오류**. 포인터를 통해 값을 쓸 수 없습니다.
- `p = &k` : **가능**. 포인터 자체(가리키는 대상)는 바꿀 수 있습니다.
- `n = 100` : `n` 자체는 const가 아니므로, 직접 값을 바꾸는 것은 가능합니다.

**예상 출력**
```
100 20
```

---

### 5.3 int* const — 포인터 자체 변경 금지

```c
#include <stdio.h>
#include <string.h>
int main()
{
	int n = 10;
	int* const p = &n;

	n = 100;
	*p = 100;       // OK — 포인터를 통한 값 변경 가능
	int k = 20;
	p = &k;         // 컴파일 오류! const 포인터는 다른 주소로 변경 불가
	printf("%d %d\n", n, *p);
}
```

**설명**
- `int* const p` : **포인터 자체가 상수**입니다. 한 번 초기화하면 다른 주소를 가리킬 수 없습니다.
- `*p = 100` : **가능**. 포인터를 통해 값을 쓸 수 있습니다.
- `p = &k` : **컴파일 오류**. 포인터가 가리키는 대상을 바꿀 수 없습니다.

---

### 5.4 const int* const — 둘 다 금지

```c
#include <stdio.h>
#include <string.h>
int main()
{
	int n = 10;
	const int* const p = &n;

	n = 100;
	*p = 100;       // 컴파일 오류! 값 변경 불가
	int k = 20;
	p = &k;         // 컴파일 오류! 포인터 변경 불가
	printf("%d %d\n", n, *p);
}
```

**설명**
- `const int* const p` : 포인터를 통한 **값 변경도, 포인터 자체 변경도 모두 불가**합니다.
- 오직 **읽기**만 가능하며, 항상 초기화된 주소의 값을 읽습니다.

---

### 5.5 const 포인터 조합 정리

| 선언 | `*p = 값` (값 변경) | `p = &k` (포인터 변경) |
|------|---------------------|----------------------|
| `int* p` | **가능** | **가능** |
| `const int* p` | **불가** | **가능** |
| `int* const p` | **가능** | **불가** |
| `const int* const p` | **불가** | **불가** |

> **읽는 법**: `const`가 `*` **왼쪽**에 있으면 "가리키는 값이 상수", `*` **오른쪽**에 있으면 "포인터 자체가 상수".

---

### 5.6 const char*와 문자열 리터럴

```c
#include <stdio.h>
#include <string.h>
int main()
{
	const char* s = "ABC";

	printf("%c\n", *s);  // Read — 읽기는 가능
	*s = 'Z';            // Write — 컴파일 오류! const char*를 통해 쓸 수 없음

	printf("string: %s\n", s);
}
```

**설명**
- `"ABC"`는 **문자열 리터럴**로, 읽기 전용 메모리에 저장됩니다.
- `const char* s`로 선언하면, 컴파일러가 **쓰기 시도를 오류로 잡아** 줍니다.
- `*s = 'Z'`처럼 문자열 리터럴의 내용을 바꾸려고 하면 **컴파일 오류**가 발생합니다.
- 문자열 리터럴을 가리키는 포인터는 항상 `const char*`로 선언하는 것이 안전합니다.

---

## 6. 배열과 문자열을 함수에 전달하기

### 6.1 문자열을 함수에 전달 (PrintString)

```c
#include <stdio.h>
#include <string.h>
void PrintString(const char* s)
{
	printf("string: %s\n", s);
}
int main()
{
	char* s = "ABC";

	PrintString(s);
	PrintString("12345");
}
```

**설명**
- `void PrintString(const char* s)` : 문자열 포인터를 받아 출력하는 함수입니다.
- 매개변수에 `const`를 붙여, 함수 안에서 문자열을 **수정하지 않겠다**는 의도를 나타냅니다.
- 변수 `s`를 전달해도 되고, 문자열 리터럴 `"12345"`를 직접 전달해도 됩니다.

**예상 출력**
```
string: ABC
string: 12345
```

---

### 6.2 배열을 함수에 전달 (PrintArray)

```c
#include <stdio.h>
#include <string.h>
void PrintArray(const int arr[], int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}
int main()
{
	int arr[4] = { 10,20,30,40 };

	PrintArray(arr, 4);
	printf("%d\n", arr[0]);
}
```

**설명**
- `void PrintArray(const int arr[], int size)` : 정수 배열과 크기를 받아 출력합니다.
- 배열 이름 `arr`은 **첫 번째 원소의 주소**이므로, 함수에 전달하면 원본 배열을 직접 접근합니다.
- `const int arr[]`로 선언하면, 함수 안에서 배열 원소를 **변경할 수 없습니다** (읽기 전용).
- 배열 크기는 함수에서 알 수 없으므로, `size` 매개변수로 **별도 전달**해야 합니다.

**예상 출력**
```
10 20 30 40
10
```

---

### 6.3 배열 초기화 함수 추가 (ResetArray)

```c
#include <stdio.h>
#include <string.h>
void PrintArray(const int arr[], int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}
void ResetArray(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
		arr[i] = 0;
}
int main()
{
	int arr[4] = { 10,20,30,40 };

	ResetArray(arr, 4);
	PrintArray(arr, 4);
}
```

**설명**
- `ResetArray` : 배열의 모든 원소를 **0으로 초기화**합니다.
- `PrintArray`와 달리, `ResetArray`의 매개변수에는 `const`가 **없습니다**. 배열을 **수정해야** 하기 때문입니다.
- `ResetArray(arr, 4)` 호출 후 `PrintArray(arr, 4)`를 하면, 원래 {10, 20, 30, 40}이었던 배열이 {0, 0, 0, 0}으로 바뀐 것을 확인할 수 있습니다.

**예상 출력**
```
0 0 0 0
```

> **핵심**: 배열을 함수에 전달하면 **원본이 전달**(포인터 전달)됩니다. 읽기만 할 때는 `const`를 붙이고, 수정이 필요할 때는 `const` 없이 선언합니다.

---

## 7. 메뉴 기반 정수 관리 프로그램

이 절에서는 `_getch`와 `switch`를 활용하여, 정수를 입력·출력·검색·삭제하는 **메뉴 기반 프로그램**을 단계별로 완성합니다. `_getch()`는 `<conio.h>`에 선언된 함수로, **Enter 없이 키 하나를 바로 입력받습니다**.

### 7.1 기본 메뉴 구조 (_getch와 switch)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
void Menu()
{
	puts("1. 정수 입력");
	puts("2. 모든 정수 출력");
	puts("3. 정수 찾기");
	puts("4. 정수 삭제");
	puts("===============");
}
int main()
{
	int* arr = (int*)malloc(sizeof(int) * 1000);
	int count=0;
	int run = 1;

	while (run)
	{
		Menu();
		switch (_getch())
		{
		case '1':
			printf("메뉴1");
			break;
		case '2':
			printf("메뉴2");
			break;
		case '3':
			printf("메뉴3");
			break;
		case '4':
			printf("메뉴4");
			break;
		default:
			printf("프로그램 종료!");
			run = 0;
			break;
		}
	}
	free(arr);
}
```

**설명**
- `Menu()` : `puts`로 메뉴 항목을 출력합니다. `puts`는 문자열 출력 후 자동 줄바꿈합니다.
- `_getch()` : 키보드에서 **한 글자를 바로 입력**받습니다 (Enter 불필요).
- `switch` : 입력된 키에 따라 해당 `case`로 분기합니다.
  - `'1'`~`'4'` : 각 메뉴에 해당하는 동작 (이 단계에서는 텍스트만 출력).
  - `default` : 1~4 외의 키를 누르면 `run = 0`으로 설정하여 **while 루프 종료** → 프로그램 종료.
- `while (run)` : `run`이 1이면 계속 반복, 0이 되면 종료합니다.
- 동적 배열 `arr`은 아직 사용하지 않지만, 다음 단계를 위해 미리 할당해 둡니다.

---

### 7.2 메뉴에 기능 추가 (인라인 구현)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
void Menu()
{
	puts("1. 정수 입력");
	puts("2. 모든 정수 출력");
	puts("3. 정수 찾기");
	puts("4. 정수 삭제");
	puts("===============");
}
int main()
{
	int* arr = (int*)malloc(sizeof(int) * 1000);
	int count = 0;
	int run = 1;

	while (run)
	{
		Menu();
		switch (_getch())
		{
		case '1':
			{
				int data = 0;
				printf("정수입력:");
				scanf_s("%d", &data);
				arr[count++] = data;
			}
			break;
		case '2':
			for (int i = 0; i < count; ++i)
				printf("[%d] : %d\n", i, arr[i]);
			break;
		case '3':
			{
				int data = 0;
				printf("찾을 정수 입력:");
				scanf_s("%d", &data);
				for (int i = 0; i < count; ++i)
					if (data == arr[i])
					{
						printf("%d의 원소는 %d\n", i, arr[i]);
						break;
					}
			}
			break;
		case '4':
			{
				int data = 0;
				printf("삭제할 정수 입력:");
				scanf_s("%d", &data);
				for (int i = 0; i < count; ++i)
					if (data == arr[i])
					{
						for (int j = i; j < count - 1; ++j)
							arr[j] = arr[j + 1];
						--count;
						break;
					}
			}
			break;
		default:
			printf("프로그램 종료!");
			run = 0;
			break;
		}
	}
	free(arr);
}
```

**설명**
- 7.1의 뼈대에 **실제 기능**을 추가한 버전입니다. 모든 로직이 `switch` 안에 인라인으로 작성되어 있습니다.

| 메뉴 | 동작 |
|------|------|
| **1. 정수 입력** | `scanf_s`로 정수를 입력받아 `arr[count++]`에 저장 |
| **2. 모든 정수 출력** | 0번부터 `count-1`번까지 모든 원소 출력 |
| **3. 정수 찾기** | 입력한 값과 일치하는 원소를 찾아 인덱스와 값 출력 |
| **4. 정수 삭제** | 일치하는 원소를 찾아 뒤의 원소를 한 칸씩 앞으로 당기고 `count` 감소 |

- `case` 안에서 **변수를 선언**할 때는 `{ }` 블록으로 감싸야 합니다 (C의 문법 규칙).
- 삭제 알고리즘: 배열에서 원소를 제거하면 빈 자리가 생기므로, `arr[j] = arr[j + 1]`로 뒤의 원소를 앞으로 복사합니다.

---

### 7.3 함수로 분리한 완성 프로그램

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
void Menu()
{
	puts("1. 정수 입력");
	puts("2. 모든 정수 출력");
	puts("3. 정수 찾기");
	puts("4. 정수 삭제");
	puts("===============");
}
void InputInteger(int arr[], int* pcount)
{
	int data = 0;
	printf("정수입력:");
	scanf_s("%d", &data);
	arr[(*pcount)++] = data;
}
void PrintInteger(const int arr[], int count)
{
	for (int i = 0; i < count; ++i)
		printf("[%d] : %d\n", i, arr[i]);
}
void SearchInteger(const int arr[], int count)
{
	int data = 0;
	printf("찾을 정수 입력:");
	scanf_s("%d", &data);
	for (int i = 0; i < count; ++i)
		if (data == arr[i])
		{
			printf("%d의 원소는 %d\n", i, arr[i]);
			break;
		}
}
void RemoveInteger(int arr[], int* pcount)
{
	int data = 0;
	printf("삭제할 정수 입력:");
	scanf_s("%d", &data);
	for (int i = 0; i < *pcount; ++i)
		if (data == arr[i])
		{
			for (int j = i; j < *pcount - 1; ++j)
				arr[j] = arr[j + 1];
			--*pcount;
			break;
		}
}
int main()
{
	int* arr = (int*)malloc(sizeof(int) * 1000);
	int count = 0;
	int run = 1;

	while (run)
	{
		Menu();
		switch (_getch())
		{
		case '1':
			InputInteger(arr, &count);
			break;
		case '2':
			PrintInteger(arr, count);
			break;
		case '3':
			SearchInteger(arr, count);
			break;
		case '4':
			RemoveInteger(arr, &count);
			break;
		default:
			printf("프로그램 종료!");
			run = 0;
			break;
		}
	}
	free(arr);
}
```

**설명**
- 7.2의 인라인 코드를 **별도 함수**로 분리한 **최종 완성본**입니다.
- `main` 함수가 간결해지고, 각 기능을 독립적으로 테스트·수정할 수 있습니다.

| 함수 | 매개변수 | 역할 |
|------|----------|------|
| `InputInteger` | `int arr[], int* pcount` | 정수 입력 후 배열에 추가 |
| `PrintInteger` | `const int arr[], int count` | 모든 원소 출력 |
| `SearchInteger` | `const int arr[], int count` | 특정 정수 검색 |
| `RemoveInteger` | `int arr[], int* pcount` | 특정 정수 삭제 |

- **`int* pcount`** (포인터로 전달): `InputInteger`와 `RemoveInteger`는 `count`를 **변경**해야 하므로 포인터를 받습니다. `(*pcount)++`처럼 역참조하여 원본 값을 증가시킵니다.
- **`const int arr[]`**: `PrintInteger`와 `SearchInteger`는 배열을 읽기만 하므로 `const`를 붙여 실수로 수정하는 것을 방지합니다.
- **`int arr[]`** (const 없음): `InputInteger`와 `RemoveInteger`는 배열을 수정해야 하므로 `const` 없이 선언합니다.

**예상 실행 흐름**
```
1. 정수 입력
2. 모든 정수 출력
3. 정수 찾기
4. 정수 삭제
===============
(1을 누르면)
정수입력:42
1. 정수 입력
2. 모든 정수 출력
3. 정수 찾기
4. 정수 삭제
===============
(2를 누르면)
[0] : 42
```

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| **동적 메모리 할당** | `malloc(크기)` → 힙 메모리 할당, `free(포인터)` → 해제 |
| **sizeof 활용** | `malloc(sizeof(int) * n)` — 타입 크기를 직접 쓰지 않아 이식성 좋음 |
| **동적 배열** | `int* arr = (int*)malloc(sizeof(int) * n)` — 배열처럼 `arr[i]`로 접근 |
| **스택 vs 힙** | 스택은 크기 제한(~1MB), 힙은 큰 배열에 적합 |
| **메모리 영역** | 코드, 데이터(전역/static), 스택(지역), 힙(malloc) |
| **strlen** | 문자열 길이 반환 (널 문자 제외) |
| **strcpy_s** | 문자열 복사: `strcpy_s(dest, size, src)` |
| **strcat_s** | 문자열 이어 붙이기: `strcat_s(dest, size, src)` |
| **strcmp** | 문자열 비교: 같으면 0, 사전순 앞이면 음수, 뒤면 양수 |
| **const 변수** | `const int cn = 10;` — 값 변경 불가 |
| **const int\*** | 포인터를 통한 값 변경 불가, 포인터 변경 가능 |
| **int\* const** | 포인터를 통한 값 변경 가능, 포인터 변경 불가 |
| **배열을 함수에 전달** | 배열 이름 = 포인터, 크기는 별도 전달, 읽기 전용이면 `const` 사용 |
| **_getch()** | Enter 없이 키 하나 입력, `<conio.h>` 필요 |
| **switch** | 여러 조건 분기, 각 case 끝에 `break` 필수 |
| **puts** | 문자열 출력 + 자동 줄바꿈 |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `malloc`으로 int 5개짜리 동적 배열을 만들고, 사용자로부터 `scanf_s`로 5개의 정수를 입력받은 뒤 모두 출력하고, `free`로 해제하는 프로그램을 작성하세요.

2. 두 개의 문자열 `"Hello"`와 `" World"`를 `strcpy_s`와 `strcat_s`를 사용하여 하나로 합쳐 `"Hello World"`를 출력하세요.

3. `const int*`, `int* const`, `const int* const`를 각각 선언하고, 값 변경과 포인터 변경을 시도하여 **어떤 줄에서 컴파일 오류가 나는지** 직접 확인해 보세요.

4. 7.3절의 메뉴 프로그램에 **"5. 모든 정수 합계 출력"** 기능을 추가하는 `SumInteger` 함수를 작성해 보세요.

5. `ustrcmp` 함수를 참고하여, 두 문자열이 **대소문자를 무시하고** 같은지 비교하는 `ustricmp` 함수를 직접 구현해 보세요. (힌트: `'A'`와 `'a'`의 ASCII 코드 차이는 32입니다.)

---

이 강의 자료는 **example/ex14.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 1~3장은 **동적 메모리와 배열**의 기초, 4장은 **문자열 함수**, 5~6장은 **const와 함수 전달**, 7장은 **종합 실습 프로그램**입니다. 1장부터 순서대로 직접 코드를 입력하고 실행해 보면서 학습하면 효과적입니다.
