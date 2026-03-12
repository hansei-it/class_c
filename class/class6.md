# C언어 기초 강의 6 - ex6.cpp 코드를 통한 배열을 함수에 전달하기

이 강의는 **example/ex6.cpp**에 담긴 예제들을 바탕으로, **배열을 함수의 매개변수로 전달하는 방법**과 `char` 배열, 인물 정보 출력 등 실용적인 함수 활용 패턴을 정리합니다.

---

## 0. 여섯 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- 배열을 함수에 전달할 때 **포인터(주소)**로 전달됨을 이해한다.
- `int*`, `char*` 매개변수로 배열을 받아 처리하는 함수를 작성할 수 있다.
- `char` 배열의 값과 문자를 함께 출력하는 방법을 익힌다.
- 여러 개의 매개변수를 사용하는 함수를 설계할 수 있다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 인물 정보 출력 함수
2. **2장** – int 배열을 함수에 전달
3. **3장** – 포인터 매개변수로 값 출력
4. **4장** – char 배열을 함수에 전달 — 메인 예제
5. **5장** – 정리 표와 연습 문제

---

## 1. 인물 정보 출력 함수

함수의 필요성과 매개변수 활용을 실생활 예제로 살펴봅니다.

### 1.1 함수 없이 직접 출력

```c
#include <stdio.h>
int main()
{
  printf("이름 : 홍길동\n");
  printf("나이 : 25\n");
  printf("전화번호: 010-1234-1212\n");
}
```

---

### 1.2 고정된 함수로 분리

```c
#include <stdio.h>
void PrintHong(void)
{
  printf("이름 : 홍길동\n");
  printf("나이 : 25\n");
  printf("전화번호: 010-1234-1212\n");
  printf("\n");
}
int main()
{
  PrintHong();
  PrintHong();
  PrintHong();
}
```

**설명**
- `void PrintHong(void)` : 매개변수도, 반환값도 없는 함수입니다.
- 동일한 사람 정보를 여러 번 출력할 때 재사용할 수 있습니다.
- 하지만 항상 "홍길동"만 출력되는 한계가 있습니다.

---

### 1.3 매개변수로 일반화

```c
#include <stdio.h>
void PrintPerson(const char* name, int age, const char* phone)
{
  printf("이름 : %s\n", name);
  printf("나이 : %d\n", age);
  printf("전화번호: %s\n", phone);
  printf("\n");
}
int main()
{
  PrintPerson("홍길동", 25, "010-1234-1212");
  PrintPerson("이영희", 30, "010-5678-1212");
  PrintPerson("김철수", 29, "010-1234-3456");
}
```

**설명**
- `const char* name` : 문자열 포인터. 호출 시 전달된 문자열을 가리킵니다.
- `const`는 함수 안에서 `name`이 가리키는 문자열을 **수정할 수 없게** 보호합니다.
- 이름, 나이, 전화번호를 인자로 전달하면 어떤 사람 정보든 출력할 수 있습니다.

**예상 출력**
```
이름 : 홍길동
나이 : 25
전화번호: 010-1234-1212

이름 : 이영희
나이 : 30
전화번호: 010-5678-1212

이름 : 김철수
나이 : 29
전화번호: 010-1234-3456
```

---

## 2. int 배열을 함수에 전달

### 2.1 포인터 매개변수로 정수 출력

```c
#include <stdio.h>
void PrintInteger(int n)
{
  printf("%d\n", n);
}
void main()
{
  int n = 100;
  PrintInteger(n);   // 100
}
```

- 값을 복사해서 전달합니다 (call by value). 함수 안에서 `n`을 바꿔도 밖의 `n`은 변하지 않습니다.

---

### 2.2 포인터로 전달 (call by pointer)

```c
#include <stdio.h>
void PrintInteger(int* p)
{
  printf("%d\n", *p);
}
void main()
{
  int n = 100;
  PrintInteger(&n);   // n의 주소 전달
}
```

