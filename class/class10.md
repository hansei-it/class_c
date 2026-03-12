# C언어 기초 강의 10 - ex10.cpp 코드를 통한 함수·배열·const 종합

이 강의는 **example/ex10.cpp**에 담긴 예제들을 바탕으로, **`const` 한정자**, **포인터와 const의 조합**, **동적 문자열 배열** 관리, 그리고 함수와 배열을 종합적으로 활용하는 패턴을 정리합니다.

---

## 0. 열 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- `const int`, `const char*`, `const char* const`의 차이를 이해한다.
- 배열을 함수에 전달할 때 포인터와 `const` 조합을 올바르게 사용할 수 있다.
- 문자열 포인터 배열(`char*[]`)로 여러 문자열을 동적으로 관리할 수 있다.
- 함수에서 배열 합계를 구하되 버그를 찾아 수정하는 능력을 키운다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – char 배열 기초 복습 (값, 주소, 포인터 산술)
2. **2장** – `const` 변수
3. **3장** – 포인터와 `const`의 세 가지 조합
4. **4장** – 여러 포인터로 배열 공유
5. **5장** – 문자열을 함수에 전달 (`const char*`)
6. **6장** – 동적 문자열 배열 (`char*[]` + malloc)
7. **7장** – 메인 예제 + 버그 분석
8. **8~9장** – 정리 표와 연습 문제

---

## 1. char 배열 기초 복습

### 1.1 char 값, 문자, 주소 동시 출력

```c
#include <stdio.h>
int main()
{
  char arr[4] = { 'A', 'B', 'C', 'D' };

  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]); // ASCII
  printf("%c %c %c %c\n", arr[0], arr[1], arr[2], arr[3]); // 문자
  printf("%p %p %p %p\n", &arr[0], &arr[1], &arr[2], &arr[3]);
  printf("%p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3);
  printf("%c %c %c %c\n", *arr, *(arr+1), *(arr+2), *(arr+3));
}
```

**설명**
- `arr`와 `&arr[0]`은 같은 주소입니다.
- `arr + n`과 `&arr[n]`도 같은 주소입니다.
- `*(arr + n)`과 `arr[n]`도 같은 값입니다.

---

### 1.2 char 값의 범위

```c
#include <stdio.h>
int main()
{
  char c = 'A';   // 65
  int n = 'A';    // 65

  printf("%d %d\n", c, n);
  printf("%c %c\n", c, n);
}
```

- `char c = 65;`, `char c = 0x41;`, `char c = 'A';` 모두 동일합니다.

```c
  char c = 128;  // signed char 범위 초과 → -128 (또는 환경에 따라 다름)
  int n = 128;   // int 범위 내 → 128 정상

  char c = 255;  // signed char로 -1, unsigned char로 255
```

---

### 1.3 char 배열로 문자열 사용

```c
#include <stdio.h>
int main()
{
  char arr[5] = { 'A', 'B', 'C', 'D' };  // 마지막은 자동으로 0('\0')

  printf("%p %s\n", arr, arr);           // 주소와 문자열
  printf("%p %s\n", arr + 2, arr + 2);   // 두 번째부터
}
```

**예상 출력**
```
[주소] ABCD
[주소+2] CD
```

---

## 2. `const` 변수

### 2.1 const int — 값 변경 불가

```c
#include <stdio.h>
int main()
{
  int n = 10;
  const int cn = 10;

  printf("%d %d\n", n, cn);
  n = 20;       // O: 일반 변수
  // cn = 20;   // X: const 변수는 변경 불가 → 컴파일 오류
  printf("%d %d\n", n, cn);
}
```

**설명**
- `const int cn = 10;` : 초기화 이후 값을 **변경할 수 없습니다**.
- 컴파일러가 변경 시도를 **오류로 잡아줍니다**.

---

## 3. 포인터와 `const`의 세 가지 조합

