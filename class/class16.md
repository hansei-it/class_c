# C언어 기초 강의 16 - ex16.cpp 코드를 통한 구조체·포인터·동적 메모리 관리

이 강의는 **example/ex16.cpp**에 담긴 예제들을 바탕으로, C언어의 **포인터**, **배열**, **문자열**, **구조체**, **동적 메모리 할당**을 단계별로 학습하는 내용입니다. 파일의 아래쪽이 가장 기초적인 내용이고, 위로 올라갈수록 발전된 내용입니다.

---

## 0. 학습 목표

- 포인터 변수(`*`)와 주소 연산자(`&`)를 복습하고, 포인터를 함수에 전달할 수 있다.
- 배열과 포인터의 관계를 이해하고, 포인터 산술을 사용할 수 있다.
- 정적 배열과 동적 배열(`malloc`/`free`)의 차이를 안다.
- 함수에 배열을 전달하는 여러 방식(`int*`, `int[]`, `const int[]`)을 구분할 수 있다.
- `char*`와 `char[]`의 차이를 이해하고, `strcpy_s`, `strlen`을 사용할 수 있다.
- 구조체(`struct`)를 정의·초기화하고, `.`과 `->`로 멤버에 접근할 수 있다.
- `typedef`를 사용하여 타입 이름을 간결하게 정의할 수 있다.
- 구조체 배열을 선언하고, 동적으로 할당·관리할 수 있다.
- 구조체 관리 함수를 분리하여 모듈화된 프로그램을 작성할 수 있다.

---

## 1. 포인터 기초 복습

### 1.1 포인터 변수와 함수 전달

```c
#include <stdio.h>
void PrintChar(char* pc)
{
    printf("char : %c\n", *pc);
}
void PrintInt(int* pn)
{
    printf("int : %d\n", *pn);
}
int main()
{
    char c = 'A';
    int n = 100;

    char* pc = &c;
    int* pn = &n;

    printf("char : %c\n", *pc);
    PrintChar(&c);
    printf("int : %d\n", *pn);
    PrintInt(&n);
}
```

**설명**
- `char* pc = &c;` : 변수 `c`의 **주소**를 포인터 `pc`에 저장합니다.
- `*pc` : 포인터가 가리키는 곳의 **값**을 읽습니다 (역참조).
- `PrintChar(&c)` : 변수의 주소를 함수에 전달하면, 함수 안에서 `*pc`로 원본 값에 접근할 수 있습니다.
- `int*`도 같은 원리입니다. 타입에 맞는 포인터를 사용합니다.

**예상 출력**
```
char : A
char : A
int : 100
int : 100
```

---

## 2. 배열과 포인터

### 2.1 배열 요소와 주소 출력

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[5] = { 10,20,30,40,50 };

    printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("%p %p %p %p %p\n", arr, arr+1, arr+2, arr+3, arr+4);
}
```

**설명**
- `arr[i]` : 배열의 i번째 요소에 접근합니다.
- `arr` : 배열 이름은 **첫 번째 요소의 주소**와 같습니다.
- `arr+1` : 다음 요소의 주소입니다. `int`가 4바이트이므로 주소가 4씩 증가합니다.
- `%p` : 주소를 16진수로 출력하는 형식 지정자입니다.

**예상 출력 (주소 값은 환경마다 다름)**
```
10 20 30 40 50
0061FF00 0061FF04 0061FF08 0061FF0C 0061FF10
```

---

### 2.2 배열 이름과 포인터 변수

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[5] = { 10,20,30,40,50 };
    int* pa = arr;

    printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
    printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
}
```

**설명**
- `int* pa = arr;` : 배열 이름 `arr`은 `int*` 타입으로 자동 변환됩니다.
- `pa[i]`와 `arr[i]`는 **같은 요소**를 가리킵니다.
- 배열과 포인터는 `[]` 연산자를 동일하게 사용할 수 있습니다.

**예상 출력**
```
10 20 30 40 50
10 20 30 40 50
0061FF00 0061FF04 0061FF08 0061FF0C 0061FF10
```

---

