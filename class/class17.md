# C언어 기초 강의 17 - ex17.cpp 코드를 통한 2차원 배열, 배열 포인터, 구조체 기반 동적 문자열 관리

이 강의는 **example/ex17.cpp**에 담긴 예제들을 바탕으로, **2차원 배열**과 **배열 포인터**, **구조체(typedef struct)**를 활용한 **동적 문자열 배열 관리** 프로그램을 단계별로 학습합니다.

---

## 0. 학습 목표

- 메뉴 기반 프로그램의 구조를 이해하고 `switch`-`case`와 `_getch()`를 활용할 수 있다.
- `typedef struct`로 구조체를 정의하고, 구조체 포인터로 함수에 전달할 수 있다.
- `malloc`/`free`를 사용한 동적 메모리 할당과 해제 패턴을 이해한다.
- **이중 포인터(`char**`)**를 이용한 동적 문자열 배열을 관리할 수 있다.
- 2차원 배열의 선언·초기화·메모리 구조를 이해한다.
- **배열 포인터 `int(*pa)[N]`**의 의미를 알고, 2차원 배열을 함수에 전달할 수 있다.
- 2차원 배열을 활용한 패턴(대각선, X자) 출력 프로그램을 작성할 수 있다.

---

## 0.1 수업 진행 순서

| 순서 | 내용 |
|------|------|
| **1장** | 메뉴 기반 프로그램 구조 (`_getch`, `switch`) |
| **2장** | StringArray 구조체 정의와 함수 틀 잡기 |
| **3장** | 문자열 추가·출력·검색·삭제 구현 |
| **4장** | 메모리 해제(`free`)와 `FreeString` 함수 |
| **5장** | `char**` 동적 할당과 `capacity` 관리 |
| **6장** | 2차원 배열 기초 (선언, 출력, 메모리 주소) |
| **7장** | 배열 포인터 `int(*pa)[N]` |
| **8장** | 2차원 배열을 함수에 전달하기 |
| **9장** | 2차원 배열 패턴 (대각선, X자) |
| **10장** | 정리 표와 연습 문제 |

---

## 1. 메뉴 기반 프로그램 구조

### 1.1 기본 메뉴 루프와 switch-case

```c
#include <stdio.h>
#include <conio.h>

void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
int main()
{
    int run = 1;
    while (run)
    {
        switch (_getch())
        {
        case '1':
            printf("입력");
            break;
        case '2':
            printf("출력");
            break;
        case '3':
            printf("검색");
            break;
        case '4':
            printf("삭제");
            break;
        case '0':
            run = 0;
            break;
        }
    }
}
```

**설명**
- `#include <conio.h>` : `_getch()` 함수를 사용하기 위해 포함합니다 (Windows 전용).
- `_getch()` : 키보드에서 **한 글자를 즉시** 읽어옵니다. Enter를 누르지 않아도 바로 입력됩니다.
- `puts("문자열")` : 문자열을 출력하고 **자동으로 줄바꿈**합니다 (`printf` + `\n`과 동일한 효과).
- `switch (_getch())` : 입력된 문자에 따라 분기합니다. `'1'`은 **문자 '1'**(ASCII 49)입니다.
- `int run = 1;` + `while (run)` : `run`이 0이 되면 반복이 종료됩니다. `case '0'`에서 `run = 0`으로 설정하여 프로그램을 끝냅니다.
- 아직 `Menu()` 함수를 호출하지 않고 있으므로, 메뉴가 화면에 표시되지 않습니다 (다음 버전에서 개선).

---

## 2. StringArray 구조체 정의와 함수 틀

### 2.1 구조체 정의와 빈 함수 틀

```c
#include <stdio.h>
#include <conio.h>

typedef struct _stringArray
{
    char* buf[100];
    int count;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{

}
void PrintString(const StringArray* psa)
{

}
void SearchString(const StringArray* psa)
{

}
void RemoveString(StringArray* psa)
{

}
int main()
{
    StringArray sa = { 0 };
    int run = 1;
    while (run)
    {
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }
}
```

