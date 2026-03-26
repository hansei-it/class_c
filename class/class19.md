# C언어 기초 강의 19 - ex19.cpp 코드를 통한 공용체, 비트필드, 파일 입출력

이 강의는 **example/ex19.cpp**에 담긴 예제들을 바탕으로, 공용체(union), 비트필드(bit-field), 그리고 텍스트/바이너리 파일 입출력을 단계적으로 학습하는 내용입니다.

---

## 0. 학습 목표

- **비트필드(bit-field)** 구조체를 선언하고, 비트 단위로 데이터를 다룰 수 있다.
- **공용체(union)**의 메모리 공유 원리를 이해하고, 같은 메모리를 다른 타입으로 해석할 수 있다.
- **파일 입출력**의 3단계(열기 → 읽기/쓰기 → 닫기)를 이해한다.
- **텍스트 모드**와 **바이너리 모드**의 차이(CR/LF 변환)를 설명할 수 있다.
- `fprintf`/`fscanf`/`fgets`를 이용한 **텍스트 파일 입출력**을 할 수 있다.
- `fwrite`/`fread`를 이용한 **바이너리 파일 입출력**을 할 수 있다.
- 헤더와 바디로 구성된 **커스텀 바이너리 파일 포맷**을 설계하고 구현할 수 있다.

---

## 0.1 수업 진행 순서 제안

1. **1장** – 비트필드 구조체 (비트 단위 데이터 조작)
2. **2장** – 공용체(union) (메모리 공유와 타입 재해석)
3. **3장** – 파일 입출력 기초 (fopen, fprintf, fclose)
4. **4장** – 텍스트 파일 읽기 (fscanf, fgets)
5. **5장** – 텍스트 모드 vs 바이너리 모드 (CR/LF)
6. **6장** – 바이너리 파일 입출력 (fwrite, fread)
7. **7장** – 커스텀 바이너리 파일 포맷 설계

---

## 1. 비트필드(Bit-field) 구조체

비트필드는 구조체의 멤버를 **비트 단위**로 크기를 지정하여, 메모리를 절약하거나 하드웨어 레지스터를 다룰 때 유용합니다.

### 1.1 기본 비트필드 선언

```c
#include <stdio.h>

struct _bitfield
{
	unsigned int a1 : 1;
	unsigned int a2 : 1;
	unsigned int a3 : 2;
	unsigned int a4 : 4;
};

int main()
{
	struct _bitfield bit = { 0 };

	bit.a3 = 3;
	printf("%08X\n", bit);
}
```

**설명**
- `unsigned int a1 : 1;` : 멤버 `a1`에 **1비트**만 할당합니다. 저장 가능한 값: 0 또는 1.
- `a2 : 1` → 1비트, `a3 : 2` → 2비트(0~3), `a4 : 4` → 4비트(0~15).
- 전체 `a1+a2+a3+a4 = 1+1+2+4 = 8비트`이므로, 하나의 `unsigned int`(4바이트) 안에 들어갑니다.
- `bit.a3 = 3;` → a3는 2비트이므로 이진수 `11`이 저장됩니다.
- 비트 배치: `a4(4bit) | a3(2bit) | a2(1bit) | a1(1bit)` → a3에 3을 넣으면 `0000 11 0 0` = `0x0C`.

**예상 출력**
```
0000000C
```

---

### 1.2 8비트 비트필드와 비트 연산

```c
#include <stdio.h>

struct _bitfield
{
	unsigned int a1 : 8;
	unsigned int a2 : 8;
	unsigned int a3 : 8;
	unsigned int a4 : 8;
};

int main()
{
	struct _bitfield bit = { 0 };

	bit.a1 |= 0xFF;
	bit.a3 |= 0xFF;
	printf("%08X\n", bit);
	bit.a1 |= 0xFF;
	bit.a3 ^= 0xFF;
	printf("%08X\n", bit);
}
```

**설명**
- 각 멤버가 **8비트(1바이트)**씩이므로, 4개 합쳐서 32비트 = 4바이트를 차지합니다.
- `bit.a1 |= 0xFF;` : a1의 모든 비트를 1로 설정 → `a1 = 0xFF`.
- `bit.a3 |= 0xFF;` : a3의 모든 비트를 1로 설정 → `a3 = 0xFF`.
- 메모리 배치: `a4 | a3 | a2 | a1` → `0x00FF00FF`.
- `bit.a3 ^= 0xFF;` : a3를 XOR로 반전 → `0xFF ^ 0xFF = 0x00`.
- 결과: `a4 | a3 | a2 | a1` → `0x000000FF`.

