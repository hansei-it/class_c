# C언어 기초 강의 11 - ex11.cpp 코드를 통한 함수 선언·함수 포인터·콜백

이 강의는 **example/ex11.cpp**, **ex11_2.cpp**, **ex11_3.cpp**, **printstring.h/.cpp**에 담긴 예제들을 바탕으로, **함수 선언(전방 선언)**, **함수 포인터**, **콜백(callback) 패턴**, 그리고 **헤더 파일 분리**를 정리합니다.

---

## 0. 열한 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- 함수를 사용하기 전에 **선언(전방 선언)**이 필요한 이유를 이해한다.
- **함수 이름**이 곧 코드 영역에 있는 주소임을 이해한다.
- `int (*pf)(int, int)` 형태의 **함수 포인터**를 선언하고 사용할 수 있다.
- 함수 포인터를 매개변수로 넘겨 **콜백(callback)** 패턴을 구현할 수 있다.
- **헤더 파일(`.h`)과 구현 파일(`.cpp`)로 코드를 분리**하는 이유와 방법을 이해한다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 문자열 출력 방법 복습
2. **2장** – 함수 선언 (전방 선언, forward declaration)
3. **3장** – 함수 이름은 주소다
4. **4장** – 함수 포인터 기초
5. **5장** – 함수 포인터를 활용한 교체 패턴
6. **6장** – 콜백(callback) 패턴 — 서버/클라이언트 코드
7. **7장** – 헤더 파일과 소스 파일 분리
8. **8장** – 메인 예제 분석
9. **9~10장** – 정리 표와 연습 문제

---

## 1. 문자열 출력 방법 복습

### 1.1 printf로 직접 출력

```c
#include <stdio.h>
int main()
{
  printf("%s", "Hello");

  const char* s = "Hello";
  printf("%s", s);

  char a[] = "Hello";
  printf("%s", a);
}
```

**설명**
- 문자열 리터럴, `const char*` 포인터, `char` 배열 모두 `%s`로 출력할 수 있습니다.
- 세 방식 모두 동일하게 "Hello"가 출력됩니다.

---

### 1.2 함수로 감싸서 출력

```c
#include <stdio.h>
void PrintString(const char* str)
{
  printf("%s", str);
}
int main()
{
  PrintString("Hello");

  const char* s = "Hello";
  PrintString(s);

  char a[] = "Hello";
  PrintString(a);
}
```

**설명**
- `PrintString` 함수가 `main` 위에 있으면 바로 사용할 수 있습니다.
- 하지만 `main` 아래에 정의하면 컴파일러가 "PrintString이 뭔지 모른다"는 오류를 냅니다.

---

## 2. 함수 선언 (전방 선언, Forward Declaration)

### 2.1 함수 정의를 main 아래로 이동할 때의 문제

```c
#include <stdio.h>
int main()
{
  PrintString("Hello");  // 오류: PrintString을 아직 모름
}
void PrintString(const char* str)
{
  printf("%s", str);
}
```

- 컴파일러는 소스를 **위에서 아래로** 읽습니다.
- `main`에서 `PrintString`을 호출하려면 그 이전에 정의나 선언이 있어야 합니다.

---

### 2.2 함수 선언으로 해결

```c
#include <stdio.h>
void PrintString(const char* str);  // 함수 선언 (세미콜론 필수!)

int main()
{
  PrintString("Hello");

  const char* s = "Hello";
  PrintString(s);

  char a[] = "Hello";
  PrintString(a);
}

void PrintString(const char* str)   // 함수 정의 (구현)
{
  printf("%s", str);
}
```

**설명**
- `void PrintString(const char* str);` : **함수 선언**입니다. 세미콜론으로 끝납니다.
  - "이런 함수가 어딘가에 있다"고 컴파일러에게 미리 알려줍니다.
- `void PrintString(const char* str) { ... }` : **함수 정의(구현)**입니다.
  - 선언이 따로 있으면 정의는 `main` 아래로 내려도 됩니다.

**선언 vs 정의 비교**

| 구분 | 형태 | 역할 |
|------|------|------|
| 함수 **선언** | `void f(int n);` | 함수 시그니처만 알림 (세미콜론) |
| 함수 **정의** | `void f(int n) { ... }` | 실제 코드 포함 |

---

### 2.3 선언을 main 앞에, 정의는 main 뒤에 (일반적인 스타일)

```c
#include <stdio.h>
void PrintString(const char* str); // 선언

void PrintString(const char* str)  // 선언 + 정의 위치는 어디든 가능
{
  printf("%s", str);
}

int main()
{
  PrintString("Hello");

  const char* s = "Hello";
  PrintString(s);

  char a[] = "Hello";
  PrintString(a);
}
```

---

## 3. 함수 이름은 주소다

### 3.1 함수의 주소 출력

