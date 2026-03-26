# C언어 기초 강의 18 - ex18.cpp 코드를 통한 비트 연산, 열거형, 구조체, 동적 메모리 할당, typedef와 함수 포인터

이 강의는 **example/ex18.cpp**에 담긴 예제들을 바탕으로, 비트 연산부터 구조체·동적 메모리·typedef·함수 포인터까지 폭넓은 중급 C 문법을 설명합니다.

---

## 0. 학습 목표

- 비트 연산자(`&`, `|`, `^`, `~`)와 시프트 연산자(`<<`, `>>`)를 이해하고 활용할 수 있다.
- `signed char`와 `unsigned char`의 범위 차이와 오버플로우를 이해한다.
- 비트 플래그의 설정(set), 해제(clear), 토글(toggle) 패턴을 사용할 수 있다.
- `enum`(열거형)으로 상수 그룹을 정의하고, `const`와의 차이를 안다.
- `struct`(구조체)를 선언·초기화하고, 멤버에 접근하며, 함수로 조작할 수 있다.
- `malloc`/`free`를 이용한 구조체 동적 메모리 할당과 해제를 할 수 있다.
- 2차원 동적 배열을 할당·초기화·출력·해제할 수 있다.
- `typedef`로 자료형에 별칭을 주고, **함수 포인터**를 선언·사용할 수 있다.

---

## 1. 비트 연산자의 기초 (&, |, ^, ~)

### 1.1 비트 AND, OR, XOR, NOT

```c
#include <stdio.h>
int main()
{
    int a = 5;
    int b = 6;

    printf("%x\n", a & b);
    printf("%x\n", a | b);
    printf("%x\n", a ^ b);
    printf("%x\n", ~a);
    printf("%x\n", ~b);
    printf("\n");
    printf("%d\n", a & b);
    printf("%d\n", a | b);
    printf("%d\n", a ^ b);
    printf("%d\n", ~a);
    printf("%d\n", ~b);
}
```

**설명**

| 연산자 | 이름 | 동작 |
|--------|------|------|
| `&` | AND | 두 비트 모두 1이면 1 |
| `\|` | OR | 둘 중 하나라도 1이면 1 |
| `^` | XOR | 두 비트가 다르면 1 |
| `~` | NOT | 모든 비트 반전 |

- `a = 5` → 이진수 `0101`, `b = 6` → 이진수 `0110`
  - `a & b` = `0100` = **4**
  - `a | b` = `0111` = **7**
  - `a ^ b` = `0011` = **3**
  - `~a` = 모든 비트 반전 → **-6** (2의 보수 표현)
  - `~b` = **-7**

**예상 출력**
```
4
7
3
fffffffa
fffffff9

4
7
3
-6
-7
```

---

## 2. char 자료형의 부호와 범위

`char`는 1바이트(8비트)로, **signed**인지 **unsigned**인지에 따라 저장 가능한 범위가 달라집니다. `%x`로 출력하면 내부 16진수 표현을 확인할 수 있습니다.

### 2.1 char c = 127 (범위 안)

```c
#include <stdio.h>
int main()
{
    char c = 127;

    printf("%d %x\n", c, c);
}
```

**설명**
- `signed char`의 최댓값은 **127**입니다. 범위 안이므로 정상 출력됩니다.

**예상 출력**
```
127 7f
```

---

### 2.2 char c = 128 (오버플로우)

```c
#include <stdio.h>
int main()
{
    char c = 128;

    printf("%d %x\n", c, c);
}
```

**설명**
- `signed char`의 범위는 **-128 ~ 127**입니다. 128은 범위를 벗어나 **오버플로우**가 발생합니다.
- 이진수 `10000000`은 signed로 해석하면 **-128**이 됩니다.

**예상 출력**
```
-128 ffffff80
```

---

### 2.3 unsigned char c = 128

```c
#include <stdio.h>
int main()
{
    unsigned char c = 128;

    printf("%d %x\n", c, c);
}
```

**설명**
- `unsigned char`의 범위는 **0 ~ 255**이므로 128은 정상 범위입니다.

**예상 출력**
```
128 80
```

---

### 2.4 unsigned char c = 255

```c
#include <stdio.h>
int main()
{
    unsigned char c = 255;

    printf("%d %x\n", c, c);
}
```

**설명**
- `unsigned char`의 최댓값은 **255** (`0xFF`)입니다. 정상 출력됩니다.
- 만약 `signed char`에 255를 넣으면 **-1**이 출력됩니다(`0xFF`는 signed에서 -1).

**예상 출력**
```
255 ff
```

---

## 3. 시프트 연산자

### 3.1 왼쪽 시프트 (<<)

