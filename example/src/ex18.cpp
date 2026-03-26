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

//#include <stdio.h>
//enum {
//	A=100,
//	B,
//	C,
//	D,
//	E,
//	F,
//	G,
//	H
//};
//int main()
//{
//	printf("%d\n", A);
//	printf("%d\n", B);
//	printf("%d\n", C);
//	printf("%d\n", D);
//	printf("%d\n", E);
//	printf("%d\n", F);
//}

//#include <stdio.h>
//enum {
//	A = 0x1,
//	B = 0x2,
//	C = 0x4,
//	D = 0x8,
//	E = 0x10,
//	F = 0x20,
//	G = 0x40,
//	H = 0x80
//};
//int main()
//{
//	A = 10;
//	printf("%d\n", A);
//	printf("%d\n", B);
//	printf("%d\n", C);
//	printf("%d\n", D);
//	printf("%d\n", E);
//	printf("%d\n", F);
//}

//#include <stdio.h>
//const int A = 0x1;//(16Áø¼ö)
//const int B = 0x2;
//const int C = 0x4;
//const int D = 0x8;
//const int E = 0x10;
//const int F = 0x20;
//const int G = 0x40;
//const int H = 0x80;
//int main()
//{
//	unsigned int data = 0;
//
//	printf("%08x\n", data);
//	data |= C;
//	printf("%08x\n", data);
//	data |= B;
//	printf("%08x\n", data);
//	data |= A; //set
//	printf("%08x\n", data);
//	data &= ~C; //off
//	printf("%08x\n", data);
//	data ^= B; //togle
//	printf("%08x\n", data);
//}

//#include <stdio.h>
//const int A = 0x1;
//const int B = 0x2;
//const int C = 0x4;
//const int D = 0x8;
//const int E = 0x16;
//int main()
//{
//	unsigned int data = 0;
//
//	printf("%08x\n", data);
//	data |= C;
//	printf("%08x\n", data);
//	data |= C;
//	printf("%08x\n", data);
//	data |= B;
//	printf("%08x\n", data);
//	data |= A;
//	printf("%08x\n", data);
//	data &= ~C;
//	printf("%08x\n", data);
//}


//#include <stdio.h>
//const int A = 0x1;
//const int B = 0x2;
//const int C = 0x4;
//const int D = 0x8;
//const int E = 0x16;
//int main()
//{
//	unsigned int data = 0;
//
//	printf("%08x\n", data);
//	data |= C;
//	printf("%08x\n", data);
//	data |= C;
//	printf("%08x\n", data);
//}

//#include <stdio.h>
//int main()
//{
//	int a = -32;
//
//	printf("%d %x\n", a >> 0, a >> 0);
//	printf("%d %x\n", a >> 1, a >> 1);
//	printf("%d %x\n", a >> 2, a >> 2);
//	printf("%d %x\n", a >> 3, a >> 3);
//	printf("%d %x\n", a >> 4, a >> 4);
//	printf("%d %x\n", a >> 5, a >> 5);
//	printf("%d %x\n", a >> 6, a >> 6);
//	printf("%d %x\n", a >> 7, a >> 7);
//}


//#include <stdio.h>
//int main()
//{
//	int a = 2;
//
//	printf("%d %x\n", a << 0, a << 0);
//	printf("%d %x\n", a << 1, a << 1);
//	printf("%d %x\n", a << 2, a << 2);
//	printf("%d %x\n", a << 3, a << 3);
//	printf("%d %x\n", a << 4, a << 4);
//}

//#include <stdio.h>
//int main()
//{
//	//char c = 255;
//	unsigned char c = 255;
//
//	printf("%d %x\n", c, c);
//}

//#include <stdio.h>
//int main()
//{
//	unsigned char c = 128;
//
//	printf("%d %x\n", c, c);
//}

//#include <stdio.h>
//int main()
//{
//	char c = 128;
//
//	printf("%d %x\n", c, c);
//}

//#include <stdio.h>
//int main()
//{
//	char c = 127;
//
//	printf("%d %x\n", c, c);
//}

