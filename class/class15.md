# C언어 기초 강의 15 - ex15.cpp 코드를 통한 구조체(struct) 활용

이 강의는 **example/ex15.cpp**에 담긴 예제들을 바탕으로, 구조체의 정의부터 동적 할당·관리 함수 패턴까지 단계적으로 설명한 내용입니다. 아래로 갈수록 기초적인 내용이며, 위로 갈수록 발전된 내용입니다.

> **참고**: 실제 구조체 코드는 `ex16.cpp`에 수록되어 있습니다. 본 강의에서는 해당 파일의 모든 예제(활성 코드 + 주석 처리 블록)를 포함합니다.

---

## 0. 학습 목표

- 구조체(`struct`)를 정의하고 변수를 선언·초기화할 수 있다.
- `sizeof`로 구조체와 멤버의 크기를 확인할 수 있다.
- 멤버 접근 연산자 `.`과 포인터 멤버 접근 연산자 `->`의 차이를 이해한다.
- `typedef`로 구조체에 별칭을 부여하고, 포인터 별칭(`PPoint`)을 만들 수 있다.
- 구조체를 함수에 **값**으로 전달하는 것과 **포인터**로 전달하는 것의 차이를 이해한다.
- 구조체 배열을 선언·초기화하고, 포인터로 다룰 수 있다.
- `malloc`/`free`로 구조체 배열을 동적 할당·해제할 수 있다.
- `SetPoint`/`PrintPoint` 패턴, `AllocPointArray`/`FreePointArray`/`InitPointArray` 패턴을 이해하고 작성할 수 있다.

---

## 1. 구조체 정의와 sizeof

### 1.1 구조체 선언과 sizeof (기초)

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
	struct Point k = { 2,3 };

	printf("int size : %d\n", sizeof(n));
	printf("Point size : %d\n", sizeof(k));
}
```

**설명**
- `struct Point { double x; double y; };` : 멤버 `x`, `y`를 가진 **구조체 `Point`**를 정의합니다.
- 구조체는 **여러 변수를 하나로 묶어** 관리하는 사용자 정의 자료형입니다.
- `struct Point k = { 2, 3 };` : 구조체 변수 `k`를 선언하고, `x`에 2, `y`에 3을 넣어 **초기화**합니다.
- `sizeof(k)` : 구조체 `k`가 메모리에서 차지하는 **바이트 수**를 반환합니다.
- `double`은 8바이트이므로, `Point`는 멤버 2개 × 8바이트 = **16바이트**입니다.

**예상 출력**
```
int size : 4
Point size : 16
```

---

### 1.2 구조체 멤버 값 출력

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
	struct Point k = { 2,3 };

	printf("int size : %d\n", sizeof(n));
	printf("Point size : %d\n", sizeof(k));
	printf("%d\n", n);
	printf("(%g,%g)\n", k.x, k.y);
}
```

**설명**
- `k.x`, `k.y` : **점(`.`) 연산자**로 구조체 멤버에 접근합니다.
- `%g`는 실수를 불필요한 0 없이 짧게 출력하는 형식 지정자입니다.

**예상 출력**
```
int size : 4
Point size : 16
10
(2,3)
```

---

### 1.3 구조체 멤버의 sizeof

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
	struct Point k = { 2,3 };

	printf("int size : %d\n", sizeof(n));
	printf("Point size : %d\n", sizeof(k));
	printf("x size : %d\n", sizeof(k.x));
	printf("%d\n", n);
	printf("(%g,%g)\n", k.x, k.y);
}
```

**설명**
- `sizeof(k.x)` : 구조체의 **개별 멤버** 크기도 확인할 수 있습니다.
- `k.x`는 `double`이므로 **8바이트**입니다.

**예상 출력**
```
int size : 4
Point size : 16
x size : 8
10
(2,3)
```

---

## 2. 구조체 변수와 멤버 접근 (`.` 연산자)

### 2.1 int 멤버를 가진 구조체

```c
#include <stdio.h>
struct Point
{
	int x;
	int y;
};
int main()
{
	struct Point pt = { 2,3 };

	printf("(%d, %d)\n", pt.x, pt.y);
}
```

**설명**
- 이번에는 멤버를 `int`로 선언했습니다. `sizeof(Point)`는 **8바이트**(4 + 4)가 됩니다.
- `struct Point pt = { 2, 3 };` : 중괄호 `{ }`로 멤버를 **순서대로** 초기화합니다.
- `pt.x`는 2, `pt.y`는 3입니다.

**예상 출력**
```
(2, 3)
```

---

## 3. 구조체 포인터와 함수 전달

### 3.1 `(*p).x` 문법으로 포인터 멤버 접근

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
	struct Point pt = { 2,3 };

	SetPoint(&pt, 4, 5);
	PrintPoint(pt);
}
```