**예상 출력**
```
00FF00FF
000000FF
```

---

## 2. 공용체(Union)

공용체는 **모든 멤버가 같은 메모리 주소를 공유**합니다. 구조체와 달리, 가장 큰 멤버의 크기가 전체 크기가 됩니다.

### 2.1 기본 공용체 선언

```c
#include <stdio.h>

typedef union data {
	int n;
	char arr[4];
} Data;

int main()
{
	Data u1 = { 0x44434241 };

	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("size : %d\n", sizeof(u1));
}
```

**설명**
- `union data` : `int n`과 `char arr[4]`가 **같은 메모리**를 공유합니다.
- `0x44434241`을 `int n`에 저장하면, 같은 메모리를 `char arr[4]`로 읽을 수 있습니다.
- **리틀 엔디안** 시스템에서: `arr[0]=0x41('A')`, `arr[1]=0x42('B')`, `arr[2]=0x43('C')`, `arr[3]=0x44('D')`.
- `sizeof(u1)` : `int`(4바이트)와 `char[4]`(4바이트) 중 큰 쪽 → **4바이트**.

**예상 출력**
```
ABCD
41424344
size : 4
```

---

### 2.2 공용체에 double 멤버 추가

```c
#include <stdio.h>

typedef union data {
	int n;
	char arr[4];
	double d;
} Data;

int main()
{
	Data u1 = { 0x44434241 };

	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("size : %d\n", sizeof(u1));
}
```

**설명**
- `double d`(8바이트)가 추가되었으므로, union의 크기가 **8바이트**로 커집니다.
- union의 크기 = 가장 큰 멤버의 크기 = `sizeof(double)` = **8**.
- 값을 `int n`으로 초기화했으므로 `arr[0]~arr[3]`까지만 의미 있는 값이 들어 있습니다.

**예상 출력**
```
ABCD
41424344
size : 8
```

---

### 2.3 공용체의 메모리 주소 확인

```c
#include <stdio.h>

typedef union data {
	int n;
	char arr[4];
	double d;
} Data;

int main()
{
	Data u1 = { 0x44434241 };

	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
	printf("size : %d\n", sizeof(u1));
	printf("%p\n", &u1.n);
	printf("%p\n", u1.arr);
	printf("%p\n", &u1);
}
```

**설명**
- `&u1.n`, `u1.arr`, `&u1` 세 주소를 출력합니다.
- union의 모든 멤버는 **같은 시작 주소**를 공유하므로, 세 값이 모두 동일합니다.
- 이것이 union의 핵심: **하나의 메모리 공간을 여러 타입으로 해석**합니다.

**예상 출력 (주소 값은 실행 환경에 따라 다름)**
```
ABCD
41424344
size : 8
00AFFC00
00AFFC00
00AFFC00
```

---

## 3. 파일 입출력 기초

C에서 파일 작업은 **3단계**로 이루어집니다: 열기 → 읽기/쓰기 → 닫기.

### 3.1 파일 입출력의 기본 구조 (뼈대)

```c
#include <stdio.h>

int main()
{
	FILE* pf = NULL;

	//1. 파일 열기(생성)
	fopen();
	//2. 파일 읽기, 쓰기
	fprintf();
	fscanf();
	//3. 파일 닫기
	fclose();
}
```

**설명**
- `FILE* pf` : 파일을 가리키는 **파일 포인터**를 선언합니다.
- **fopen** : 파일을 열어서 파일 포인터를 얻습니다.
- **fprintf / fscanf** : 파일에 쓰기/읽기를 합니다 (printf/scanf의 파일 버전).
- **fclose** : 파일을 닫아서 자원을 해제합니다.
- 이 코드는 함수 호출 형태만 보여주는 **뼈대 코드**로, 실제 실행되지는 않습니다.

---

### 3.2 텍스트 파일에 한 줄 쓰기

```c
#include <stdio.h>

int main()
{
	FILE* pf = NULL;

	//1. 파일 열기(생성)
	fopen_s(&pf, "test.txt", "wt");
	//2. 파일 쓰기
	fprintf(pf, "Hello!\n");
	//3. 파일 닫기
	fclose(pf);
}
```