**설명**
- `typedef struct _stringArray { ... } StringArray;` : **구조체를 정의**하면서 동시에 `StringArray`라는 **별칭(typedef)**을 만듭니다. 이후 `struct _stringArray` 대신 `StringArray`로 간결하게 쓸 수 있습니다.
- `char* buf[100]` : **문자열 포인터 100개**를 담는 배열입니다. 각 `buf[i]`는 `char*`로, 동적으로 할당된 문자열의 주소를 저장합니다.
- `int count` : 현재 저장된 문자열의 **개수**를 추적합니다.
- `StringArray sa = { 0 };` : 구조체를 **0으로 초기화**합니다 (모든 포인터 = NULL, count = 0).
- `StringArray* psa` : 구조체를 **포인터로** 전달하여 함수 안에서 원본을 수정할 수 있게 합니다.
- `const StringArray* psa` : `PrintString`, `SearchString`은 내용을 **읽기만** 하므로 `const`를 붙여 변경을 방지합니다.
- `&sa` : 구조체 변수 `sa`의 **주소**를 전달합니다.
- 함수 본체는 아직 비어 있으며, **구조(뼈대)**만 잡은 상태입니다.

---

## 3. 문자열 추가·출력·검색·삭제 구현

### 3.1 AddString과 PrintString 구현

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char* buf[100];
    int count;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{

}
void RemoveString(StringArray* psa)
{

}
int main()
{
    StringArray sa = { 0 };
    int run = 1;
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }
}
```

**설명**
- `#include <string.h>` : `strlen`, `strcpy_s`, `strcmp` 등 문자열 함수를 사용합니다.
- `#include <stdlib.h>` : `malloc`, `free` 등 동적 메모리 함수를 사용합니다.
- **AddString 동작 원리:**
  1. `gets_s(str, 500)` : 사용자로부터 문자열을 입력받아 지역 배열 `str`에 저장합니다.
  2. `malloc(strlen(str) + 1)` : 입력된 문자열 길이 + 1(널 문자 `\0`) 만큼 **힙 메모리를 동적 할당**합니다.
  3. `strcpy_s(s, ...)` : 할당된 메모리에 문자열을 **복사**합니다.
  4. `psa->buf[psa->count] = s` : 할당된 메모리 주소를 배열에 저장합니다.
  5. `++psa->count` : 카운트를 1 증가시킵니다.
- **PrintString 동작 원리:** `count`만큼 반복하며 각 문자열을 인덱스와 함께 출력합니다.
- `main`에서 `Menu()` 호출이 추가되어 메뉴가 화면에 표시됩니다.

---

### 3.2 SearchString과 RemoveString 구현 (메모리 해제 없는 버전)

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char* buf[100];
    int count;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{
    char str[500];
    printf("검색할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            printf("[%d] : %s 있습니다.\n", i, str);
            break;
        }
    }
}
void RemoveString(StringArray* psa)
{
    char str[500];
    printf("삭제할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            for (int j = i; j < psa->count - 1; ++j)
                psa->buf[j] = psa->buf[j + 1];
            --psa->count;
            break;
        }
    }
}
int main()
{
    StringArray sa = { 0 };
    int run = 1;
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }
}
```

**설명**
- **SearchString 동작 원리:**
  1. 사용자로부터 검색할 문자열을 입력받습니다.
  2. `strcmp(str, psa->buf[i]) == 0` : 두 문자열이 **같으면 0**을 반환합니다.
  3. 찾으면 인덱스와 함께 출력하고 `break`로 탈출합니다.
- **RemoveString 동작 원리:**
  1. 삭제할 문자열을 찾습니다.
  2. 찾은 위치부터 뒤의 요소를 **한 칸씩 앞으로** 이동시킵니다 (`buf[j] = buf[j+1]`).
  3. `--psa->count`로 개수를 줄입니다.
- **문제점:** 삭제된 문자열의 메모리를 `free`하지 않아 **메모리 누수(memory leak)**가 발생합니다!

---

## 4. 메모리 해제 - free와 FreeString

### 4.1 RemoveString에 free 추가 + FreeString 함수

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char* buf[100];
    int count;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{
    char str[500];
    printf("검색할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            printf("[%d] : %s 있습니다.\n", i, str);
            break;
        }
    }
}
void RemoveString(StringArray* psa)
{
    char str[500];
    printf("삭제할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            free(psa->buf[i]);
            for (int j = i; j < psa->count - 1; ++j)
                psa->buf[j] = psa->buf[j + 1];
            --psa->count;
            break;
        }
    }
}
void FreeString(StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        free(psa->buf[i]);
}
int main()
{
    StringArray sa = { 0 };
    int run = 1;
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }

    FreeString(&sa);
}
```