**설명**
- `SetPoint(struct Point* p, ...)` : 구조체 **포인터**를 매개변수로 받습니다.
- `(*p).x = x;` : 포인터 `p`를 **역참조**(`*p`)한 뒤 `.`으로 멤버에 접근합니다. 괄호가 필수입니다(`*p.x`는 `*(p.x)`로 해석되어 오류).
- `PrintPoint(struct Point pt)` : 구조체를 **값으로** 전달합니다. 원본의 **복사본**이 만들어집니다.
- `SetPoint`은 포인터로 받았으므로 **원본을 수정**하고, `PrintPoint`은 값으로 받았으므로 **읽기만** 합니다.

**예상 출력**
```
(4, 5)
```

---

### 3.2 `->` 연산자로 포인터 멤버 접근

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
	struct Point pt = { 2,3 };

	SetPoint(&pt, 4, 5);
	PrintPoint(pt);
}
```

**설명**
- `p->x`는 `(*p).x`와 **동일한 의미**입니다. 화살표 연산자(`->`)가 더 간결하므로 실무에서 주로 사용합니다.
- `p->x = x;` : 포인터 `p`가 가리키는 구조체의 멤버 `x`에 값을 대입합니다.

**예상 출력**
```
(4, 5)
```

---

### 3.3 main에서 구조체 포인터 사용

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
	struct Point pt = { 2,3 };

	SetPoint(&pt, 4, 5);
	PrintPoint(pt);

	struct Point* p = &pt;
	printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `struct Point* p = &pt;` : `main`에서도 구조체 포인터를 선언할 수 있습니다.
- `&pt`로 구조체 변수의 **주소**를 얻어 포인터 `p`에 저장합니다.
- `p->x`, `p->y`로 포인터를 통해 멤버에 접근합니다.

**예상 출력**
```
(4, 5)
4 , 5
```

---

## 4. typedef

### 4.1 typedef 분리 선언

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
	Point pt = { 2,3 };

	SetPoint(&pt, 4, 5);
	PrintPoint(pt);

	Point* p = &pt;
	printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `typedef struct _Point Point;` : `struct _Point`라는 긴 이름에 **`Point`라는 별칭**을 부여합니다.
- 이후 `struct _Point` 대신 **`Point`**만 써도 됩니다.
- `Point pt = { 2,3 };`처럼 `struct` 키워드 없이 깔끔하게 사용할 수 있습니다.

**예상 출력**
```
(4, 5)
4 , 5
```

---

### 4.2 typedef 결합 선언

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
	struct _Point pt = { 2,3 };

	SetPoint(&pt, 4, 5);
	PrintPoint(pt);

	Point* p = &pt;
	printf("%d , %d\n", p->x, p->y);
}
```

**설명**
- `typedef struct _Point { ... } Point;` : 구조체 정의와 typedef를 **한 번에** 작성합니다. 가장 널리 쓰이는 패턴입니다.
- `struct _Point pt`와 `Point pt`는 **동일한 타입**입니다. 둘 다 사용 가능하지만, 보통 `Point`를 씁니다.

**예상 출력**
```
(4, 5)
4 , 5
```

---

### 4.3 typedef로 포인터 별칭 만들기 (PPoint)

```c
#include <stdio.h>
typedef struct _Point
{
	int x;
	int y;
} Point, *PPoint;

int main()
{
	Point pt = { 2,3 };
	PPoint p = &pt;

	printf("%d, %d\n", pt.x, pt.y);
	printf("%d, %d\n", p->x, p->y);
}
```

**설명**
- `} Point, *PPoint;` : `Point`는 `struct _Point`의 별칭, `PPoint`는 `struct _Point*`(구조체 포인터)의 별칭입니다.
- `PPoint p = &pt;`는 `Point* p = &pt;`와 **동일**합니다.
- 포인터 별칭은 코드를 짧게 만들지만, 가독성을 위해 `Point*`를 직접 쓰는 경우도 많습니다.

**예상 출력**
```
2, 3
2, 3
```

---

## 5. 구조체 배열

### 5.1 구조체 배열 선언과 직접 출력

```c
#include <stdio.h>
typedef struct _Point
{
	int x;
	int y;
} Point;
int main()
{
	Point pt = { 2,3 };
	Point ptArray[10] = { {1,1},{2,2},{3,3} };
	Point* pa = ptArray;

	for (int i = 0; i < 10; ++i)
		printf("(%d, %d)\n", ptArray[i].x, ptArray[i].y);
	for (int i = 0; i < 10; ++i)
		printf("(%d, %d)\n", pa[i].x, pa[i].y);
}
```

