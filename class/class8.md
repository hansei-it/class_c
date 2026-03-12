# C언어 기초 강의 8 - ex8.cpp 코드를 통한 동적 메모리 할당

이 강의는 **example/ex8.cpp**에 담긴 예제들을 바탕으로, **동적 메모리 할당(malloc/free)**과 힙(Heap) 메모리 사용법, 문자열 복사를 정리합니다.

---

## 0. 여덟 번째 수업 준비

### 0.1 이 수업에서 배우는 것 (학습 목표)

- `malloc`으로 **힙(Heap) 메모리를 동적으로 할당**하고, `free`로 해제할 수 있다.
- 스택 메모리(지역 변수)와 힙 메모리의 차이를 이해한다.
- 동적으로 할당한 메모리에 배열처럼 접근하는 방법을 익힌다.
- `strcpy_s`로 문자열을 복사하는 방법을 익힌다.

---

### 0.2 수업 진행 순서 제안

1. **1장** – 스택 vs 힙 메모리
2. **2장** – `malloc`과 `free` 기초
3. **3장** – 동적 배열 할당
4. **4장** – 문자열 복사와 `strcpy_s`
5. **5장** – 메인 예제
6. **6~7장** – 정리 표와 연습 문제

---

## 1. 스택 vs 힙 메모리

### 1.1 스택 변수 (자동 관리)

```c
#include <stdio.h>
int main()
{
  // Stack area
  int n = 10;
  int* p = &n;
  const char* s = "Hello";
  int arr[5] = { 10, 20, 30, 40, 50 };

  printf("%d %d\n", n, *p);
  printf("string : %s\n", s);

  for (int i = 0; i < 5; ++i)
    printf("%d\n", arr[i]);
}
```

**설명**
- 지역 변수들은 모두 **스택(Stack)**에 저장됩니다.
- 함수가 반환될 때 자동으로 해제됩니다.
- 스택 크기는 제한적입니다 (일반적으로 수 MB 이하).

---

### 1.2 힙 메모리란?

```
Stack (제한적, 자동 관리):  int n = 10;
                              → 함수 종료 시 자동 해제

Heap  (대용량, 수동 관리):  int* p = malloc(4);
                              → free(p)를 직접 호출해야 해제
```

- **힙(Heap)**: 실행 중에 크기를 결정하고 직접 할당/해제하는 메모리 영역.
- `malloc`으로 할당하고, `free`로 해제합니다.
- `free`를 잊으면 **메모리 누수(memory leak)**가 발생합니다.

---

## 2. `malloc`과 `free` 기초

### 2.1 정수 하나 동적 할당

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int* p = (int*)malloc(sizeof(int));
  *p = 10;
  printf("%d\n", *p);
  free(p);
}
```

**설명**
- `#include <stdlib.h>` : `malloc`과 `free`를 사용하기 위해 필요합니다.
- `malloc(sizeof(int))` : `int` 크기(4바이트)만큼 힙에서 메모리를 할당합니다.
- `(int*)` : `malloc`은 `void*`를 반환하므로, `int*`로 **캐스팅**합니다.
- `*p = 10` : 할당된 메모리에 값을 씁니다.
- `free(p)` : 사용이 끝나면 반드시 메모리를 **해제**합니다.

---

### 2.2 스택 변수와 힙 변수 비교

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n = 10;               // 스택
  int* p1 = &n;

  int* p2 = (int*)(void*)malloc(4);  // 힙
  *p2 = 10;

  printf("%d %d\n", *p1, *p2);

  free(p2);   // 스택의 n은 해제 불필요, 힙의 p2만 free
}
```

**비교 표**

| 구분 | 스택 변수 | 힙 변수 |
|------|-----------|---------|
| 선언 | `int n = 10;` | `int* p = (int*)malloc(4);` |
| 해제 | 자동 (함수 종료 시) | 수동 (`free(p)`) |
| 크기 결정 | 컴파일 시 | 실행 중 |
| 크기 제한 | 적음 (수 MB) | 많음 (수 GB) |

---

### 2.3 NULL 체크 (안전한 사용)

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  double* p = (double*)malloc(sizeof(double));
  if (p != NULL)   // 할당 성공 여부 확인
  {
    *p = 10.12345;
    printf("%g\n", *p);
    free(p);
  }
}
```