```c
#include <stdio.h>
int main()
{
    int a = 2;

    printf("%d %x\n", a << 0, a << 0);
    printf("%d %x\n", a << 1, a << 1);
    printf("%d %x\n", a << 2, a << 2);
    printf("%d %x\n", a << 3, a << 3);
    printf("%d %x\n", a << 4, a << 4);
}
```

**설명**
- `<<` 연산자는 비트를 **왼쪽으로** 밀어냅니다. 한 칸 밀면 **×2** 효과입니다.
- `2 << 0` = 2, `2 << 1` = 4, `2 << 2` = 8, `2 << 3` = 16, `2 << 4` = 32

**예상 출력**
```
2 2
4 4
8 8
16 10
32 20
```

---

### 3.2 오른쪽 시프트 (>>) - 음수

```c
#include <stdio.h>
int main()
{
    int a = -32;

    printf("%d %x\n", a >> 0, a >> 0);
    printf("%d %x\n", a >> 1, a >> 1);
    printf("%d %x\n", a >> 2, a >> 2);
    printf("%d %x\n", a >> 3, a >> 3);
    printf("%d %x\n", a >> 4, a >> 4);
    printf("%d %x\n", a >> 5, a >> 5);
    printf("%d %x\n", a >> 6, a >> 6);
    printf("%d %x\n", a >> 7, a >> 7);
}
```

**설명**
- `>>` 연산자는 비트를 **오른쪽으로** 밀어냅니다. 한 칸 밀면 **÷2** 효과입니다.
- **음수**를 오른쪽 시프트할 때, 대부분의 컴파일러는 **산술 시프트**(최상위 부호 비트를 유지)를 수행합니다.
- `-32 >> 1` = -16, `-32 >> 5` = -1. -1 이후로는 계속 -1이 됩니다(모든 비트가 1이므로).

**예상 출력**
```
-32 ffffffe0
-16 fffffff0
-8 fffffff8
-4 fffffffc
-2 fffffffe
-1 ffffffff
-1 ffffffff
-1 ffffffff
```

---

## 4. 비트 플래그 활용

비트 플래그는 각 비트를 **스위치**처럼 사용하여 여러 상태를 하나의 정수에 저장하는 기법입니다.

### 4.1 기본 OR 연산으로 플래그 설정

```c
#include <stdio.h>
const int A = 0x1;
const int B = 0x2;
const int C = 0x4;
const int D = 0x8;
const int E = 0x16;
int main()
{
    unsigned int data = 0;

    printf("%08x\n", data);
    data |= C;
    printf("%08x\n", data);
    data |= C;
    printf("%08x\n", data);
}
```

**설명**
- `const int`로 각 비트 위치를 상수로 정의합니다. `A = 0x1`(비트0), `B = 0x2`(비트1), `C = 0x4`(비트2) 등.
- `data |= C` : **OR** 연산으로 C 플래그를 **켭니다(set)**.
- 이미 켜진 비트에 다시 OR 해도 **값이 변하지 않습니다**.

**예상 출력**
```
00000000
00000004
00000004
```

---

### 4.2 비트 설정(set)과 해제(clear)

```c
#include <stdio.h>
const int A = 0x1;
const int B = 0x2;
const int C = 0x4;
const int D = 0x8;
const int E = 0x16;
int main()
{
    unsigned int data = 0;

    printf("%08x\n", data);
    data |= C;
    printf("%08x\n", data);
    data |= C;
    printf("%08x\n", data);
    data |= B;
    printf("%08x\n", data);
    data |= A;
    printf("%08x\n", data);
    data &= ~C;
    printf("%08x\n", data);
}
```

**설명**
- `data |= 플래그` : 해당 비트를 **켜기(set)**
- `data &= ~플래그` : 해당 비트를 **끄기(clear)**. `~C`는 C 비트만 0이고 나머지가 1인 마스크를 만들어, AND 연산으로 C만 끕니다.

| 동작 | 16진수 결과 |
|------|-------------|
| 초기 상태 | `00000000` |
| `\|= C` (비트2 켜기) | `00000004` |
| `\|= C` (이미 켜짐) | `00000004` |
| `\|= B` (비트1 켜기) | `00000006` |
| `\|= A` (비트0 켜기) | `00000007` |
| `&= ~C` (비트2 끄기) | `00000003` |

**예상 출력**
```
00000000
00000004
00000004
00000006
00000007
00000003
```

---

### 4.3 비트 설정, 해제, 토글(toggle)