```c
#include <stdio.h>
int Add(int a, int b)
{
  return a + b;
}
int Sub(int a, int b)
{
  return a - b;
}
int main()
{
  printf("main : %p\n", main);
  printf("Add  : %p\n", Add);
  printf("Sub  : %p\n", Sub);

  printf("%d\n", Add(1, 2));
}
```

**설명**
- 함수 이름(`main`, `Add`, `Sub`) 자체가 **코드 영역(Code Area)에 있는 주소**입니다.
- `%p`로 출력하면 각 함수의 코드 시작 주소를 볼 수 있습니다.
- `Add`와 `&Add`는 동일한 주소입니다.

**예상 출력 예시**
```
main : 00401090
Add  : 00401050
Sub  : 00401070
3
```

---

## 4. 함수 포인터 기초

### 4.1 함수 포인터 선언과 사용

```c
#include <stdio.h>
int Add(int a, int b)
{
  return a + b;
}
int Sub(int a, int b)
{
  return a - b;
}
int main()
{
  int result = Add(10, 20);
  printf("result : %d\n", result);

  result = Sub(10, 20);
  printf("result : %d\n", result);
}
```

이제 함수 포인터로 같은 작업을 해 봅니다:

```c
#include <stdio.h>
int Add(int a, int b) { return a + b; }
int Sub(int a, int b) { return a - b; }

int main()
{
  printf("main : %p\n", main);
  printf("Add  : %p\n", Add);
  printf("Sub  : %p\n", Sub);

  void* pv = Add;              // void*로도 주소 저장 가능
  int (*pfunc)(int a, int b) = Add;  // 함수 포인터 선언 및 초기화
  pfunc = Sub;                 // 다른 함수로 교체

  printf("%d\n", Sub(1, 2));     // -1
  printf("%d\n", pfunc(1, 2));   // -1 (pfunc이 Sub를 가리킴)
}
```

**함수 포인터 선언 문법**
```c
반환타입 (*변수이름)(매개변수목록);
```

예시:
```c
int (*pf)(int, int);       // int를 두 개 받아 int를 반환하는 함수 포인터
void (*pf)(const char*);   // const char*를 받아 void를 반환하는 함수 포인터
```

---

### 4.2 함수 포인터로 Add, Sub 교체

```c
#include <stdio.h>
int Add(int a, int b) { return a + b; }
int Sub(int a, int b) { return a - b; }

int main()
{
  int (*pf)(int, int) = NULL;

  pf = Add;
  printf("%d\n", pf(5, 5));   // 10

  pf = Sub;                   // 같은 포인터로 다른 함수 호출
  printf("%d\n", pf(5, 5));   // 0
}
```

**설명**
- 함수 포인터 `pf`는 `Add`를 가리킬 수도, `Sub`를 가리킬 수도 있습니다.
- `pf(5, 5)` : 현재 `pf`가 가리키는 함수를 호출합니다.
- 실행 중에 호출할 함수를 **동적으로 교체**할 수 있습니다.

---

## 5. 배열을 출력 함수와 함수 포인터 활용

### 5.1 배열 직접 출력

```c
#include <stdio.h>
int main()
{
  int arr[10] = { 5, 7, 3, 4, 6, 2, 1, 9, 7, 3 };

  for (int i = 0; i < 10; ++i)
    printf("%5d", arr[i]);
  printf("\n");
}
```

---

### 5.2 PrintArray 함수로 분리

```c
#include <stdio.h>
void PrintArray(int arr[], int size)
{
  for (int i = 0; i < size; ++i)
    printf("%5d", arr[i]);
  printf("\n");
}
int main()
{
  int arr[10] = { 5, 7, 3, 4, 6, 2, 1, 9, 7, 3 };

  PrintArray(arr, 10);
  PrintArray(arr + 5, 3);   // 5번째 요소부터 3개
  PrintArray(arr, 5);        // 처음 5개
}
```

**설명**
- `PrintArray(arr + 5, 3)` : 배열의 6번째 요소(`arr[5]`)부터 3개만 출력합니다.
- 포인터 산술로 배열의 일부 구간을 함수에 전달할 수 있습니다.

---

### 5.3 배열 + 결과 계산 함께 처리

```c
#include <stdio.h>
void PrintArray(int arr[], int size)
{
  for (int i = 0; i < size; ++i)
    printf("%5d", arr[i]);
  printf("\n");
}
int main()
{
  int arr[10] = { 5, 7, 3, 4, 6, 2, 1, 9, 7, 3 };
  PrintArray(arr, 10);

  int a = 10, b = 20;
  int result = a + b;
  printf("result = %d\n", result);
  printf("result = %d\n", result);
  printf("result = %d\n", result);
}
```

---

## 6. 콜백(Callback) 패턴

콜백은 **함수를 인자로 전달하여, 호출받는 쪽(서버)이 적절한 시점에 그 함수를 호출**하는 패턴입니다.