**설명**
- 이전 버전과의 **핵심 차이점**:
  1. `RemoveString`에서 요소를 이동하기 **전에** `free(psa->buf[i])`를 호출하여 삭제할 문자열의 메모리를 해제합니다.
  2. `FreeString` 함수가 추가되어, 프로그램 종료 전에 **남아 있는 모든 문자열**의 메모리를 해제합니다.
- **메모리 관리 패턴:** `malloc`으로 할당한 메모리는 반드시 `free`로 해제해야 합니다.
  - **삭제 시:** 해당 요소 `free`
  - **종료 시:** 남은 모든 요소 `free`

---

## 5. char** 동적 할당과 capacity 관리

### 5.1 char** 동적 할당 버전 (고정 배열 → 동적 배열)

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char** buf;
    int count;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{
    char str[500];
    printf("검색할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            printf("[%d] : %s 있습니다.\n", i, str);
            break;
        }
    }
}
void RemoveString(StringArray* psa)
{
    char str[500];
    printf("삭제할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            free(psa->buf[i]);
            for (int j = i; j < psa->count - 1; ++j)
                psa->buf[j] = psa->buf[j + 1];
            --psa->count;
            break;
        }
    }
}
void InitString(StringArray* psa, int capacity)
{
    psa->buf = (char**)malloc(sizeof(char*) * capacity);
    psa->count = 0;
}
void FreeString(StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        free(psa->buf[i]);
}
int main()
{
    StringArray sa;
    int run = 1;

    InitString(&sa, 1000);
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }

    FreeString(&sa);
}
```

**설명**
- **핵심 변경:** `char* buf[100]` (고정 크기 100) → `char** buf` (동적 크기).
- `char** buf` : **이중 포인터**입니다. `char*` 포인터들의 배열을 가리키는 포인터로, `malloc`으로 원하는 크기만큼 할당할 수 있습니다.
- `InitString` 함수가 추가되어 **초기화를 전담**합니다:
  - `(char**)malloc(sizeof(char*) * capacity)` : `char*` 포인터 `capacity`개를 저장할 메모리를 할당합니다.
  - 예: `capacity = 1000`이면 문자열 포인터 1000개분의 공간이 확보됩니다.
- `main`에서 `{ 0 }` 초기화 대신 `InitString(&sa, 1000)`을 호출합니다.

**이중 포인터 메모리 구조**
```
sa.buf ──→ [ char* | char* | char* | ... | char* ]   ← malloc으로 할당 (1000칸)
              │        │        │
              ▼        ▼        ▼
           "Hello"  "World"  "Test"                   ← 각각 malloc으로 할당
```

---

### 5.2 capacity 필드 추가 (오버플로우 방지)

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char** buf;
    int count;
    int capacity;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    if (psa->count >= psa->capacity)
        return;

    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{
    char str[500];
    printf("검색할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            printf("[%d] : %s 있습니다.\n", i, str);
            break;
        }
    }
}
void RemoveString(StringArray* psa)
{
    char str[500];
    printf("삭제할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            free(psa->buf[i]);
            for (int j = i; j < psa->count - 1; ++j)
                psa->buf[j] = psa->buf[j + 1];
            --psa->count;
            break;
        }
    }
}
void InitString(StringArray* psa, int capacity)
{
    psa->buf = (char**)malloc(sizeof(char*) * capacity);
    psa->count = 0;
    psa->capacity = capacity;
}
void FreeString(StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        free(psa->buf[i]);
}
int main()
{
    StringArray sa;
    int run = 1;

    InitString(&sa, 1000);
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }

    FreeString(&sa);
}
```

**설명**
- **핵심 변경:** 구조체에 `int capacity` 필드가 추가되었습니다.
- `AddString`에 **오버플로우 검사**가 추가: `if (psa->count >= psa->capacity) return;`
  - 할당된 용량을 초과하여 문자열을 추가하지 못하도록 방지합니다.
