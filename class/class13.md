# C언어 기초 강의 13 - ex13.cpp 코드를 통한 문자열과 포인터 활용

이 강의는 **example/ex13.cpp**에 담긴 예제들을 바탕으로, **문자열(char\* 와 char[])**, **널 종료 문자**, **ASCII 코드**, **문자열 복사**, **배열 최소값 찾기 함수**, **sizeof와 배열 크기**, **포인터와 배열 이름** 등을 정리한 내용입니다. 파일 아래쪽 코드가 가장 기초적인 내용이고, 위로 갈수록 발전된 내용입니다.

---

## 0. 학습 목표와 준비물

### 0.1 학습 목표

- 포인터와 배열 이름의 관계를 이해하고, 주소 연산(`&`, `+`, `-`)을 사용할 수 있다.
- `sizeof`로 배열 전체 크기, 원소 크기, 원소 개수를 구할 수 있다.
- 배열을 함수에 전달하는 방법(`int* arr`, `int arr[]`)을 이해한다.
- 배열에서 최소값을 찾는 함수를 단계적으로 작성할 수 있다.
- `char*`와 `char[]`의 차이를 알고, 문자열 리터럴의 특성을 이해한다.
- 널 종료 문자(`'\0'`)를 이용한 문자열 순회 방법을 사용할 수 있다.
- ASCII 코드를 이해하고, 대/소문자를 판별하여 개수를 셀 수 있다.
- 문자열 복사를 반복문과 `strcpy`로 구현할 수 있다.
- 널 포인터(NULL), 널 문자(`'\0'`), 빈 문자열(`""`)의 차이를 설명할 수 있다.

---

### 0.2 준비물

| 항목 | 설명 |
|------|------|
| **개발 환경** | Visual Studio, Dev C++, Code::Blocks, VS Code + C 확장 등 C/C++을 컴파일·실행할 수 있는 도구 |
| **교재/예제** | ex13.cpp (또는 이 강의 자료의 코드 블록) |
| **선수 지식** | 포인터 기초(`*`, `&`), 배열 선언, for/while 반복문, 함수 정의와 호출 |
| **실습** | 주석 처리된 코드를 하나씩 풀어서 **컴파일 → 실행**해 보는 것이 필수입니다. |

---

## 1. 포인터와 주소 연산 복습

포인터와 배열의 관계를 이해하는 것이 문자열을 다루기 위한 첫걸음입니다.

### 1.1 short 포인터와 주소 증감

```c
#include <stdio.h>
int main()
{
	short n = 100;

	printf("%p \n", &n);
	printf("%p \n", &n+1);
	printf("%p \n", &n-1);
}
```

**설명**
- `&n` : 변수 `n`의 **메모리 주소**를 구합니다.
- `&n + 1` : `short`는 **2바이트**이므로, 주소가 **2만큼 증가**합니다.
- `&n - 1` : 주소가 **2만큼 감소**합니다.
- 포인터 연산에서 `+1`은 "다음 원소"를 의미하며, 실제 증가하는 바이트 수는 **가리키는 타입의 크기**에 따라 달라집니다.

---

### 1.2 short 포인터 변수 사용

```c
#include <stdio.h>
int main()
{
	short n = 100;
	short* p = &n;

	printf("%p %p\n", &n, p);
	printf("%p %p\n", &n + 1, p+1);
	printf("%p %p\n", &n - 1, p-1);
}
```

**설명**
- `short* p = &n;` : 포인터 변수 `p`에 `n`의 주소를 저장합니다.
- `&n`과 `p`는 **같은 주소**를 가리키므로, `&n + 1`과 `p + 1`도 동일합니다.
- 포인터 변수를 사용하면 주소를 변수처럼 다룰 수 있어 편리합니다.

---

### 1.3 배열 원소의 주소 확인

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };

	printf("%p\n", &arr[0]);
	printf("%p\n", &arr[1]);
	printf("%p\n", &arr[2]);
	printf("%p\n", &arr[3]);
	printf("\n");
	printf("%p\n", &arr[0]+1);
	printf("%p\n", &arr[1]+1);
	printf("%p\n", &arr[2]+1);
	printf("%p\n", &arr[3]+1);
}
```

**설명**
- `int` 배열의 원소는 메모리에 **연속으로** 배치됩니다.
- `&arr[0]`과 `&arr[1]`의 차이는 `sizeof(int)` = **4바이트**입니다.
- `&arr[0] + 1`은 `&arr[1]`과 **같은 주소**입니다. 포인터 연산에서 `+1`은 "다음 원소"를 뜻합니다.

---

### 1.4 포인터 역참조로 값 읽기

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	int* p = &arr[0];

	printf("%p\n", &arr[0]);
	printf("%p\n", &arr[1]);
	printf("%p\n", &arr[2]);
	printf("%p\n", &arr[3]);
	printf("\n");
	printf("%d\n", *p);
}
```

**설명**
- `int* p = &arr[0];` : 포인터 `p`가 배열의 **첫 번째 원소**를 가리킵니다.
- `*p` : 포인터가 가리키는 주소의 **값을 읽는** 연산(역참조)입니다. 결과는 `10`입니다.

---