### 6.1 콜백 기초: PrintPattern 전달

```c
#include <stdio.h>
///////////////////// 서버 코드
void PrintArray(int arr[], int size, void (*pf)(int))
{
  for (int i = 0; i < size; ++i)
    pf(arr[i]);  // 콜백 호출 (callback)
  printf("\n");
}
///////////////////// 클라이언트 코드
void PrintPattern(int data)  // 콜백 함수
{
  printf("%d\n", data);
}
int main()
{
  int arr[10] = { 5, 7, 3, 4, 6, 2, 1, 9, 7, 3 };

  PrintArray(arr, 10, PrintPattern);  // 함수를 인자로 전달
}
```

**설명**
- `void (*pf)(int)` : `int` 하나를 받아 `void`를 반환하는 함수 포인터 매개변수.
- `PrintArray`는 배열을 순회하며, 각 요소를 처리할 방법은 **호출자가 결정**합니다.
- `PrintPattern`을 전달하면 단순 숫자 출력, 다른 함수를 전달하면 다른 동작을 수행합니다.

---

### 6.2 콜백 함수 교체: PrintPattern2 전달

```c
#include <stdio.h>
void PrintArray(int arr[], int size, void (*pf)(int))
{
  for (int i = 0; i < size; ++i)
    pf(arr[i]);
  printf("\n");
}
void PrintPattern(int data)           // 콜백 함수 1
{
  printf("%d\n", data);
}
void PrintPattern2(int data)          // 콜백 함수 2
{
  printf("int : %d\n", data);
}
int main()
{
  int arr[10] = { 5, 7, 3, 4, 6, 2, 1, 9, 7, 3 };

  PrintArray(arr, 10, PrintPattern);   // 단순 숫자 출력
  PrintArray(arr, 10, PrintPattern2);  // "int : " 접두사 붙여 출력
}
```

**예상 출력**
```
5
7
3
4
6
2
1
9
7
3

int : 5
int : 7
...
```

**콜백 패턴의 장점**

| 구분 | 설명 |
|------|------|
| 서버 코드 | `PrintArray` : 배열 순회 로직을 담당 |
| 클라이언트 코드 | `PrintPattern`, `PrintPattern2` : 각 요소를 어떻게 처리할지 결정 |
| 유연성 | `PrintArray`를 수정하지 않고도 출력 형태를 자유롭게 바꿀 수 있음 |

---

## 7. 헤더 파일과 소스 파일 분리

코드가 커지면 하나의 파일에 모든 코드를 넣는 것은 비효율적입니다. **헤더 파일(`.h`)과 구현 파일(`.cpp`)로 분리**합니다.

### 7.1 파일 구성

```
printstring.h    ← 함수 선언 (인터페이스)
printstring.cpp  ← 함수 정의 (구현)
ex11_3.cpp       ← main 코드 (사용)
```

---

### 7.2 printstring.h (함수 선언)

```c
#pragma once
void PrintString(const char* str);  // 함수 선언
```

**설명**
- `#pragma once` : 이 헤더 파일이 **한 번만 포함되도록** 합니다. 중복 포함 방지.
- 함수 선언만 있고, 구현은 없습니다.

---

### 7.3 printstring.cpp (함수 정의)

```c
#include <stdio.h>

void PrintString(const char* str)  // 함수 정의 (구현)
{
  printf("%s", str);
}
```

**설명**
- 함수의 **실제 코드**가 여기에 있습니다.
- 여러 파일에서 `printstring.h`를 `#include`하면 이 함수를 사용할 수 있습니다.

---

### 7.4 ex11_3.cpp (사용 코드)

```c
#include <stdio.h>
#include "printstring.h"   // 헤더 파일 포함 (큰따옴표 = 현재 폴더에서 검색)

int main()
{
  PrintString("Hello");
  PrintString("Hello");
  PrintString("Hello");
  PrintString("Hello");
  PrintString("Hello");
}
```

**설명**
- `#include "printstring.h"` : `printstring.h`에 있는 함수 선언을 가져옵니다.
  - `<>` (꺾쇠): 시스템/표준 헤더 파일 (예: `<stdio.h>`)
  - `""` (큰따옴표): 현재 프로젝트의 사용자 헤더 파일 (예: `"printstring.h"`)
- 실제 함수 구현은 `printstring.cpp`에 있지만, `ex11_3.cpp`에서 선언만 있어도 컴파일이 됩니다. 링크 단계에서 `printstring.cpp`의 구현이 연결됩니다.

**헤더 분리의 이점**

| 이점 | 설명 |
|------|------|
| 재사용성 | 여러 `.cpp` 파일에서 같은 헤더를 `#include`해 사용 |
| 유지보수 | 구현을 바꿔도 헤더(인터페이스)가 같으면 사용 코드 수정 불필요 |
| 컴파일 속도 | 변경된 파일만 재컴파일 가능 |

