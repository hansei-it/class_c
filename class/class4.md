# C언어 기초 강의 4 - ex4.cpp 코드를 통한 함수 기초

이 강의는 **example/ex4.cpp**에 담긴 예제들을 바탕으로, C언어의 **함수(function)** 개념을 처음부터 단계적으로 익힙니다.

---

## 0. 네 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- 함수를 **왜 쓰는지** (코드 재사용, 구조화)를 이해한다.
- `void` 함수와 반환값이 있는 `int` 함수를 구분하여 작성할 수 있다.
- 매개변수(parameter)를 통해 함수에 값을 전달할 수 있다.
- 함수 안에서 `for` 루프로 반복 작업을 처리할 수 있다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 함수가 없을 때의 문제점
2. **2장** – void 함수 만들기
3. **3장** – 매개변수로 함수를 유연하게
4. **4장** – 반환값이 있는 함수 (int, TotalInteger)
5. **5장** – 함수에 문자열 전달
6. **6장** – 배열 기초 (함수와 함께)
7. **7장** – 포인터 기초 복습 (함수 관점)
8. **8~9장** – 정리 표와 연습 문제

---

## 1. 함수가 없을 때의 문제점

### 1.1 같은 코드가 여러 번 반복되는 경우

```c
#include <stdio.h>
int main()
{
  printf("1.Hello!\n");
  printf("2.Hello!\n");
  printf("3.Hello!\n");
  printf("4.Hello!\n");
  printf("5.Hello!\n");
}
```

만약 "Hello!"를 두 번, 세 번 더 출력하고 싶다면 같은 코드를 복사해야 합니다. 이런 **중복(duplication)**이 문제입니다.

---

## 2. void 함수 만들기

### 2.1 함수로 묶기

```c
#include <stdio.h>
void PrintHello()
{
  for (int i = 0; i < 10; ++i)
    printf("%d.Hello!\n", i + 1);
}
void main()
{
  PrintHello();
}
```

**설명**
- `void PrintHello()` : 반환값 없이 `Hello!`를 10번 출력하는 함수입니다.
- `void main()` : `main` 앞의 `void`는 반환값이 없다는 의미입니다 (표준은 `int main()`이지만, 학습용 코드에서 자주 사용됩니다).
- `PrintHello();` : 함수를 **호출(call)**합니다. 이 한 줄만으로 10번 출력이 실행됩니다.

---

### 2.2 여러 번 호출

```c
#include <stdio.h>
void PrintHello()
{
  for (int i = 0; i < 10; ++i)
    printf("%d.Hello!\n", i + 1);
}
void main()
{
  PrintHello();
  PrintHello();
  PrintHello();
}
```

**설명**
- `PrintHello()`를 세 번 호출하면 Hello!가 **30번** 출력됩니다.
- 함수를 만들어 두면 **재사용**이 쉽습니다. 코드를 복사할 필요가 없습니다.

---

## 3. 매개변수로 함수를 유연하게

### 3.1 매개변수 없이 고정된 함수의 한계

```c
void PrintHello(int size)
{
  for (int i = 0; i < 10; ++i)  // size 대신 10으로 고정
    printf("%d.Hello!\n", i + 1);
}
void main()
{
  PrintHello(2);
  PrintHello(3);
  PrintHello(5);
}
```

- `size`를 받지만 실제로는 10으로 고정되어, `PrintHello(2)`와 `PrintHello(5)`가 모두 10번 출력됩니다.

---

### 3.2 매개변수를 실제로 활용

```c
#include <stdio.h>
void PrintHello(int size)
{
  for (int i = 0; i < size; ++i)
    printf("%d.Hello!\n", i + 1);
}
void main()
{
  PrintHello(2);
  PrintHello(3);
  PrintHello(5);
}
```

**설명**
- `int size` : 호출 시 전달된 값을 `size`라는 **매개변수(parameter)**로 받습니다.
- `PrintHello(2)` → `size = 2` → 2번 출력
- `PrintHello(3)` → `size = 3` → 3번 출력
- `PrintHello(5)` → `size = 5` → 5번 출력

**예상 출력**
```
1.Hello!
2.Hello!
1.Hello!
2.Hello!
3.Hello!
1.Hello!
2.Hello!
3.Hello!
4.Hello!
5.Hello!
```

---

### 3.3 문자열도 매개변수로 전달

```c
#include <stdio.h>
void Print(int size, const char* s)
{
  for (int i = 0; i < size; ++i)
    printf("%d.%s\n", i + 1, s);
}
void main()
{
  Print(2, "ABC");
  Print(3, "12345");
  Print(5, "Hello~");
}
```