//#include <stdio.h>
//int main()
//{
//	int a = 5;
//	int b = 6;
//
//	printf("%x\n", a & b);
//	printf("%x\n", a | b);
//	printf("%x\n", a ^ b);
//	printf("%x\n", ~a);
//	printf("%x\n", ~b);
//	printf("\n");
//	printf("%d\n", a & b);
//	printf("%d\n", a | b);
//	printf("%d\n", a ^ b);
//	printf("%d\n", ~a);
//	printf("%d\n", ~b);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//void FreePerson(Person* p)
//{
//	free(p->name);
//	free(p->phone);
//
//	free(p);
//}
//Person* AllocPerson()
//{
//	return  (Person*)malloc(sizeof(Person));
//}
//int main()
//{
//	Person* per1 = 0;
//	Person* per2 = 0;
//
//	per1 = AllocPerson();
//	per2 = AllocPerson();
//
//	SetPersonName(per1, "È«±æ´ç");
//	SetPersonPhone(per1, "010-1212-3434");
//	SetPersonName(per2, "Àå±æ»ê");
//	SetPersonPhone(per2, "010-2345-6543");
//
//	PrintPerson(per1);
//	PrintPerson(per2);
//
//	FreePerson(per1);
//	FreePerson(per2);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//void FreePerson(Person* p)
//{
//	free(p->name);
//	free(p->phone);
//
//	free(p);
//}
//Person* AllocPerson()
//{
//	return  (Person*)malloc(sizeof(Person));
//}
//int main()
//{
//	Person* per1 = 0;
//	Person* per2 = 0;
//
//	per1 = AllocPerson();
//	per2 = AllocPerson();
//
//	SetPersonName(per1, "È«±æ´ç");
//	SetPersonPhone(per1, "010-1212-3434");
//	SetPersonName(per2, "Àå±æ»ê");
//	SetPersonPhone(per2, "010-2345-6543");
//
//	PrintPerson(per1);
//	PrintPerson(per2);
//
//	FreePerson(per1);
//	FreePerson(per2);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//void FreePerson(Person* p)
//{
//	free(p->name);
//	free(p->phone);
//
//	free(p);
//}
//int main()
//{
//	Person* per1 = 0;
//	Person* per2 = 0;
//
//	per1 = (Person*)malloc(sizeof(Person));
//	per2 = (Person*)malloc(sizeof(Person));
//
//	SetPersonName(per1, "È«±æ´ç");
//	SetPersonPhone(per1, "010-1212-3434");
//	SetPersonName(per2, "Àå±æ»ê");
//	SetPersonPhone(per2, "010-2345-6543");
//
//	PrintPerson(per1);
//	PrintPerson(per2);
//
//	FreePerson(per1);
//	FreePerson(per2);
//}

//#pragma warning(disable:6387)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//void FreePerson(Person* p)
//{
//	free(p->name);
//	free(p->phone);
//}
//int main()
//{
//	Person per1 = { 0 };
//	Person per2 = { 0 };
//
//	SetPersonName(&per1, "È«±æ´ç");
//	SetPersonPhone(&per1, "010-1212-3434");
//	SetPersonName(&per2, "Àå±æ»ê");
//	SetPersonPhone(&per2, "010-2345-6543");
//
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//
//	FreePerson(&per1);
//	FreePerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//void FreePerson(Person* p)
//{
//	free(p->name);
//	free(p->phone);
//}
//int main()
//{
//	Person per1 = { 0 };
//	Person per2 = { 0 };
//
//	SetPersonName(&per1, "È«±æ´ç");
//	SetPersonPhone(&per1, "010-1212-3434");
//	SetPersonName(&per2, "Àå±æ»ê");
//	SetPersonPhone(&per2, "010-2345-6543");
//
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//
//	FreePerson(&per1);
//	FreePerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//int main()
//{
//	Person per1 = { 0 };
//	Person per2 = { 0 };
//
//	SetPersonName(&per1, "È«±æ´ç");
//	SetPersonPhone(&per1, "010-1212-3434");
//	SetPersonName(&per2, "Àå±æ»ê");
//	SetPersonPhone(&per2, "010-2345-6543");
//
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char* name;
//	char* phone;
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	p->name = (char*)malloc(strlen(name) + 1); //**
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	p->phone = (char*)malloc(strlen(phone) + 1);
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//int main()
//{
//	Person per1 = { 0 };
//	Person per2 = { 0 };
//
//	SetPersonName(&per1, "È«±æ´ç");
//	SetPersonPhone(&per1, "010-1212-3434");
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//void PrintPerson(const Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetPersonName(Person* p, const char* name)
//{
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPersonPhone(Person* p, const char* phone)
//{
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	SetPersonName(&per1, "È«±æ´ç");
//	SetPersonPhone(&per1, "010-1212-3434");
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//void PrintPerson(Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//void SetName(Person* p, const char* name)
//{
//	strcpy_s(p->name, strlen(name) + 1, name);
//}
//void SetPhone(Person* p, const char* phone)
//{
//	strcpy_s(p->phone, strlen(phone) + 1, phone);
//}
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	SetName(&per1, "È«±æ´ç");
//	SetPhone(&per1, "010-1212-3434");
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//void PrintPerson(Person* p)
//{
//	printf("name: %s, phone: %s\n", p->name, p->phone);
//}
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	//per1.name = "È«±æ´ç";
//	strcpy_s(per1.name, strlen("È«±æ´ç") + 1, "È«±æ´ç");
//	strcpy_s(per1.phone, strlen("010-1212-3434") + 1, "010-1212-3434");
//	PrintPerson(&per1);
//	PrintPerson(&per2);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	//per1.name = "È«±æ´ç";
//	strcpy_s(per1.name, strlen("È«±æ´ç") + 1, "È«±æ´ç");
//	strcpy_s(per1.phone,strlen("010-1212-3434")+1, "010-1212-3434");
//	printf("name: %s, phone: %s\n", per1.name, per1.phone);
//	printf("name: %s, phone: %s\n", per2.name, per2.phone);
//}

