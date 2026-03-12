# C언어 기초 강의 3 - ex3.cpp 코드를 통한 제어문과 증감 연산자

이 강의는 **example/ex3.cpp**에 담긴 예제들을 바탕으로, C언어의 조건문(if-else, switch-case)과 반복문(for, while, do-while), 그리고 증감 연산자(`++`, `--`)를 정리한 내용입니다.

---

## 0. 세 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- `if-else`, `switch-case`로 조건에 따라 실행 흐름을 분기할 수 있다.
- `for`, `while`, `do-while`로 반복 작업을 처리할 수 있다.
- `break`와 `continue`로 반복문 흐름을 제어할 수 있다.
- 전위(`++n`)와 후위(`n++`) 증감 연산자의 차이를 이해한다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 포인터 기초 복습 (값, 주소, 역참조)
2. **2장** – if-else 조건문 심화
3. **3장** – switch-case
4. **4장** – for 반복문
5. **5장** – while / do-while
6. **6장** – break / continue
7. **7장** – 증감 연산자 (`++`, `--`) — 메인 예제
8. **8~9장** – 정리 표와 연습 문제

---

## 1. 포인터 기초 복습 (값, 주소, 역참조)

2강에서 배운 내용을 짧게 복습합니다.

### 1.1 값, 주소, 쉬프트 응용

```c
#include <stdio.h>
int main()
{
  int n = 2;

  printf("%d\n", n     ); // n
  printf("%d\n", n << 1); // n*2
  printf("%d\n", n << 2); // n*4
  printf("%d\n", n << 3); // n*8
}
```

**예상 출력**
```
2
4
8
16
```

---

### 1.2 역참조 연산자 `*`

```c
#include <stdio.h>
int main()
{
  int n = 10;

  printf("%d\n", n);        // 값
  printf("%p\n", &n);       // 주소
  printf("%d\n", *&n);      // 역참조: 주소가 가리키는 값
  printf("%p\n", &*&n);     // 역참조 후 다시 주소
}
```

**설명**
- `&n` : 변수 `n`의 주소.
- `*주소` : 해당 주소에 저장된 **값**을 읽습니다 (역참조, dereference).
- `*&n`은 `n`과 동일하고, `&*&n`은 `&n`과 동일합니다.

---

### 1.3 `(&n)[0]` — 인덱스 표기

```c
#include <stdio.h>
int main()
{
  int n = 10;

  printf("%d\n", n);
  printf("%p\n", &n);
  printf("%d\n", (&n)[0]);  // n의 주소를 배열처럼 사용
}
```

**설명**
- `(&n)[0]`은 `n`의 주소에서 0번째 요소, 즉 `n` 자체와 같습니다.
- 이 표기법은 포인터와 배열의 관계를 이해할 때 기초가 됩니다.

---

## 2. if-else 조건문 심화

### 2.1 if만 쓰는 경우

```c
#include <stdio.h>
int main()
{
  // 제어문 if / if-else / switch-case

  if (100 > 5)
  {
    printf("1. Hello\n");
    printf("2. Hello\n");
    printf("3. Hello\n");
  }

  printf("4. Hello\n");
  printf("5. Hello\n");
}
```

**설명**
- `if {}` 없이 뒤의 `printf("4."), printf("5.")`는 조건과 무관하게 **항상** 실행됩니다.
- `100 > 5`가 참이므로 1, 2, 3, 4, 5 모두 출력됩니다.

**예상 출력**
```
1. Hello
2. Hello
3. Hello
4. Hello
5. Hello
```

---

### 2.2 거짓인 if

```c
#include <stdio.h>
int main()
{
  if (100 < 50)
  {
    printf("1. Hello\n");
    printf("2. Hello\n");
    printf("3. Hello\n");
  }

  printf("4. Hello\n");
  printf("5. Hello\n");
}
```

- `100 < 50`은 거짓 → 중괄호 안 1~3은 건너뜁니다.

**예상 출력**
```
4. Hello
5. Hello
```

---

### 2.3 if-else : 1 (참)과 0 (거짓)

```c
#include <stdio.h>
int main()
{
  // 제어문 if / if-else / switch-case
  if (1)
  {
    printf("1. Hello\n");
    printf("2. Hello\n");
    printf("3. Hello\n");
  }
  else
  {
    printf("4. Hello\n");
    printf("5. Hello\n");
  }
}
```

**설명**
- `if (1)` : 1은 참이므로 위 블록이 실행됩니다.
- `if (0)` : 0은 거짓이므로 `else` 블록이 실행됩니다.