**설명**
- `const char* s` : 문자열 포인터입니다. `"ABC"`, `"12345"` 같은 문자열 리터럴을 받습니다.
- `const`는 함수 안에서 `s`가 가리키는 문자열을 **수정하지 않겠다**는 약속입니다.

---

## 4. 반환값이 있는 함수

### 4.1 고정값을 반환하는 함수

```c
#include <stdio.h>
int TotalInteger()
{
  return 55;
}
int main()
{
  int sum = TotalInteger();
  printf("sum = %d\n", sum);
}
```

**설명**
- `int TotalInteger()` : `int`를 반환하는 함수입니다.
- `return 55;` : 호출한 곳으로 55를 **반환**합니다.
- `sum = TotalInteger();` : 함수의 반환값 55가 `sum`에 저장됩니다.

---

### 4.2 계산해서 반환하는 함수

```c
#include <stdio.h>
int TotalInteger()
{
  int sum = 0;
  for (int i = 1; i <= 10; ++i)
    sum += i;
  return sum;
}
int main()
{
  int sum = TotalInteger();
  printf("sum = %d\n", sum);
}
```

**예상 출력**
```
sum = 55
```

---

### 4.3 두 수를 더하는 함수

```c
#include <stdio.h>
int Sum(int _a, int _b)
{
  return _a + _b;
}
int main()
{
  int a = 10;
  int b = 20;
  int sum = Sum(a, b);

  printf("sum = %d\n", sum);
  printf("sum = %d\n", Sum(1, 2));
  printf("sum = %d\n", Sum(15, 15));
}
```

**설명**
- `int _a, int _b` : 두 정수를 매개변수로 받습니다. (변수 이름 앞 `_`는 관행적으로 매개변수임을 표시하기도 합니다.)
- 함수를 호출할 때 전달하는 값을 **인자(argument)**, 함수 정의에서 받는 변수를 **매개변수(parameter)**라고 합니다.

**예상 출력**
```
sum = 30
sum = 3
sum = 30
```

---

### 4.4 범위 합산 함수

```c
#include <stdio.h>
int TotalInteger(int a, int b)
{
  int sum = 0;
  for (int i = a; i <= b; ++i)
    sum += i;
  return sum;
}
int main()
{
  int sum = TotalInteger(1, 5);
  printf("sum = %d\n", sum);
  printf("sum = %d\n", TotalInteger(20, 30));
}
```

**설명**
- `a`부터 `b`까지 합산합니다.
- `TotalInteger(20, 30)` : 반환값을 변수에 저장하지 않고 `printf`에 직접 전달해도 됩니다.

**예상 출력**
```
sum = 15
sum = 275
```

---

## 5. 배열 기초

### 5.1 변수 4개 vs 배열

```c
#include <stdio.h>
int main()
{
  int a = 10;
  int b = 20;
  int c = 30;
  int d = 40;
  int arr[4] = { 10, 20, 30, 40 };

  printf("%d %d %d %d\n", a, b, c, d);
  printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
}
```

**설명**
- `int arr[4]` : 정수 4개를 연속으로 저장하는 **배열**입니다.
- `arr[0]`, `arr[1]`, ... : **인덱스(index)**로 각 요소에 접근합니다. 인덱스는 **0부터** 시작합니다.
- 변수 4개 `a, b, c, d`와 `arr[0]~arr[3]`은 동일한 결과를 출력합니다.

---

### 5.2 for로 배열 출력

```c
#include <stdio.h>
int main()
{
  int a = 10, b = 20, c = 30, d = 40;
  int arr[4] = { 10, 20, 30, 40 };

  printf("%d %d %d %d\n", a, b, c, d);

  for (int i = 0; i < 4; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}
```

**설명**
- 배열 + for 루프 조합은 **C에서 가장 자주 쓰이는 패턴** 중 하나입니다.
- 인덱스 `i`가 0부터 3까지 변화하면서 `arr[i]`를 순서대로 접근합니다.

---

### 5.3 배열의 주소와 sizeof

```c
#include <stdio.h>
int main()
{
  int arr[4] = { 10, 20, 30, 40 };

  printf("%p\n", &arr[0]);
  printf("%p\n", &arr[1]);
  printf("%p\n", &arr[2]);
  printf("%p\n", &arr[3]);
}
```

- 배열 요소들은 **연속된 메모리**에 저장됩니다.
- `int`는 4바이트이므로 주소가 4씩 증가합니다.

```c
printf("%d %d\n", sizeof(arr), sizeof(arr[0]));
// int 배열 4개 → 16바이트, int 1개 → 4바이트
```

---

### 5.4 double 배열과 for