- `InitString`에서 `psa->capacity = capacity;`로 용량을 기록합니다.
- 이로써 구조체가 **count**(현재 개수)와 **capacity**(최대 용량) 두 가지 정보를 모두 관리합니다.

---

### 5.3 UninitString으로 정리 (최종 버전)

```c
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stringArray
{
    char** buf;
    int count;
    int capacity;
}StringArray;
void Menu()
{
    puts("1. 문자열 입력:");
    puts("2. 모든 문자열 출력:");
    puts("3. 문자열 검색:");
    puts("4. 문자열 삭제:");
    puts("0. 프로그램 종료");
}
void AddString(StringArray* psa)
{
    if (psa->count >= psa->capacity)
        return;

    printf("문자열 입력:");
    char str[500];
    gets_s(str, 500);
    char* s = (char*)malloc(strlen(str) + 1);
    strcpy_s(s, strlen(str) + 1, str);

    psa->buf[psa->count] = s;
    ++psa->count;
}
void PrintString(const StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        printf("[%d] : %s\n", i, psa->buf[i]);
}
void SearchString(const StringArray* psa)
{
    char str[500];
    printf("검색할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            printf("[%d] : %s 있습니다.\n", i, str);
            break;
        }
    }
}
void RemoveString(StringArray* psa)
{
    char str[500];
    printf("삭제할 문자열 입력:");
    gets_s(str, 500);
    for (int i = 0; i < psa->count; ++i)
    {
        if (strcmp(str, psa->buf[i]) == 0)
        {
            free(psa->buf[i]);
            for (int j = i; j < psa->count - 1; ++j)
                psa->buf[j] = psa->buf[j + 1];
            --psa->count;
            break;
        }
    }
}
void InitString(StringArray* psa, int capacity)
{
    psa->buf = (char**)malloc(sizeof(char*) * capacity);
    psa->count = 0;
    psa->capacity = capacity;
}
void UninitString(StringArray* psa)
{
    for (int i = 0; i < psa->count; ++i)
        free(psa->buf[i]);
}
int main()
{
    StringArray sa;
    int run = 1;

    InitString(&sa, 1000);
    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            AddString(&sa);
            break;
        case '2':
            PrintString(&sa);
            break;
        case '3':
            SearchString(&sa);
            break;
        case '4':
            RemoveString(&sa);
            break;
        case '0':
            run = 0;
            break;
        }
    }

    UninitString(&sa);
}
```

**설명**
- **핵심 변경:** `FreeString` → `UninitString`으로 함수 이름이 변경되었습니다.
- `InitString`(초기화) ↔ `UninitString`(해제)로 **대칭적인 이름 쌍**을 이루어 코드의 의도가 더 명확해집니다.
- **메모리 관리 패턴 정리:**

| 동작 | 함수 | 설명 |
|------|------|------|
| **초기화** | `InitString` | `char**` 배열을 `malloc`으로 할당, count=0, capacity 설정 |
| **추가** | `AddString` | 각 문자열을 `malloc`으로 할당 후 배열에 포인터 저장 |
| **삭제** | `RemoveString` | 해당 문자열 `free` → 배열 요소 이동 → count 감소 |
| **종료** | `UninitString` | 남은 모든 문자열 `free` |

---

## 6. 2차원 배열 기초

### 6.1 2차원 배열 선언과 출력

```c
#include <stdio.h>
int main()
{
    int arr[2][3] = { 10,20,30,40,50,60 };

    printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
}
```

**설명**
- `int arr[2][3]` : **2행 3열**의 2차원 배열을 선언합니다. 총 6개의 `int`를 저장합니다.
- `{ 10,20,30,40,50,60 }` : 값이 **행 우선(row-major)** 순서로 채워집니다.
  - `arr[0]` = {10, 20, 30} (첫 번째 행)
  - `arr[1]` = {40, 50, 60} (두 번째 행)
- `arr[행][열]`로 특정 요소에 접근합니다.

**예상 출력**
```
10 20 30
40 50 60
```

---

### 6.2 2차원 배열의 메모리 주소

