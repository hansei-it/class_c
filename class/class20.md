# C언어 기초 강의 20 - ex20.cpp 코드를 통한 구조체·함수 조합, 동적 메모리 관리, 파일 입출력

이 강의는 **example/ex20.cpp**에 담긴 예제들을 바탕으로, 구조체와 함수를 조합하여 **범용 데이터 컨테이너**를 만들고, **바이너리 파일 입출력**까지 발전시키는 과정을 정리한 내용입니다. 아래에서 위로 올라갈수록 발전된 코드이며, 주석 처리된 모든 예제를 포함합니다.

---

## 0. 학습 목표

- `typedef enum`과 `enum class`를 이용해 **열거형**을 정의하고 활용할 수 있다.
- `struct`(구조체)와 **void 포인터**(`void*`)를 결합하여 **다중 타입 데이터**를 저장하는 구조를 설계할 수 있다.
- 구조체를 다루는 **함수**(Init, Uninit, Add, Print, Get, Create)를 작성하여 **모듈화**된 코드를 만들 수 있다.
- `malloc` / `free`를 이용한 **동적 메모리 할당**과 **메모리 누수** 문제를 이해한다.
- **얕은 복사**(shallow copy)의 위험성과 해결 방법을 안다.
- `getchar`, `scanf_s`, `gets_s`를 이용한 **입력 처리**와 입력 버퍼 문제를 이해한다.
- `_getch`와 `switch`를 이용한 **메뉴 기반 프로그램**을 작성할 수 있다.
- `fopen_s`, `fwrite`, `fread`, `fclose`를 이용한 **바이너리 파일 입출력**을 구현할 수 있다.
- **커스텀 파일 포맷**(헤더 + 바디)을 설계하고 읽고 쓸 수 있다.

---

## 1. enum (열거형) 기초

### 1.1 typedef enum과 값 확인

```c
#include<stdio.h>
typedef enum { INT, DOUBLE, STRING, NONE} DataType;

struct Data
{
    void* pdata;
    DataType type;
};

int main()
{
    DataType type = INT;

    printf("%d\n", type);
    printf("%d\n", DOUBLE);
    printf("%d\n", STRING);
    printf("%d\n", NONE);
}
```

**설명**
- `typedef enum { INT, DOUBLE, STRING, NONE } DataType;` : 열거형(enum)을 정의하면서 `DataType`이라는 별칭을 붙입니다.
- 열거형의 각 값은 **0부터 자동으로 번호**가 매겨집니다: `INT=0`, `DOUBLE=1`, `STRING=2`, `NONE=3`.
- 이 열거형은 뒤에 나올 `Data` 구조체에서 **저장된 데이터의 타입을 구분**하는 용도로 사용됩니다.
- `struct Data`에는 `void* pdata`(어떤 타입이든 가리킬 수 있는 범용 포인터)와 `DataType type`(데이터 종류 표시)이 들어 있습니다.

**예상 출력**
```
0
1
2
3
```

---

## 2. Data 구조체와 void 포인터

### 2.1 다중 타입 데이터 저장과 PrintData 함수

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};

void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
int main()
{
    Data data;

    int* pn = (int*)malloc(sizeof(int));
    *pn = 100;
    data.pdata = pn;
    data.type = INT;

    Data data2;
    double* pd = (double*)malloc(sizeof(double));
    *pd = 2.56;
    data2.pdata = pd;
    data2.type = DOUBLE;

    Data data3;
    char* s = (char*)malloc(sizeof(char) * 100);
    strcpy_s(s, strlen("Hello!") + 1, "Hello!");
    data3.pdata = s;
    data3.type = STRING;

    PrintData(&data);
    PrintData(&data2);
    PrintData(&data3);
}
```

**설명**
- `void*`는 **어떤 타입의 포인터든 담을 수 있는** 범용 포인터입니다. 사용할 때는 반드시 **(타입\*)으로 형변환**해야 합니다.
- `malloc(sizeof(int))` : 정수 하나를 담을 메모리를 **동적으로 할당**합니다. 반환값은 `void*`이므로 `(int*)`로 캐스팅합니다.
- `PrintData` 함수는 `Data` 구조체의 `type` 값을 보고 `switch`문으로 **적절한 형변환 후 출력**합니다.
  - `*(int*)pd->pdata` : void 포인터 → int 포인터 → 역참조하여 값 읽기
  - `*(double*)pd->pdata` : void 포인터 → double 포인터 → 역참조
  - `(char*)pd->pdata` : void 포인터 → char 포인터 (문자열은 역참조 불필요, `%s`가 주소부터 읽음)
- `main`에서 정수(100), 실수(2.56), 문자열("Hello!")을 각각 별도의 `Data` 구조체에 저장하고 출력합니다.

**예상 출력**
```
int : 100
double : 2.56
string : Hello!
```

---

## 3. DataArray 구조체와 기본 함수

### 3.1 DataArray 기본 구조 - 같은 포인터 공유

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = { 0 };
    data.pdata = (int*)malloc(sizeof(int));
    *(int*)data.pdata = 100;
    data.type = INT;
    AddDataArray(&da, &data);
    AddDataArray(&da, &data);
    AddDataArray(&da, &data);

    PrintDataArray(&da);

    Data data2 = GetDataArray(&da, 0);
    PrintData(&data2);
    UninitDataArray(&da);
}
```

**설명**
- `DataArray`는 `Data` 배열을 **동적으로 관리**하는 컨테이너 구조체입니다.
  - `buf` : Data 배열의 시작 주소
  - `capacity` : 최대 저장 가능 개수
  - `size` : 현재 저장된 개수