```c
#include <stdio.h>
int main()
{
  char arr[] = "ABCDEF";
  char* s1 = arr;             // 일반 포인터
  const char* s2 = arr;       // 가리키는 값 변경 불가
  const char* const s3 = arr; // 포인터 자체도, 값도 변경 불가

  s1[0] = 'Z';  // O
  s1 = arr;     // O

  // s2[0] = 'Z'; // X: const가 가리키는 값 변경 불가
  s2 = arr;     // O: 포인터 자체는 변경 가능

  // s3[0] = 'Z'; // X: 값 변경 불가
  // s3 = arr;    // X: 포인터 변경 불가
}
```

**세 가지 const 조합 정리**

| 선언 | 값 변경 | 포인터 변경 | 의미 |
|------|---------|------------|------|
| `char* s` | O | O | 완전 자유 |
| `const char* s` | X | O | 읽기 전용 데이터 가리킴 |
| `char* const s` | O | X | 포인터 고정, 값은 수정 가능 |
| `const char* const s` | X | X | 완전 읽기 전용 |

---

### 3.1 배열 공유: 여러 포인터가 같은 배열

```c
#include <stdio.h>
int main()
{
  char arr[] = "ABCDEF";
  char* s1 = arr;
  char* s2 = arr;

  s1[0] = 'T';   // arr[0] = 'T'
  printf("%s %s %s\n", arr, s1, s2);   // TBCDEf TBCDEf TBCDEf
}
```

**설명**
- `s1`, `s2`, `arr`은 모두 **같은 배열**을 가리킵니다.
- `s1[0]`을 변경하면 `arr`, `s2`에도 반영됩니다.

---

## 4. 문자열을 함수에 전달

### 4.1 일반 포인터로 전달

```c
#include <stdio.h>
void PrintAddress(char* s)
{
  printf("pointer : %p\n", s);
}
void PrintString(char* s)
{
  printf("string : %s\n", s);
}
int main()
{
  char arr[5] = { 'A', 'B', 'C', 'D' };
  char* s1 = arr;
  char* s2 = s1;

  PrintAddress(arr);
  PrintString(arr);
}
```

---

### 4.2 `const char*`로 보호하여 전달

```c
#include <stdio.h>
void PrintAddress(const char* s)
{
  // s[0] = 'a';  // X: 컴파일 오류
  printf("pointer : %p\n", s);
}
void PrintString(const char* s)
{
  printf("string : %s\n", s);
}
int main()
{
  char arr[5] = { 'A', 'B', 'C', 'D' };
  char* s1 = arr;
  char* s2 = s1;

  PrintAddress(arr);
  PrintString(arr);
}
```

**설명**
- 함수 매개변수를 `const char*`로 선언하면, 함수 안에서 **실수로 문자열을 수정**하는 것을 컴파일러가 방지합니다.
- 읽기 전용으로 사용하는 문자열 함수는 항상 `const char*`를 사용하는 것이 좋습니다.

---

## 5. 동적 문자열 배열

### 5.1 문자열 배열 (`char*[]`)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char* sArray[100] = { NULL };   // char* 포인터 100개 배열

  sArray[0] = InputString();      // 동적 할당된 문자열
  sArray[1] = InputString();
  sArray[2] = InputString();

  printf("string : %s\n", sArray[0]);
  printf("string : %s\n", sArray[1]);
  printf("string : %s\n", sArray[2]);

  free(sArray[0]);
  free(sArray[1]);
  free(sArray[2]);
}
```

**설명**
- `char* sArray[100]` : `char*` 포인터 100개짜리 배열.
- 각 요소는 동적 할당된 문자열의 주소입니다.
- 사용 후 각 요소를 `free`해야 합니다.

---

### 5.2 while 루프로 동적 문자열 목록 관리

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* InputString()
{
  char buffer[500];
  printf("문자열 입력:");
  gets_s(buffer, 500);

  char* m = (char*)malloc(strlen(buffer) + 1);
  strcpy_s(m, strlen(buffer) + 1, buffer);

  return m;
}
int main()
{
  char* sArray[100] = { NULL };
  int index = 0;

  while (1)
  {
    char* data = InputString();
    if (strcmp(data, "exit") == 0)  // "exit" 입력 시 종료
    {
      free(data);
      break;
    }
    sArray[index++] = data;
  }

  for (int i = 0; i < index; ++i)
    printf("string[%d] : %s\n", i, sArray[i]);

  for (int i = 0; i < index; ++i)
    free(sArray[i]);
}
```