### 1.5 포인터 산술과 역참조

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	int* p = &arr[0];

	printf("%p\n", &arr[0]);
	printf("%p\n", &arr[1]);
	printf("%p\n", &arr[2]);
	printf("%p\n", &arr[3]);
	printf("\n");
	printf("%p %d\n", p, *(p+0));
	printf("%p %d\n", p + 1, *(p+1));
	printf("%p %d\n", p + 2, *(p+2));
	printf("%p %d\n", p + 3, *(p+3));
}
```

**설명**
- `p + i` : 포인터에서 **i번째 원소**의 주소를 계산합니다.
- `*(p + i)` : 그 주소의 **값을 읽습니다**. 즉 `arr[i]`와 같습니다.

---

### 1.6 포인터 인덱싱과 역참조의 동등성

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	int* p = &arr[0];

	printf("%d %d\n", *p, p[0]);
	printf("%d %d\n", *(p+1), p[1]);
	printf("%d %d\n", *(p+2), p[2]);
	printf("%d %d\n", *(p+3), p[3]);
}
```

**설명**
- `*(p + i)`와 `p[i]`는 **완전히 같은 의미**입니다.
- C에서 `p[i]`는 내부적으로 `*(p + i)`로 변환됩니다.
- 따라서 포인터도 배열처럼 `[]` 인덱싱을 사용할 수 있습니다.

---

### 1.7 배열 이름 = 첫 번째 원소의 주소

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	
	printf("%p %p\n", &arr[0], arr);
	printf("%p %p\n", &arr[0]+1, arr+1);
}
```

**설명**
- **배열 이름 `arr`은 `&arr[0]`과 같은 주소**를 나타냅니다.
- `arr + 1`은 `&arr[0] + 1`과 같으므로 `&arr[1]`입니다.
- 배열 이름은 포인터처럼 사용할 수 있지만, 재대입(`arr = 다른주소`)은 불가능합니다.

---

### 1.8 포인터에 변수 주소와 배열 이름 대입

```c
#include <stdio.h>
int main()
{
	int n = 100;
	int arr[4] = { 10,20,30,40 };

	int* pa = &n;
	int* pb = arr;

	printf("%p %p\n", pa, pb);
}
```

**설명**
- `int* pa = &n;` : 일반 변수의 주소를 포인터에 저장합니다.
- `int* pb = arr;` : 배열 이름(= 첫 번째 원소 주소)을 포인터에 저장합니다.
- 둘 다 `int*` 타입이므로 동일한 방식으로 사용할 수 있습니다.

---

## 2. 함수에 배열 전달하기

배열은 함수에 전달할 때 **포인터**로 전달됩니다. 이 절에서는 단계적으로 배열을 함수에 전달하는 방법을 익힙니다.

### 2.1 함수에 포인터만 전달 (크기 없음)

```c
#include <stdio.h>
void PrintArray(int* pa)
{
	printf("%d\n", pa[0]);
	printf("%d\n", pa[1]);
	printf("%d\n", pa[2]);
	printf("%d\n", pa[3]);

}
int main()
{
	int arr[4] = { 10,20,30,40 };

	PrintArray(arr);
}
```

**설명**
- `PrintArray(arr)` : 배열 이름 `arr`을 인자로 넘기면, 함수에서는 **포인터**(`int* pa`)로 받습니다.
- 함수 안에서 `pa[0]`, `pa[1]` 등으로 원소에 접근할 수 있습니다.
- 단점: 배열 크기를 함수가 **알 수 없으므로**, 원소 개수를 하드코딩해야 합니다.

**예상 출력**
```
10
20
30
40
```

---

### 2.2 함수에 포인터와 크기 전달 (직접 인덱싱)

```c
#include <stdio.h>
void PrintArray(int* pa, int size)
{
	printf("%d\n", pa[0]);
	printf("%d\n", pa[1]);
	printf("%d\n", pa[2]);
	printf("%d\n", pa[3]);
}
int main()
{
	int arr[4] = { 10,20,30,40 };

	PrintArray(arr, 4);
}
```

**설명**
- `size` 매개변수를 추가하여 배열의 크기 정보를 함께 전달합니다.
- 아직 `size`를 사용하지 않고 직접 인덱싱하고 있어 개선이 필요합니다.

---

### 2.3 PrintArray를 for 루프로 개선

```c
#include <stdio.h>
void PrintArray(int* pa, int size)
{
	for(int i = 0 ; i < size ; ++i)
		printf("%d\n", pa[i]);
}
int main()
{
	int arr[4] = { 10,20,30,40 };

	PrintArray(arr, 4);
}
```

**설명**
- `for` 루프와 `size`를 사용하여 **어떤 크기의 배열이든** 출력할 수 있습니다.
- 이제 `PrintArray`는 범용적인 함수가 되었습니다.

---

### 2.4 부분 배열 전달

```c
#include <stdio.h>
void PrintArray(int* pa, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d\n", pa[i]);
	printf("\n");
}
int main()
{
	int arr[4] = { 10,20,30,40 };

	PrintArray(arr, 2);
	PrintArray(arr + 2, 2);
	PrintArray(arr+1, 3);
}
```

**설명**
- `PrintArray(arr, 2)` : 배열의 **처음 2개** 원소(10, 20)를 출력합니다.
- `PrintArray(arr + 2, 2)` : 배열의 **3번째부터 2개** 원소(30, 40)를 출력합니다.
- `PrintArray(arr + 1, 3)` : 배열의 **2번째부터 3개** 원소(20, 30, 40)를 출력합니다.
- 포인터 산술(`arr + n`)을 이용하면 배열의 **일부분**만 함수에 전달할 수 있습니다.

**예상 출력**
```
10
20