**설명**
- `Point ptArray[10]` : 구조체 10개짜리 **배열**을 선언합니다.
- `{ {1,1},{2,2},{3,3} }` : 앞 3개만 초기화하고, 나머지 7개는 **0으로 자동 초기화**됩니다.
- `Point* pa = ptArray;` : 배열 이름은 **첫 번째 원소의 주소**입니다. 포인터에 대입할 수 있습니다.
- `ptArray[i].x`와 `pa[i].x`는 **동일한 결과**입니다.

**예상 출력**
```
(1, 1)
(2, 2)
(3, 3)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(1, 1)
(2, 2)
(3, 3)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
(0, 0)
```

---

### 5.2 PrintPoint 함수 — 값으로 전달

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
	Point pt = { 2,3 };
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
- `void PrintPoint(Point pt)` : 구조체를 **값으로**(복사본) 받아 출력합니다.
- `PrintPoint(ptArray[i])` : 배열의 각 원소를 함수에 전달합니다.
- 값 전달이므로 함수 안에서 `pt`를 변경해도 **원본에 영향 없음**입니다.

---

### 5.3 PrintPoint 함수 — 포인터로 전달

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
	Point pt = { 2,3 };
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
- `void PrintPoint(Point* p)` : 구조체를 **포인터로** 받습니다.
- `PrintPoint(&ptArray[i])` : 배열 원소의 **주소**를 전달합니다.
- 포인터 전달은 구조체 복사가 일어나지 않으므로 **효율적**입니다. 단, 원본을 수정할 수 있다는 점에 주의합니다.

---

### 5.4 PrintPoint 함수 — const 포인터로 전달

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
	Point pt = { 2,3 };
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
- `const Point* p` : 포인터를 통해 **읽기만 가능**하고, 멤버를 수정할 수 없게 합니다.
- 출력 전용 함수에서 `const`를 붙이면 **실수로 값을 바꾸는 것을 방지**할 수 있습니다.
- 포인터의 효율성 + 안전성을 모두 얻는 **권장 패턴**입니다.

---

## 6. 동적 구조체 할당 (malloc/free)

### 6.1 malloc으로 구조체 배열 할당 — 멤버 직접 접근

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
- `(Point*)malloc(sizeof(Point) * 10)` : `Point` 10개 분량의 메모리를 **힙(heap)**에 동적 할당합니다.
- `sizeof(Point) * 10` = 8 × 10 = **80바이트**.
- `pa[i].x = i + 1;` : 동적 배열도 일반 배열처럼 **인덱스와 `.`**으로 멤버에 접근할 수 있습니다.
- `free(pa);` : 사용이 끝나면 반드시 **해제**해야 메모리 누수가 발생하지 않습니다.

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

### 6.2 malloc + SetPoint 패턴

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
- `SetPoint(&pa[i], i + 1, i + 1)` : 멤버를 직접 대입하는 대신 **`SetPoint` 함수**로 값을 설정합니다.
- 이렇게 하면 값을 설정하는 로직이 **한 곳에 모여** 유지보수가 쉽습니다.
- `SetPoint` + `PrintPoint` 조합은 구조체를 다룰 때 기본이 되는 패턴입니다.

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

## 7. 구조체 관리 함수 패턴

### 7.1 AllocPointArray — 반환값 방식 (Point* 매개변수)

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
- 메모리 **할당**, **해제**, **초기화**, **출력**을 각각 **독립 함수**로 분리한 패턴입니다.
- `AllocPointArray(int cap)` : `Point` 배열을 동적 할당한 뒤 **포인터를 반환**합니다.
- `FreePointArray(Point* pa)` : 동적 배열을 **해제**합니다.
- `InitPointArray(Point* pa, int size)` : 배열의 각 원소를 `SetPoint`로 초기화합니다.
- `PrintPointArray(const Point* pa, int size)` : 배열의 모든 원소를 `PrintPoint`로 출력합니다.
- `main`이 **매우 간결**해지고, 각 함수의 역할이 명확합니다.

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

### 7.2 AllocPointArray — 반환값 방식 (Point pa[] 매개변수)

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
- 이전 예제와 거의 동일하지만, 함수 매개변수 표기를 `Point* pa` 대신 **`Point pa[]`**로 변경했습니다.
- C에서 함수 매개변수로 선언된 `Point pa[]`는 **`Point* pa`와 동일**합니다. 배열이 복사되는 것이 아니라 포인터로 전달됩니다.
- `Point pa[]` 표기는 "이 매개변수가 배열을 가리킨다"는 **의도를 명확히** 전달하는 장점이 있습니다.

---