- `InitDataArray` : 배열을 `malloc`으로 할당하고 size를 0으로 초기화합니다.
- `AddDataArray` : `pda->buf[pda->size++] = *pd;`로 **구조체 값을 복사**하여 저장합니다.
- **주의점**: 같은 `data` 변수를 3번 `AddDataArray`에 넣으면, 3개의 항목이 모두 **같은 pdata 주소**를 가리킵니다. 이것이 **얕은 복사(shallow copy)** 문제입니다.
- `GetDataArray`는 값을 **복사(return by value)**하여 돌려줍니다.
- `UninitDataArray`에서 `free(pda->buf)`만 하고 있어, 개별 `pdata` 메모리가 **해제되지 않습니다**(메모리 누수).

**예상 출력**
```
int : 100
int : 100
int : 100
int : 100
```

---

### 3.2 GetDataArray를 통한 데이터 수정 (얕은 복사 문제)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = { 0 };
    data.pdata = (int*)malloc(sizeof(int));
    *(int*)data.pdata = 100;
    data.type = INT;
    AddDataArray(&da, &data);
    AddDataArray(&da, &data);
    AddDataArray(&da, &data);
    *(int*)GetDataArray(&da, 0).pdata = 200;
    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- 이전 예제와 거의 동일하지만, `*(int*)GetDataArray(&da, 0).pdata = 200;`이 추가되었습니다.
- `GetDataArray`로 0번 항목을 가져와서 `pdata`가 가리키는 값을 **200으로 변경**합니다.
- 세 항목이 모두 **같은 메모리 주소(`pdata`)**를 공유하고 있으므로, **하나를 바꾸면 셋 다 바뀝니다**.
- 이것이 **얕은 복사의 위험성**입니다: 구조체 자체는 복사되지만, 내부 포인터가 가리키는 데이터는 공유됩니다.

**예상 출력**
```
int : 200
int : 200
int : 200
```

---