---

### 2.4 변수를 조건에 사용하기

```c
#include <stdio.h>
int main()
{
  int n = 10;

  if (n == 10)
  {
    printf("1. Hello\n");
    printf("2. Hello\n");
    printf("3. Hello\n");
  }
  else
  {
    printf("4. Hello\n");
    printf("5. Hello\n");
  }
}
```

**예상 출력**
```
1. Hello
2. Hello
3. Hello
```

---

## 3. switch-case

`switch`는 하나의 변수값에 따라 여러 경우 중 하나를 실행합니다.

### 3.1 기본 switch-case

```c
#include <stdio.h>
int main()
{
  switch (1)
  {
  case 1:
    printf("case 1\n");
    break;
  case 2:
    printf("case 2\n");
    break;
  case 3:
    printf("case 3\n");
    break;
  default:
    printf("default \n");
    break;
  }
}
```

**설명**
- `switch (값)` : 값과 일치하는 `case`로 점프합니다.
- `break` : 해당 `case` 실행 후 `switch` 블록을 빠져나옵니다. **`break`가 없으면 다음 `case`도 연속 실행**됩니다 (fall-through).
- `default` : 일치하는 `case`가 없을 때 실행됩니다.

**예상 출력**
```
case 1
```

---

### 3.2 변수를 사용한 switch-case

```c
#include <stdio.h>
int main()
{
  int n = 0;
  printf("정수 입력: ");
  scanf_s("%d", &n);

  switch (n)
  {
  case 1:
    printf("case 1\n");
    break;
  case 2:
    printf("case 2\n");
    break;
  case 3:
    printf("case 3\n");
    break;
  default:
    printf("default \n");
    break;
  }
}
```

**설명**
- `scanf_s("%d", &n)` : 키보드로부터 정수를 입력받아 `n`에 저장합니다.
  - `&n`은 `n`의 주소 → `scanf_s`가 그 주소에 값을 직접 씁니다.
- 1, 2, 3 이외의 값을 입력하면 `default`가 실행됩니다.

---

### 3.3 문자(키 입력)를 사용한 switch-case

```c
#include <stdio.h>
#include <conio.h>  // _getch()

int main()
{
  switch (_getch())
  {
  case 49:           // '1'의 ASCII 코드
    printf("case 1\n");
    break;
  case '2':          // 50
    printf("case 2\n");
    break;
  case '3':          // 51
    printf("case 3\n");
    break;
  default:
    printf("default \n");
    break;
  }
}
```

**설명**
- `_getch()` : 키보드에서 문자 한 개를 **에코 없이** 입력받습니다 (`conio.h` 필요).
- `case 49:`와 `case '1':`은 **동일**합니다. '1'의 ASCII 코드가 49이기 때문입니다.

---

## 4. for 반복문

### 4.1 가장 기본적인 for

```c
#include <stdio.h>
int main()
{
  // 루프문 : for(), while(), do-while()

  for (int i = 1; i <= 10; i = i + 1)
  {
    printf("Hello!\n");
  }
}
```

**설명**
- `for (초기화; 조건; 증감)` 구조입니다.
  - **초기화**: `int i = 1` — 반복 변수 `i`를 1로 시작.
  - **조건**: `i <= 10` — 조건이 참인 동안 반복.
  - **증감**: `i = i + 1` — 매 반복 후 `i`를 1 증가.
- `i`가 1부터 10까지 총 **10번** 실행됩니다.

---

### 4.2 인덱스를 출력에 활용

```c
#include <stdio.h>
int main()
{
  for (int i = 0; i < 10; i = i + 1)
  {
    printf("Hello! : %d\n", i);
  }
}
```

- `i`는 0부터 시작해 9까지 출력됩니다.

```c
  for (int i = 0; i < 10; ++i)
  {
    printf("Hello! : %d\n", i + 1);
  }
```

- `++i`는 `i = i + 1`과 동일. `i + 1`을 출력하면 1부터 10까지 보입니다.

---

### 4.3 증감값 바꾸기

```c
#include <stdio.h>
int main()
{
  for (int i = 0; i < 10; i += 2)  // i = i + 2
  {
    printf("Hello! : %d\n", i + 1);
  }
}
```

- `i`가 0, 2, 4, 6, 8로 증가 → 5번만 실행됩니다.

---

### 4.4 for로 합산하기