### 2.3 정적 배열 vs 동적 배열 (malloc/free)

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[5] = { 0 };
    int* pa = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; ++i)
    {
        arr[i] = (i + 1) * 10;
        pa[i] = (i + 1) * 10;
    }

    for (int i = 0; i < 5; ++i)
        printf("%d %d\n", arr[i], pa[i]);

    free(pa);
}
```

**설명**
- `int arr[5]` : **스택(stack)**에 생성되는 **정적 배열**입니다. 크기가 컴파일 시 결정됩니다.
- `malloc(sizeof(int) * 5)` : **힙(heap)**에 생성되는 **동적 배열**입니다. 실행 중에 크기를 정할 수 있습니다.
- 둘 다 `[i]`로 동일하게 접근하지만, 동적 배열은 반드시 `free(pa)`로 해제해야 합니다.

**예상 출력**
```
10 10
20 20
30 30
40 40
50 50
```

---

## 3. 함수에 배열 전달

### 3.1 int* 매개변수로 전달

```c
#include <stdio.h>
#include <stdlib.h>
void PrintArray(int* pa, int size)
{
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
}
int main()
{
    int arr[5] = { 10,20,30,40,50 };
    int* pa = arr;

    printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
    PrintArray(arr, 5);

    printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
}
```

**설명**
- `void PrintArray(int* pa, int size)` : 배열을 `int*`(포인터)로 받습니다.
- 함수에 `arr`을 전달하면, 배열의 **시작 주소**가 복사됩니다.
- 함수 안에서 `pa[i]`로 원본 배열 요소에 접근할 수 있습니다.

---

### 3.2 int pa[] 매개변수로 전달

```c
#include <stdio.h>
#include <stdlib.h>
void PrintArray(int pa[], int size)
{
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
}
int main()
{
    int arr[5] = { 10,20,30,40,50 };
    int* pa = arr;

    printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
    PrintArray(arr, 5);

    printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
}
```

**설명**
- `void PrintArray(int pa[], int size)` : `int pa[]`는 `int* pa`와 **동일한 의미**입니다.
- 함수 매개변수에서 배열 표기 `[]`와 포인터 표기 `*`는 같은 방식으로 동작합니다.
- `[]` 표기는 "배열을 받는다"는 **의도를 명확히** 전달하는 장점이 있습니다.

---

### 3.3 const int pa[] - 읽기 전용 매개변수

```c
#include <stdio.h>
#include <stdlib.h>
void PrintArray(const int pa[], int size)
{
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
}
int main()
{
    int arr[5] = { 10,20,30,40,50 };
    int* pa = arr;

    printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
    PrintArray(arr, 5);

    printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
}
```

**설명**
- `const int pa[]` : 함수 안에서 배열 요소를 **수정할 수 없게** 보호합니다.
- 출력만 하는 함수라면 `const`를 붙여서 **실수로 값을 변경하는 것을 방지**하는 것이 좋습니다.

---

## 4. 문자열 (char 배열과 포인터)

### 4.1 char*와 char[] 기본

```c
#include <stdio.h>
int main()
{
    char* s = "홍길동";
    char a[] = "홍길동";

    printf("name : %s\n", s);
    printf("name : %s\n", a);
}
```

**설명**
- `char* s = "홍길동"` : **문자열 리터럴**의 주소를 포인터에 저장합니다. 리터럴은 **읽기 전용** 메모리에 있습니다.
- `char a[] = "홍길동"` : 문자열을 **배열에 복사**합니다. 배열이므로 내용 수정이 가능합니다.

**예상 출력**
```
name : 홍길동
name : 홍길동
```

---

### 4.2 문자열과 문자 접근

```c
#include <stdio.h>
int main()
{
    char* s = "ABCD";
    char a[] = "ABCD";

    printf("%s %s %s\n", s, a, "ABCD");
    printf("%c %c %c\n", s[1], a[1], "ABCD"[1]);
}
```

**설명**
- `%s`로 문자열 전체를 출력하고, `[1]`로 두 번째 문자에 접근합니다.
- `s[1]`, `a[1]`, `"ABCD"[1]` 모두 `'B'`를 반환합니다.
- 문자열 리터럴에도 직접 `[]` 인덱스를 사용할 수 있습니다.

**예상 출력**
```
ABCD ABCD ABCD
B B B
```

---

### 4.3 char*와 char[]의 수정 차이 (중요!)

```c
#include <stdio.h>
int main()
{
    char* s = "ABCD";
    char a[] = "ABCD";

    printf("%p %s\n", s, s);
    printf("%p %s\n", a, a);
    printf("%c %d\n", s[0], s[0]);
    printf("%c %d\n", a[0], a[0]);
    s[0] = 'H'; // X - 실행 시 오류 (읽기 전용 메모리)
    a[0] = 'H'; // O - 정상 동작
}
```

**설명**
- `s[0] = 'H'` : `char*`가 가리키는 문자열 리터럴은 **읽기 전용**이므로, 수정하면 **런타임 오류**가 발생합니다.
- `a[0] = 'H'` : `char[]` 배열은 수정 가능하므로 정상 동작합니다.
- 이것이 `char*`와 `char[]`의 **가장 중요한 차이점**입니다.

| 구분 | `char* s = "ABCD"` | `char a[] = "ABCD"` |
|------|---------------------|---------------------|
| 저장 위치 | 읽기 전용 메모리(문자열 리터럴) | 스택(배열에 복사) |
| 수정 가능 | **불가** (런타임 오류) | **가능** |
| 다른 문자열 대입 | `s = "XYZ"` 가능 (포인터 변경) | `a = "XYZ"` **불가** (배열 이름은 상수) |

---

### 4.4 문자열 변경과 strcpy_s

```c
#include <stdio.h>
#include <string.h>
int main()
{
    char* s = "홍길동";
    char a[] = "홍길동";

    s = "홍길당";
    //a = "홍길당";  // X - 배열 이름에 직접 대입 불가
    strcpy_s(a, strlen("홍길당") + 1, "홍길당");
    printf("name : %s\n", s);
    printf("name : %s\n", a);
}
```

**설명**
- `s = "홍길당"` : 포인터는 다른 문자열 리터럴을 **가리키도록 변경** 가능합니다.
- `a = "홍길당"` : 배열 이름은 **상수**라서 직접 대입할 수 없습니다. 컴파일 오류가 발생합니다.
- `strcpy_s(a, ...)` : 배열의 내용을 변경하려면 **문자열 복사 함수**를 사용해야 합니다.
- `strlen("홍길당") + 1` : 복사할 길이에 널 종단 문자(`'\0'`) 공간을 포함해야 합니다.

---

### 4.5 동적 할당 문자열 - 잘못된 사용

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* s = "홍길동";
    char a[] = "홍길동";
    char* h = (char*)malloc(100);

    s = "홍길당";
    strcpy_s(a, strlen("홍길당") + 1, "홍길당");
    h = "홍길당";  // 잘못된 사용! malloc 메모리 주소를 잃어버림

    printf("name : %s\n", s);
    printf("name : %s\n", a);
    printf("name : %s\n", h);

    //free(h);  // h가 리터럴을 가리키므로 free 불가 → 메모리 누수
}
```