30
40

20
30
40

```

---

### 2.5 음수 인덱스와 역순 접근

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	int* pa = arr + 3;

	printf("%d\n", pa[0]);
	printf("%d\n", pa[-1]);
	printf("%d\n", pa[-2]);
	printf("%d\n", pa[-3]);
	printf("\n");
	printf("%d\n", pa[3-0]);
	printf("%d\n", pa[3-1]);
	printf("%d\n", pa[3-2]);
	printf("%d\n", pa[3-3]);
}
```

**설명**
- `int* pa = arr + 3;` : 포인터를 배열의 **마지막 원소**(인덱스 3)에 위치시킵니다.
- `pa[-1]`은 `*(pa - 1)`이므로, 한 칸 앞의 원소(30)에 접근합니다.
- C에서 **음수 인덱스**도 문법적으로 가능하지만, 배열 범위를 벗어나지 않도록 주의해야 합니다.

**예상 출력**
```
40
30
20
10

40
30
20
10
```

---

### 2.6 포인터로 정방향·역방향 순회

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	int* pa = arr;

	for (int i = 0; i < 4; ++i)
		printf("%d %d\n", pa[i], pa[3 - i]);
}
```

**설명**
- `pa[i]` : 정방향(10→20→30→40)으로 접근합니다.
- `pa[3 - i]` : 역방향(40→30→20→10)으로 접근합니다.
- 하나의 루프에서 **정방향과 역방향**을 동시에 출력할 수 있습니다.

**예상 출력**
```
10 40
20 30
30 20
40 10
```

---

## 3. sizeof와 배열 크기

### 3.1 sizeof로 배열 크기와 원소 개수 구하기 (크기 지정 배열)

```c
#include <stdio.h>
int main()
{
	int arr[4] = { 10,20,30,40 };
	printf("array size : %d\n", sizeof(arr));
	printf("element size : %d\n", sizeof(arr[0]));
	printf("array count : %d\n", sizeof(arr)/sizeof(int));

	int* pa = arr;
	printf("%p %p\n", pa, arr);
	printf("%d %d\n", pa[0], arr[0]);
	printf("%d %d\n", sizeof(pa), sizeof(arr));
}
```

**설명**
- `sizeof(arr)` : 배열 전체의 바이트 크기 → `4 × 4 = 16`
- `sizeof(arr[0])` : 원소 하나의 바이트 크기 → `4`
- `sizeof(arr) / sizeof(int)` : **원소 개수** → `16 / 4 = 4`
- `sizeof(pa)` : **포인터 변수**의 크기(32비트: 4, 64비트: 8). 배열 크기와 **다릅니다**.
- `sizeof(arr)` : 배열 이름에 `sizeof`를 쓰면 **배열 전체 크기**가 나옵니다.
- 포인터와 배열 이름은 주소로 사용할 때는 같지만, `sizeof`에서는 **다르게 동작**합니다.

---

### 3.2 sizeof 활용 (크기 미지정 배열)

```c
#include <stdio.h>
int main()
{
	int arr[ ] = { 10,20,30,40,50 };
	printf("array size : %d\n", sizeof(arr));
	printf("element size : %d\n", sizeof(arr[0]));
	printf("array count : %d\n", sizeof(arr) / sizeof(int));

	int* pa = arr;
	printf("%p %p\n", pa, arr);
	printf("%d %d\n", pa[0], arr[0]);
	printf("%d %d\n", sizeof(pa), sizeof(arr));
}
```

**설명**
- `int arr[] = { 10,20,30,40,50 };` : 크기를 생략하면 초기화 값의 개수로 크기가 결정됩니다(5개).
- `sizeof(arr)` → `5 × 4 = 20`
- `sizeof(arr) / sizeof(int)` → `20 / 4 = 5`

**예상 출력 (64비트 환경)**
```
array size : 20
element size : 4
array count : 5
(주소 출력)
10 10
8 20
```

---

## 4. 배열 최소값 찾기 함수 (Min)

배열에서 최소값을 찾는 함수를 **단계적으로 발전**시키며 작성합니다.

### 4.1 Min 함수 뼈대 (잘못된 초기값)

```c
#include <stdio.h>
int Min(int* arr, int size)
{
	int minValue = -0xfffffff;
	return minValue;
}
int main()
{
	int arr[] = { 54,70,32,20,15,68,90,94 };
	int size = 8;

	int value = Min(arr, size);
	printf("가장 작은 원소 : %d\n", value);
}
```

**설명**
- `Min` 함수의 **뼈대**만 만든 상태입니다. 아직 배열을 순회하지 않습니다.
- `-0xfffffff`는 매우 작은 음수이므로, 항상 이 값이 반환됩니다.
- 이 코드는 **아직 올바르지 않습니다** — 다음 단계에서 개선합니다.

---

### 4.2 Min 함수 — 최소값 반환 (minValue 방식)

```c
#include <stdio.h>
int Min(int* arr, int size)
{
	int minValue = 0xfffffff;
	for (int i = 0; i < size; ++i)
		if( minValue > arr[i])
			minValue = arr[i];

	return minValue;
}
int main()
{
	int arr[] = { 54,70,32,20,15,68,90,94 };
	int size = 8;

	int value = Min(arr, size);
	printf("가장 작은 원소 : %d\n", value);
}
```

**설명**
- `minValue`를 매우 큰 값(`0xfffffff`)으로 초기화한 뒤, 배열을 순회하며 더 작은 값이 있으면 갱신합니다.
- 최종적으로 `minValue`에 배열의 **최소값**이 들어갑니다.
- 단점: 초기값을 임의로 큰 값으로 잡았으므로, 배열 원소가 모두 그보다 크면 오류가 발생할 수 있습니다.

**예상 출력**
```
가장 작은 원소 : 15
```

---

### 4.3 Min 함수 — 더미 반환 (인덱스 반환으로 전환 준비)

```c
#include <stdio.h>
int Min(int* arr, int size)
{	
	return 3;
}
int main()
{
	int arr[] = { 54,70,32,20,15,68,90,94 };
	int size = 8;

	int idx = Min(arr, size);
	if( idx != -1)
		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
}
```

**설명**
- 이제 **값** 대신 **인덱스**를 반환하는 방식으로 전환합니다.
- 더미로 `return 3;`을 넣어 구조를 먼저 만듭니다. `arr[3]`은 `20`입니다.
- `idx != -1` : 유효하지 않은 경우 `-1`을 반환하도록 규약을 정합니다.

**예상 출력**
```
가장 작은 원소 : [3]-20
```

---

### 4.4 Min 함수 — 인덱스 반환 (int* arr)

```c
#include <stdio.h>
int Min(int* arr, int size)
{
	if (size <= 0)
		return -1;

	int minIndex = 0;
	for (int i = 1; i < size; ++i)
		if (arr[minIndex] > arr[i])
			minIndex = i;
	return minIndex;
}
int main()
{
	int arr[] = { 54,70,32,20,15,68,90,94 };
	int size = 8;

	int idx = Min(arr, size);
	if (idx != -1)
		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
}
```

**설명**
- `minIndex`를 `0`(첫 번째 원소)으로 초기화하고, 나머지를 순회하며 더 작은 원소의 **인덱스**를 갱신합니다.
- `size <= 0`이면 배열이 비어 있으므로 `-1`을 반환합니다.
- 인덱스를 반환하면 **값과 위치 모두** 알 수 있어 유용합니다.

**예상 출력**
```
가장 작은 원소 : [4]-15
```

---

### 4.5 Min 함수 — 인덱스 반환 (int arr[] 매개변수)

```c
#include <stdio.h>
int Min(int arr[], int size)
{
	if (size <= 0)
		return -1;

	int minIndex = 0;
	for (int i = 1; i < size; ++i)
		if (arr[minIndex] > arr[i])
			minIndex = i;
	return minIndex;
}
int main()
{
	int arr[] = { 54,70,32,20,15,68,90,94 };
	int size = 8;

	int idx = Min(arr, size);
	if (idx != -1)
		printf("가장 작은 원소 : [%d]-%d\n", idx, arr[idx]);
}
```

**설명**
- 매개변수를 `int* arr` 대신 `int arr[]`로 쓸 수도 있습니다. **둘은 동일**합니다.
- 함수 매개변수에서 `int arr[]`은 `int* arr`과 같은 의미이며, 크기 정보는 전달되지 않습니다.
- 주석에 `//int* arr, int arr[100]`이라고 적혀 있는 것은 세 가지 표기가 모두 같다는 뜻입니다.