**설명**
- `malloc`이 실패하면 `NULL`을 반환합니다.
- `if (p != NULL)` 체크로 할당 성공 여부를 확인하는 것이 좋습니다.
- 실패 원인: 메모리 부족, 매우 큰 할당 요청 등.

---

## 3. 동적 배열 할당

### 3.1 정수 배열 동적 할당

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int* p1 = (int*)malloc(sizeof(int));
  int* p2 = (int*)malloc(sizeof(int) * 5);

  *p1 = 10;               // p1[0] = 10
  *(p2 + 0) = 10;
  *(p2 + 1) = 20;
  *(p2 + 2) = 30;
  *(p2 + 3) = 40;
  *(p2 + 4) = 50;

  printf("data : %d\n", p1[0]);
  for (int i = 0; i < 5; ++i)
    printf("%5d", p2[i]);
  printf("\n");

  free(p1);
  free(p2);
}
```

**설명**
- `malloc(sizeof(int) * 5)` : int 5개 크기(20바이트)만큼 할당합니다.
- 할당된 메모리를 `p2[0]`~`p2[4]`처럼 **배열처럼 사용**할 수 있습니다.
- `free(p1)`, `free(p2)` : 각각 따로 해제합니다.

---

### 3.2 대용량 배열 동적 할당

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int* arr = (int*)malloc(sizeof(int) * 1024 * 1024);

  for (int i = 0; i < 1024 * 1024; ++i)
    arr[i] = i;

  for (int i = 0; i < 10; ++i)
    printf("%5d", arr[i]);
  printf("\n");

  free(arr);
}
```

**설명**
- `1024 * 1024`개 정수 = 약 **4MB** 힙 할당.
- 스택으로는 불가능한 크기지만, 힙은 가능합니다.
- 사용 후 반드시 `free(arr)`로 해제합니다.

---

## 4. 문자열 복사와 `strcpy_s`

### 4.1 왜 `s2 = s1`이 안 되는가

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  const char* s1 = "Hello!";
  char* s2 = (char*)malloc(7);

  // s2 = s1;   // 주소 복사 → 내용 복사가 아님, 힙 메모리 누수 발생
  s2[0] = s1[0];
  s2[1] = '\0';

  printf("%s %s\n", s1, s2);

  free(s2);
}
```

**설명**
- `s2 = s1`은 `s2`가 `s1`과 같은 주소를 가리키게 할 뿐, 내용을 복사하지 않습니다.
- 또한 원래 `s2`가 가리키던 힙 메모리 주소를 잃어 **메모리 누수**가 발생합니다.

---

### 4.2 직접 문자 복사

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  const char* s1 = "Hello!";
  char* s2 = (char*)malloc(7);

  s2[0] = s1[0];
  s2[1] = s1[1];
  s2[2] = s1[2];
  s2[3] = s1[3];
  s2[4] = s1[4];
  s2[5] = s1[5];
  s2[6] = s1[6];  // '\0' 복사

  printf("%s %s\n", s1, s2);

  free(s2);
}
```

---

### 4.3 for 루프로 복사

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char* s = (char*)malloc(sizeof(char) * 7);
  char arr[] = "Hello!";

  for (int i = 0; i < 7; ++i)
    s[i] = arr[i];

  printf("%s %s\n", s, arr);
  printf("%p %p\n", s, arr);  // 서로 다른 주소

  free(s);
}
```

---

### 4.4 null 찾아서 복사

```c
  for (int i = 0; arr[i] != '\0'; ++i)
    s[i] = arr[i];
  s[6] = arr[6];  // '\0' 복사
```

---

### 4.5 대입 조건을 이용한 복사

```c
  for (int i = 0; s[i] = arr[i]; ++i)
    ;  // 빈 루프: 대입 후 값이 '\0'(0)이면 종료
```

**설명**
- `s[i] = arr[i]` : 대입 후 대입된 값을 조건으로 사용합니다.
- `'\0'`(값 0)이 대입되면 조건이 거짓이 되어 루프가 종료됩니다.
- 동시에 `'\0'`도 복사됩니다 (편리한 패턴).

---

### 4.6 `strcpy_s`로 안전하게 복사

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char* s = (char*)malloc(sizeof(char) * 7);
  char arr[] = "Hello!";

  strcpy_s(s, 7, arr);   // dst, dst_size, src

  printf("%s %s\n", s, arr);
  printf("%p %p\n", s, arr);

  free(s);
}
```