**설명**
- `h = "홍길당"` : `h`가 가리키던 `malloc` 메모리의 주소를 **잃어버립니다** (메모리 누수).
- `free(h)` : 이제 `h`는 문자열 리터럴을 가리키므로, `free`를 호출하면 **오류**가 발생합니다.
- 이 코드는 **하면 안 되는 예시**입니다. 올바른 방법은 다음 절을 참고하세요.

---

### 4.6 동적 할당 문자열 - 올바른 사용

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* s = "홍길동";
    char a[] = "홍길동";
    char* h = (char*)malloc(100);

    s = "홍길당";
    strcpy_s(a, strlen("홍길당") + 1, "홍길당");
    //h = "홍길당"; // X - 이렇게 하면 안 됨
    strcpy_s(h, strlen("홍길당") + 1, "홍길당");

    printf("name : %s\n", s);
    printf("name : %s\n", a);
    printf("name : %s\n", h);

    free(h);
}
```

**설명**
- `strcpy_s(h, ...)` : `malloc`으로 할당한 메모리에 문자열을 **복사**합니다.
- 이렇게 하면 `h`는 여전히 힙 메모리를 가리키므로 `free(h)`가 정상 동작합니다.
- **동적 할당 메모리에는 항상 복사 함수(`strcpy_s`)를 사용**해야 합니다.

| 방식 | char* s | char a[] | char* h (malloc) |
|------|---------|----------|------------------|
| 변경 방법 | `s = "새 문자열"` | `strcpy_s(a, ...)` | `strcpy_s(h, ...)` |
| 직접 대입 | O (포인터 변경) | X (컴파일 오류) | X (메모리 누수!) |

---

### 4.7 strlen 함수

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    printf("%d\n", strlen("ABC"));
    printf("%d\n", strlen("홍길동"));
}
```