```c
#include <stdio.h>
const int A = 0x1;
const int B = 0x2;
const int C = 0x4;
const int D = 0x8;
const int E = 0x10;
const int F = 0x20;
const int G = 0x40;
const int H = 0x80;
int main()
{
    unsigned int data = 0;

    printf("%08x\n", data);
    data |= C;
    printf("%08x\n", data);
    data |= B;
    printf("%08x\n", data);
    data |= A;
    printf("%08x\n", data);
    data &= ~C;
    printf("%08x\n", data);
    data ^= B;
    printf("%08x\n", data);
}
```

**설명**

| 패턴 | 연산 | 설명 |
|------|------|------|
| **set** (켜기) | `data \|= 플래그` | 해당 비트를 1로 |
| **clear** (끄기) | `data &= ~플래그` | 해당 비트를 0으로 |
| **toggle** (반전) | `data ^= 플래그` | 해당 비트가 1이면 0으로, 0이면 1로 |

- `data ^= B` : B 비트가 1이었으므로 0으로 토글됩니다.

**예상 출력**
```
00000000
00000004
00000006
00000007
00000003
00000001
```

---

## 5. 열거형 (enum)

### 5.1 순차 값 enum

```c
#include <stdio.h>
enum {
    A=100,
    B,
    C,
    D,
    E,
    F,
    G,
    H
};
int main()
{
    printf("%d\n", A);
    printf("%d\n", B);
    printf("%d\n", C);
    printf("%d\n", D);
    printf("%d\n", E);
    printf("%d\n", F);
}
```

**설명**
- `enum`은 관련된 정수 상수들을 **그룹으로 정의**합니다.
- 첫 번째 값을 `A=100`으로 지정하면, 이후 B, C, D, ...는 **자동으로 1씩 증가**합니다.
- B=101, C=102, D=103, E=104, F=105

**예상 출력**
```
100
101
102
103
104
105
```

---

### 5.2 16진수 비트 플래그 enum과 대입 제한

```c
#include <stdio.h>
enum {
    A = 0x1,
    B = 0x2,
    C = 0x4,
    D = 0x8,
    E = 0x10,
    F = 0x20,
    G = 0x40,
    H = 0x80
};
int main()
{
    A = 10;       // 컴파일 오류!
    printf("%d\n", A);
    printf("%d\n", B);
    printf("%d\n", C);
    printf("%d\n", D);
    printf("%d\n", E);
    printf("%d\n", F);
}
```

**설명**
- `enum`의 값은 **각 비트 위치를 2의 거듭제곱**으로 지정하여 비트 플래그로 사용할 수 있습니다.
- **핵심**: `enum` 상수는 **값을 변경할 수 없습니다**. `A = 10;`은 **컴파일 오류**입니다.
- 이 점이 `const int`와 `enum`이 공통으로 갖는 특성입니다. 둘 다 **읽기 전용** 상수를 만듭니다.

---

## 6. 구조체 (struct) 기초

구조체는 **서로 다른 자료형의 변수들을 하나로 묶는** 사용자 정의 자료형입니다.

### 6.1 구조체 선언, 초기화, 출력

```c
#include <stdio.h>
#include <stdlib.h>
struct Person
{
    char name[20];
    char phone[20];
};
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    printf("name: %s, phone: %s\n", per1.name, per1.phone);
    printf("name: %s, phone: %s\n", per2.name, per2.phone);
    printf("%d %d\n", sizeof(per1), sizeof(per1.name));
    printf("%p %p\n", &per1, per1.name);
}
```

**설명**
- `struct Person` : `name`(20바이트)과 `phone`(20바이트)을 가진 구조체를 정의합니다.
- `Person per1 = { "홍길동", "010-1234-1111" };` : 구조체 변수를 선언하면서 **초기화**합니다.
- `.`(점) 연산자로 멤버에 접근합니다: `per1.name`, `per1.phone`
- `sizeof(per1)` → **40** (name 20 + phone 20)
- `&per1`과 `per1.name`의 주소가 **같을 수 있습니다**(첫 번째 멤버의 시작 주소 = 구조체 시작 주소).

**예상 출력**
```
name: 홍길동, phone: 010-1234-1111
name: 장길산, phone: 010-4567-2222
40 20
(주소 값) (주소 값)
```

---

### 6.2 배열 멤버의 범위 밖 접근

```c
#include <stdio.h>
#include <stdlib.h>
struct Person
{
    char name[20];
    char phone[20];
};
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    printf("name: %s, phone: %s\n", per1.name, per1.phone);
    printf("name: %s, phone: %s\n", per2.name, per2.phone);
    printf("%d %d\n", sizeof(per1), sizeof(per1.name));
    printf("%p %p\n", &per1, per1.name);
    printf("%c", per1.name[20]);
}
```