//#include <stdio.h>
//#include <stdlib.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	printf("name: %s, phone: %s\n", per1.name, per1.phone);
//	printf("name: %s, phone: %s\n", per2.name, per2.phone);
//	printf("%d %d\n", sizeof(per1), sizeof(per1.name));
//	printf("%p %p\n", &per1, per1.name);
//	printf("%c", per1.name[20]);
//}

//#include <stdio.h>
//#include <stdlib.h>
//struct Person
//{
//	char name[20];
//	char phone[20];
//};
//int main()
//{
//	Person per1 = { "È«±æµ¿", "010-1234-1111" };
//	Person per2 = { "Àå±æ»ê", "010-4567-2222" };
//
//	printf("name: %s, phone: %s\n", per1.name, per1.phone);
//	printf("name: %s, phone: %s\n", per2.name, per2.phone);
//	printf("%d %d\n", sizeof(per1), sizeof(per1.name));
//	printf("%p %p\n", &per1, per1.name);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int** AllocMemory(int row, int col)
//{
//	int** pa = (int**)malloc(sizeof(int*) * row);
//	for (int i = 0; i < row; ++i)
//		pa[i] = (int*)malloc(sizeof(int) * col);
//
//	return pa;
//}
//void FreeMomory(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//		free(pa[i]);
//	free(pa);
//}
//void InitArray(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//		for (int j = 0; j < col; ++j)
//			pa[i][j] = i * col + j + 1;
//}
//void PrintArray(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//			printf("%3d", pa[i][j]);
//		printf("\n");
//	}
//}
//int main()
//{
//	int row = 7, col = 8;
//
//	int** pa = AllocMemory(row, col);
//
//	InitArray(pa, row, col);
//	PrintArray(pa, row, col);
//
//	FreeMomory(pa, row, col);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int** AllocMemory(int row, int col)
//{
//	int** pa = (int**)malloc(sizeof(int*) * row);
//	for (int i = 0; i < row; ++i)
//		pa[i] = (int*)malloc(sizeof(int) * col);
//
//	return pa;
//}
//void FreeMomory(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//		free(pa[i]);
//	free(pa);
//}
//void InitArray(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//		for (int j = 0; j < col; ++j)
//			pa[i][j] = i * col + j + 1;
//}
//void PrintArray(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//			printf("%3d", pa[i][j]);
//		printf("\n");
//	}
//}
//int main()
//{
//	int row = 7, col = 8;
//
//	int** pa = AllocMemory(row, col);
//
//	InitArray(pa, row, col);
//	PrintArray(pa, row, col);
//
//	FreeMomory(pa, row, col);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int** AllocMemory(int row, int col)
//{
//	int** pa = (int**)malloc(sizeof(int*) * row);
//	for (int i = 0; i < row; ++i)
//		pa[i] = (int*)malloc(sizeof(int) * col);
//
//	return pa;
//}
//void FreeMomory(int** pa, int row, int col)
//{
//	for (int i = 0; i < row; ++i)
//		free(pa[i]);
//	free(pa);
//}
//int main()
//{
//	int row = 5, col = 4;
//
//	int** pa = AllocMemory(row, col);
//
//	for (int i = 0; i < row; ++i)
//		for (int j = 0; j < col; ++j)
//			pa[i][j] = i * col + j + 1;
//
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//			printf("%3d", pa[i][j]);
//		printf("\n");
//	}
//
//	FreeMomory(pa, row, col);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//	int row = 5, col = 4;
//
//	int** pa = (int**)malloc(sizeof(int*) * row);
//
//	for(int i = 0 ; i < row ; ++i)
//		pa[i] = (int*)malloc(sizeof(int) * col);
//
//	for (int i = 0; i < row; ++i)
//		for (int j = 0; j < col; ++j)
//			pa[i][j] = i * col + j + 1;
//
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//			printf("%3d", pa[i][j]);
//		printf("\n");
//	}
//
//	for (int i = 0; i < row; ++i)
//		free(pa[i]);
//
//	free(pa);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//	int row = 5, col = 4;
//
//	int** pa = (int**)malloc(sizeof(int*) * row);
//
//	pa[0] = (int*)malloc(sizeof(int) * col);
//	pa[1] = (int*)malloc(sizeof(int) * col);
//	pa[2] = (int*)malloc(sizeof(int) * col);
//	pa[3] = (int*)malloc(sizeof(int) * col);
//	pa[4] = (int*)malloc(sizeof(int) * col);
//
//	for (int i = 0; i < row; ++i)
//		for (int j = 0; j < col; ++j)
//			pa[i][j] = i * col + j + 1;
//
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//			printf("%3d", pa[i][j]);
//		printf("\n");
//	}
//
//	free(pa[0]);
//	free(pa[1]);
//	free(pa[2]);
//	free(pa[3]);
//	free(pa[4]);
//
//	free(pa);
//}