**설명**
- `fopen_s(&pf, "test.txt", "wt")` : "test.txt" 파일을 **텍스트 쓰기 모드**(`"wt"`)로 엽니다.
  - `"w"` : 쓰기 모드 (파일이 없으면 생성, 있으면 내용을 지우고 새로 씀).
  - `"t"` : 텍스트 모드 (기본값, 생략 가능).
  - `fopen_s`는 MSVC(Visual Studio)에서 제공하는 보안 강화 버전입니다.
- `fprintf(pf, "Hello!\n")` : 파일 포인터 `pf`가 가리키는 파일에 "Hello!\n"을 씁니다. `printf`와 거의 같지만, 첫 번째 인자가 파일 포인터입니다.
- `fclose(pf)` : 파일을 닫습니다. **반드시 닫아야** 데이터가 확실히 저장됩니다.

---

### 3.3 여러 타입의 데이터를 텍스트 파일에 쓰기

```c
#include <stdio.h>

int main()
{
	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wt");
	if (pf != NULL)
	{
		fprintf(pf, "Hello!\n");
		int n = 100;
		fprintf(pf, "%d\n", n);
		double d = 2.5;
		fprintf(pf, "%g\n", d);

		fclose(pf);
	}
}
```

**설명**
- `if (pf != NULL)` : 파일 열기에 **실패**하면 `pf`가 `NULL`이 됩니다. 반드시 확인해야 프로그램이 비정상 종료되지 않습니다.
- 문자열, 정수(`%d`), 실수(`%g`)를 각각 한 줄씩 파일에 씁니다.
- 텍스트 모드에서는 데이터가 **사람이 읽을 수 있는 문자열**로 저장됩니다.

**생성되는 test.txt 내용**
```
Hello!
100
2.5
```

---

## 4. 텍스트 파일 읽기

### 4.1 fprintf로 쓰고 fscanf_s로 읽기

```c
#include <stdio.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;
	fopen_s(&pf, "test.txt", "w");
	{
		int ndata = 100;
		double ddata = 2.55;
		const char* sdata = "Hello!";

		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
	}
	fclose(pf);

	fopen_s(&pf, "test.txt", "r");
	{
		int ndata = 0;
		double ddata = 0;
		char sdata[100];

		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
		printf("read : %d %g %s\n", ndata, ddata, sdata);
		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
		printf("read : %d %g %s\n", ndata, ddata, sdata);
		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
		printf("read : %d %g %s\n", ndata, ddata, sdata);
	}
	fclose(pf);
}
```

**설명**
- **쓰기**: `fprintf`로 `int`, `double`, `char*`를 공백으로 구분하여 한 줄에 씁니다.
- **읽기**: `fscanf_s`로 형식에 맞게 읽어들입니다.
  - `%d` → `int*` (`&ndata`), `%lf` → `double*` (`&ddata`), `%s` → `char[]` (`sdata`).
  - `fscanf_s`의 `%s`에는 버퍼 크기(100)를 추가 인자로 전달해야 합니다 (보안 강화).
- 같은 파일 포인터 `pf`를 재사용하지만, 쓰기 후 `fclose` → 다시 `fopen_s`로 읽기 모드(`"r"`)로 엽니다.

**예상 출력**
```
read : 100 2.55 Hello!
read : 100 2.55 Hello!
read : 100 2.55 Hello!
```

---

### 4.2 fprintf로 쓰고 fgets로 줄 단위 읽기

```c
#include <stdio.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;
	fopen_s(&pf, "test.txt", "w");
	{
		int ndata = 100;
		double ddata = 2.55;
		const char* sdata = "Hello!";

		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
	}
	fclose(pf);

	fopen_s(&pf, "test.txt", "r");
	{
		int ndata = 0;
		double ddata = 0;
		char sdata[100];

		fgets(sdata, 100, pf);
		printf("read : %s", sdata);
		fgets(sdata, 100, pf);
		printf("read : %s", sdata);
		fgets(sdata, 100, pf);
		printf("read : %s", sdata);
	}
	fclose(pf);
}
```

**설명**
- `fgets(sdata, 100, pf)` : 파일에서 **한 줄**(또는 최대 99자)을 읽어 `sdata`에 저장합니다.
- `fgets`는 **줄바꿈(`\n`)까지 포함**해서 읽으므로, `printf`에서 `\n`을 추가로 넣지 않아도 됩니다.
- `fscanf`와 차이: `fscanf`는 형식에 맞게 **파싱**하고, `fgets`는 줄 전체를 **문자열 그대로** 가져옵니다.