**설명**
- `strlen("ABC")` : 문자열의 **길이**(바이트 수)를 반환합니다. `'\0'`(널 종단 문자)은 포함하지 않습니다.
- `"ABC"` → **3** (영문 1글자 = 1바이트)
- `"홍길동"` → 한글은 인코딩에 따라 다릅니다 (EUC-KR: 6바이트, UTF-8: 9바이트).

---

## 5. 구조체(struct) 기초

### 5.1 구조체 정의와 변수 선언

```c
#include <stdio.h>
struct Point
{
    int x;
    int y;
};
int main()
{
    struct Point pt = { 2, 3 };

    printf("(%d, %d)\n", pt.x, pt.y);
}
```

**설명**
- `struct Point { int x; int y; };` : 두 개의 `int` 멤버를 가진 **구조체**를 정의합니다.
- `struct Point pt = { 2, 3 };` : 구조체 변수를 선언하고 **중괄호 초기화**합니다.
- `pt.x`, `pt.y` : **점(.)** 연산자로 멤버에 접근합니다.

**예상 출력**
```
(2, 3)
```

---

### 5.2 sizeof로 구조체 크기 확인

```c
#include <stdio.h>
struct Point
{
    double x;
    double y;
};
int main()
{
    int n = 10;
    struct Point k = { 2, 3 };

    printf("int size : %d\n", sizeof(n));
    printf("Point size : %d\n", sizeof(k));
}
```

**설명**
- `sizeof(n)` : `int`는 보통 **4바이트**입니다.
- `sizeof(k)` : `double` 2개이므로 보통 **16바이트**입니다 (8 + 8).

**예상 출력**
```
int size : 4
Point size : 16
```

---

### 5.3 구조체 값 출력

```c
#include <stdio.h>
struct Point
{
    double x;
    double y;
};
int main()
{
    int n = 10;
    struct Point k = { 2, 3 };

    printf("int size : %d\n", sizeof(n));
    printf("Point size : %d\n", sizeof(k));
    printf("%d\n", n);
    printf("(%g,%g)\n", k.x, k.y);
}
```

**설명**
- 이전 예제에 `printf`로 값을 출력하는 코드가 추가되었습니다.
- `%g` : 실수를 간결하게 출력합니다 (불필요한 0 제거).
- `k.x`는 `double`이므로 `%g`, `%f`, `%lf` 등으로 출력합니다.

**예상 출력**
```
int size : 4
Point size : 16
10
(2,3)
```

---

### 5.4 멤버의 sizeof

```c
#include <stdio.h>
struct Point
{
    double x;
    double y;
};
int main()
{
    int n = 10;
    struct Point k = { 2, 3 };

    printf("int size : %d\n", sizeof(n));
    printf("Point size : %d\n", sizeof(k));
    printf("x size : %d\n", sizeof(k.x));
    printf("%d\n", n);
    printf("(%g,%g)\n", k.x, k.y);
}
```

**설명**
- `sizeof(k.x)` : 멤버 `x`는 `double`이므로 **8바이트**입니다.
- 구조체 전체 크기(16) = 멤버 `x`(8) + 멤버 `y`(8) 임을 확인할 수 있습니다.

**예상 출력**
```
int size : 4
Point size : 16
x size : 8
10
(2,3)
```

---

## 6. 구조체 포인터

### 6.1 (*p).x 문법

```c
#include <stdio.h>
struct Point
{
    int x;
    int y;
};
void PrintPoint(struct Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
void SetPoint(struct Point* p, int x, int y)
{
    (*p).x = x;
    (*p).y = y;
}
int main()
{
    struct Point pt = { 2, 3 };

    SetPoint(&pt, 4, 5);
    PrintPoint(pt);
}
```

**설명**
- `struct Point* p` : 구조체 **포인터**입니다.
- `(*p).x` : 포인터를 먼저 **역참조**한 뒤, 점 연산자로 멤버에 접근합니다.
- 괄호가 필수입니다. `*p.x`는 `*(p.x)`로 해석되어 오류가 발생합니다.
- `PrintPoint(pt)` : 구조체를 **값으로** 함수에 전달합니다 (복사됨).

**예상 출력**
```
(4, 5)
```

---

### 6.2 p->x 문법 (화살표 연산자)