---

## 5. 문자열 포인터와 출력

이제 배열과 포인터의 기초를 바탕으로 **문자열**을 다룹니다.

### 5.1 char* 문자열과 주소 출력

```c
#include <stdio.h>
int main()
{
	char* s = "Hello!";

	printf("%s\n", s);
	printf("%s\n", "Hello!");
	printf("%p\n", s);
	printf("%p\n", "Hello!");
}
```

**설명**
- `char* s = "Hello!";` : 문자열 리터럴 `"Hello!"`의 **시작 주소**를 포인터 `s`에 저장합니다.
- `%s`로 출력하면 문자열 내용이, `%p`로 출력하면 **메모리 주소**가 나옵니다.
- `s`와 `"Hello!"`의 주소가 **같을 수도** 있습니다(컴파일러가 동일 리터럴을 합칠 수 있음).

---

### 5.2 const char* 문자열

```c
#include <stdio.h>
int main()
{
	const char* s = "Hello!";

	printf("%s\n", s);
	printf("%s\n", "Hello!");
	printf("%p\n", s);
	printf("%p\n", "Hello!");
}
```

**설명**
- `const char*`는 문자열 리터럴을 가리킬 때 **더 안전한 선언**입니다.
- `const`를 붙이면 `s[0] = 'Z'`처럼 **수정을 시도할 때 컴파일 오류**가 발생하여, 실수를 방지합니다.

---

### 5.3 문자열 포인터 연산

```c
#include <stdio.h>
int main()
{
	char* s = "Hello!";

	printf("%s %p\n", s, s);
	printf("%s %p\n", s + 1, s + 1);
	printf("%c %c\n", *s, s[0]);
}
```

**설명**
- `s` : `"Hello!"` 전체를 출력합니다.
- `s + 1` : **두 번째 문자**부터의 문자열, 즉 `"ello!"`를 출력합니다.
- `*s`와 `s[0]`은 **같은 값**(첫 번째 문자 `'H'`)입니다.

**예상 출력**
```
Hello! (주소)
ello! (주소+1)
H H
```

---

## 6. 문자열의 개별 문자 접근과 순회