### 3.3 CreateData 팩토리 함수 도입 - 메모리 해제 미비

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
Data CreateData(int item)
{
    Data data = { 0 };
    data.pdata = (int*)malloc(sizeof(int));
    *(int*)data.pdata = item;
    data.type = INT;

    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = CreateData(100);
    AddDataArray(&da, &data);
    data = CreateData(200);
    AddDataArray(&da, &data);
    data = CreateData(300);
    AddDataArray(&da, &data);

    *(int*)GetDataArray(&da, 0).pdata = 200;
    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- `CreateData(int item)` : **팩토리 함수**가 도입되었습니다. 매번 `malloc`으로 새로운 메모리를 할당하여 Data를 생성합니다.
- 이제 `CreateData(100)`, `CreateData(200)`, `CreateData(300)` 각각이 **별도의 메모리**를 가지므로, 얕은 복사 문제가 해결됩니다.
- `GetDataArray(&da, 0).pdata`로 0번 항목만 200으로 변경하면, **0번만 바뀌고 나머지는 유지**됩니다.
- **문제점**: `UninitDataArray`에서 `free(pda->buf)`만 하고, 각 항목의 `pdata`는 해제하지 않아 **메모리 누수**가 발생합니다.

**예상 출력**
```
int : 200
int : 200
int : 300
```

---

### 3.4 올바른 메모리 해제 (1)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        free(pda->buf[i].pdata);
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
Data CreateData(int item)
{
    Data data = { 0 };
    data.pdata = (int*)malloc(sizeof(int));
    *(int*)data.pdata = item;
    data.type = INT;

    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = CreateData(100);
    AddDataArray(&da, &data);
    data = CreateData(200);
    AddDataArray(&da, &data);
    data = CreateData(300);
    AddDataArray(&da, &data);

    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- **핵심 변경**: `UninitDataArray`에서 `free(pda->buf)` 전에 **각 항목의 `pdata`를 개별적으로 `free`**합니다.
- `malloc`으로 할당한 메모리는 반드시 `free`로 해제해야 합니다. 해제 순서는 **안쪽(개별 pdata) → 바깥쪽(buf 배열)** 입니다.
- 이렇게 하면 메모리 누수가 발생하지 않습니다.

**예상 출력**
```
int : 100
int : 200
int : 300
```

---

### 3.5 올바른 메모리 해제 (2) - 동일 패턴 반복

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        free(pda->buf[i].pdata);
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
Data CreateData(int item)
{
    Data data = { 0 };
    data.pdata = (int*)malloc(sizeof(int));
    *(int*)data.pdata = item;
    data.type = INT;

    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = CreateData(100);
    AddDataArray(&da, &data);
    data = CreateData(200);
    AddDataArray(&da, &data);
    data = CreateData(300);
    AddDataArray(&da, &data);

    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- 3.4절과 **동일한 구조**입니다. 수업에서 같은 패턴을 반복하여 학생들이 `CreateData` → `AddDataArray` → `PrintDataArray` → `UninitDataArray`의 흐름을 익히도록 한 예제입니다.
- 이 패턴은 이후 다중 타입 지원으로 발전하는 기반이 됩니다.

---

## 4. CreateData 팩토리 함수 발전

### 4.1 다중 타입 CreateData (하드코딩 값)

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        free(pda->buf[i].pdata);
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
Data CreateData(DataType dt)
{
    Data data = { 0 };
    switch (dt)
    {
    case INT: {
        data.pdata = (int*)malloc(sizeof(int));
        *(int*)data.pdata = 100;
        data.type = INT;
    }
            break;
    case DOUBLE: {
        data.pdata = (double*)malloc(sizeof(double));
        *(double*)data.pdata = 2.56;
        data.type = DOUBLE;
    }
               break;
    case STRING: {
        char buf[500] = "Hello!";
        data.pdata = (char*)malloc(strlen(buf) + 1);
        strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
        data.type = STRING;
    }
               break;
    }
    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = CreateData(INT);
    AddDataArray(&da, &data);
    data = CreateData(DOUBLE);
    AddDataArray(&da, &data);
    data = CreateData(STRING);
    AddDataArray(&da, &data);

    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- `CreateData`의 매개변수가 `int item`에서 `DataType dt`로 바뀌었습니다. 이제 **INT, DOUBLE, STRING 타입**을 모두 생성할 수 있습니다.
- `switch (dt)`로 타입을 판단하여 각각 다른 크기의 메모리를 할당합니다.
  - `INT` : `sizeof(int)` 크기 할당, 값 100 저장
  - `DOUBLE` : `sizeof(double)` 크기 할당, 값 2.56 저장
  - `STRING` : 문자열 길이 + 1(널 문자) 크기 할당, `strcpy_s`로 복사
- 아직 값이 **하드코딩**(고정값)되어 있어, 실제 사용에는 한계가 있습니다.

**예상 출력**
```
int : 100
double : 2.56
string : Hello!
```

---

### 4.2 다중 타입 CreateData (사용자 입력)

```c
#pragma warning(disable:26812 6011 6387)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        free(pda->buf[i].pdata);
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
Data CreateData(DataType dt)
{
    Data data = { 0 };
    switch (dt)
    {
    case INT: {
        int item;
        printf("정수 입력:");
        scanf_s("%d", &item);
        data.pdata = (int*)malloc(sizeof(int));
        *(int*)data.pdata = item;
        data.type = INT;
    }
            break;
    case DOUBLE: {
        double item;
        printf("실수 입력:");
        scanf_s("%lf", &item);
        data.pdata = (double*)malloc(sizeof(double));
        *(double*)data.pdata = item;
        data.type = DOUBLE;
    }
            break;
    case STRING: {
        char buf[500] = "";
        printf("문자열 입력:");
        gets_s(buf, 500);
        data.pdata = (char*)malloc(strlen(buf) + 1);
        strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
        data.type = STRING;
    }
            break;
    }
    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
int main()
{
    DataArray da;

    InitDataArray(&da, 10000);

    Data data = CreateData(INT);
    AddDataArray(&da, &data);
    data = CreateData(DOUBLE);
    AddDataArray(&da, &data);
    data = CreateData(STRING);
    AddDataArray(&da, &data);

    PrintDataArray(&da);

    UninitDataArray(&da);
}
```

**설명**
- 하드코딩 값 대신 `scanf_s`와 `gets_s`로 **사용자 입력**을 받습니다.
- `scanf_s("%d", &item)` : 정수 입력
- `scanf_s("%lf", &item)` : 실수 입력 (double은 `%lf`)
- `gets_s(buf, 500)` : 한 줄 전체를 문자열로 입력받음 (공백 포함)
- `#pragma warning(disable:26812 6011 6387)` : Visual Studio의 특정 경고를 끄는 **전처리기 지시문**입니다. 학습 중 불필요한 경고를 숨기기 위해 사용합니다.

---

## 5. 입력 처리

### 5.1 getchar 기초

```c
#pragma warning(disable:26812 6011 6387)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char c = getchar();
    printf("%d\n", c);

    c = getchar();
    printf("%d\n", c);
}
```

**설명**
- `getchar()` : 키보드에서 **문자 하나**를 읽어 반환합니다.
- 사용자가 `A`를 입력하고 Enter를 누르면:
  - 첫 번째 `getchar()`는 `'A'`(ASCII 65)를 읽습니다.
  - 두 번째 `getchar()`는 **Enter 키의 줄바꿈 문자 `'\n'`**(ASCII 10)을 읽습니다.
- 이것이 **입력 버퍼** 문제입니다: Enter를 누르면 `'\n'`도 버퍼에 남아서 다음 입력에 영향을 줍니다.

**예상 출력 (사용자가 'A' 입력 후 Enter)**
```
65
10
```

---

### 5.2 scanf_s와 입력 버퍼 처리

```c
#pragma warning(disable:26812 6011 6387)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int n = 0;
    scanf_s("%d", &n);
    printf("int : %d\n", n);

    scanf_s("%d", &n);
    getchar();
    printf("int : %d\n", n);

    char buf[100];
    gets_s(buf, 100);
    printf("string : %s\n", buf);
}
```

**설명**
- `scanf_s("%d", &n)` : 정수를 입력받습니다. 숫자만 읽고 **Enter(`'\n'`)는 버퍼에 남겨둡니다**.
- 두 번째 `scanf_s` 뒤에 `getchar()`를 호출하여 **남은 `'\n'`을 제거**합니다.
- `gets_s(buf, 100)` : 한 줄 전체를 읽습니다. 만약 `getchar()`로 `'\n'`을 제거하지 않으면, `gets_s`가 빈 줄을 읽어버리는 문제가 발생합니다.
- 이 예제는 `scanf_s`와 `gets_s`를 **섞어 사용할 때** 입력 버퍼를 주의해야 한다는 것을 보여줍니다.

---

## 6. 메뉴 기반 프로그램

### 6.1 typedef enum BOOL과 메뉴 루프

```c
#pragma warning(disable:26812 6011 6387)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
typedef enum { FALSE, TRUE} BOOL;
typedef enum { INT, DOUBLE, STRING, NONE } DataType;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        free(pda->buf[i].pdata);
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
void Flush()
{
    while (getchar() != '\n')
        ;
}
Data CreateData(DataType dt)
{
    Data data = { 0 };
    switch (dt)
    {
    case INT: {
        int item;
        printf("정수 입력:");
        scanf_s("%d", &item); Flush();
        data.pdata = (int*)malloc(sizeof(int));
        *(int*)data.pdata = item;
        data.type = INT;
    }
            break;
    case DOUBLE: {
        double item;
        printf("실수 입력:");
        scanf_s("%lf", &item); Flush();
        data.pdata = (double*)malloc(sizeof(double));
        *(double*)data.pdata = item;
        data.type = DOUBLE;
    }
            break;
    case STRING: {
        char buf[500] = "";
        printf("문자열 입력:");
        gets_s(buf, 500);
        data.pdata = (char*)malloc(strlen(buf) + 1);
        strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
        data.type = STRING;
    }
            break;
    }
    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
void Menu()
{
    puts("1. 정수, 실수, 문자열 입력:");
    puts("2. 모든 데이터 출력:");
    puts("3. 부가 기능");
    puts("0. 프로그램 종료!");
    puts("");
}
int main()
{
    BOOL run = TRUE;
    DataArray da;
    InitDataArray(&da, 10000);

    while (run)
    {
        Menu();
        switch (_getch())
        {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '0':
            run = FALSE;
            break;
        }
    }

    UninitDataArray(&da);
}
```

**설명**
- `typedef enum { FALSE, TRUE } BOOL;` : C에는 `bool` 타입이 기본 제공되지 않으므로(C99 이전), 열거형으로 직접 만듭니다.
- `Flush()` : `scanf_s` 후 남은 입력 버퍼를 **줄바꿈 문자까지 모두 소비**하는 유틸리티 함수입니다.
  ```c
  while (getchar() != '\n') ;
  ```
  `'\n'`을 만날 때까지 한 글자씩 읽고 버립니다. 빈 `while` 본문은 `;`로 표시합니다.
- `Menu()` : 메뉴를 화면에 출력하는 **헬퍼 함수**입니다.
- `_getch()` : `<conio.h>`에 정의된 함수로, Enter 없이 **키 하나를 즉시 읽습니다**. 메뉴 선택에 적합합니다.
- `while (run)` : `run`이 `TRUE`인 동안 메뉴를 반복합니다. `'0'`을 누르면 `run = FALSE`로 루프를 종료합니다.
- 이 단계에서는 메뉴의 **뼈대만** 만들어져 있고, `case '1'`~`case '3'`은 아직 비어 있습니다.

---

## 7. 파일 입출력 (바이너리)

### 7.1 기본 바이너리 파일 쓰기/읽기

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    FILE* pf = NULL;
    fopen_s(&pf, "..\\test.ati", "wb");
    {
        {
            char logo[2] = { 'M','F' };
            unsigned short empty = 0;
            fwrite(logo, 1, sizeof(char) * 2, pf);
            fwrite(&empty, 1, sizeof(unsigned short), pf);
            int dataCount = 4;
            fwrite(&dataCount, 1, sizeof(int), pf);
        }
        {
            char dtype = 'I';
            int ndata = 100;
            double ddata = 2.6;
            const char* sdata = "Hello!";
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&ndata, 1, sizeof(int), pf);

            dtype = 'D';
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&ddata, 1, sizeof(double), pf);

            dtype = 'S';
            int slen = strlen(sdata) + 1;
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&slen, 1, sizeof(int), pf);
            fwrite(sdata, 1, slen, pf);

            dtype = 'I';
            ndata = 25;
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&ndata, 1, sizeof(int), pf);
        }
    }
    fclose(pf);

    fopen_s(&pf, "..\\test.ati", "rb");
    {
        int dataCount = 0;
        {
            char header[8];
            fread(header, 1, sizeof(header), pf);
            if (!(header[0] == 'M' && header[1] == 'F'))
            {
                printf("파일 포멧이 다릅니다.");
                return -1;
            }
            dataCount = *(int*)(header + 4);
        }
        {
            for (int i = 0; i < dataCount; ++i)
            {
                char type = 0;
                fread(&type, 1, sizeof(char), pf);
                switch (type)
                {
                case 'I':
                {
                    int data = 0;
                    fread(&data, 1, sizeof(int), pf);
                    printf("int : %d\n", data);
                }
                break;
                case 'D':
                {
                    double data = 0;
                    fread(&data, 1, sizeof(double), pf);
                    printf("double : %g\n", data);
                }
                break;
                case 'S':
                {
                    int slen = 0;
                    fread(&slen, 1, sizeof(int), pf);
                    char* buf = (char*)malloc(slen);
                    fread(buf, 1, slen, pf);
                    printf("string : %s\n", buf);
                    free(buf);
                }
                break;
                default:
                    break;
                }
            }
        }
    }
    fclose(pf);
}
```

**설명**
- **커스텀 바이너리 파일 포맷**을 직접 설계하여 읽고 쓰는 예제입니다.
- **파일 구조 (헤더 + 바디)**:

| 영역 | 필드 | 크기 | 설명 |
|------|------|------|------|
| **헤더** | logo | 2바이트 | 'M','F' - 파일 식별자 |
| | empty | 2바이트 | 예약 (미사용) |
| | dataCount | 4바이트 | 저장된 데이터 개수 |
| **바디** | dtype | 1바이트 | 'I', 'D', 'S' 중 하나 |
| | data | 가변 | 타입에 따라 int(4), double(8), 문자열(길이+데이터) |

- `fopen_s(&pf, "파일경로", "wb")` : **바이너리 쓰기 모드**로 파일을 엽니다.
- `fwrite(&변수, 1, 크기, pf)` : 변수의 메모리 내용을 그대로 파일에 씁니다.
- `fopen_s(&pf, "파일경로", "rb")` : **바이너리 읽기 모드**로 파일을 엽니다.
- `fread(&변수, 1, 크기, pf)` : 파일에서 지정한 크기만큼 읽어 변수에 저장합니다.
- 읽기 시 헤더를 먼저 읽고 `'M','F'`인지 확인하여 **파일 포맷을 검증**합니다.
- 문자열의 경우 길이(`slen`)를 먼저 쓰고, 그 길이만큼 데이터를 쓰는 방식으로 **가변 길이 데이터**를 처리합니다.

**예상 출력**
```
int : 100
double : 2.6
string : Hello!
int : 25
```

---

### 7.2 파일 입출력 함수 분리와 메뉴 프로그램 (1)

```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void SetFile()
{
    FILE* pf = NULL;

    fopen_s(&pf, "..\\test.ati", "wb");
    {
        {
            char logo[2] = { 'M','F' };
            unsigned short empty = 0;
            fwrite(logo, 1, sizeof(char) * 2, pf);
            fwrite(&empty, 1, sizeof(unsigned short), pf);
            int dataCount = 10000;
            fwrite(&dataCount, 1, sizeof(int), pf);
        }
    }
    fclose(pf);
}
void IWriteData(char dtype, int ndata)
{
    FILE* pf = NULL;
    fopen_s(&pf, "..\\test.ati", "ab");
    {
        fwrite(&dtype, 1, sizeof(char), pf);
        fwrite(&ndata, 1, sizeof(int), pf);
    }
    fclose(pf);
}
void DWriteData(char dtype, double Ddata)
{
    FILE* pf = NULL;
    fopen_s(&pf, "..\\test.ati", "ab");
    {
        fwrite(&dtype, 1, sizeof(char), pf);
        fwrite(&Ddata, 1, sizeof(double), pf);
    }
    fclose(pf);
}
void SWriteData(char dtype, char* Sdata, int slen)
{
    FILE* pf = NULL;
    fopen_s(&pf, "..\\test.ati", "ab");
    {
        fwrite(&dtype, 1, sizeof(char), pf);
        fwrite(&slen, 1, sizeof(int), pf);
        fwrite(Sdata, 1, slen, pf);
    }
    fclose(pf);
}
void ReadData(int dataCount)
{
    FILE* pf = NULL;
    fopen_s(&pf, "..\\test.ati", "rb");
    {
        char header[8];
        fread(header, 1, sizeof(header), pf);
        if (!(header[0] == 'M' && header[1] == 'F'))
        {
            printf("File Format 다름");
            abort;
        }

        for (int i = 0; i < dataCount; ++i)
        {
            char type = 0;
            fread(&type, 1, sizeof(char), pf);
            switch (type)
            {
            case 'I':
            {
                int data = 0;
                fread(&data, 1, sizeof(int), pf);
                printf("int  : %d\n", data);
                break;
            }
            case 'D':
            {
                double data = 0;
                fread(&data, 1, sizeof(double), pf);
                printf("double  : %lf\n", data);
                break;
            }
            case 'S':
            {
                int slen = 0;
                fread(&slen, 1, sizeof(int), pf);
                char* buf = (char*)malloc(slen);
                fread(buf, 1, slen, pf);
                printf("string  : %s\n", buf);

                free(buf);
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
    fclose(pf);
}
void Menu()
{
    printf("============================\n");
    printf(" 1. 데이터 입력:\n");
    printf(" 2. 모든 데이터 출력:\n");
    printf(" 0. 프로그램 종료\n");
    printf("============================\n");
    printf("매뉴를 선택하세요\n");
}
int main()
{
    int menu = 1;
    int dataCount = 0;
    char dtype = '0';
    int ndata = 0;
    double ddata = 0;
    char sdata[100] = { 0 };
    SetFile();
    do
    {
        Menu();
        scanf_s("%d", &menu);
        printf("%d", menu);
        switch (menu)
        {
        case 1:
        {
            printf(" 데이터 입력을 선택하셧습니다\n");
            dataCount = dataCount + 1;
            printf("추가할 데이터의 타입을 정하세요\n");
            scanf_s(" %c", &dtype);
            if (dtype == 'I')
            {
                printf("추가할 데이터를 입력하세요\n");
                scanf_s("%d", &ndata);
                IWriteData(dtype, ndata);
            }
            else if (dtype == 'D')
            {
                printf("추가할 데이터를 입력하세요\n");
                scanf_s("%lf", &ddata);
                DWriteData(dtype, ddata);
            }
            else if (dtype == 'S')
            {
                printf("추가할 데이터를 입력하세요\n");
                scanf_s("%s", sdata, 100);
                SWriteData(dtype, sdata, strlen(sdata) + 1);
            }
            break;
        }
        case 2:
        {
            printf(" 데이터 출력을 선택하셧습니다\n");
            ReadData(dataCount);
            break;
        }
        case 0:
        {
            printf("프로그램을 종료를 선택하셧습니다\n");
            break;
        }
        }
    } while (menu != 0);
}
```

**설명**
- 파일 입출력 기능을 **함수별로 분리**한 구조입니다.
- `SetFile()` : 파일을 새로 만들고 **헤더만 기록**합니다.
- `IWriteData`, `DWriteData`, `SWriteData` : 타입별로 데이터를 **추가(append) 모드(`"ab"`)**로 기록합니다.
- `ReadData(int dataCount)` : 헤더 검증 후 dataCount만큼 데이터를 읽어 출력합니다.
- `do-while` 루프와 `scanf_s`를 이용한 메뉴 시스템입니다.
- `scanf_s(" %c", &dtype)` : 서식 문자열의 `" %c"`에서 **앞의 공백**이 남은 공백/줄바꿈을 건너뛰는 역할을 합니다.

---

### 7.3 대화형 파일 입출력 프로그램 (2)

```c
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

void util(void)
{
    system("cls");
    printf("1.입력\n");
    printf("2.출력\n");
    printf("3.프로그램 종료\n");
    printf("===========================\n");
}

void input_util(void)
{
    system("cls");
    printf("1.숫자\n");
    printf("2.실수\n");
    printf("3.문자열\n");
    printf("4.뒤로\n");
    printf("===========================\n");
}

void header_info_write(FILE* pf)
{
    char logo[2] = { 'H','S' };
    unsigned short empty = 0;
    fwrite(logo, 1, sizeof(char) * 2, pf);
    fwrite(&empty, 1, sizeof(unsigned short), pf);
}

int judge_header(FILE* pf)
{
    char header[4];
    fread(header, 1, sizeof(header), pf);
    if (!(header[0] == 'H' and header[1] == 'S'))
    {
        printf("파일 포멧이 다릅니다.");
        return 0;
    }
    return 1;
}

void state_write()
{
    FILE* pf = NULL;
    fopen_s(&pf, "test.lhs", "wb");
    header_info_write(pf);
    int run = 1;
    while (run)
    {
        input_util();
        char dtype = 0;
        switch (_getch())
        {
        case '1':
        {
            dtype = 'I';
            int data;
            printf("숫자 입력 : ");
            scanf_s("%d", &data);
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&data, 1, sizeof(int), pf);
        }
        break;
        case '2':
        {
            dtype = 'D';
            double data;
            printf("실수 입력 : ");
            scanf_s("%lf", &data);
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&data, 1, sizeof(double), pf);
        }
        break;
        case '3':
        {
            dtype = 'S';
            char data[500];
            printf("문자열 입력 : ");
            scanf_s("%s", &data, 500);
            int slen = strlen(data) + 1;
            fwrite(&dtype, 1, sizeof(char), pf);
            fwrite(&slen, 1, sizeof(int), pf);
            fwrite(data, 1, slen, pf);
        }
        break;
        case '4':
        {
            run = 0;
            dtype = 'E';
            fwrite(&dtype, 1, sizeof(char), pf);
            fclose(pf);
        }
        break;
        default:
            break;
        }
    }
}

void state_read()
{
    FILE* pf = NULL;
    int run = 1;
    fopen_s(&pf, "test.lhs", "rb");
    if (judge_header(pf))
    {
        while (run)
        {
            char type = 0;
            fread(&type, 1, sizeof(char), pf);
            switch (type)
            {
            case 'I':
            {
                int data = 0;
                fread(&data, 1, sizeof(int), pf);
                printf("int : %d\n", data);
            }
            break;
            case 'D':
            {
                double data = 0;
                fread(&data, 1, sizeof(double), pf);
                printf("double : %g\n", data);
            }
            break;
            case 'S':
            {
                int slen = 0;
                fread(&slen, 1, sizeof(int), pf);
                char* buf = (char*)malloc(slen);

                fread(buf, 1, slen, pf);
                printf("string : %s\n", buf);
                free(buf);
            }
            break;
            case 'E':
                run = 0;
                fclose(pf);
                printf("아무키나 입력하세요\n");
                _getch();
                break;
            default:
                break;
            }
        }
    }
}

int main(void)
{
    int loop = 1;
    while (loop)
    {
        util();
        switch (_getch())
        {
        case '1':
            state_write();
            break;
        case '2':
            state_read();
            break;
        case '3':
            loop = 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
```

**설명**
- 이전 예제를 더 발전시켜, **완전한 대화형 파일 입출력 프로그램**을 구성합니다.
- `system("cls")` : 화면을 지우는 명령입니다 (`<Windows.h>` 또는 `<stdlib.h>` 필요).
- **종료 마커(`'E'`)**: 데이터 개수를 헤더에 미리 쓰는 대신, 바디 끝에 `'E'` 타입을 기록하여 "여기서 끝"을 표시합니다. 읽기 시 `'E'`를 만나면 루프를 종료합니다.
- `header_info_write` / `judge_header` : 헤더 쓰기/검증을 별도 함수로 분리했습니다.
- `state_write` : 파일을 열고, 사용자가 `'4'`(뒤로)를 선택할 때까지 반복하여 데이터를 기록합니다.
- `state_read` : 파일을 열고, `'E'` 마커를 만날 때까지 데이터를 읽어 출력합니다.

---

## 8. 최종 완성 코드 (enum class)

### 8.1 enum class와 ChooseData 함수

이것이 ex20.cpp의 **활성(주석 처리되지 않은) 코드**이며, 앞서 배운 모든 개념이 종합된 최종 버전입니다.

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
enum class BOOL { FALSE, TRUE } ;
enum class DataType { INT, DOUBLE, STRING, NONE } ;

struct Data
{
    void* pdata;
    DataType type;
};
struct DataArray
{
    Data* buf;
    int capacity;
    int size;
};
void InitDataArray(DataArray* pda, int cap)
{
    pda->capacity = cap;
    pda->size = 0;
    pda->buf = (Data*)malloc(sizeof(Data) * pda->capacity);
}
void UninitDataArray(DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
    {
        free(pda->buf[i].pdata);
        pda->buf[i].pdata = NULL;
    }
    free(pda->buf);
}
void PrintData(const Data* pd)
{
    switch (pd->type)
    {
    case DataType::INT:
        printf("int : %d\n", *(int*)pd->pdata);
        break;
    case DataType::DOUBLE:
        printf("double : %g\n", *(double*)pd->pdata);
        break;
    case DataType::STRING:
        printf("string : %s\n", (char*)pd->pdata);
        break;
    default:
        break;
    }
}
void Flush()
{
    while (getchar() != '\n')
        ;
}
Data CreateData(DataType dt)
{
    Data data = { 0 };
    switch (dt)
    {
    case DataType::INT: {
        int item;
        printf("정수 입력:");
        scanf_s("%d", &item); Flush();
        data.pdata = (int*)malloc(sizeof(int));
        if( data.pdata )
            *(int*)data.pdata = item;
        data.type = DataType::INT;
    }
            break;
    case DataType::DOUBLE: {
        double item;
        printf("실수 입력:");
        scanf_s("%lf", &item); Flush();
        data.pdata = (double*)malloc(sizeof(double));
        if( data.pdata)
            *(double*)data.pdata = item;
        data.type = DataType::DOUBLE;
    }
               break;
    case DataType::STRING: {
        char buf[500] = "";
        printf("문자열 입력:");
        gets_s(buf, 500);
        data.pdata = (char*)malloc(strlen(buf) + 1);
        if( data.pdata )
            strcpy_s((char*)data.pdata, strlen(buf) + 1, buf);
        data.type = DataType::STRING;
    }
               break;
    }
    return data;
}
void AddDataArray(DataArray* pda, Data* pd)
{
    pda->buf[pda->size++] = *pd;
}
void PrintDataArray(const DataArray* pda)
{
    for (int i = 0; i < pda->size; ++i)
        PrintData(&pda->buf[i]);
}
Data GetDataArray(const DataArray* pda, int idx)
{
    return pda->buf[idx];
}
void Menu()
{
    puts("1. 정수, 실수, 문자열 입력:");
    puts("2. 모든 데이터 출력:");
    puts("3. 부가 기능");
    puts("0. 프로그램 종료!");
    puts("");
}
Data ChooseData()
{
    printf("정수[0], 실수[1], 문자열[2] 입력하세요:");
    Data data = { 0 };
    switch ((DataType)(_getch()-'0'))
    {
    case DataType::INT:
        data = CreateData(DataType::INT);
        break;
    case DataType::DOUBLE:
        data = CreateData(DataType::DOUBLE);
        break;
    case DataType::STRING:
        data = CreateData(DataType::STRING);
        break;
    }
    return data;
}
int main()
{
    BOOL run = BOOL::TRUE;
    DataArray da;
    InitDataArray(&da, 10000);

    DataType dt = (DataType)5;
    while (run == BOOL::TRUE)
    {
        Menu();
        switch (_getch())
        {
        case '1':
        {
            Data data = ChooseData();
            AddDataArray(&da, &data);
        }
            break;
        case '2':
            PrintDataArray(&da);
            break;
        case '3':
            break;
        case '0':
            run = BOOL::FALSE;
            break;
        }
    }

    UninitDataArray(&da);
}
```

**설명**

**1) typedef enum → enum class (C++ 기능)**

| 구분 | `typedef enum` | `enum class` |
|------|----------------|--------------|
| 사용법 | `INT`, `DOUBLE` 등 직접 사용 | `DataType::INT`, `DataType::DOUBLE`처럼 **범위 지정** |
| 이름 충돌 | 다른 열거형과 이름이 겹칠 수 있음 | 범위가 분리되어 **충돌 없음** |
| 암시적 변환 | 정수로 자동 변환됨 | 정수로 **자동 변환 불가** (명시적 캐스팅 필요) |

- `enum class BOOL { FALSE, TRUE };` → `BOOL::TRUE`, `BOOL::FALSE`로 사용
- `enum class DataType { INT, DOUBLE, STRING, NONE };` → `DataType::INT` 등으로 사용

**2) ChooseData 함수**
- `_getch()`로 키 하나를 읽고, `'0'`을 빼서 숫자(0, 1, 2)로 변환합니다.
- `(DataType)(_getch()-'0')` : 결과를 `DataType`으로 캐스팅하여 `switch`에 사용합니다.
- 메뉴 선택(1번)을 누르면 `ChooseData()`가 호출되고, 사용자가 타입을 고르면 `CreateData`로 데이터를 생성합니다.

**3) malloc 후 NULL 검사**
- `if(data.pdata)` : `malloc`이 메모리 할당에 실패하면 `NULL`을 반환합니다. NULL이 아닐 때만 값을 저장하여 **안전한 코드**를 작성합니다.

**4) UninitDataArray에서 pdata = NULL**
- `free` 후 `pda->buf[i].pdata = NULL;`로 설정하여, 해제된 메모리에 실수로 접근하는 것을 방지합니다. 이를 **댕글링 포인터 방지**라고 합니다.

---

## 9. 보충 학습

### 9.1 구조체와 함수 조합 패턴 정리

ex20.cpp 전체에서 반복되는 패턴은 **구조체를 정의하고, 그 구조체를 다루는 함수를 만드는** 것입니다. 이는 나중에 배울 **객체지향 프로그래밍(OOP)**의 기초가 됩니다.

| 함수 | 역할 | OOP 대응 |
|------|------|----------|
| `InitDataArray` | 초기화 (메모리 할당) | 생성자 (Constructor) |
| `UninitDataArray` | 정리 (메모리 해제) | 소멸자 (Destructor) |
| `AddDataArray` | 데이터 추가 | 멤버 함수 (Add) |
| `PrintDataArray` | 전체 출력 | 멤버 함수 (Print) |
| `GetDataArray` | 데이터 조회 | 멤버 함수 (Get) |
| `CreateData` | 데이터 생성 | 팩토리 함수 (Factory) |

### 9.2 동적 메모리 관리 원칙

| 원칙 | 설명 |
|------|------|
| **malloc ↔ free 짝 맞추기** | `malloc`으로 할당한 메모리는 반드시 `free`로 해제 |
| **안쪽부터 해제** | 중첩 구조에서는 안쪽(개별 pdata) → 바깥쪽(buf 배열) 순서로 해제 |
| **NULL 검사** | `malloc` 반환값이 NULL인지 확인 후 사용 |
| **해제 후 NULL 대입** | `free` 후 포인터를 NULL로 설정하여 댕글링 포인터 방지 |
| **얕은 복사 주의** | 구조체 대입은 포인터 값만 복사하므로, 데이터 공유 문제 발생 가능 |

### 9.3 파일 열기 모드 정리

| 모드 | 의미 | 파일 없을 때 |
|------|------|-------------|
| `"wb"` | 바이너리 쓰기 (새로 생성) | 새 파일 생성 |
| `"rb"` | 바이너리 읽기 | 오류 (열기 실패) |
| `"ab"` | 바이너리 추가 (파일 끝에 이어 쓰기) | 새 파일 생성 |

### 9.4 #pragma warning (전처리기 지시문)

일부 예제에 `#pragma warning(disable:26812 6011 6387)`이 사용되었습니다.

| 경고 번호 | 의미 |
|-----------|------|
| **26812** | enum class 대신 enum 사용 경고 |
| **6011** | NULL 포인터 역참조 가능성 경고 |
| **6387** | 매개변수가 NULL일 수 있음 경고 |

`#pragma`는 **컴파일러별 전처리기 지시문**으로, 여기서는 Visual Studio 전용 경고를 끄는 데 사용합니다. 학습 단계에서는 경고를 숨기기보다 **원인을 이해하고 코드를 개선**하는 것이 좋습니다.

---

## 10. 정리 표

| 주제 | 내용 |
|------|------|
| typedef enum | `typedef enum { A, B, C } Name;` → 값을 이름으로 사용 (`A`, `B`, `C`) |
| enum class | `enum class Name { A, B, C };` → 범위 지정 필수 (`Name::A`) |
| void* | 어떤 타입이든 가리킬 수 있는 범용 포인터, 사용 시 형변환 필수 |
| malloc / free | 동적 메모리 할당/해제 (`<stdlib.h>`) |
| 구조체 + 함수 | Init / Uninit / Add / Print / Get / Create 패턴 |
| 얕은 복사 | 구조체 대입(`=`)은 포인터 값만 복사 → 같은 메모리 공유 위험 |
| 입력 버퍼 | `scanf_s` 후 `'\n'`이 남음 → `getchar()` 또는 `Flush()`로 제거 |
| _getch() | Enter 없이 키 하나 즉시 읽기 (`<conio.h>`) |
| gets_s | 한 줄 전체 문자열 입력 (공백 포함) |
| fwrite / fread | 바이너리 파일 쓰기/읽기 |
| fopen_s 모드 | `"wb"` 쓰기, `"rb"` 읽기, `"ab"` 추가 |
| 커스텀 파일 포맷 | 헤더(식별자+메타정보) + 바디(타입 마커+데이터) |
| NULL 검사 | `malloc` 후 반환값 확인, `free` 후 NULL 대입 |
| #pragma warning | Visual Studio 전용 경고 제어 전처리기 지시문 |

---

## 11. 연습 문제 (스스로 풀어보기)

1. `typedef enum { RED, GREEN, BLUE } Color;`를 정의하고, 각 값을 `printf`로 출력하여 어떤 숫자가 나오는지 확인하세요.

2. `Data` 구조체에 `double` 값 3.14를 저장하고 `PrintData`로 출력하는 코드를 작성해 보세요. (`malloc` → 형변환 → 값 저장 → 출력 → `free`)

3. `CreateData` 함수를 수정하여, 정수를 입력받을 때 **음수를 입력하면 거부하고 다시 입력받도록** 만들어 보세요. (힌트: `while` 루프 사용)

4. `UninitDataArray`에서 `free(pda->buf)`만 하고 개별 `pdata`를 해제하지 않으면 어떤 문제가 생기는지 설명하세요. 실제로 두 버전을 작성하고 비교해 보세요.

5. 바이너리 파일에 학생 이름(문자열)과 점수(정수)를 3명분 기록한 뒤, 다시 읽어서 출력하는 프로그램을 작성해 보세요. (힌트: 타입 마커로 `'N'`(이름)과 `'S'`(점수)를 사용)

6. 7.1절의 파일 포맷에서, 헤더의 `dataCount`를 **0으로 초기화**하고 데이터를 추가할 때마다 `fseek`로 헤더 위치로 돌아가서 개수를 갱신하는 방식으로 개선해 보세요.

---

이 강의 자료는 **example/ex20.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. **가장 아래(기초)**부터 **위(발전)**로 진행하며, 1→2→3 순서로 학습하면 구조체와 함수의 조합이 어떻게 발전하는지 자연스럽게 이해할 수 있습니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