**설명**
- 6.1과 동일하지만, 마지막 줄에서 `per1.name[20]`에 접근합니다.
- `name[20]`은 크기가 20인 배열이므로 유효 인덱스는 **0~19**입니다. `name[20]`은 **범위 밖 접근**으로 **정의되지 않은 동작**(Undefined Behavior)을 일으킵니다.
- 메모리상으로 `name[20]`은 바로 뒤의 `phone[0]`과 같은 위치일 수 있습니다.

---

### 6.3 strcpy_s로 구조체 멤버 변경

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char name[20];
    char phone[20];
};
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    strcpy_s(per1.name, strlen("홍길당") + 1, "홍길당");
    strcpy_s(per1.phone, strlen("010-1212-3434") + 1, "010-1212-3434");
    printf("name: %s, phone: %s\n", per1.name, per1.phone);
    printf("name: %s, phone: %s\n", per2.name, per2.phone);
}
```

**설명**
- 배열(`char name[20]`)에는 `=`으로 직접 문자열을 대입할 수 **없습니다**. `per1.name = "홍길당";`은 오류입니다.
- `strcpy_s(대상, 크기, 원본)` 함수를 사용하여 문자열을 **복사**해야 합니다.
- `strlen(문자열) + 1` : 문자열 길이 + 널 종료 문자(`\0`)까지 포함한 크기를 지정합니다.

**예상 출력**
```
name: 홍길당, phone: 010-1212-3434
name: 장길산, phone: 010-4567-2222
```

---

### 6.4 PrintPerson 함수 분리

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char name[20];
    char phone[20];
};
void PrintPerson(Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    strcpy_s(per1.name, strlen("홍길당") + 1, "홍길당");
    strcpy_s(per1.phone, strlen("010-1212-3434") + 1, "010-1212-3434");
    PrintPerson(&per1);
    PrintPerson(&per2);
}
```

**설명**
- 출력 코드를 `PrintPerson` 함수로 분리하면 **재사용성**이 높아집니다.
- 구조체 포인터를 매개변수로 받아, `->` 연산자로 멤버에 접근합니다.
- `&per1` : 구조체 변수의 **주소**를 전달합니다.

---