### 6.1 개별 문자 하나씩 출력

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";

	printf("%d %c\n", s[0], s[0]);
	printf("%d %c\n", s[1], s[1]);
	printf("%d %c\n", s[2], s[2]);
}
```

**설명**
- `s[0]`은 `'A'`(ASCII 65), `s[1]`은 `'B'`(66), `s[2]`는 `'C'`(67)입니다.
- `%d`로 출력하면 **ASCII 코드**, `%c`로 출력하면 **문자**가 나옵니다.

**예상 출력**
```
65 A
66 B
67 C
```

---

### 6.2 for 루프로 문자열 순회 (길이 직접 지정)

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";

	for(int i = 0 ; i < 3 ; ++i)
		printf("%d %c\n", s[i], s[i]);
}
```

**설명**
- `i < 3` : 문자열의 길이를 **직접 지정**하여 순회합니다.
- 단점: 문자열이 바뀌면 숫자도 바꿔야 합니다. 다음 예제에서 개선합니다.

---

### 6.3 널 종료 문자('\0')를 이용한 순회

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";

	printf("NULL '\\0' : %d\n", '\0');

	for (int i = 0; s[i] ; ++i)
	//for (int i = 0; s[i] != '\0'; ++i)
		printf("%d %c\n", s[i], s[i]);
}
```

**설명**
- C 문자열은 끝에 **널 문자 `'\0'`**(값 0)이 자동으로 붙습니다. `"ABC"`는 실제로 `{'A','B','C','\0'}`입니다.
- `s[i]` : `'\0'`이면 값이 `0`이므로 **거짓(false)**이 되어 루프가 종료됩니다.
- `s[i] != '\0'`과 `s[i]`는 **같은 조건**입니다(0이 아닌 값은 참).
- 이 방식을 사용하면 문자열 길이를 미리 알 필요가 없습니다.

**예상 출력**
```
NULL '\0' : 0
65 A
66 B
67 C
```

---

## 7. char\*와 char[]의 차이

### 7.1 char* 문자열 리터럴 수정 시도

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";

	printf("%c\n", s[0]);
	s[0] = 'Z';
}
```

**설명**
- `char* s = "ABC";` : `s`는 **읽기 전용 메모리**에 저장된 문자열 리터럴을 가리킵니다.
- `s[0] = 'Z';` : 읽기 전용 메모리를 수정하려 하면 **런타임 오류**(크래시)가 발생할 수 있습니다.
- 문자열 리터럴은 **수정 불가**입니다.

---

### 7.2 const char*로 수정 방지

```c
#include <stdio.h>
int main()
{
	const char* s = "ABC";

	printf("%c\n", s[0]);
	s[0] = 'Z';
}
```

**설명**
- `const char*`로 선언하면, `s[0] = 'Z';`에서 **컴파일 오류**가 발생합니다.
- 런타임에 크래시가 나는 것보다 **컴파일 시점에 오류를 잡는 것**이 훨씬 안전합니다.
- 문자열 리터럴을 가리킬 때는 `const char*`를 쓰는 것이 좋습니다.

---

### 7.3 문자열을 만드는 4가지 방법

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";
	char a[] = "ABC";
	char b[4] = { 'A','B','C','\0' };
	char c[4] = { 65,66,67,0 };
	
	printf("%s\n", s);
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
}
```

**설명**

| 선언 | 의미 |
|------|------|
| `char* s = "ABC";` | 문자열 리터럴의 **주소**를 포인터에 저장 (읽기 전용) |
| `char a[] = "ABC";` | 문자열을 **배열에 복사** (수정 가능, 크기 자동 4) |
| `char b[4] = {'A','B','C','\0'};` | 문자 하나씩 배열에 저장, **널 문자 직접 추가** |
| `char c[4] = {65,66,67,0};` | ASCII 코드 숫자로 저장 (65='A', 66='B', 67='C', 0='\0') |

- 네 가지 모두 `%s`로 출력하면 `"ABC"`가 나옵니다.

**예상 출력**
```
ABC
ABC
ABC
ABC
```

---

### 7.4 char* vs char[] — 수정 가능 여부

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";
	char a[] = "ABC";
	
	//s[0] = 'Z';
	a[0] = 'Z';
	printf("%s\n", s);
	printf("%s\n", a);
}
```

**설명**
- `char* s` : 문자열 리터럴을 가리키므로, `s[0] = 'Z'`는 **위험**(주석 처리됨).
- `char a[]` : 배열에 문자열이 **복사**되어 있으므로, `a[0] = 'Z'`는 **정상 동작**합니다.
- 문자열을 **수정할 필요가 있다면 `char[]`**, 읽기만 한다면 `const char*`를 사용합니다.

**예상 출력**
```
ABC
ZBC
```

---

### 7.5 문자열 재대입과 개별 문자 수정

```c
#include <stdio.h>
int main()
{
	char* s = "ABC";
	char a[4] = "ABC";

	s = "DEH";
	//a = "DEH";
	a[0] = 'D';
	a[1] = 'E';
	a[2] = 'H';
	a[3] = 'Z';
	printf("%s\n", s);
	printf("%s\n", a);
}
```

**설명**
- `s = "DEH";` : 포인터는 다른 문자열 리터럴의 주소로 **재대입 가능**합니다.
- `a = "DEH";` : 배열 이름은 **재대입 불가**합니다(주석 처리됨).
- 배열은 원소를 하나씩 바꿔야 합니다: `a[0] = 'D'`, `a[1] = 'E'`, ...
- `a[3] = 'Z'` : 원래 `'\0'`이 있던 위치에 `'Z'`를 넣으면 **널 종료가 사라져** `printf`가 메모리 뒤쪽의 쓰레기 값까지 출력할 수 있습니다.