```c
#include <stdio.h>
int main()
{
  int sum = 0;

  for (int i = 1; i <= 5; ++i)
    sum += i;

  printf("sum = %d\n", sum);
  printf("\n");
}
```

**설명**
- `sum += i`는 `sum = sum + i`와 동일합니다.
- 1 + 2 + 3 + 4 + 5 = **15**

**예상 출력**
```
sum = 15
```

반복문 없이 직접 쓰면:
```c
sum = sum + 1;
sum = sum + 2;
sum = sum + 3;
sum = sum + 4;
sum = sum + 5;
```
for 문을 사용하면 이런 반복 코드를 **한 번에** 처리할 수 있습니다.

---

### 4.5 초기화를 바깥으로 빼는 형태

```c
#include <stdio.h>
int main()
{
  int sum = 0;
  int i = 1;

  for (; i <= 10; ++i)
  {
    sum += i;
  }

  printf("Sum = %d\n", sum);
}
```

- `for`의 초기화 부분을 비워 둘 수 있습니다. (세미콜론은 반드시 있어야 합니다.)

---

## 5. while / do-while 반복문

### 5.1 while — 무한 루프

```c
#include <stdio.h>
int main()
{
  while (1)
  {
    printf("Hello\n");
  }
}
```

**설명**
- `while (조건)` : 조건이 참인 동안 반복합니다.
- `while (1)` : 조건이 항상 참 → **무한 루프**입니다. 강제 종료(`Ctrl+C`)하기 전까지 멈추지 않습니다.

---

### 5.2 while — 조건 있는 반복

```c
#include <stdio.h>
int main()
{
  int n = 0;
  while (n < 5)
  {
    printf("Hello\n");
    n++;
  }
}
```

- `n`이 0, 1, 2, 3, 4일 때 실행 → 총 5번 출력.

---

### 5.3 while — 조건 거짓이면 한 번도 실행 안 됨

```c
#include <stdio.h>
int main()
{
  int n = 0;
  while (n > 0)
  {
    printf("%d\n", n);
  }
}
```

- `n = 0`이므로 `n > 0`은 처음부터 거짓 → 아무것도 출력되지 않습니다.

---

### 5.4 do-while — 최소 한 번은 실행

```c
#include <stdio.h>
int main()
{
  int n = 0;
  do
  {
    printf("%d\n", n);
  } while (n > 0);
}
```

**설명**
- `do { } while (조건)` : 블록을 먼저 **한 번 실행**한 후, 조건을 확인합니다.
- `n = 0`이라서 `while (n > 0)`은 거짓이지만, 먼저 한 번 실행했으므로 `0`이 출력됩니다.

**while vs do-while 비교**

| 구분 | 조건 확인 시점 | 최소 실행 횟수 |
|------|--------------|----------------|
| `while` | 블록 **전** | 0번 (조건이 처음부터 거짓이면) |
| `do-while` | 블록 **후** | 1번 (항상 최소 1회 실행) |

---

### 5.5 사용자 입력을 이용한 while 루프

```c
#include <stdio.h>
int main()
{
  while (1)
  {
    int n = 0;
    printf("정수 입력:");
    scanf_s("%d", &n);
    if (n > 0)
    {
      printf("Hello : %d\n", n);
    }
    else
    {
      break;
    }
  }
}
```

**설명**
- 사용자가 양수를 입력하면 계속 출력, 0 이하 값을 입력하면 `break`로 루프를 빠져나옵니다.
- 무한 루프 + `break`의 조합으로 **언제든 탈출할 수 있는 루프**를 만들 수 있습니다.

---

## 6. break와 continue

### 6.1 for에서 짝수만 출력 (if 이용)

```c
#include <stdio.h>
int main()
{
  for (int i = 1; i <= 10; ++i)
  {
    if (i % 2 == 0)
      printf("%5d", i);
  }
  printf("\n");
}
```

**예상 출력**
```
    2    4    6    8   10
```

---

### 6.2 continue — 홀수 건너뛰기

```c
#include <stdio.h>
int main()
{
  for (int i = 1; i <= 10; ++i)
  {
    if (i % 2 == 0)
      continue;  // 짝수이면 아래 printf 건너뜀

    printf("%5d", i);
  }
  printf("\n");
}
```

**설명**
- `continue` : 현재 반복 회차의 나머지 코드를 건너뛰고 **다음 반복**으로 넘어갑니다.
- 짝수(`i % 2 == 0`)이면 `continue`로 `printf`를 건너뛰므로, 홀수만 출력됩니다.

**예상 출력**
```
    1    3    5    7    9
```