### 6.5 SetName, SetPhone 함수 분리

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char name[20];
    char phone[20];
};
void PrintPerson(Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetName(Person* p, const char* name)
{
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPhone(Person* p, const char* phone)
{
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    SetName(&per1, "홍길당");
    SetPhone(&per1, "010-1212-3434");
    PrintPerson(&per1);
    PrintPerson(&per2);
}
```

**설명**
- `strcpy_s` 호출도 `SetName`, `SetPhone` 함수로 분리했습니다.
- 매개변수 `const char* name` : 원본 문자열을 **수정하지 않겠다**는 의미입니다.
- 이처럼 **구조체를 다루는 함수들을 분리**하면, main 함수가 깔끔해지고 유지보수가 쉬워집니다.

---

### 6.6 함수 이름 개선과 const 활용

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char name[20];
    char phone[20];
};
void PrintPerson(const Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetPersonName(Person* p, const char* name)
{
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPersonPhone(Person* p, const char* phone)
{
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
int main()
{
    Person per1 = { "홍길동", "010-1234-1111" };
    Person per2 = { "장길산", "010-4567-2222" };

    SetPersonName(&per1, "홍길당");
    SetPersonPhone(&per1, "010-1212-3434");
    PrintPerson(&per1);
    PrintPerson(&per2);
}
```

**설명**
- 6.5에서 발전: 함수 이름을 `SetPersonName`, `SetPersonPhone`으로 **더 명확하게** 변경했습니다.
- `PrintPerson`의 매개변수를 `const Person* p`로 변경: 이 함수 안에서 `p`의 멤버를 **수정하지 않겠다**는 약속입니다.
- `const`를 적극 활용하면 실수로 값을 변경하는 버그를 **컴파일 단계에서 방지**할 수 있습니다.

> **참고**: ex18.cpp에서 이 구조(char[20] + 함수 분리)의 코드가 동일한 형태로 여러 번 반복됩니다. 수업 중 코드를 점진적으로 발전시키며 저장한 흔적입니다.

---

## 7. 구조체와 동적 메모리 할당

고정 크기 배열(`char[20]`) 대신, **포인터(`char*`) + malloc**을 사용하면 필요한 만큼만 메모리를 할당할 수 있습니다.

### 7.1 char* 멤버와 malloc 기초

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char* name;
    char* phone;
};
void PrintPerson(const Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetPersonName(Person* p, const char* name)
{
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPersonPhone(Person* p, const char* phone)
{
    p->phone = (char*)malloc(strlen(phone) + 1);
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
int main()
{
    Person per1 = { 0 };
    Person per2 = { 0 };

    SetPersonName(&per1, "홍길당");
    SetPersonPhone(&per1, "010-1212-3434");
    PrintPerson(&per1);
    PrintPerson(&per2);
}
```

**설명**
- `char* name` : 고정 배열 대신 **포인터**로 선언합니다. 처음에는 아무것도 가리키지 않습니다.
- `malloc(strlen(name) + 1)` : 문자열 길이 + 1(널 문자)만큼 **힙 메모리를 할당**합니다.
- `Person per1 = { 0 };` : 모든 멤버를 **0(NULL)으로 초기화**합니다.
- `per2`는 데이터를 설정하지 않았으므로, `PrintPerson(&per2)`는 **NULL 포인터 출력** 문제가 발생할 수 있습니다.
- 이 예제에는 **free**가 없어 **메모리 누수**가 발생합니다.

---

### 7.2 FreePerson 함수 추가 (스택 할당)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char* name;
    char* phone;
};
void PrintPerson(const Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetPersonName(Person* p, const char* name)
{
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPersonPhone(Person* p, const char* phone)
{
    p->phone = (char*)malloc(strlen(phone) + 1);
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
void FreePerson(Person* p)
{
    free(p->name);
    free(p->phone);
}
int main()
{
    Person per1 = { 0 };
    Person per2 = { 0 };

    SetPersonName(&per1, "홍길당");
    SetPersonPhone(&per1, "010-1212-3434");
    SetPersonName(&per2, "장길산");
    SetPersonPhone(&per2, "010-2345-6543");

    PrintPerson(&per1);
    PrintPerson(&per2);

    FreePerson(&per1);
    FreePerson(&per2);
}
```

**설명**
- `FreePerson` 함수를 추가하여, `malloc`으로 할당한 `name`과 `phone` 메모리를 **해제**합니다.
- **규칙**: `malloc`으로 할당한 메모리는 반드시 `free`로 해제해야 합니다. 그렇지 않으면 **메모리 누수**가 발생합니다.
- 구조체 자체(`per1`, `per2`)는 **스택에 있으므로** `free(p)`를 호출하지 **않습니다**.

**예상 출력**
```
name: 홍길당, phone: 010-1212-3434
name: 장길산, phone: 010-2345-6543
```

> **참고**: ex18.cpp에서 이 패턴(스택 할당 + FreePerson)이 `#pragma warning(disable:6387)` 유무 차이로 여러 번 등장합니다. `#pragma warning`은 MSVC에서 특정 경고를 비활성화하는 지시문으로, 코드 동작에는 영향을 주지 않습니다.

---

### 7.3 구조체 자체를 힙에 할당 (malloc)

```c
#pragma warning(disable:6387)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char* name;
    char* phone;
};
void PrintPerson(const Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetPersonName(Person* p, const char* name)
{
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPersonPhone(Person* p, const char* phone)
{
    p->phone = (char*)malloc(strlen(phone) + 1);
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
void FreePerson(Person* p)
{
    free(p->name);
    free(p->phone);

    free(p);
}
int main()
{
    Person* per1 = 0;
    Person* per2 = 0;

    per1 = (Person*)malloc(sizeof(Person));
    per2 = (Person*)malloc(sizeof(Person));

    SetPersonName(per1, "홍길당");
    SetPersonPhone(per1, "010-1212-3434");
    SetPersonName(per2, "장길산");
    SetPersonPhone(per2, "010-2345-6543");

    PrintPerson(per1);
    PrintPerson(per2);

    FreePerson(per1);
    FreePerson(per2);
}
```

**설명**
- 7.2와의 핵심 차이: 구조체 **자체도 힙에 동적 할당**합니다.
- `Person* per1 = 0;` → 포인터 변수 선언 (NULL 초기화)
- `per1 = (Person*)malloc(sizeof(Person));` → Person 구조체 크기만큼 힙에 할당
- `FreePerson`에서 `free(p->name)`, `free(p->phone)`, **`free(p)`** 세 번 해제합니다.
  - 멤버부터 해제한 후, 마지막에 구조체 자체를 해제합니다. 순서가 중요합니다!

---

### 7.4 AllocPerson 함수로 추상화

```c
#pragma warning(disable:6387)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person
{
    char* name;
    char* phone;
};
void PrintPerson(const Person* p)
{
    printf("name: %s, phone: %s\n", p->name, p->phone);
}
void SetPersonName(Person* p, const char* name)
{
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy_s(p->name, strlen(name) + 1, name);
}
void SetPersonPhone(Person* p, const char* phone)
{
    p->phone = (char*)malloc(strlen(phone) + 1);
    strcpy_s(p->phone, strlen(phone) + 1, phone);
}
void FreePerson(Person* p)
{
    free(p->name);
    free(p->phone);

    free(p);
}
Person* AllocPerson()
{
    return  (Person*)malloc(sizeof(Person));
}
int main()
{
    Person* per1 = 0;
    Person* per2 = 0;

    per1 = AllocPerson();
    per2 = AllocPerson();

    SetPersonName(per1, "홍길당");
    SetPersonPhone(per1, "010-1212-3434");
    SetPersonName(per2, "장길산");
    SetPersonPhone(per2, "010-2345-6543");

    PrintPerson(per1);
    PrintPerson(per2);

    FreePerson(per1);
    FreePerson(per2);
}
```

**설명**
- `AllocPerson()` 함수를 추가하여 구조체 할당도 **캡슐화**했습니다.
- 이제 구조체에 대한 **CRUD 패턴**이 완성됩니다:
  - **생성**: `AllocPerson()` → 메모리 할당
  - **설정**: `SetPersonName()`, `SetPersonPhone()` → 데이터 입력
  - **읽기**: `PrintPerson()` → 데이터 출력
  - **삭제**: `FreePerson()` → 메모리 해제
- 이 패턴은 객체지향 프로그래밍의 **생성자/소멸자** 개념과 비슷합니다.

**예상 출력**
```
name: 홍길당, phone: 010-1212-3434
name: 장길산, phone: 010-2345-6543
```

---

## 8. 2차원 동적 배열

정적 2차원 배열(`int arr[5][4]`)은 크기가 컴파일 시 고정됩니다. **동적 2차원 배열**은 실행 중에 크기를 결정할 수 있습니다.

### 8.1 수동 행별 malloc / free

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row = 5, col = 4;

    int** pa = (int**)malloc(sizeof(int*) * row);

    pa[0] = (int*)malloc(sizeof(int) * col);
    pa[1] = (int*)malloc(sizeof(int) * col);
    pa[2] = (int*)malloc(sizeof(int) * col);
    pa[3] = (int*)malloc(sizeof(int) * col);
    pa[4] = (int*)malloc(sizeof(int) * col);

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            pa[i][j] = i * col + j + 1;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            printf("%3d", pa[i][j]);
        printf("\n");
    }

    free(pa[0]);
    free(pa[1]);
    free(pa[2]);
    free(pa[3]);
    free(pa[4]);

    free(pa);
}
```

**설명**
- `int** pa` : **포인터의 포인터**. 각 원소가 `int*`(행 하나의 시작 주소)입니다.
- `malloc(sizeof(int*) * row)` : 행 포인터 배열(5개의 `int*`)을 할당합니다.
- 각 `pa[i]`에 열 크기만큼 `int` 배열을 개별적으로 할당합니다.
- 해제할 때는 **각 행을 먼저 free한 후**, 마지막에 **행 포인터 배열을 free**합니다.
- 이 방식은 **행이 많아지면 코드가 길어지는** 단점이 있습니다.

**예상 출력**
```
  1  2  3  4
  5  6  7  8
  9 10 11 12
 13 14 15 16
 17 18 19 20
```

---

### 8.2 반복문으로 개선

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row = 5, col = 4;

    int** pa = (int**)malloc(sizeof(int*) * row);

    for(int i = 0 ; i < row ; ++i)
        pa[i] = (int*)malloc(sizeof(int) * col);

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            pa[i][j] = i * col + j + 1;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            printf("%3d", pa[i][j]);
        printf("\n");
    }

    for (int i = 0; i < row; ++i)
        free(pa[i]);

    free(pa);
}
```

**설명**
- 8.1에서 `pa[0]`~`pa[4]`를 하나씩 할당/해제하던 것을 **for 문**으로 간결하게 바꿨습니다.
- `row`, `col` 값만 바꾸면 **어떤 크기의 2차원 배열도** 만들 수 있습니다.

---

### 8.3 AllocMemory / FreeMemory 함수로 분리

```c
#include <stdio.h>
#include <stdlib.h>

int** AllocMemory(int row, int col)
{
    int** pa = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; ++i)
        pa[i] = (int*)malloc(sizeof(int) * col);

    return pa;
}
void FreeMemory(int** pa, int row, int col)
{
    for (int i = 0; i < row; ++i)
        free(pa[i]);
    free(pa);
}
int main()
{
    int row = 5, col = 4;

    int** pa = AllocMemory(row, col);

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            pa[i][j] = i * col + j + 1;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            printf("%3d", pa[i][j]);
        printf("\n");
    }

    FreeMemory(pa, row, col);
}
```

**설명**
- 할당과 해제를 각각 `AllocMemory`, `FreeMemory` 함수로 **캡슐화**했습니다.
- `main` 함수가 더 깔끔해지고, 할당/해제 로직을 **재사용**할 수 있습니다.

---

### 8.4 InitArray / PrintArray 함수 추가

```c
#include <stdio.h>
#include <stdlib.h>

int** AllocMemory(int row, int col)
{
    int** pa = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; ++i)
        pa[i] = (int*)malloc(sizeof(int) * col);

    return pa;
}
void FreeMemory(int** pa, int row, int col)
{
    for (int i = 0; i < row; ++i)
        free(pa[i]);
    free(pa);
}
void InitArray(int** pa, int row, int col)
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            pa[i][j] = i * col + j + 1;
}
void PrintArray(int** pa, int row, int col)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            printf("%3d", pa[i][j]);
        printf("\n");
    }
}
int main()
{
    int row = 7, col = 8;

    int** pa = AllocMemory(row, col);

    InitArray(pa, row, col);
    PrintArray(pa, row, col);

    FreeMemory(pa, row, col);
}
```

**설명**
- 초기화와 출력도 `InitArray`, `PrintArray` 함수로 분리했습니다.
- `main` 함수는 이제 **4줄**로 매우 간결합니다: 할당 → 초기화 → 출력 → 해제
- 크기를 `7×8`로 변경하여 더 큰 배열을 테스트합니다.

**예상 출력**
```
  1  2  3  4  5  6  7  8
  9 10 11 12 13 14 15 16
 17 18 19 20 21 22 23 24
 25 26 27 28 29 30 31 32
 33 34 35 36 37 38 39 40
 41 42 43 44 45 46 47 48
 49 50 51 52 53 54 55 56
```

---

## 9. typedef와 함수 포인터

이 절은 ex18.cpp의 **활성(실행되는) 코드**이며, 가장 발전된 예제입니다.

### 9.1 typedef의 다양한 활용

```c
#include <stdio.h>
typedef int INT;
typedef unsigned char UCHAR;
typedef int* PINT;
typedef int(*PA)[3];
typedef int (*PFUN)(int, int);

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
    INT n = 10;
    UCHAR c = 200;
    int arr[2][3] = { 1,2 };
    PA pa = arr;
    PFUN f1 = Add, f2 = Sub;

    printf("%d\n", n);
    printf("%d\n", c);
    printf("%d\n", pa[0][1]);
    printf("%d %d\n", f1(1, 2), f2(1, 2));
}
```

**설명**

`typedef`는 기존 자료형에 **별칭(alias)**을 붙이는 키워드입니다.

| typedef 선언 | 의미 | 사용 예 |
|-------------|------|---------|
| `typedef int INT;` | `int`를 `INT`로 사용 | `INT n = 10;` |
| `typedef unsigned char UCHAR;` | `unsigned char`를 `UCHAR`로 사용 | `UCHAR c = 200;` |
| `typedef int* PINT;` | `int*`(int 포인터)를 `PINT`로 사용 | `PINT p = &n;` |
| `typedef int(*PA)[3];` | `int`형 3열짜리 2차원 배열 포인터를 `PA`로 사용 | `PA pa = arr;` |
| `typedef int (*PFUN)(int, int);` | `int`를 반환하고 `int` 2개를 받는 **함수 포인터**를 `PFUN`으로 사용 | `PFUN f1 = Add;` |

**함수 포인터 상세 설명**
- `PFUN f1 = Add;` : 함수 `Add`의 **주소**를 `f1`에 저장합니다.
- `f1(1, 2)` : `f1`이 가리키는 함수(`Add`)를 호출합니다. → 1 + 2 = **3**
- `f2(1, 2)` : `f2`가 가리키는 함수(`Sub`)를 호출합니다. → 1 - 2 = **-1**
- 함수 포인터를 사용하면 **어떤 함수를 호출할지 실행 중에 결정**할 수 있습니다.

**배열 포인터 상세 설명**
- `int arr[2][3] = { 1, 2 };` : 나머지는 0으로 초기화됩니다. → `{ {1,2,0}, {0,0,0} }`
- `PA pa = arr;` : 2차원 배열을 가리키는 포인터. `pa[0][1]` = 2

**예상 출력**
```
10
200
2
3 -1
```

---

## 10. 정리 표

| 주제 | 핵심 내용 |
|------|-----------|
| 비트 AND (`&`) | 두 비트 모두 1이면 1 |
| 비트 OR (`\|`) | 둘 중 하나라도 1이면 1 |
| 비트 XOR (`^`) | 두 비트가 다르면 1 |
| 비트 NOT (`~`) | 모든 비트 반전 |
| 왼쪽 시프트 (`<<`) | 비트를 왼쪽으로 이동 (×2 효과) |
| 오른쪽 시프트 (`>>`) | 비트를 오른쪽으로 이동 (÷2 효과) |
| `signed char` 범위 | -128 ~ 127 |
| `unsigned char` 범위 | 0 ~ 255 |
| 비트 set | `data \|= FLAG` |
| 비트 clear | `data &= ~FLAG` |
| 비트 toggle | `data ^= FLAG` |
| `enum` | 관련 정수 상수 그룹, 자동 증가, 값 변경 불가 |
| `struct` | 서로 다른 자료형을 하나로 묶는 사용자 정의 자료형 |
| `.` 연산자 | 구조체 변수의 멤버 접근: `per1.name` |
| `->` 연산자 | 구조체 포인터의 멤버 접근: `p->name` |
| `malloc` | 힙에 메모리 동적 할당 |
| `free` | 동적 할당된 메모리 해제 |
| `strcpy_s` | 안전한 문자열 복사 (MSVC) |
| 2D 동적 배열 | `int**` + 행별 malloc |
| `typedef` | 자료형에 별칭 부여 |
| 함수 포인터 | 함수의 주소를 변수에 저장, 간접 호출 가능 |

---

## 11. 연습 문제 (스스로 풀어보기)

1. `unsigned char`에 256을 넣으면 어떤 값이 저장되는지 예측하고, `%d`와 `%x`로 확인해 보세요.

2. `int a = 0xFF;`에 대해 다음 비트 연산 결과를 예측하고 코드로 확인하세요:
   - `a & 0x0F` = ?
   - `a | 0xF0` = ?
   - `a ^ 0xFF` = ?

3. `enum Color { RED, GREEN=5, BLUE };`에서 `RED`, `GREEN`, `BLUE`의 값은 각각 무엇인지 확인하세요.

4. `struct Student { char name[30]; int score; };`를 선언하고, 학생 2명의 이름과 점수를 저장한 뒤 출력하는 프로그램을 작성하세요. (`SetName`, `PrintStudent` 함수를 분리하세요.)

5. 연습문제 4의 `Student`에서 `char name[30]` 대신 `char* name`을 사용하도록 바꾸고, `malloc`/`free`를 사용하여 메모리를 관리하세요.

6. `typedef`를 이용하여 `void (*)(const char*)` 타입을 `PRINTFUNC`라는 이름으로 정의하고, `printf`를 감싼 래퍼 함수를 함수 포인터로 호출해 보세요.

7. 3×5 크기의 2차원 동적 배열을 할당하고, 구구단(3단~5단)을 저장한 뒤 표 형태로 출력하세요. 할당/해제/초기화/출력을 각각 함수로 분리하세요.

---

## 12. 코드 발전 과정 요약

ex18.cpp는 수업 중 코드를 점진적으로 발전시킨 흔적이 담겨 있습니다. 아래는 **아래(기초)에서 위(고급)로** 코드가 발전한 전체 흐름입니다.

```
[비트 연산 기초]
  기본 비트 연산 (&, |, ^, ~)
    → signed/unsigned char 범위 실험
      → 시프트 연산 (<<, >>)
        → 비트 플래그 (set → clear → toggle)
          → enum으로 상수 정의

[구조체 기초]
  struct 선언 + printf
    → sizeof / 주소 확인
      → strcpy_s로 멤버 변경
        → 함수 분리 (PrintPerson, SetName)
          → 함수 이름 개선 + const 활용

[동적 메모리 할당]
  char* 멤버 + malloc (free 없음)
    → FreePerson 추가 (스택 할당)
      → 구조체 자체를 힙에 malloc
        → AllocPerson 함수 추가

[2차원 동적 배열]
  수동 행별 malloc/free
    → 반복문 사용
      → AllocMemory/FreeMemory 함수
        → InitArray/PrintArray 추가

[typedef와 함수 포인터]
  typedef로 자료형 별칭
    → 함수 포인터 typedef
      → 배열 포인터 typedef
```

---

이 강의 자료는 **example/ex18.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 각 섹션은 **기초 → 발전** 순서로 배치되어 있으므로, 1장부터 순서대로 진행하면 됩니다. 비트 연산과 구조체는 독립적인 주제이므로 **1~5장(비트 연산·enum)** → **6~7장(구조체·동적 메모리)** → **8장(2D 배열)** → **9장(typedef·함수 포인터)** 순서로 수업하는 것을 권장합니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