**예상 출력**
```
DEH
DEHZ(뒤에 쓰레기 값이 이어질 수 있음)
```

---

## 8. ASCII 코드와 문자

### 8.1 숫자의 다양한 표기법과 문자 변환

```c
#include <stdio.h>
int main()
{
	int n = 65;
	printf("%d %c\n", n, n);

	n = 0x41;
	printf("%d %c\n", n, n);

	n = 0101;
	printf("%d %c\n", n, n);
}
```

**설명**
- `65`, `0x41`(16진수), `0101`(8진수)은 모두 **같은 값 65**입니다.
- `%d`로 출력하면 `65`, `%c`로 출력하면 `'A'`가 나옵니다.

| 표기 | 진법 | 값 |
|------|------|------|
| `65` | 10진수 | 65 |
| `0x41` | 16진수 | 4×16 + 1 = 65 |
| `0101` | 8진수 | 1×64 + 0×8 + 1 = 65 |

**예상 출력**
```
65 A
65 A
65 A
```

---

### 8.2 대문자와 소문자의 ASCII 코드 차이

```c
#include <stdio.h>
int main()
{
	printf("%c %c\n", 'A', 'a');
	printf("%d %d\n", 'A', 'a');
	printf("%d\n", 'A'-'a');
}
```

**설명**
- `'A'`는 65, `'a'`는 97입니다.
- `'A' - 'a'` = 65 - 97 = **-32** : 대문자와 소문자는 항상 **32 차이**가 납니다.
- 소문자를 대문자로 바꾸려면 `-32`, 대문자를 소문자로 바꾸려면 `+32`를 하면 됩니다.

**예상 출력**
```
A a
65 97
-32
```

---

### 8.3 숫자 문자의 ASCII 코드

```c
#include <stdio.h>
int main()
{
	printf("%c %c\n", '0', '1');
	printf("%d %d\n", '0', '1');
	printf("%d\n", '1' - '0');
	printf("%d\n", '0'+1);
}
```

**설명**
- `'0'`은 ASCII 48, `'1'`은 49입니다.
- `'1' - '0'` = 49 - 48 = **1** : 문자 `'1'`에서 `'0'`을 빼면 **정수 1**이 됩니다.
- `'0' + 1` = 48 + 1 = **49** : `%c`로 출력하면 `'1'`이 됩니다.
- 문자 숫자를 정수로 바꾸려면 `ch - '0'`을 사용합니다.

**예상 출력**
```
0 1
48 49
1
49
```

---

## 9. 대문자/소문자 개수 세기

### 9.1 잘못된 비교 (문자열과 문자 비교)

```c
#include <stdio.h>
int main()
{
	char* s = "ABCsefsafeDEF*(34";

	int largeAlpha = 0;
	for(int i = 0 ; s[i] ; ++i)
		if (s[i] == "대문자")
		{
			++largeAlpha;
		}

	printf("대문자는 %d개입니다.\n", largeAlpha);
}
```

**설명**
- `s[i] == "대문자"` : **문자(`char`)와 문자열(`char*`)을 비교**하고 있으므로 **의미 없는 비교**입니다.
- 이 코드는 **올바르지 않습니다**. 대문자인지 판별하려면 ASCII 코드 범위를 비교해야 합니다.
- 다음 예제에서 올바른 방법을 보여줍니다.

---

### 9.2 올바른 대문자 세기

```c
#include <stdio.h>
int main()
{
	char* s = "ABCsefsafeDEF*(34";

	int largeAlpha = 0;
	for (int i = 0; s[i]; ++i)
		if ('A' <= s[i] && s[i] <= 'Z')
		{
			++largeAlpha;
		}

	printf("대문자는 %d개입니다.\n", largeAlpha);
}
```

**설명**
- `'A' <= s[i] && s[i] <= 'Z'` : ASCII에서 대문자는 **65('A') ~ 90('Z')** 범위에 연속으로 있습니다.
- 이 조건으로 문자가 대문자인지 정확히 판별할 수 있습니다.
- `"ABCsefsafeDEF*(34"`에서 대문자: A, B, C, D, E, F → **6개**

**예상 출력**
```
대문자는 6개입니다.
```

---

### 9.3 대문자와 소문자 모두 세기

```c
#include <stdio.h>
int main()
{
	char* s = "ABCsefsafeDEF*(34";

	int smallAlpha = 0;
	int largeAlpha = 0;
	for (int i = 0; s[i]; ++i)
	{
		if ('A' <= s[i] && s[i] <= 'Z')
			++largeAlpha;
		else if ('a' <= s[i] && s[i] <= 'z')
			++smallAlpha;
	}

	printf("소문자는 %d개입니다.\n", smallAlpha);
	printf("대문자는 %d개입니다.\n", largeAlpha);
}
```

**설명**
- `'a' <= s[i] && s[i] <= 'z'` : 소문자는 **97('a') ~ 122('z')** 범위입니다.
- `if ~ else if`로 대문자와 소문자를 **각각 세는** 구조입니다.
- `*`, `(`, `3`, `4` 등은 어느 조건에도 해당하지 않으므로 무시됩니다.
- 대문자: A,B,C,D,E,F → **6개**, 소문자: s,e,f,s,a,f,e → **7개**