```c
#include <stdio.h>
int main()
{
    int arr[2][3] = { 10,20,30,40,50,60 };

    printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("\n");
    printf("%p %p %p\n", &arr[0][0], &arr[0][1], &arr[0][2]);
    printf("%p %p %p\n", &arr[1][0], &arr[1][1], &arr[1][2]);
    printf("\n");
    printf("%p %p %p\n", arr, arr[0], arr[1]);
}
```

**설명**
- `%p` : **포인터(주소)**를 16진수로 출력합니다.
- `&arr[0][0]`, `&arr[0][1]`, ... : 각 요소의 메모리 주소입니다. `int`가 4바이트이므로 주소가 **4씩 증가**합니다.
- `arr`, `arr[0]` : 배열 이름은 **첫 번째 요소의 주소**를 나타냅니다. `arr`과 `arr[0]`은 같은 주소를 가리키지만 **타입이 다릅니다**.
  - `arr` : `int(*)[3]` 타입 (행 단위 포인터)
  - `arr[0]` : `int*` 타입 (요소 단위 포인터)
- `arr[1]`은 `arr[0]`보다 `3 * sizeof(int) = 12` 바이트 뒤에 위치합니다.

**예상 출력 (주소는 실행 환경마다 다름)**
```
10 20 30
40 50 60

0061FE00 0061FE04 0061FE08
0061FE0C 0061FE10 0061FE14

0061FE00 0061FE00 0061FE0C
```

---

### 6.3 메모리 구조와 인덱스 분석

```c
#include <stdio.h>
int main()
{
    int arr[2][3] = { 10,20,30,40,50,60 };

    printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("\n");
    printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("%d %d %d\n", arr[0][3], arr[0][4], arr[0][5]);
    printf("\n");
    printf("%d %d %d\n", arr[1][-3], arr[1][-2], arr[1][-1]);
    printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("\n");
    printf("%p %p %p\n", &arr[0][0], &arr[0][1], &arr[0][2]);
    printf("%p %p %p\n", &arr[1][0], &arr[1][1], &arr[1][2]);
    printf("\n");
    printf("%p %p %p\n", arr, arr[0], arr[1]);
}
```

**설명**
- 이 예제는 2차원 배열이 메모리에서 **1차원으로 연속 배치**된다는 것을 보여줍니다.
- `arr[0][3]` : 문법적으로 `arr[0]`은 3개짜리인데 인덱스 3을 사용합니다. 실제로는 `arr[1][0]`과 같은 메모리 위치를 가리킵니다.
- `arr[1][-3]` : 음수 인덱스로 `arr[0][0]`과 같은 위치에 접근합니다.
- **핵심:** C에서 배열은 메모리에 연속으로 저장되므로, 인덱스 범위를 벗어나면 **다른 행의 데이터에 접근**하게 됩니다. 이는 이해를 위한 예제이며, 실제 코드에서는 **범위를 벗어나지 않도록** 주의해야 합니다.

**예상 출력**
```
10 20 30
40 50 60

10 20 30
40 50 60

10 20 30
40 50 60

0061FE00 0061FE04 0061FE08
0061FE0C 0061FE10 0061FE14

0061FE00 0061FE00 0061FE0C
```

---

## 7. 배열 포인터 `int(*pa)[N]`

### 7.1 2차원 배열과 배열 포인터

```c
#include <stdio.h>
int main()
{
    int arr[2][3] = { 10,20,30,40,50,60 };

    printf("%d %d %d\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("%d %d %d\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("\n");
    printf("%p %p %p\n", arr, arr[0], arr[1]);

    int(*pa)[3];
    pa = arr;
    printf("\n");
    printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
    printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
    printf("\n");
    printf("%p %p %p\n", pa, pa[0], pa[1]);
}
```

**설명**
- `int(*pa)[3]` : **배열 포인터**를 선언합니다. `pa`는 "int 3개짜리 배열"을 가리키는 포인터입니다.
- `pa = arr` : 2차원 배열 `arr`의 이름은 `int(*)[3]` 타입으로 변환되어 `pa`에 대입됩니다.
- `pa[0][0]`, `pa[1][2]` 등 **2차원 배열처럼** 사용할 수 있습니다.
- `pa`의 주소 출력은 `arr`과 동일합니다 — 같은 메모리를 가리키기 때문입니다.

