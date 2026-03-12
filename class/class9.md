# C언어 기초 강의 9 - ex9.cpp 코드를 통한 void 포인터와 주소의 형식 변환

이 강의는 **example/ex9.cpp**에 담긴 예제들을 바탕으로, **`void*` (범용 포인터)**와 **포인터 형식 변환(캐스팅)**을 정리합니다.

---

## 0. 아홉 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- `void*`가 어떤 타입의 주소도 저장할 수 있는 범용 포인터임을 이해한다.
- `(타입*)` 캐스팅으로 `void*`를 원하는 타입의 포인터로 변환하는 방법을 익힌다.
- 주소에 대한 형식 변환이 포인터 산술에 어떤 영향을 미치는지 이해한다.
- 동적 문자열 입력 함수(InputString 패턴)를 익힌다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 다양한 타입의 주소 출력
2. **2장** – 포인터 타입과 주소 산술 (타입별 크기 차이)
3. **3장** – `void*` 범용 포인터
4. **4장** – 주소의 형식 변환 — 메인 예제
5. **5장** – 동적 문자열 입력 함수 패턴
6. **6~7장** – 정리 표와 연습 문제

---

## 1. 다양한 타입의 주소 출력

### 1.1 char, int, double의 주소와 크기

```c
#include <stdio.h>
int main()
{
  char c = 'A';
  int n = 10;
  double d = 4.5;

  printf("%c %d %g\n", c, n, d);
  printf("%p %p %p\n", &c, &n, &d);
  printf("%p %p %p\n", &c + 1, &n + 1, &d + 1);
}
```

**설명**
- `&c + 1` : `char*`에 1을 더함 → 주소 **+1** (1바이트)
- `&n + 1` : `int*`에 1을 더함 → 주소 **+4** (4바이트)
- `&d + 1` : `double*`에 1을 더함 → 주소 **+8** (8바이트)

각 타입의 포인터 산술은 해당 타입의 크기만큼 이동합니다.

---

### 1.2 같은 주소를 다른 타입으로 캐스팅

```c
#include <stdio.h>
int main()
{
  char c = 'A';
  int n = 10;
  double d = 4.5;

  // 동일한 주소 기준, 각 타입으로 +1 이동
  printf("%p %p %p\n",
    (char*)&c + 1, (int*)&n + 1, (double*)&d + 1);

  // 타입을 교차 적용
  printf("%p %p %p\n",
    (int*)&c + 1, (double*)&n + 1, (char*)&d + 1);
}
```

**설명**
- `(int*)&c + 1` : `c`의 주소를 `int*`로 캐스팅한 뒤 1을 더함 → 주소 **+4** (int 크기)
- 즉, 포인터 산술의 이동 크기는 **포인터 타입이 결정**합니다.

---

## 2. 포인터 타입과 주소 산술 정리

| 포인터 타입 | `+ 1` 시 주소 증가량 |
|------------|-------------------|
| `char*` | +1 바이트 |
| `int*` | +4 바이트 |
| `double*` | +8 바이트 |

같은 변수의 주소라도 **캐스팅된 타입**에 따라 포인터 산술 크기가 달라집니다.

---

## 3. `void*` 범용 포인터

### 3.1 void* 개념

- `void*` : 어떤 타입의 주소든 저장할 수 있는 **범용 포인터**입니다.
- 단, `void*`에서는 역참조(`*`)나 포인터 산술이 **직접 불가**합니다. 반드시 구체적인 타입으로 캐스팅해야 합니다.

```c
void* pv = NULL;

int n = 10;
pv = &n;           // int*를 void*에 저장 가능
printf("%d", *(int*)pv);   // 사용 시 int*로 캐스팅 필요
```

---

## 4. 주소의 형식 변환 — 메인 예제

### 4.1 void*로 여러 타입 출력 (교재 메인 코드)

```c
#include <stdio.h>
int main()
{
  // 주소의 형식 변환
  char c = 'A';
  int n = 10;
  double d = 4.5;

  void* pv = NULL;

  pv = &c;
  printf("%c", *(char*)pv);    // 'A'

  pv = &n;
  printf("%d", *(int*)pv);     // 10

  pv = &d;
  printf("%g", *(double*)pv);  // 4.5
}
```

**단계별 분석**

| 단계 | 코드 | 의미 |
|------|------|------|
| 1 | `pv = &c` | `pv`에 `char c`의 주소 저장 |
| 2 | `*(char*)pv` | `pv`를 `char*`로 캐스팅 후 역참조 → `'A'` |
| 3 | `pv = &n` | `pv`에 `int n`의 주소 저장 |
| 4 | `*(int*)pv` | `pv`를 `int*`로 캐스팅 후 역참조 → `10` |
| 5 | `pv = &d` | `pv`에 `double d`의 주소 저장 |
| 6 | `*(double*)pv` | `pv`를 `double*`로 캐스팅 후 역참조 → `4.5` |

**예상 출력**
```
A104.5
```
> `\n`이 없으므로 한 줄에 이어서 출력됩니다.

---

### 4.2 void*를 사용할 때 규칙

```c
void* pv = &n;

// 역참조 직접 불가
// *pv = 10;        // X: 컴파일 오류
// pv + 1;          // X: 포인터 산술 불가

// 타입 캐스팅 후 사용 가능
*(int*)pv = 10;     // O
(int*)pv + 1;       // O
```

---

## 5. 동적 문자열 입력 함수 패턴