**예상 출력**
```
소문자는 7개입니다.
대문자는 6개입니다.
```

---

## 10. 문자열 복사

### 10.1 간결한 for 루프 복사

```c
#include <stdio.h>
int main()
{
	char* s = "ABCsefsafeDEF*(34";
	char cs[100];

	for (int i = 0; cs[i] = s[i]; ++i)
		; //empty...

	printf("%s %s\n", cs, s);
}
```

**설명**
- `cs[i] = s[i]` : 대입 연산의 결과는 대입된 **값 자체**입니다.
- `'\0'`이 대입되면 값이 `0`(거짓)이 되어 루프가 종료됩니다.
- 루프 본문은 **빈 문장(`;`)**이며, 조건식 안에서 복사와 종료 검사를 동시에 수행합니다.
- 매우 간결하지만, 처음에는 이해하기 어려울 수 있습니다.

---

### 10.2 do-while 루프로 문자열 복사

```c
#include <stdio.h>
int main()
{
	char* s = "";
	char cs[100];

	int i = 0;
	do {
		cs[i] = s[i++];
	} while (s[i-1]);

	printf("%s %s\n", cs, s);
}
```

**설명**
- `do-while` 루프는 **최소 한 번** 실행되므로, 빈 문자열(`""`)도 `'\0'`을 복사합니다.
- `s[i++]` : 현재 인덱스의 값을 복사한 후 `i`를 증가시킵니다.
- `s[i-1]` : 방금 복사한 문자가 `'\0'`인지 확인합니다.
- 빈 문자열의 경우 `'\0'` 하나만 복사되고 루프가 종료됩니다.

---

### 10.3 널 포인터 / 널 문자 / 빈 문자열의 차이

```c
#include <stdio.h>
int main()
{
	int* p = NULL; //널 포인터
	char c = '\0'; //널 문자
	char* s = "";  //널 문자열


}
```

**설명**

| 개념 | 선언 | 의미 |
|------|------|------|
| **널 포인터 (NULL)** | `int* p = NULL;` | 아무것도 가리키지 않는 포인터. 값은 `0` |
| **널 문자 ('\0')** | `char c = '\0';` | 값이 `0`인 문자. 문자열의 **끝**을 표시 |
| **빈 문자열 ("")** | `char* s = "";` | `'\0'` 하나만 있는 문자열. **길이는 0**이지만 메모리에 존재함 |

- 세 가지는 모두 `0`과 관련이 있지만 **의미가 다릅니다**.
- 널 포인터를 역참조(`*p`)하면 **크래시**가 발생합니다.
- 빈 문자열은 유효한 문자열이지만 내용이 없을 뿐입니다.

---

### 10.4 strlen으로 문자열 길이 구하고 복사하기

```c
#include <stdio.h>
#include <string.h>
int main()
{
	char* s = "ABCsefsafeDEF*(34";
	char cs[100];
	int slen = strlen(s); //sizeof(s);
	for (int i = 0; i < slen + 1; ++i)
		cs[i] = s[i];

	printf("length : %d\n", slen);
	printf("%s, %s\n", s, cs);
}
```

**설명**
- `#include <string.h>` : 문자열 관련 함수(`strlen`, `strcpy` 등)를 사용하기 위한 헤더입니다.
- `strlen(s)` : 문자열의 **길이**를 반환합니다(`'\0'`은 포함하지 않음). `"ABCsefsafeDEF*(34"`의 길이는 **17**입니다.
- `slen + 1` : `'\0'`까지 포함해서 복사해야 하므로 **+1**이 필요합니다.
- 주석의 `sizeof(s)`는 포인터 크기(4 또는 8)를 반환하므로 **문자열 길이가 아닙니다**. `strlen`을 사용해야 합니다.

**예상 출력**
```
length : 17
ABCsefsafeDEF*(34, ABCsefsafeDEF*(34
```

---

### 10.5 사용자 정의 문자열 복사 함수 (ustrcpy)

```c
#include <stdio.h>
#include <string.h>
void ustrcpy(char dest[], char* src)
{
	int slen = strlen(src);
	for (int i = 0; i < slen + 1; ++i)
		dest[i] = src[i];
}
int main()
{
	char* s = "ABCsefsafeDEF*(34";
	char cs[100];
	//strcpy_s(cs, strlen(s)+1, s);
	ustrcpy(cs, s);

	printf("%s, %s\n", s, cs);
}
```

**설명**
- `ustrcpy` 함수는 `strcpy`와 동일한 기능을 **직접 구현**한 것입니다.
- `char dest[]`와 `char* src`는 둘 다 포인터로 전달됩니다.
- `strlen(src) + 1`만큼 복사하여 `'\0'`까지 포함합니다.
- 주석의 `strcpy_s`는 안전한 버전의 표준 함수입니다(Visual Studio에서 권장).

**예상 출력**
```
ABCsefsafeDEF*(34, ABCsefsafeDEF*(34
```

---

## 11. 고급 문자열 주제

### 11.1 char* vs char[] 주소 비교 (== 연산자)

```c
#include <stdio.h>
int main()
{
	char* s1 = "ABCDE";
	//char* s2 = "ABCDE";
	char s2[] = "ABCDE";

	printf("%d\n", s1 == s2);
}
```