| 표현 | 타입 | 의미 |
|------|------|------|
| `int(*pa)[3]` | 배열 포인터 | int 3개짜리 배열을 가리키는 포인터 |
| `int* pa[3]` | 포인터 배열 | int 포인터 3개를 담는 배열 (다른 것!) |

---

### 7.2 배열 포인터로 선언과 동시에 대입

```c
#include <stdio.h>
int main()
{
    int arr[2][3] = { 10,20,30,40,50,60 };
    int(*pa)[3] = arr;

    printf("\n");
    printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
    printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
    printf("\n");
    printf("%p %p %p\n", pa, pa[0], pa[1]);
}
```

**설명**
- 이전 예제와 동일하지만, `int(*pa)[3] = arr;`로 **선언과 동시에 초기화**하는 간결한 형태입니다.

---

### 7.3 1차원 배열을 2차원 배열 포인터로 캐스팅

```c
#include <stdio.h>
int main()
{
    int arr[6] = { 10,20,30,40,50,60 };
    int(*pa)[3] = (int(*)[3]) arr;

    printf("\n");
    printf("%d %d %d\n", pa[0][0], pa[0][1], pa[0][2]);
    printf("%d %d %d\n", pa[1][0], pa[1][1], pa[1][2]);
    printf("\n");
    printf("%p %p %p\n", pa, pa[0], pa[1]);
}
```

**설명**
- `int arr[6]` : **1차원 배열** 6개짜리입니다.
- `(int(*)[3]) arr` : 1차원 배열의 주소를 "int 3개짜리 배열 포인터"로 **캐스팅**합니다.
- 캐스팅 후 `pa[0]` = {10, 20, 30}, `pa[1]` = {40, 50, 60}으로 **2차원처럼 접근**할 수 있습니다.
- 이것이 가능한 이유는 메모리에서 1차원이든 2차원이든 **연속으로 배치**되기 때문입니다.

**예상 출력**
```

10 20 30
40 50 60

(주소) (주소) (주소)
```

---

## 8. 2차원 배열을 함수에 전달하기

### 8.1 main에서 직접 값 할당과 출력

```c
#include <stdio.h>
int main()
{
    int arr[5][5] = { 0, 678};

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            arr[i][j] = i * 5 + j + 1;

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
}
```

**설명**
- `int arr[5][5] = { 0, 678 }` : 첫 번째 요소는 0, 두 번째 요소는 678, **나머지는 모두 0**으로 초기화됩니다.
- `printf("%5d", arr[i][j])` : **5칸 너비**로 정수를 출력하여 깔끔하게 정렬합니다.
- `arr[i][j] = i * 5 + j + 1` : 1부터 25까지 순서대로 값을 채웁니다.
- 이 예제는 모든 로직이 `main`에 있어 코드가 길고 반복적입니다. 다음에 함수로 분리합니다.

**예상 출력**
```
    0  678    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    1    2    3    4    5
    6    7    8    9   10
   11   12   13   14   15
   16   17   18   19   20
   21   22   23   24   25
```

---

### 8.2 PrintArray 함수로 분리

```c
#include <stdio.h>
void PrintArray(int (*arr)[5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
}
int main()
{
    int arr[5][5] = { 0, 678 };

    PrintArray(arr);
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            arr[i][j] = i * 5 + j + 1;
    PrintArray(arr);
}
```

**설명**
- `void PrintArray(int (*arr)[5])` : 2차원 배열을 받는 함수입니다. 매개변수 타입은 **배열 포인터** `int(*)[5]`입니다.
- `int (*arr)[5]`와 `int arr[][5]`는 **같은 의미**입니다. 둘 다 "int 5개짜리 배열을 가리키는 포인터"입니다.
- 출력 로직이 함수로 분리되어 `main`이 간결해졌습니다.

---

### 8.3 PrintArray와 InitArray 함수 분리

```c
#include <stdio.h>
void PrintArray(int(*arr)[5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
}
void InitArray(int(*pa)[5])
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            pa[i][j] = i * 5 + j + 1;
}
int main()
{
    int arr[5][5] = { 0, 678 };

    PrintArray(arr);
    InitArray(arr);
    PrintArray(arr);
}
```