**설명**
- `#include <string.h>` : 문자열 함수들을 사용하기 위해 필요합니다.
- `strcpy_s(dst, dst_size, src)` : `src`의 내용을 `dst`에 복사합니다.
  - `dst_size` : 목적지 버퍼의 크기. 이 크기를 초과하면 오류가 발생합니다.
  - 기존 `strcpy`보다 **안전**합니다 (버퍼 오버플로우 방지).

**예상 출력**
```
Hello! Hello!
[서로 다른 주소]
```

---

### 4.7 CopyString 함수화

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CopyString(char* dst, const char* src)
{
  strcpy_s(dst, strlen(src) + 1, src);
}
int main()
{
  const char* s1 = "Hello!";
  char* s2 = (char*)malloc(7);

  CopyString(s2, s1);

  printf("%s %s\n", s1, s2);

  free(s2);
}
```

**설명**
- `strlen(src)` : 문자열의 길이를 반환합니다 (`'\0'` 제외). `"Hello!"`는 6.
- `strlen(src) + 1` : `'\0'`까지 포함한 크기.
- 이렇게 함수로 감싸면 재사용이 쉽습니다.

---

## 5. 메인 예제 분석

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char* s = (char*)malloc(sizeof(char) * 7);
  char arr[] = "Hello!";

  strcpy_s(s, 7, arr);

  printf("%s %s\n", s, arr);
  printf("%p %p\n", s, arr);

  free(s);
}
```

**단계별 분석**
1. `malloc(sizeof(char) * 7)` : 힙에 7바이트 할당.
2. `char arr[] = "Hello!"` : 스택에 `{'H','e','l','l','o','!','\0'}` 복사본 생성.
3. `strcpy_s(s, 7, arr)` : `arr` 내용을 힙의 `s`로 복사.
4. `printf` : 두 문자열 출력 (내용은 같지만 주소는 다름).
5. `free(s)` : 힙 메모리 해제.

**예상 출력**
```
Hello! Hello!
[힙 주소] [스택 주소]
```

---

## 6. 정리 표

| 주제 | 내용 |
|------|------|
| `malloc(n)` | 힙에서 n바이트 할당, `void*` 반환 |
| `free(p)` | 힙 메모리 해제 |
| `(int*)malloc(...)` | void*를 원하는 타입으로 캐스팅 |
| NULL 체크 | `if (p != NULL)` 로 할당 성공 확인 |
| 메모리 누수 | `free` 없이 포인터를 잃으면 해제 불가 |
| `sizeof(int) * n` | n개 정수 크기 계산 |
| `strcpy_s(dst, size, src)` | 안전한 문자열 복사 |
| `strlen(s)` | 문자열 길이 (`'\0'` 제외) |
| `#include <stdlib.h>` | malloc/free 선언 |
| `#include <string.h>` | strcpy_s/strlen 선언 |

---

## 7. 연습 문제 (스스로 풀어보기)

1. `malloc`으로 `double` 하나를 할당하고, `3.14`를 저장한 뒤 출력하고 `free`로 해제해 보세요.
2. `malloc`으로 int 10개짜리 배열을 할당하고, 1~10을 저장한 뒤 출력하고 해제해 보세요.
3. `char arr[] = "World";`를 `malloc`으로 할당한 공간에 직접 for 루프로 복사해 보세요.
4. `strcpy_s`를 사용해 `"Korea"` 문자열을 동적 할당 공간에 복사하고 출력해 보세요.
5. `malloc`을 사용하되 `free`를 생략했을 때 어떤 문제가 생기는지 (메모리 누수) 개념적으로 설명해 보세요.

---

이 강의 자료는 **example/ex8.cpp**에 있는 모든 예제를 바탕으로 구성했습니다. **`malloc`/`free`**는 C에서 힙 메모리를 직접 제어하는 핵심 기능입니다. 반드시 `free`를 짝지어 사용하고, NULL 체크 습관을 들이는 것이 중요합니다.