### 7.3 AllocPointArray — 이중 포인터 방식 (주석 처리 버전)

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
- `AllocPointArray(Point** pp, int cap)` : **이중 포인터**를 매개변수로 받아, 함수 안에서 `*pp`에 할당된 주소를 대입합니다.
- `*pp = (Point*)malloc(...)` : 호출한 쪽의 포인터 변수(`pa`)에 **직접 주소를 저장**합니다.
- `AllocPointArray(&pa, 10)` : `pa`의 **주소**를 넘깁니다. 함수가 끝나면 `pa`에 malloc 결과가 들어 있습니다.
- 반환값 방식과 비교했을 때, 이중 포인터 방식은 **반환값을 다른 용도(에러 코드 등)로 활용**할 수 있는 장점이 있습니다.

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

### 7.4 AllocPointArray — 이중 포인터 방식 (활성 코드)

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
- 이 코드는 파일에서 **주석 처리되지 않은 최종 활성 코드**입니다.
- 구조를 정리하면 다음과 같습니다:

| 영역 | 함수 | 역할 |
|------|------|------|
| **Point.c** | `SetPoint` | 구조체 멤버 값 설정 |
| | `PrintPoint` | 구조체 멤버 값 출력 |
| **PointArray.c** | `AllocPointArray` | 구조체 배열 동적 할당 |
| | `FreePointArray` | 구조체 배열 메모리 해제 |
| | `InitPointArray` | 구조체 배열 초기화 |
| | `PrintPointArray` | 구조체 배열 전체 출력 |
| **Main** | `main` | 위 함수들을 조합하여 프로그램 실행 |

- 실제 프로젝트에서는 이 함수들을 **별도 파일**(`Point.c`, `PointArray.c`)로 분리하여 관리합니다.

---

## 8. 정리 표

| 주제 | 내용 |
|------|------|
| 구조체 정의 | `struct Point { int x; int y; };` |
| 구조체 변수 | `struct Point pt = { 2, 3 };` |
| 멤버 접근 (`.`) | `pt.x`, `pt.y` |
| 포인터 멤버 접근 (`->`) | `p->x` (= `(*p).x`) |
| sizeof | `sizeof(struct Point)`, `sizeof(pt)`, `sizeof(pt.x)` |
| typedef (분리) | `typedef struct _Point Point;` |
| typedef (결합) | `typedef struct _Point { ... } Point;` |
| 포인터 별칭 | `typedef struct _Point { ... } Point, *PPoint;` |
| 값으로 전달 | `void PrintPoint(Point pt)` — 복사본 생성 |
| 포인터로 전달 | `void SetPoint(Point* p, ...)` — 원본 수정 가능 |
| const 포인터 전달 | `void PrintPoint(const Point* p)` — 읽기 전용 |
| 구조체 배열 | `Point ptArray[10] = { {1,1},{2,2} };` |
| 동적 할당 | `Point* pa = (Point*)malloc(sizeof(Point) * n);` |
| 동적 해제 | `free(pa);` |
| 이중 포인터 할당 | `void AllocPointArray(Point** pp, int cap)` |
| 관리 함수 패턴 | `AllocPointArray` → `InitPointArray` → `PrintPointArray` → `FreePointArray` |

---

## 9. 연습 문제 (스스로 풀어보기)

1. `struct Student { char name[20]; int score; };`를 정의하고, 학생 한 명의 이름과 점수를 저장한 뒤 `printf`로 출력해 보세요.

2. `SetStudent(Student* s, const char* name, int score)` 함수를 만들어, 포인터로 전달받은 구조체의 멤버를 설정하는 코드를 작성해 보세요.

3. `Student` 구조체 배열 5개를 선언하고, 각 학생의 이름과 점수를 초기화한 뒤 `for`문으로 전부 출력해 보세요.

4. `malloc`으로 `Student` 3개 분량의 메모리를 동적 할당하고, 값을 넣은 뒤 출력하고, `free`로 해제하는 전체 코드를 작성해 보세요.

5. `AllocStudentArray`, `FreeStudentArray`, `InitStudentArray`, `PrintStudentArray` 함수를 각각 만들어, `main`에서 이 함수들만 호출하여 프로그램을 완성해 보세요.

6. `sizeof(struct Student)`의 값을 예측해 보고, 실제로 출력해 확인해 보세요. `name`이 20바이트, `score`가 4바이트라면 합계는? (패딩이 있을 수도 있습니다.)

---

이 강의 자료는 **example/ex16.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 가장 기초인 **구조체 정의와 sizeof**(1장)부터 시작하여, **멤버 접근**(2장) → **포인터와 함수 전달**(3장) → **typedef**(4장) → **구조체 배열**(5장) → **동적 할당**(6장) → **관리 함수 패턴**(7장) 순서로 진행하면 됩니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