**설명**
- `InitArray` 함수가 추가되어 **초기화 로직도 함수로 분리**되었습니다.
- `main`이 **3줄**로 매우 간결해졌습니다: 출력 → 초기화 → 출력.
- 배열 포인터 매개변수를 사용하므로, 함수 안에서 배열 요소를 수정하면 **원본 배열이 수정**됩니다 (포인터를 통해 접근하므로).

---

### 8.4 매개변수 표기: `int arr[][5]` vs `int(*arr)[5]`

```c
#include <stdio.h>
void PrintArray(int arr[][5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}
void InitArray(int pa[][5])
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            pa[i][j] = i * 5 + j + 1;
}
int main()
{
    int arr[5][5] = { 0, 678 };

    PrintArray(arr);
    InitArray(arr);
    PrintArray(arr);
}
```

**설명**
- 이 예제는 매개변수를 `int arr[][5]` 표기로 작성한 버전입니다.
- **핵심:** `int arr[][5]`와 `int(*arr)[5]`는 함수 매개변수에서 **완전히 동일**합니다.

| 표기 | 의미 | 비고 |
|------|------|------|
| `int arr[][5]` | 첫 번째 차원 생략, 두 번째 차원 5 | 읽기 쉬움 |
| `int(*arr)[5]` | int 5개짜리 배열의 포인터 | 포인터임이 명확 |

---

## 9. 2차원 배열 패턴 (대각선, X자)

### 9.1 대각선 패턴 - 조건문 사용 (i == j)

```c
#include <stdio.h>
void PrintArray(int arr[][5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int arr[5][5] = { 0 };

    PrintArray(arr);
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (i == j)
                arr[i][j] = 1;
    PrintArray(arr);
}
```

**설명**
- `int arr[5][5] = { 0 }` : 5×5 배열을 **모두 0**으로 초기화합니다.
- `if (i == j)` : 행 번호와 열 번호가 같은 위치, 즉 **주대각선(main diagonal)**에 1을 넣습니다.
- 결과는 **단위행렬**과 비슷한 형태입니다.

**예상 출력**
```
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0

    1    0    0    0    0
    0    1    0    0    0
    0    0    1    0    0
    0    0    0    1    0
    0    0    0    0    1
```

---

### 9.2 대각선 패턴 - 간결한 방식 (arr[i][i])

```c
#include <stdio.h>
void PrintArray(int arr[][5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int arr[5][5] = { 0 };

    PrintArray(arr);
    for (int i = 0; i < 5; ++i)
        arr[i][i] = 1;
    PrintArray(arr);
}
```

**설명**
- 이전 예제와 결과는 동일하지만, **이중 for문과 if문** 대신 **단일 for문**에서 `arr[i][i] = 1`로 직접 대각선에 접근합니다.
- `i == j`인 위치는 항상 `arr[i][i]`이므로, 이 방식이 더 효율적이고 간결합니다.

---

### 9.3 X 패턴 (대각선 + 반대각선) — 활성 코드

```c
#include <stdio.h>
void PrintArray(int arr[][5])
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            printf("%5d", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int arr[5][5] = { 0 };

    PrintArray(arr);
    for (int i = 0; i < 5; ++i)
    {
        arr[i][i] = 1;
        arr[i][4-i] = 1;
    }
    PrintArray(arr);
}
```

**설명**
- 이 예제는 ex17.cpp의 **현재 활성 코드**(주석 처리되지 않은 코드)입니다.
- `arr[i][i] = 1` : **주대각선** (왼쪽 위 → 오른쪽 아래).
- `arr[i][4-i] = 1` : **반대각선** (오른쪽 위 → 왼쪽 아래).
  - `i=0` → `arr[0][4]`, `i=1` → `arr[1][3]`, ... , `i=4` → `arr[4][0]`
- 두 대각선이 합쳐져서 **X자 패턴**이 완성됩니다.

**예상 출력**
```
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0
    0    0    0    0    0

    1    0    0    0    1
    0    1    0    1    0
    0    0    1    0    0
    0    1    0    1    0
    1    0    0    0    1
```

---