```c
#include <stdio.h>
int main()
{
  double arr[4] = { 10, 20, 30, 40 };

  for (int i = 0; i < 4; ++i)
    printf("%p %g\n", &arr[i], arr[i]);
}
```

- `double`은 **8바이트**이므로 주소가 8씩 증가합니다.

---

## 6. 포인터 기초 복습 (함수 관점)

### 6.1 포인터 변수 선언과 사용

```c
#include <stdio.h>
int main()
{
  int n = 100;
  int* pa = &n;   // pa는 n의 주소를 저장하는 포인터

  printf("%d %p\n", n, pa);    // n의 값, pa(= n의 주소)
  printf("%d %p\n", n, &n);    // n의 값, n의 주소
  printf("%d %d\n", n, *pa);   // n의 값, pa가 가리키는 값
}
```

**설명**
- `int* pa` : **int형 포인터 변수** `pa`입니다. `int`의 주소를 저장합니다.
- `pa = &n` : `n`의 주소를 `pa`에 저장합니다.
- `*pa` : 역참조 → `pa`가 가리키는 주소의 값, 즉 `n`의 값을 읽습니다.
- `pa`와 `&n`은 동일한 주소입니다.

---

### 6.2 포인터로 값 변경

```c
#include <stdio.h>
int main()
{
  double d = 4.55;
  double* pd = NULL;  // NULL: 아무것도 가리키지 않는 포인터

  pd = &d;

  *pd = 3.14;   // pd가 가리키는 주소(d)에 3.14 저장

  printf("%p %p\n", &d, pd);   // 두 주소가 같음
  printf("%g %g\n", *&d, *pd); // 두 값이 같음 (3.14)
  printf("%g %g\n", d, *pd);   // 3.14 3.14
}
```

**설명**
- `double* pd = NULL` : 처음에는 아무것도 가리키지 않게 `NULL`로 초기화합니다.
- `*pd = 3.14` : 포인터를 통해 `d`의 값을 **간접적으로 변경**합니다.
- `NULL`을 역참조(`*NULL`)하면 프로그램이 충돌하므로, 포인터를 쓰기 전 반드시 유효한 주소를 대입해야 합니다.

---

## 7. 메인 예제: for를 활용한 PrintHello 함수

```c
#include <stdio.h>
void PrintHello(int size)
{
  for (int i = 0; i < size; ++i)
    printf("%d.Hello!\n", i + 1);
}
int main()
{
  PrintHello(5);
  PrintHello(3);
  PrintHello(10);
}
```

**설명**
- `size` 매개변수로 출력 횟수를 동적으로 제어합니다.
- `main`에서 세 번 호출하여 5번, 3번, 10번 출력합니다.

**예상 출력**
```
1.Hello!
2.Hello!
3.Hello!
4.Hello!
5.Hello!
1.Hello!
2.Hello!
3.Hello!
1.Hello!
...
10.Hello!
```

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| 함수 정의 | `반환타입 함수이름(매개변수) { ... }` |
| void 함수 | 반환값 없음 |
| int 함수 | `return 값;`으로 정수 반환 |
| 매개변수 | 호출 시 전달된 값을 받는 변수 |
| 인자 | 함수 호출 시 전달하는 값 |
| 함수 호출 | `함수이름(인자);` |
| 배열 선언 | `타입 이름[크기] = { 초기값, ... }` |
| 배열 접근 | `arr[0]`, `arr[1]`, ... (0부터 시작) |
| for + 배열 | `for (int i = 0; i < 크기; ++i)` 패턴 |
| 포인터 선언 | `int* p = &변수;` |
| 역참조 | `*p` : 포인터가 가리키는 값 |
| NULL 포인터 | 아무것도 가리키지 않는 포인터 |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `PrintHello(7)`을 호출했을 때 "1.Hello!" ~ "7.Hello!"가 출력되는지 직접 확인해 보세요.
2. `int Sum(int a, int b)` 함수를 작성하여 `Sum(3, 7)`의 결과를 출력해 보세요.
3. `int arr[5] = {10, 20, 30, 40, 50};`을 선언하고 for 루프로 각 요소와 주소를 출력해 보세요.
4. `int* p = &arr[0];`을 선언하고 `p`를 통해 `arr[2]`를 100으로 바꾼 뒤, 배열 전체를 다시 출력해 보세요.
5. `TotalInteger(a, b)` 함수를 작성하여 `a > b`이면 합산 없이 0을 반환하도록 수정해 보세요.

---

이 강의 자료는 **example/ex4.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **함수**는 C언어에서 코드를 구조화하는 핵심 개념입니다. 배열과 for 루프를 함수와 결합하면 훨씬 강력한 프로그램을 만들 수 있습니다.