**예상 출력**
```
read : 100 2.55 Hello!
read : 100 2.55 Hello!
read : 100 2.55 Hello!
```

---

## 5. 텍스트 모드 vs 바이너리 모드 (CR/LF)

### 5.1 CR과 LF의 코드 값

```c
#include <stdio.h>
#include <string.h>

int main()
{
	printf("%d %d\n", '\r', '\n');

	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "w");

	char arr[2] = { 10 };
	fwrite(arr, 1, sizeof(char), pf);

	fclose(pf);
}
```

**설명**
- `'\r'`(CR, Carriage Return) = **13**, `'\n'`(LF, Line Feed) = **10**.
- Windows에서 줄바꿈은 **CR+LF**(13, 10) 2바이트로 표현됩니다.
- `arr[0] = 10` → `'\n'` 값입니다.
- **텍스트 모드**(`"w"`)로 열면, `'\n'`(10)을 쓸 때 OS가 자동으로 **CR+LF**(13, 10) 2바이트로 변환합니다.
- 결과: 1바이트를 썼는데 파일에는 **2바이트**가 저장될 수 있습니다.

**예상 출력 (콘솔)**
```
13 10
```

---

### 5.2 바이너리 모드로 쓰기

```c
#include <stdio.h>
#include <string.h>

int main()
{
	printf("%d %d\n", '\r', '\n');

	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wb");

	char arr[2] = { 10 };
	fwrite(arr, 1, sizeof(char), pf);

	fclose(pf);
}
```

**설명**
- `"wb"` : **바이너리 쓰기 모드**로 열면, CR/LF 변환이 일어나지 않습니다.
- `'\n'`(10)을 쓰면 파일에 **정확히 1바이트**(값 10)만 저장됩니다.
- 바이너리 데이터를 저장할 때는 반드시 `"wb"`/`"rb"`를 사용해야 데이터가 변형되지 않습니다.

| 모드 | 플래그 | CR/LF 변환 | 용도 |
|------|--------|-------------|------|
| **텍스트** | `"w"`, `"r"`, `"wt"`, `"rt"` | O (자동 변환) | 사람이 읽는 텍스트 파일 |
| **바이너리** | `"wb"`, `"rb"` | X (변환 없음) | 이진 데이터, 이미지, 커스텀 포맷 |

---

## 6. 바이너리 파일 입출력 (fwrite / fread)

### 6.1 fwrite로 여러 타입 데이터 저장

```c
#include <stdio.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;

	fopen_s(&pf, "test.txt", "wb");
	if (pf != NULL)
	{
		const char* s = "Hello!\n";
		fwrite(s, 1, strlen(s) + 1, pf);
		int n = 100;
		fwrite(&n, 1, sizeof(int), pf);
		double d = 2.5;
		fwrite(&d, 1, sizeof(double), pf);

		fclose(pf);
	}
}
```

**설명**
- `fwrite(데이터주소, 항목크기, 항목수, 파일포인터)` : 메모리의 내용을 **그대로** 파일에 씁니다.
- `fwrite(s, 1, strlen(s)+1, pf)` : 문자열 + 널 종료 문자(`\0`)까지 포함하여 저장합니다.
- `fwrite(&n, 1, sizeof(int), pf)` : `int` 변수의 **4바이트**를 그대로 저장합니다.
- `fwrite(&d, 1, sizeof(double), pf)` : `double` 변수의 **8바이트**를 그대로 저장합니다.
- 바이너리 모드이므로 파일에 저장된 내용은 텍스트 에디터로 열면 읽을 수 없지만, **정확한 값**이 보존됩니다.

---

## 7. 커스텀 바이너리 파일 포맷 (.ati)

실전에서는 여러 타입의 데이터를 하나의 파일에 저장하기 위해 **자체 파일 포맷**을 설계합니다. 이 절에서는 헤더(header)와 바디(body)로 구성된 커스텀 포맷을 구현합니다.

### 7.1 커스텀 포맷 - 쓰기만 구현