**설명**
- `int* p` : 정수의 **주소를 받는** 매개변수입니다.
- `PrintInteger(&n)` : `n`의 주소를 전달합니다.
- `*p`로 역참조하여 값을 읽습니다.

---

### 2.3 주소와 값을 함께 출력

```c
#include <stdio.h>
void PrintInteger(int* p)
{
  printf("%p : %d\n", p, *p);
}
void main()
{
  int n = 100;
  PrintInteger(&n);
  printf("%p\n", &n);
}
```

---

### 2.4 int 배열을 함수에 전달

```c
#include <stdio.h>
void PrintArray(int* pa, int size)
{
  printf("size: %d\n", size);
  printf("%d\n", pa[0]);
  printf("%d\n", pa[1]);
  printf("%d\n", pa[2]);
  printf("%d\n", pa[3]);
  printf("%d\n", pa[4]);
}
void main()
{
  int arr[5] = { 10, 20, 30, 40, 50 };
  PrintArray(arr, 5);
}
```

**설명**
- `PrintArray(arr, 5)` : `arr`은 배열 이름으로, `&arr[0]`과 동일한 주소입니다.
- 함수 매개변수 `int* pa`로 배열의 첫 번째 요소 주소가 전달됩니다.
- `size`를 함께 전달해야 함수 안에서 배열의 크기를 알 수 있습니다.

> **중요**: 배열을 함수에 전달할 때 배열의 크기 정보는 따로 전달해야 합니다. `sizeof(arr)`을 함수 안에서 사용하면 배열 크기가 아닌 포인터 크기가 나옵니다.

---

### 2.5 for로 배열 출력

```c
#include <stdio.h>
void PrintArray(int* pa, int size)
{
  printf("size: %d\n", size);
  for (int i = 0; i < size; ++i)
    printf("%d\n", pa[i]);
}
void main()
{
  int arr[5] = { 10, 20, 30, 40, 50 };
  PrintArray(arr, 5);

  int arr2[3] = { 100, 200, 300 };
  PrintArray(arr2, 3);
}
```

**설명**
- 같은 `PrintArray` 함수를 다른 크기의 배열에도 재사용할 수 있습니다.
- `size`만 바꾸면 어떤 크기의 배열도 처리할 수 있습니다.

**예상 출력**
```
size: 5
10
20
30
40
50
size: 3
100
200
300
```

---

## 3. char 배열을 함수에 전달 — 메인 예제

### 3.1 char 배열 출력 함수 (교재 메인 코드)

```c
#include <stdio.h>
void PrintArray(char* pa, int size)
{
  printf("size: %d\n", size);
  for (int i = 0; i < size; ++i)
    printf("%d : %c\n", pa[i], pa[i]);
}
void main()
{
  char arr[5] = { 'A', 'B', 'C', 'D', 'E' };
  PrintArray(arr, 5);

  char arr2[3] = { 'a', 'b', 'c' };
  PrintArray(arr2, 3);
}
```

**설명**
- `char* pa` : `char` 배열의 주소를 받는 포인터입니다.
- `printf("%d : %c\n", pa[i], pa[i])` : 같은 값을 `%d`(정수, ASCII 코드)와 `%c`(문자) 두 가지 형태로 출력합니다.
  - `'A'`의 ASCII 코드는 65, `'a'`는 97입니다.

**예상 출력**
```
size: 5
65 : A
66 : B
67 : C
68 : D
69 : E
size: 3
97 : a
98 : b
99 : c
```

---

### 3.2 int 배열 전달과 char 배열 전달 비교

| 구분 | int 배열 | char 배열 |
|------|----------|-----------|
| 매개변수 타입 | `int* pa` | `char* pa` |
| 요소 크기 | 4바이트 | 1바이트 |
| 출력 형식 지정자 | `%d` | `%c` (문자), `%d` (ASCII 코드) |
| 전달 방식 | 배열 이름 (주소) | 배열 이름 (주소) |

---

## 4. 배열 이름과 `&arr[0]`의 관계