---

### 7.5 ex11_2.cpp (독립 예제)

```c
#include <stdio.h>
int main()
{
  printf("%d", 100);
}
```

- 가장 단순한 형태의 독립 프로그램입니다.
- `main`이 **OS가 호출하는 함수**임을 확인하는 기초 예제입니다.

---

## 8. 메인 예제 분석: void 함수 포인터

```c
#include <stdio.h>
void PrintString(const char* s)
{
  printf("string : %s\n", s);
}
int main()
{
  PrintString("Hello!");             // string : Hello!

  void (*pf)(const char* s);         // 함수 포인터 선언
  pf = PrintString;                  // PrintString 함수 주소 저장

  pf("Hello!");                      // string : Hello!
}
```

**단계별 분석**

| 코드 | 의미 |
|------|------|
| `void (*pf)(const char* s)` | `const char*`를 받아 `void`를 반환하는 함수 포인터 `pf` 선언 |
| `pf = PrintString` | `PrintString` 함수의 주소를 `pf`에 저장 |
| `pf("Hello!")` | `pf`가 가리키는 함수(`PrintString`)를 "Hello!"로 호출 |

**예상 출력**
```
string : Hello!
string : Hello!
```

두 출력이 완전히 동일합니다.  
`PrintString("Hello!")`와 `pf("Hello!")`는 **동일한 함수를 호출**합니다.

---

### 8.1 main도 함수다 — OS가 호출하는 함수

```c
//#include <stdio.h>
//int main()  // ← OS(운영체제)가 호출하는 함수
//{
//
//  return 0;
//}
```

**설명**
- `main` 함수는 특별해 보이지만, 사실 **운영체제가 호출하는 일반 함수**입니다.
- `return 0;` : 프로그램이 정상 종료했음을 OS에 알립니다. (0 = 성공)
- `main`의 주소도 `printf("%p\n", main);`으로 출력할 수 있습니다.

---

## 9. 정리 표

| 주제 | 내용 |
|------|------|
| 함수 선언 | `반환타입 함수이름(매개변수목록);` (세미콜론 필수) |
| 함수 정의 | `반환타입 함수이름(매개변수목록) { ... }` |
| 함수 이름 | 코드 영역의 **주소**. `%p`로 출력 가능 |
| 함수 포인터 선언 | `반환타입 (*변수명)(매개변수목록);` |
| 함수 포인터 초기화 | `pf = 함수이름;` (괄호 없이 이름만 사용) |
| 함수 포인터 호출 | `pf(인자);` 또는 `(*pf)(인자);` |
| 콜백 패턴 | 함수 포인터를 매개변수로 전달, 호출받는 쪽에서 실행 |
| 헤더 파일 `.h` | 함수 선언 + `#pragma once` |
| 구현 파일 `.cpp` | 함수 정의 |
| `#include "파일.h"` | 사용자 헤더 포함 (큰따옴표) |
| `#include <파일.h>` | 시스템/표준 헤더 포함 (꺾쇠) |
| `main` 함수 | OS가 호출하는 진입점, `return 0`으로 정상 종료 알림 |

---

## 10. 연습 문제 (스스로 풀어보기)

1. `int Mul(int a, int b) { return a * b; }` 함수를 작성하고, `int (*pf)(int, int)`로 함수 포인터를 선언하여 `pf(3, 4)`로 호출해 보세요.
2. `Add`, `Sub`, `Mul` 세 함수를 모두 가리킬 수 있는 함수 포인터 배열 `int (*ops[3])(int, int)`를 선언하고, for 루프로 각각 `(10, 5)` 인자를 전달하여 출력해 보세요.
3. `PrintArray` 함수에 콜백 패턴을 적용하여, 홀수만 출력하는 `PrintOdd(int data)`와 짝수만 출력하는 `PrintEven(int data)` 두 개의 콜백 함수를 만들어 보세요.
4. `myfunc.h`와 `myfunc.cpp` 파일을 새로 만들어, `int Square(int n)` 함수를 헤더/구현 파일로 분리하고, `main.cpp`에서 헤더를 포함해 호출해 보세요.
5. `main` 함수의 주소를 `%p`로 출력해 보고, `Add`, `Sub` 함수의 주소와 비교해 모두 다른 주소임을 확인해 보세요.

---

이 강의 자료는 **example/ex11.cpp**, **ex11_2.cpp**, **ex11_3.cpp**, **printstring.h/cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **함수 포인터**와 **콜백 패턴**은 이후 이벤트 처리, 정렬 비교 함수(`qsort`) 등 다양한 곳에서 활용됩니다. **헤더 파일 분리**는 실제 프로젝트에서 코드를 구조화하는 가장 기본적인 방법입니다.