```c
#include <stdio.h>
#include <string.h>

int main()
{
	FILE* pf = NULL;
	fopen_s(&pf, "..\\test.ati", "wb");
	{
		//header
		{
			char logo[2] = { 'M','F' };
			unsigned short empty = 0;
			fwrite(logo, 1, sizeof(char) * 2, pf);
			fwrite(&empty, 1, sizeof(unsigned short), pf);
			int dataCount = 4;
			fwrite(&dataCount, 1, sizeof(int), pf);
		}
		//body
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
		// (아직 읽기 부분은 구현하지 않음)
	}
	fclose(pf);
}
```

**설명**

이 예제는 커스텀 포맷의 **쓰기 부분**만 완성한 중간 단계입니다.

**파일 헤더 구조 (8바이트)**

| 오프셋 | 크기 | 내용 | 설명 |
|--------|------|------|------|
| 0 | 2 | `'M'`, `'F'` | 파일 식별 로고 (매직 넘버) |
| 2 | 2 | `0` | 예약 영역 |
| 4 | 4 | `4` | 데이터 개수 |

**파일 바디 구조 (데이터별 반복)**

| 타입 코드 | 저장 형태 |
|-----------|-----------|
| `'I'` (int) | `[타입 1바이트][int 4바이트]` |
| `'D'` (double) | `[타입 1바이트][double 8바이트]` |
| `'S'` (string) | `[타입 1바이트][길이 4바이트][문자열 데이터]` |

- 각 데이터 앞에 **타입 코드**(1바이트)를 넣어서, 읽을 때 어떤 타입인지 판별할 수 있습니다.
- 문자열은 길이가 가변이므로, 길이 정보(`slen`)를 먼저 저장합니다.

---