**설명**
- `s1 == s2` : 문자열의 **내용**이 아니라 **주소**를 비교합니다.
- `char* s1`은 리터럴의 주소, `char s2[]`는 배열의 주소이므로 **서로 다른 주소** → `0`(거짓)
- 주석의 `char* s2 = "ABCDE"`로 바꾸면, 컴파일러가 같은 리터럴을 공유할 경우 **같은 주소** → `1`(참)이 될 수도 있습니다.
- 문자열 내용을 비교하려면 `strcmp` 함수를 사용해야 합니다.

---

### 11.2 int*로 문자열을 가리키면? (잘못된 사용)

```c
#include <stdio.h>
int main()
{
	int* s1 = "ABCDE";

	printf("%s\n", s1);
}
```

**설명**
- `int*`에 문자열 리터럴(`char*`)을 대입하는 것은 **타입 불일치**입니다.
- 컴파일러가 경고를 내지만, `printf`의 `%s`는 내부적으로 `char*`로 해석하므로 우연히 출력될 수 있습니다.
- 이 코드는 **올바르지 않으며**, 반드시 `char*`를 사용해야 합니다.

---

### 11.3 int 배열에 문자와 '\0' 저장 (활성 코드)

```c
#include <stdio.h>
int main()
{
	int s1[] = { 'A','B','C','D','E','\0' };

	printf("%s\n", s1);
}
```

**설명**
- `int s1[]`에 문자를 저장하면, 각 원소가 **4바이트**로 저장됩니다.
- `%s`는 `char*` 타입의 바이트 단위 문자열을 기대하므로, `int` 배열을 넘기면 **예상과 다른 결과**가 나올 수 있습니다.
- 리틀 엔디안 시스템에서는 각 `int`의 첫 바이트에 ASCII 값이 들어가고 나머지 3바이트가 0이므로, 첫 문자 `'A'`만 출력되고 멈출 수 있습니다.
- 문자열은 반드시 `char` 타입 배열이나 포인터로 다뤄야 합니다.

---

## 12. 정리 표

| 주제 | 내용 |
|------|------|
| 배열 이름과 포인터 | `arr`은 `&arr[0]`과 같은 주소. 단, `sizeof(arr)` ≠ `sizeof(포인터)` |
| 포인터 산술 | `p + i`는 `i × sizeof(*p)` 바이트만큼 이동. `*(p+i)` = `p[i]` |
| 함수에 배열 전달 | `int* arr` 또는 `int arr[]`로 받음. 크기는 별도 매개변수로 전달 |
| sizeof | `sizeof(arr)` = 배열 전체 크기, `sizeof(arr)/sizeof(arr[0])` = 원소 개수 |
| Min 함수 | 인덱스 반환 방식이 값과 위치 모두 활용 가능하여 유용 |
| char* vs char[] | `char*` = 리터럴 주소(읽기 전용, 재대입 가능), `char[]` = 복사본(수정 가능, 재대입 불가) |
| 널 종료 문자 | `'\0'`(값 0)이 문자열의 끝을 표시. `for(; s[i]; )` 패턴으로 순회 |
| ASCII 코드 | `'A'`=65, `'a'`=97, `'0'`=48. 대소문자 차이=32 |
| 대소문자 판별 | `'A' <= ch && ch <= 'Z'` (대문자), `'a' <= ch && ch <= 'z'` (소문자) |
| strlen | `'\0'` 제외한 문자열 길이. `sizeof(포인터)`와 다름 |
| 문자열 복사 | `'\0'`까지 포함해서 복사. `strlen(s)+1`개 복사 또는 `s[i]`가 0이 될 때까지 |
| NULL vs '\0' vs "" | NULL=널 포인터, '\0'=널 문자(값 0), ""=빈 문자열(`'\0'`만 존재) |
| 문자열 비교 | `==`는 주소 비교. 내용 비교는 `strcmp` 사용 |

---

## 13. 연습 문제 (스스로 풀어보기)

1. `char* s = "Hello, World!";`에서 `s[7]`의 ASCII 코드와 문자를 출력해 보세요.

2. 문자열 `"Programming"`에서 대문자와 소문자의 개수를 각각 세는 프로그램을 작성해 보세요.

3. `char a[] = "ABCDE";`를 선언하고, for 루프를 이용하여 모든 문자를 소문자로 바꿔서 출력하는 프로그램을 작성해 보세요. (힌트: `'A' + 32 = 'a'`)

4. 문자열을 입력받아 길이를 직접 세는 `my_strlen` 함수를 작성해 보세요. (`strlen`을 사용하지 않고 `'\0'`을 이용)

5. `int arr[] = {88, 45, 72, 13, 56, 29};`에서 최소값의 **인덱스와 값**을 함께 출력하는 `Min` 함수를 작성해 보세요.

6. 다음 세 선언의 차이를 설명하고, 각각에서 `sizeof`의 결과를 예측해 보세요.
   ```c
   char* s = "Hello";
   char a[] = "Hello";
   char b[10] = "Hello";
   ```

7. 널 포인터(`NULL`), 널 문자(`'\0'`), 빈 문자열(`""`)의 차이를 코드로 확인해 보세요. 각각의 값을 `printf`로 출력하면 어떻게 나오나요?

---

이 강의 자료는 **example/ex13.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 파일 아래쪽의 기초 내용(포인터·배열)부터 시작하여, 위쪽의 심화 내용(문자열 복사·고급 주제)까지 순서대로 학습하면 됩니다. 각 예제를 직접 타이핑하고 **주석을 풀어가며 실행**해 보면 이해에 큰 도움이 됩니다.