### 5.1 고정 버퍼 문자열 입력

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char buffer[100];
  printf("문자열 입력:");
  gets_s(buffer, 100);

  printf("string: %s\n", buffer);
}
```

**설명**
- `gets_s(buffer, 100)` : 최대 100자까지 한 줄을 입력받습니다 (안전 버전).
- 하지만 `buffer`는 스택에 있어, 함수가 반환되면 사라집니다.

---

### 5.2 스택 버퍼를 반환하면 위험

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* InputString()
{
  char buffer[100];
  printf("문자열 입력:");
  gets_s(buffer, 100);

  return buffer;  // 위험! 스택 변수의 주소 반환
}
int main()
{
  char* s = InputString();
  printf("string: %s\n", s);  // 이미 해제된 스택 메모리 접근
}
```

**문제점**
- `buffer`는 `InputString` 함수의 스택에 있습니다.
- 함수가 반환되면 그 스택 프레임이 **해제**됩니다.
- 반환된 주소는 **더 이상 유효하지 않아** 정의되지 않은 동작이 발생합니다.

---

### 5.3 올바른 방법: 힙에 복사해서 반환

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* InputString()
{
  char buffer[100];
  printf("문자열 입력:");
  gets_s(buffer, 100);

  char* s = (char*)malloc(strlen(buffer) + 1);
  strcpy_s(s, strlen(buffer) + 1, buffer);

  return s;   // 힙의 주소 반환 → 유효
}
int main()
{
  char* s = InputString();

  printf("string: %s\n", s);

  free(s);   // 호출한 쪽에서 해제
}
```

**설명**
- `malloc(strlen(buffer) + 1)` : 입력된 문자열 길이 + `'\0'` 크기만큼 힙 할당.
- `strcpy_s(s, ...)` : 스택의 `buffer`를 힙의 `s`로 복사.
- 힙 메모리는 함수가 반환되어도 **살아있어** 안전합니다.
- `free(s)`를 호출한 쪽(`main`)에서 처리해야 합니다.

---

### 5.4 포인터를 통해 반환 (이중 포인터 패턴)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputString(char** ps)
{
  char buffer[100];
  printf("문자열 입력:");
  gets_s(buffer, 100);

  char* s = (char*)malloc(strlen(buffer) + 1);
  strcpy_s(s, strlen(buffer) + 1, buffer);

  *ps = s;   // 포인터의 포인터를 통해 값 전달
}
int main()
{
  char* s = NULL;

  InputString(&s);

  printf("string: %s\n", s);

  free(s);
}
```

**설명**
- `char** ps` : `char*`의 포인터, 즉 **이중 포인터**입니다.
- `*ps = s` : 호출한 쪽의 `char*` 변수(`main`의 `s`)에 힙 주소를 저장합니다.
- `InputString(&s)` : `s`의 주소를 전달합니다.

**이중 포인터의 의미**
```
main의 s  ──────────→ [힙 메모리]
     &s ─→ ps
           *ps = 힙 주소 → main의 s에 힙 주소 저장
```

---

### 5.5 in-out 패턴 정리

함수에서 **새 힙 메모리 주소를 전달하는 방법**:

| 방법 | 설명 |
|------|------|
| `return s;` | 함수 반환값으로 포인터 반환 |
| `*ps = s;` | 이중 포인터(`char**`)로 간접 전달 |

---

## 6. 정리 표

| 주제 | 내용 |
|------|------|
| `void*` | 어떤 타입의 주소든 저장 가능한 범용 포인터 |
| `void*` 역참조 | 반드시 타입 캐스팅 후 사용: `*(int*)pv` |
| `(타입*)p` | 포인터를 다른 타입의 포인터로 캐스팅 |
| 포인터 산술 | 이동 크기 = 캐스팅된 타입의 크기 |
| 스택 주소 반환 위험 | 함수 반환 후 스택 프레임 해제 → 주소 무효 |
| 힙 주소 반환 안전 | 함수 반환 후에도 힙 메모리 유효 |
| 이중 포인터 `char**` | 포인터 변수의 주소 = 포인터의 포인터 |
| `gets_s(buf, size)` | 최대 size만큼 한 줄 입력 (안전 버전) |
| `strlen(s)` | 문자열 길이 (`'\0'` 제외) |

---

## 7. 연습 문제 (스스로 풀어보기)

1. `void* pv = NULL;`을 선언하고 `int n = 42;`의 주소를 저장한 뒤, `*(int*)pv`로 값을 출력해 보세요.
2. `char c = 'Z';`, `int n = 100;`, `double d = 9.9;`에 대해 `void* pv`를 사용하여 세 값을 모두 출력해 보세요.
3. `int n = 10;`에서 `&n`, `(char*)&n + 1`, `(int*)&n + 1`, `(double*)&n + 1`의 주소를 출력하고 차이를 비교해 보세요.
4. `char* InputString()` 함수를 작성하여 사용자로부터 문자열을 입력받아 힙에 저장하고 반환하는 프로그램을 완성해 보세요. (free 잊지 말 것)
5. 이중 포인터 `void InputString(char** ps)` 방식으로도 같은 기능을 구현해 보세요.

---

이 강의 자료는 **example/ex9.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **`void*` 범용 포인터**와 **포인터 형식 변환**은 `malloc` 반환값 처리, 범용 함수 설계 등에서 필수적으로 사용됩니다. 스택 주소의 반환 위험과 힙을 통한 올바른 방법도 반드시 이해해야 합니다.