### 7.2 커스텀 포맷 - 쓰기 + 읽기 완성 (최종 버전)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE* pf = NULL;
	fopen_s(&pf, "..\\test.ati", "wb");
	{
		//header
		{
			char logo[2] = { 'M','F' };
			unsigned short empty = 0;
			fwrite(logo, 1, sizeof(char) * 2, pf);
			fwrite(&empty, 1, sizeof(unsigned short), pf);
			int dataCount = 4;
			fwrite(&dataCount, 1, sizeof(int), pf);
		}
		//body
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
		//file header
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
		//file body
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

이 예제는 커스텀 `.ati` 파일 포맷의 **최종 완성본**으로, 쓰기와 읽기를 모두 구현합니다.

**읽기 과정 — 헤더 파싱**
1. `fread(header, 1, 8, pf)` : 헤더 8바이트를 한 번에 읽습니다.
2. `header[0]=='M' && header[1]=='F'` : **매직 넘버** 검증. 올바른 파일 포맷인지 확인합니다.
3. `*(int*)(header + 4)` : 헤더의 오프셋 4부터 4바이트를 `int`로 **캐스팅**하여 데이터 개수를 얻습니다.

**읽기 과정 — 바디 파싱**
1. 데이터 개수(`dataCount`)만큼 **반복**합니다.
2. 먼저 **타입 코드**(1바이트)를 읽습니다.
3. `switch`문으로 타입에 따라 다르게 처리합니다:
   - `'I'` : `int` 4바이트를 읽어 출력.
   - `'D'` : `double` 8바이트를 읽어 출력.
   - `'S'` : 먼저 길이(`slen`)를 읽고, `malloc`으로 동적 할당한 뒤 문자열을 읽어 출력, `free`로 해제.

**핵심 포인트**
- `malloc(slen)` : 문자열 길이가 **가변**이므로 **동적 메모리 할당**이 필요합니다.
- `free(buf)` : 동적 할당한 메모리는 **반드시 해제**해야 합니다.
- 타입 코드를 먼저 저장/읽는 방식은 **TLV(Type-Length-Value)** 패턴의 간단한 형태입니다.

**예상 출력**
```
int : 100
double : 2.6
string : Hello!
int : 25
```

---

## 8. 정리 표

### 8.1 공용체(Union)와 비트필드

| 주제 | 내용 |
|------|------|
| **union 선언** | `typedef union { int n; char arr[4]; } Data;` |
| **union 크기** | 가장 큰 멤버의 크기 = 전체 크기 |
| **union 특성** | 모든 멤버가 같은 메모리 주소를 공유 |
| **비트필드 선언** | `unsigned int a1 : 비트수;` |
| **비트필드 용도** | 비트 단위 데이터 조작, 플래그 관리, 하드웨어 레지스터 |

### 8.2 파일 입출력

| 주제 | 내용 |
|------|------|
| **파일 3단계** | 열기(`fopen`) → 읽기/쓰기 → 닫기(`fclose`) |
| **파일 포인터** | `FILE* pf;` |
| **파일 열기** | `fopen_s(&pf, "파일명", "모드");` |
| **텍스트 쓰기** | `fprintf(pf, "서식", 값들);` |
| **텍스트 읽기** | `fscanf_s(pf, "서식", &변수들);` 또는 `fgets(buf, size, pf);` |
| **바이너리 쓰기** | `fwrite(주소, 1, 크기, pf);` |
| **바이너리 읽기** | `fread(주소, 1, 크기, pf);` |
| **텍스트 모드** | `"w"`, `"r"` — CR/LF 자동 변환 |
| **바이너리 모드** | `"wb"`, `"rb"` — 변환 없이 원본 그대로 |
| **동적 할당 읽기** | 가변 크기 데이터는 `malloc`으로 할당 후 `fread`, 사용 후 `free` |

### 8.3 파일 열기 모드 정리

| 모드 | 설명 |
|------|------|
| `"r"` | 읽기 전용 (파일이 없으면 실패) |
| `"w"` | 쓰기 전용 (파일이 없으면 생성, 있으면 덮어씀) |
| `"a"` | 추가 쓰기 (파일 끝에 이어 씀) |
| `"rb"` | 바이너리 읽기 |
| `"wb"` | 바이너리 쓰기 |
| `"wt"` | 텍스트 쓰기 (`"w"`와 동일) |

---

## 9. 예제 발전 과정 요약

ex19.cpp는 아래에서 위로 갈수록 발전하는 구조입니다. 학습 순서를 정리하면:

| 단계 | 주제 | 핵심 내용 |
|------|------|-----------|
| 1 | 비트필드 기초 | 비트 단위 멤버 선언, 비트 연산 |
| 2 | 공용체(union) | 메모리 공유, 타입 재해석, sizeof |
| 3 | 파일 I/O 뼈대 | fopen / fprintf / fclose 3단계 |
| 4 | 텍스트 파일 쓰기 | fprintf로 다양한 타입 저장 |
| 5 | 텍스트 파일 읽기 | fscanf_s(형식 파싱) vs fgets(줄 단위) |
| 6 | CR/LF 이해 | 텍스트 모드와 바이너리 모드 차이 |
| 7 | 바이너리 쓰기 | fwrite로 메모리 내용을 그대로 저장 |
| 8 | 커스텀 포맷 (쓰기) | 헤더 + 타입 코드 + 바디 설계 |
| 9 | 커스텀 포맷 (읽기) | 매직 넘버 검증, switch 타입 분기, malloc 동적 할당 |

---

## 10. 연습 문제 (스스로 풀어보기)

1. `union`을 선언하여 `int n`에 `0x41424344`를 넣고, `char arr[4]`로 각 바이트를 문자(`%c`)와 16진수(`%x`)로 출력해 보세요. 리틀 엔디안에서 어떤 순서로 출력되는지 확인하세요.

2. 비트필드 구조체를 만들어 `unsigned int r:8, g:8, b:8, a:8;` 형태로 RGBA 색상을 표현해 보세요. `r=255, g=128, b=0, a=255`를 넣고 `%08X`로 출력해 보세요.

3. 텍스트 파일에 자신의 이름, 나이, 키를 `fprintf`로 저장한 뒤, `fscanf_s`로 읽어서 화면에 출력하는 프로그램을 작성해 보세요.

4. `fwrite`로 `int` 배열 `{10, 20, 30, 40, 50}`을 바이너리 파일에 저장한 뒤, `fread`로 읽어서 출력하는 프로그램을 작성해 보세요.

5. 7.2절의 커스텀 포맷을 확장하여, 새로운 타입 코드 `'F'`(float)를 추가해 보세요. 쓰기와 읽기 모두 구현해야 합니다.

---

이 강의 자료는 **example/ex19.cpp**에 있는 모든 예제(활성 코드와 주석 처리된 예제)를 바탕으로 구성했습니다. 가장 아래의 비트필드/공용체부터 시작하여, 파일 I/O 기초 → 텍스트/바이너리 모드 → 커스텀 바이너리 포맷까지 단계적으로 발전하는 흐름입니다. 각 예제를 직접 타이핑해서 실행해 보면 이해에 큰 도움이 됩니다.