## 10. 정리 표

| 주제 | 내용 |
|------|------|
| typedef struct | `typedef struct _name { ... } Name;`으로 구조체 별칭 정의 |
| 구조체 포인터 | `Name* p`로 선언, `p->멤버`로 접근 |
| const 매개변수 | `const Name* p`는 읽기만 허용, 수정 불가 |
| char* buf[100] | 포인터 배열 — 고정 크기 100개의 문자열 포인터 |
| char** buf | 이중 포인터 — malloc으로 원하는 크기만큼 동적 할당 |
| malloc / free | 동적 메모리 할당 / 해제, 반드시 쌍으로 사용 |
| Init / Uninit 패턴 | 초기화 함수에서 malloc, 해제 함수에서 free |
| strcmp | 두 문자열 비교, 같으면 0 반환 |
| strcpy_s | 문자열 복사 (안전한 버전) |
| int arr[M][N] | 2차원 배열 선언, M행 N열 |
| arr[i][j] | 2차원 배열 요소 접근 |
| int(*pa)[N] | 배열 포인터 — int N개짜리 배열을 가리키는 포인터 |
| int arr[][N] | 함수 매개변수에서 `int(*arr)[N]`과 동일 |
| %5d | 5칸 너비 정수 출력 (정렬) |
| %p | 포인터(주소) 16진수 출력 |
| _getch() | 키 하나를 즉시 입력 (Enter 불필요, Windows) |
| puts() | 문자열 출력 + 자동 줄바꿈 |
| switch-case | 값에 따라 분기, break 필수 |

---

## 11. StringArray 진화 과정 요약

아래 표는 ex17.cpp에서 StringArray 프로그램이 단계별로 어떻게 발전했는지를 정리한 것입니다.

| 단계 | buf 타입 | capacity | free 처리 | 핵심 변화 |
|------|----------|----------|-----------|-----------|
| 1단계 | — | — | — | 메뉴 루프 + switch만 구현 |
| 2단계 | `char* buf[100]` | 고정 100 | 없음 | 구조체 정의, 빈 함수 틀 |
| 3단계 | `char* buf[100]` | 고정 100 | 없음 | AddString, PrintString 구현 |
| 4단계 | `char* buf[100]` | 고정 100 | 없음 | SearchString, RemoveString 구현 (free 누락) |
| 5단계 | `char* buf[100]` | 고정 100 | ✅ | RemoveString에 free 추가, FreeString 함수 |
| 6단계 | `char** buf` | 동적 | ✅ | 이중 포인터 + InitString + malloc |
| 7단계 | `char** buf` | 동적 + 필드 | ✅ | capacity 필드 추가, 오버플로우 방지 |
| 8단계 | `char** buf` | 동적 + 필드 | ✅ | FreeString → UninitString (이름 개선) |

---

## 12. 연습 문제 (스스로 풀어보기)

1. `int arr[3][4]`를 선언하고, 1부터 12까지 값을 채운 뒤 `PrintArray` 함수를 만들어 출력해 보세요. (매개변수 타입에 주의!)
2. 5×5 배열에서 **테두리**만 1로 채우는 프로그램을 작성해 보세요.
3. StringArray 프로그램에서 `RemoveString`의 `free(psa->buf[i])`를 빼면 어떤 문제가 생기는지 설명해 보세요.
4. `int arr[9] = {1,2,3,4,5,6,7,8,9};`를 `int(*pa)[3]`로 캐스팅하여 3×3 행렬처럼 출력해 보세요.
5. StringArray에 **정렬(Sort)** 기능을 추가해 보세요. (`strcmp`로 사전순 비교)
6. `char* buf[100]` 버전과 `char** buf` 버전의 차이를 설명하고, 각각의 장단점을 정리해 보세요.

---

이 강의 자료는 **example/ex17.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. **1~5장**은 구조체와 동적 메모리를 활용한 문자열 관리 프로그램의 단계별 발전 과정이고, **6~9장**은 2차원 배열과 배열 포인터에 관한 내용입니다. 가장 아래의 기초 예제(메뉴 루프)부터 차례로 실습하면서, 위로 올라가며 발전된 코드를 직접 타이핑해 보는 것을 권장합니다.