**설명**
- `strcmp(data, "exit") == 0` : 두 문자열이 같으면 0 반환. "exit"를 입력하면 루프 탈출.
- `sArray[index++] = data` : 문자열 주소를 배열에 저장하고 인덱스 증가.
- 마지막에 `free`를 반복해 모든 힙 메모리를 해제합니다.

---

## 6. 메인 예제 + 버그 분석

### 6.1 교재 메인 코드

```c
#include <stdio.h>
int TotalSum(int arr[], int size)
{
  int sum = 0;
  for (int i = 1; i < size; ++i)  // i = 1부터 시작 (버그!)
    sum += arr[i];

  return sum;
}
int main()
{
  int a = 10;
  int b = 20;
  int c = a + b;

  printf("%d + %d = %d\n", a, b, c);

  int arr[5] = { 4, 5, 2, 3, 100 };
  int result = TotalSum(arr, 5);

  printf("total = %d\n", result);
}
```

**예상 출력**
```
10 + 20 = 30
total = 110
```

---

### 6.2 버그 분석

`TotalSum` 함수의 루프가 `i = 1`에서 시작합니다.

```c
for (int i = 1; i < size; ++i)   // 버그: i=0을 건너뜀
  sum += arr[i];
```

- `arr[0] = 4`가 합산에서 **빠집니다**.
- 올바른 합: `4 + 5 + 2 + 3 + 100 = 114`
- 실제 출력: `5 + 2 + 3 + 100 = 110` (arr[0]=4 누락)

**수정 코드**
```c
for (int i = 0; i < size; ++i)   // 수정: i=0부터 시작
  sum += arr[i];
```

---

## 7. 보충: n, *p, *&n, *&*p 관계

```c
#include <stdio.h>
int main()
{
  int n = 10;
  int* p = &n;

  printf("%d %d\n", n, *p);       // 10 10
  printf("%p %p\n", &n, &*p);     // 같은 주소
  printf("%d %d\n", *&n, *&*p);   // 10 10
}
```

**설명**
- `*&n` : `n`의 주소를 역참조 → `n` 자체.
- `&*p` : `p`가 가리키는 값의 주소 → `&n`.
- `*&*p` : `p`를 역참조하여 값 가져옴 → `*p = n`.

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| `const int cn = 10` | 값 변경 불가 (컴파일 오류) |
| `const char* s` | s가 가리키는 값 변경 불가, 포인터 변경 가능 |
| `char* const s` | 포인터 변경 불가, 값 변경 가능 |
| `const char* const s` | 값도, 포인터도 변경 불가 |
| `char* sArray[n]` | 문자열 포인터 배열 |
| `strcmp(s1, s2)` | 같으면 0, s1 < s2면 음수, s1 > s2면 양수 |
| 배열 함수 버그 | `i = 1` 시작 → `arr[0]` 누락 |
| 올바른 루프 | `for (int i = 0; i < size; ++i)` |
| `free` 반복 | 포인터 배열의 각 요소를 개별 `free` |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `const int x = 5;`를 선언하고 `x = 10;`을 시도해 보고 오류 메시지를 확인해 보세요.
2. `char arr[] = "Hello";`에 대해 `char* s1`, `const char* s2`, `const char* const s3`를 각각 선언하고 수정 시도 시 어떻게 다른지 확인해 보세요.
3. 6.2의 `TotalSum` 버그를 수정하여 `{4, 5, 2, 3, 100}`의 올바른 합 **114**가 출력되는지 확인해 보세요.
4. `char* sArray[10] = {NULL};`을 선언하고 `malloc`으로 문자열 3개를 동적 할당해 저장한 뒤, 모두 출력하고 `free`로 해제해 보세요.
5. `strcmp("apple", "banana")`와 `strcmp("banana", "apple")`의 결과가 어떻게 다른지 확인해 보세요.

---

이 강의 자료는 **example/ex10.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **`const`와 포인터의 조합**, 그리고 **버그를 발견하고 수정하는 과정**이 이번 수업의 핵심입니다. 특히 배열 인덱스가 0부터 시작한다는 것을 항상 염두에 두어야 합니다.