---

### 6.3 break vs continue 비교

| 키워드 | 동작 |
|--------|------|
| `break` | 반복문(또는 switch)을 **완전히 빠져나갑니다** |
| `continue` | 이번 반복의 나머지를 **건너뛰고 다음 반복**으로 갑니다 |

---

## 7. 증감 연산자 (`++`, `--`) — 메인 예제

### 7.1 전위 증가 단독 사용 (교재 메인 코드)

```c
#include <stdio.h>
int main()
{
  // ++ , -- 연산자
  int n = 0;

  ++n;
  printf("%d\n", n);
}
```

**설명**
- `++n` : `n`을 1 증가시킵니다 (전위).
- 단독으로 사용할 때는 `++n`과 `n++`이 동일하게 `n`을 1 증가시킵니다.

**예상 출력**
```
1
```

---

### 7.2 전위와 후위 연속 사용

```c
#include <stdio.h>
int main()
{
  int n = 0;

  ++n;
  printf("%d\n", n);   // 1
  n++;
  printf("%d\n", n);   // 2
}
```

---

### 7.3 다른 식에서 전위/후위 차이

```c
#include <stdio.h>
int main()
{
  int n = 0;
  int r = 0;

  r = ++n;   // 전위: n을 먼저 증가(1)한 뒤 r에 대입
  printf("%d %d\n", n, r);   // n=1, r=1

  r = n++;   // 후위: 현재 n(1)을 r에 대입한 뒤 n 증가
  printf("%d %d\n", n, r);   // n=2, r=1
}
```

**예상 출력**
```
1 1
2 1
```

---

### 7.4 감소 연산자 (`--`)

```c
#include <stdio.h>
int main()
{
  int n = 0;
  int r = 0;

  r = --n;   // 전위: n을 먼저 감소(-1)한 뒤 r에 대입
  printf("%d %d\n", n, r);   // n=-1, r=-1

  r = n--;   // 후위: 현재 n(-1)을 r에 대입한 뒤 n 감소
  printf("%d %d\n", n, r);   // n=-2, r=-1
}
```

---

### 7.5 for에서 `++i` 사용

```c
#include <stdio.h>
int main()
{
  int sum = 0;

  for (int i = 0; i < 5; ++i)
    sum += i + 1;

  printf("sum = %d\n", sum);
}
```

- 루프 증감식에서 `++i`와 `i++`는 결과가 **동일**합니다.

**예상 출력**
```
sum = 15
```

---

### 7.6 b = a++ 심화 예제

```c
#include <stdio.h>
int main()
{
  int a = 10;
  int b = a++;   // 현재 a(10)를 b에 대입 → a 증가

  printf("a = %d\n", a);   // a = 11
  printf("b = %d\n", b);   // b = 10
}
```

**예상 출력**
```
a = 11
b = 10
```

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| if | 조건이 참이면 실행 |
| if-else | 참이면 if 블록, 거짓이면 else 블록 |
| switch-case | 값에 따라 분기, `break`로 탈출, `default`로 기본 처리 |
| for | `for (초기화; 조건; 증감)` |
| while | 조건이 참인 동안 반복 |
| do-while | 먼저 실행 후 조건 확인 (최소 1회 실행) |
| break | 반복문/switch 즉시 탈출 |
| continue | 현재 반복 나머지 건너뜀 |
| `++n` (전위 증가) | 먼저 증가 후 사용 |
| `n++` (후위 증가) | 먼저 사용 후 증가 |
| `--n` / `n--` | 감소 버전 |
| `scanf_s` | 키보드 입력 받기 (주소 `&n` 전달 필요) |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `for`로 1부터 100까지의 합을 구하는 프로그램을 작성해 보세요.
2. `while`로 사용자에게 숫자를 계속 입력받다가, 음수가 들어오면 종료하는 프로그램을 작성해 보세요.
3. 1부터 20까지 출력하되, 3의 배수는 `continue`로 건너뛰는 for 루프를 작성해 보세요.
4. `int a = 5;`일 때 `a++`, `++a`, `a--`, `--a`를 각각 사용하면서 `printf`로 값 변화를 확인해 보세요.
5. `switch-case`를 사용해 입력값이 1~3이면 해당 메시지를, 그 외에는 "잘못된 입력"을 출력하는 프로그램을 작성해 보세요.

---

이 강의 자료는 **example/ex3.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **7장의 증감 연산자**가 메인 예제이며, for 루프 증감식에서 자주 쓰입니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