```c
#include <stdio.h>
struct Point
{
    int x;
    int y;
};
void PrintPoint(struct Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
void SetPoint(struct Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
int main()
{
    struct Point pt = { 2, 3 };

    SetPoint(&pt, 4, 5);
    PrintPoint(pt);
}
```

**설명**
- `p->x` : `(*p).x`와 **완전히 동일**하지만, 더 간결합니다.
- 구조체 포인터에서는 **`->` 연산자**를 주로 사용합니다.
- `(*p).x = x;`와 `p->x = x;`는 같은 결과를 냅니다.

| 문법 | 의미 | 사용 상황 |
|------|------|-----------|
| `pt.x` | 변수로 직접 접근 | 구조체 **변수**일 때 |
| `(*p).x` | 역참조 후 접근 | 구조체 **포인터**일 때 (잘 안 씀) |
| `p->x` | 화살표 연산자 | 구조체 **포인터**일 때 (주로 사용) |

---

### 6.3 struct 키워드와 포인터 활용

```c
#include <stdio.h>
struct Point
{
    int x;
    int y;
};
void PrintPoint(struct Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
void SetPoint(struct Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
int main()
{
    struct Point pt = { 2, 3 };

    SetPoint(&pt, 4, 5);
    PrintPoint(pt);

    struct Point* p = &pt;
    printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `struct Point* p = &pt;` : 구조체 변수의 주소를 포인터에 저장합니다.
- `p->x` : 포인터를 통해 멤버에 접근합니다.
- C에서는 `struct` 키워드를 매번 써야 하지만, **`typedef`**를 사용하면 생략할 수 있습니다 (다음 장 참고).

**예상 출력**
```
(4, 5)
4 , 5
```

---

## 7. typedef

### 7.1 typedef를 별도로 선언

```c
#include <stdio.h>
struct _Point
{
    int x;
    int y;
};
typedef struct _Point Point;
void PrintPoint(Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
int main()
{
    Point pt = { 2, 3 };

    SetPoint(&pt, 4, 5);
    PrintPoint(pt);

    Point* p = &pt;
    printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `typedef struct _Point Point;` : `struct _Point`에 **별칭** `Point`를 부여합니다.
- 이후 `struct _Point` 대신 간단히 **`Point`**로 쓸 수 있습니다.
- 함수 매개변수와 변수 선언이 훨씬 간결해집니다.

---

### 7.2 typedef를 구조체 정의와 동시에 선언

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
int main()
{
    struct _Point pt = { 2, 3 };

    SetPoint(&pt, 4, 5);
    PrintPoint(pt);

    Point* p = &pt;
    printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `typedef struct _Point { ... } Point;` : 구조체 정의와 `typedef`를 **한 번에** 작성합니다.
- `struct _Point pt`와 `Point pt`는 같은 의미입니다. 둘 다 사용 가능합니다.
- 이 방식이 C에서 가장 **일반적으로 사용**되는 구조체 선언 패턴입니다.

---

### 7.3 typedef로 포인터 타입 정의 (PPoint)

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point, *PPoint;

int main()
{
    Point pt = { 2, 3 };
    PPoint p = &pt;

    printf("%d, %d\n", pt.x, pt.y);
    printf("%d, %d\n", p->x, p->y);
}
```

**설명**
- `typedef struct _Point { ... } Point, *PPoint;` : 구조체 정의와 동시에 **두 가지 별칭**을 만듭니다.
  - `Point` → `struct _Point`의 별칭
  - `PPoint` → `struct _Point*` (구조체 **포인터**)의 별칭
- `PPoint p = &pt;`는 `Point* p = &pt;`와 동일합니다.

**예상 출력**
```
2, 3
2, 3
```

---

## 8. 구조체 배열

### 8.1 구조체 배열과 직접 접근

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
int main()
{
    Point pt = { 2, 3 };
    Point ptArray[10] = { {1,1},{2,2},{3,3} };
    Point* pa = ptArray;

    for (int i = 0; i < 10; ++i)
        printf("(%d, %d)\n", ptArray[i].x, ptArray[i].y);
    for (int i = 0; i < 10; ++i)
        printf("(%d, %d)\n", pa[i].x, pa[i].y);
}
```

**설명**
- `Point ptArray[10]` : 10개의 `Point`를 담는 **구조체 배열**입니다.
- `{ {1,1},{2,2},{3,3} }` : 앞 3개만 초기화하고, 나머지는 **0으로 초기화**됩니다.
- `Point* pa = ptArray;` : 배열 이름은 포인터로 변환되므로, `pa[i]`로도 접근할 수 있습니다.
- `ptArray[i].x`와 `pa[i].x`는 같은 결과입니다.

**예상 출력**
```
(1, 1)
(2, 2)
(3, 3)
(0, 0)
(0, 0)
... (나머지 0, 0)
```

---

### 8.2 함수로 출력 - 값 전달 (PrintPoint by value)

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(Point pt)
{
    printf("(%d, %d)\n", pt.x, pt.y);
}
int main()
{
    Point pt = { 2, 3 };
    Point ptArray[10] = { {1,1},{2,2},{3,3} };
    Point* pa = ptArray;

    for (int i = 0; i < 10; ++i)
        PrintPoint(ptArray[i]);
    printf("\n");
    for (int i = 0; i < 10; ++i)
        PrintPoint(pa[i]);
}
```

**설명**
- `PrintPoint(Point pt)` : 구조체를 **값으로 전달**(복사)합니다.
- 함수 안에서 `pt`를 수정해도 **원본에 영향이 없습니다**.
- 구조체가 클 경우 복사 비용이 크므로, 포인터 전달이 더 효율적입니다.

---

### 8.3 함수로 출력 - 포인터 전달

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
int main()
{
    Point pt = { 2, 3 };
    Point ptArray[10] = { {1,1},{2,2},{3,3} };
    Point* pa = ptArray;

    for (int i = 0; i < 10; ++i)
        PrintPoint(&ptArray[i]);
    printf("\n");
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);
}
```

**설명**
- `PrintPoint(Point* p)` : 구조체의 **주소**를 전달합니다. 복사가 일어나지 않아 효율적입니다.
- `p->x` : 포인터로 받았으므로 화살표 연산자를 사용합니다.
- `&ptArray[i]` : 배열 i번째 요소의 **주소**를 전달합니다.

---

### 8.4 함수로 출력 - const 포인터 전달

```c
#include <stdio.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
int main()
{
    Point pt = { 2, 3 };
    Point ptArray[10] = { {1,1},{2,2},{3,3} };
    Point* pa = ptArray;

    for (int i = 0; i < 10; ++i)
        PrintPoint(&ptArray[i]);
    printf("\n");
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);
}
```

**설명**
- `const Point* p` : 포인터를 통해 **값을 수정할 수 없게** 보호합니다.
- 읽기만 하는 함수에는 `const`를 붙여서 안전하게 사용합니다.
- 포인터 전달의 **효율성**과 `const`의 **안전성**을 동시에 얻을 수 있습니다.

| 전달 방식 | 문법 | 복사 비용 | 원본 수정 |
|-----------|------|-----------|-----------|
| 값 전달 | `PrintPoint(Point pt)` | **큼** (전체 복사) | 불가 |
| 포인터 전달 | `PrintPoint(Point* p)` | **작음** (주소만) | **가능** |
| const 포인터 전달 | `PrintPoint(const Point* p)` | **작음** (주소만) | **불가** (안전) |

---

## 9. 동적 구조체 배열

### 9.1 malloc으로 구조체 배열 할당 - 직접 멤버 접근

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
int main()
{
    Point* pa = (Point*)malloc(sizeof(Point) * 10);

    for (int i = 0; i < 10; ++i)
    {
        pa[i].x = i + 1;
        pa[i].y = i + 1;
    }
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);

    free(pa);
}
```

**설명**
- `(Point*)malloc(sizeof(Point) * 10)` : `Point` 10개를 담을 수 있는 메모리를 **힙에 할당**합니다.
- `pa[i].x = i + 1` : 동적 배열도 `[]`과 `.`으로 멤버에 접근합니다.
- `free(pa)` : 사용이 끝나면 반드시 해제합니다.

**예상 출력**
```
(1, 1)
(2, 2)
(3, 3)
(4, 4)
(5, 5)
(6, 6)
(7, 7)
(8, 8)
(9, 9)
(10, 10)
```

---

### 9.2 SetPoint 함수로 초기화

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
int main()
{
    Point* pa = (Point*)malloc(sizeof(Point) * 10);

    for (int i = 0; i < 10; ++i)
        SetPoint(&pa[i], i + 1, i + 1);

    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);

    free(pa);
}
```

**설명**
- `SetPoint(&pa[i], i + 1, i + 1)` : 멤버 초기화를 **함수로 분리**했습니다.
- 직접 `pa[i].x = ...` 하는 것보다 **유지보수**가 쉽고, 초기화 로직을 한 곳에서 관리할 수 있습니다.
- 이렇게 기능을 함수로 분리하는 것이 **모듈화**의 시작입니다.

---

## 10. 구조체 배열 관리 함수 (모듈화)

### 10.1 반환 방식 - Point* 매개변수

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
Point* AllocPointArray(int cap)
{
    return (Point*)malloc(sizeof(Point) * cap);
}
void FreePointArray(Point* pa)
{
    free(pa);
}
void InitPointArray(Point* pa, int size)
{
    for (int i = 0; i < size; ++i)
        SetPoint(&pa[i], i + 1, i + 1);
}
void PrintPointArray(const Point* pa, int size)
{
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);
}
int main()
{
    Point* pa = AllocPointArray(10);

    InitPointArray(pa, 10);
    PrintPointArray(pa, 10);

    FreePointArray(pa);
}
```

**설명**
- `AllocPointArray` : `malloc`을 감싸서 **Point 배열 할당**을 담당합니다. 할당된 주소를 `return`으로 반환합니다.
- `FreePointArray` : `free`를 감싸서 해제를 담당합니다.
- `InitPointArray` : 배열 초기화를 담당합니다.
- `PrintPointArray` : 배열 출력을 담당합니다.
- 각 기능을 함수로 분리하면 `main()`이 간결해지고, **코드 재사용**이 쉬워집니다.
- 매개변수가 `Point* pa` (포인터 표기)입니다.

---

### 10.2 반환 방식 - 배열 매개변수 표기 (Point pa[])

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}
Point* AllocPointArray(int cap)
{
    return (Point*)malloc(sizeof(Point) * cap);
}
void FreePointArray(Point pa[])
{
    free(pa);
}
void InitPointArray(Point pa[], int size)
{
    for (int i = 0; i < size; ++i)
        SetPoint(&pa[i], i + 1, i + 1);
}
void PrintPointArray(const Point pa[], int size)
{
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);
}
int main()
{
    Point* pa = AllocPointArray(10);

    InitPointArray(pa, 10);
    PrintPointArray(pa, 10);

    FreePointArray(pa);
}
```

**설명**
- 이전 예제와 **동일한 동작**이지만, 매개변수를 `Point* pa` 대신 `Point pa[]`로 표기했습니다.
- `Point pa[]`와 `Point* pa`는 함수 매개변수에서 **완전히 동일**합니다.
- `pa[]` 표기는 "이 매개변수가 **배열**을 받는다"는 의도를 명확히 전달합니다.

---

### 10.3 이중 포인터 방식 (Point**) - 최종 완성 코드

```c
#include <stdio.h>
#include <stdlib.h>

// Point.c - 구조체 정의와 기본 함수
typedef struct _Point
{
    int x;
    int y;
} Point;
void PrintPoint(const Point* p)
{
    printf("(%d, %d)\n", p->x, p->y);
}
void SetPoint(Point* p, int x, int y)
{
    p->x = x;
    p->y = y;
}

// PointArray.c - 배열 관리 함수
void AllocPointArray(Point** pp, int cap)
{
    *pp = (Point*)malloc(sizeof(Point) * cap);
}
void FreePointArray(Point pa[])
{
    free(pa);
}
void InitPointArray(Point pa[], int size)
{
    for (int i = 0; i < size; ++i)
        SetPoint(&pa[i], i + 1, i + 1);
}
void PrintPointArray(const Point pa[], int size)
{
    for (int i = 0; i < 10; ++i)
        PrintPoint(&pa[i]);
}

// Main 영역
int main()
{
    Point* pa = NULL;
    AllocPointArray(&pa, 10);

    InitPointArray(pa, 10);
    PrintPointArray(pa, 10);

    FreePointArray(pa);
}
```

**설명**
- `void AllocPointArray(Point** pp, int cap)` : **이중 포인터**(포인터의 포인터)를 받습니다.
- `*pp = (Point*)malloc(...)` : 호출자의 포인터 변수를 **직접 수정**합니다.
- `AllocPointArray(&pa, 10)` : `pa`의 **주소**를 전달하여, 함수 안에서 `pa`에 새 주소를 넣을 수 있습니다.
- 코드가 `Point.c`, `PointArray.c`, `Main` 영역으로 **논리적으로 분리**되어 있어, 파일 분리가 쉽습니다.

**return 방식 vs Point** 방식 비교**

| 방식 | 함수 시그니처 | 호출 방법 |
|------|-------------|-----------|
| return | `Point* AllocPointArray(int cap)` | `pa = AllocPointArray(10);` |
| 이중 포인터 | `void AllocPointArray(Point** pp, int cap)` | `AllocPointArray(&pa, 10);` |

- `return` 방식: 직관적이지만, 반환값을 다른 용도(예: 성공/실패 여부)로 사용할 수 없습니다.
- `Point**` 방식: 반환값을 **오류 코드** 등 다른 용도로 활용할 수 있어 실무에서 자주 사용됩니다.

**예상 출력**
```
(1, 1)
(2, 2)
(3, 3)
(4, 4)
(5, 5)
(6, 6)
(7, 7)
(8, 8)
(9, 9)
(10, 10)
```

---

## 11. 정리 표

| 주제 | 내용 |
|------|------|
| 포인터 기초 | `&` 주소 연산자, `*` 역참조, `int* p = &n;` |
| 배열과 포인터 | 배열 이름 = 첫 요소 주소, `pa[i]` == `arr[i]` |
| 포인터 산술 | `arr+1`은 다음 요소 주소 (`sizeof(타입)` 만큼 이동) |
| 동적 할당 | `malloc(크기)` → 힙 할당, `free(p)` → 해제 |
| 함수에 배열 전달 | `int* pa`, `int pa[]`, `const int pa[]` 모두 동일 |
| `char*` vs `char[]` | `char*` → 리터럴 주소 (읽기 전용), `char[]` → 배열 복사 (수정 가능) |
| `strcpy_s` | 배열이나 malloc 메모리에 문자열 복사 |
| `strlen` | 문자열 길이 (`'\0'` 제외) |
| 구조체 정의 | `struct Point { int x; int y; };` |
| 멤버 접근 | `.` (변수), `->` (포인터), `(*p).x` == `p->x` |
| `typedef` | `typedef struct _Point Point;` → `struct` 생략 가능 |
| `PPoint` | `typedef struct _Point* PPoint;` → 포인터 타입 별칭 |
| 구조체 전달 | 값 전달 (복사), 포인터 전달 (효율적), const 포인터 (안전) |
| 구조체 배열 | `Point arr[10] = { {1,1}, {2,2} };` |
| 동적 구조체 배열 | `(Point*)malloc(sizeof(Point)*N)` |
| 함수 모듈화 | Alloc, Free, Init, Print 함수로 분리 |
| 이중 포인터 | `Point** pp` → 함수에서 포인터 변수 자체를 수정 |

---

## 12. 연습 문제 (스스로 풀어보기)

1. `struct Student { char name[20]; int score; };`를 정의하고, 학생 3명의 정보를 배열에 저장한 뒤 출력해 보세요.

2. `SetPoint` 함수에서 `(*p).x = x;`와 `p->x = x;`가 같은 동작임을 확인해 보세요. 각각을 사용한 두 버전의 코드를 작성하고 결과를 비교해 보세요.

3. `char* s = "Hello";`와 `char a[] = "Hello";`를 각각 만들고, `s[0] = 'h';`와 `a[0] = 'h';`의 차이를 확인해 보세요. 왜 하나는 오류가 나고 하나는 정상 동작하는지 설명해 보세요.

4. `AllocPointArray`를 **return 방식**과 **Point** 이중 포인터 방식** 두 가지로 각각 구현해 보세요.

5. `Point` 배열을 `malloc`으로 5개 할당한 뒤, 각각 `(10,20)`, `(30,40)`, `(50,60)`, `(70,80)`, `(90,100)`으로 초기화하고 출력한 후, `free`로 해제하는 프로그램을 작성해 보세요.

6. 4.5절의 "잘못된 사용" 예제에서 `h = "홍길당";`이 왜 문제인지, `free`를 빠뜨리면 어떤 문제가 생기는지 설명해 보세요.

---

이 강의 자료는 **example/ex16.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 파일의 아래쪽이 가장 기초적인 내용이고, 위로 올라갈수록 발전된 내용입니다. **1장(포인터 기초)** → **4장(문자열)** → **5장(구조체 기초)** → **10장(모듈화)** 순서로 진행하면 자연스럽게 학습할 수 있습니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