```c
#include <stdio.h>
int main()
{
  int arr[4] = { 100 };   // 첫 요소만 100, 나머지는 0

  printf("%p %p\n", &arr[0], arr);   // 동일한 주소

  int* p1 = &arr[0];
  int* p2 = arr;

  printf("%d %d\n", p1[0], p2[0]);   // 같은 값
  printf("%d %d\n", *p1, *p2);       // 같은 값
}
```

**설명**
- `arr`과 `&arr[0]`은 **동일한 주소**입니다.
- 따라서 `int* p = arr;`와 `int* p = &arr[0];`은 완전히 같습니다.

---

## 5. 배열 초기화 방법

```c
#include <stdio.h>
int main()
{
  // 전체를 0으로 초기화
  int arr[4] = { 0 };
  printf("%d\n", arr[0]);  // 0
  printf("%d\n", arr[1]);  // 0
  printf("%d\n", arr[2]);  // 0
  printf("%d\n", arr[3]);  // 0
}
```

```c
  // 일부만 초기화 → 나머지는 자동으로 0
  int arr[4] = { 1, 2 };
  // arr[0]=1, arr[1]=2, arr[2]=0, arr[3]=0
```

```c
  // 크기 자동 추론
  int arr[] = { 1, 2, 3, 4 };   // 크기 = 4
```

```c
  // 매크로로 크기 관리
  #define SIZE 10
  int arr[SIZE] = { 10, 20, 30, 40 };
```

---

## 6. `#define` 매크로 활용

```c
#include <stdio.h>
#define SIZE 10

int main()
{
  int arr[SIZE] = { 10, 20, 30, 40 };
  int* p = &arr[SIZE - 1];   // 마지막 요소 주소

  for (int i = 0; i < SIZE; ++i)
  {
    printf("%d\n", p[-(SIZE - 1 - i)]);
  }
}
```

**설명**
- `#define SIZE 10` : 상수처럼 쓸 수 있는 **매크로**입니다. 배열 크기를 한 곳에서 관리할 수 있습니다.
- `p[-(SIZE - 1 - i)]` : 마지막 요소 포인터에서 거꾸로 인덱싱해 순서대로 출력합니다.

---

## 7. 정리 표

| 주제 | 내용 |
|------|------|
| 배열을 함수에 전달 | 배열 이름 = 첫 요소 주소 전달 (포인터) |
| 함수 매개변수 | `int* pa` 또는 `int pa[]` (동일 의미) |
| 크기 전달 | 배열 크기를 `size` 매개변수로 함께 전달 |
| char 배열 | `char* pa`로 받아 `%c`(문자), `%d`(코드)로 출력 |
| `const char*` | 함수 안에서 문자열 수정 불가 |
| `arr` vs `&arr[0]` | 동일한 주소 |
| 배열 초기화 | `{0}` → 전체 0, `{1,2}` → 나머지 자동 0 |
| `#define SIZE n` | 배열 크기를 매크로로 관리 |

---

## 8. 연습 문제 (스스로 풀어보기)

1. `void PrintArray(int* pa, int size)` 함수를 작성하여 `{5, 4, 3, 2, 1}` 배열을 출력해 보세요.
2. `char arr[] = {'H','e','l','l','o'};`를 `PrintArray(char* pa, int size)`로 출력해 보세요.
3. `PrintPerson(name, age, phone)` 함수를 작성하고 자신의 정보를 출력해 보세요.
4. `#define SIZE 5`를 사용해 크기가 5인 배열을 선언하고 for 루프로 출력해 보세요.
5. 배열 `{10, 20, 30, 40, 50}`의 합을 구하는 `int SumArray(int* pa, int size)` 함수를 작성해 보세요.

---

이 강의 자료는 **example/ex6.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. 배열을 함수에 전달할 때 **포인터(주소)**로 전달된다는 점이 핵심이며, 이는 이후 포인터 심화와 문자열 처리에서 반드시 필요한 개념입니다.
