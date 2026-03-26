#include <stdio.h>
#include <stdlib.h>
//Application ¿µ¿ª
//Point.c
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
// PointArray.c
// Point*AllocPointArray(Point* p, int cap)
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
// Main ¿µ¿ª
int main()
{
	Point* pa = NULL;
	AllocPointArray(&pa, 10);

	InitPointArray(pa, 10);
	PrintPointArray(pa, 10);

	FreePointArray(pa);
}

//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//// Point*AllocPointArray(Point* p, int cap)
//void AllocPointArray(Point** pp, int cap)
//{
//	*pp = (Point*)malloc(sizeof(Point) * cap);
//}
//void FreePointArray(Point pa[])
//{
//	free(pa);
//}
//void InitPointArray(Point pa[], int size)
//{
//	for (int i = 0; i < size; ++i)
//		SetPoint(&pa[i], i + 1, i + 1);
//}
//void PrintPointArray(const Point pa[], int size)
//{
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//}
//int main()
//{
//	Point* pa = NULL;
//	AllocPointArray(&pa, 10);
//
//	InitPointArray(pa, 10);
//	PrintPointArray(pa, 10);
//
//	FreePointArray(pa);
//}

//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//Point* AllocPointArray(int cap)
//{
//	return (Point*)malloc(sizeof(Point) * cap);
//}
//void FreePointArray(Point pa[])
//{
//	free(pa);
//}
//void InitPointArray(Point pa[], int size)
//{
//	for (int i = 0; i < size; ++i)
//		SetPoint(&pa[i], i + 1, i + 1);
//}
//void PrintPointArray(const Point pa[], int size)
//{
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//}
//int main()
//{
//	Point* pa = AllocPointArray(10);
//
//	InitPointArray(pa, 10);
//	PrintPointArray(pa, 10);
//
//	FreePointArray(pa);
//}

//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//Point* AllocPointArray(int cap)
//{
//	return (Point*)malloc(sizeof(Point) * cap);
//}
//void FreePointArray(Point* pa)
//{
//	free(pa);
//}
//void InitPointArray(Point* pa, int size)
//{
//	for (int i = 0; i < size; ++i)
//		SetPoint(&pa[i], i + 1, i + 1);
//}
//void PrintPointArray(const Point* pa, int size)
//{
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//}
//int main()
//{
//	Point* pa = AllocPointArray(10);
//
//	InitPointArray(pa, 10);
//	PrintPointArray(pa, 10);
//
//	FreePointArray(pa);
//}

//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//int main()
//{
//	Point* pa = (Point*)malloc(sizeof(Point) * 10);
//
//	for (int i = 0; i < 10; ++i)
//		SetPoint(&pa[i], i + 1, i + 1);
//	
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//
//	free(pa);
//}

//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//int main()
//{	
//	Point* pa = (Point*)malloc(sizeof(Point)*10);
//
//	for (int i = 0; i < 10; ++i)
//	{
//		pa[i].x = i + 1;
//		pa[i].y = i + 1;
//	}
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//
//	free(pa);
//}

//#include <stdio.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(const Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//int main()
//{
//	Point pt = { 2,3 };
//	Point ptArray[10] = { {1,1},{2,2},{3,3} };
//	Point* pa = ptArray;
//
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&ptArray[i]);
//	printf("\n");
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//}

//#include <stdio.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(Point* p)
//{
//	printf("(%d, %d)\n", p->x, p->y);
//}
//int main()
//{
//	Point pt = { 2,3 };
//	Point ptArray[10] = { {1,1},{2,2},{3,3} };
//	Point* pa = ptArray;
//
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&ptArray[i]);
//	printf("\n");
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(&pa[i]);
//}

//#include <stdio.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//int main()
//{
//	Point pt = { 2,3 };
//	Point ptArray[10] = { {1,1},{2,2},{3,3} };
//	Point* pa = ptArray;
//
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(ptArray[i]);
//	printf("\n");
//	for (int i = 0; i < 10; ++i)
//		PrintPoint(pa[i]);
//}

//#include <stdio.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//int main()
//{
//	Point pt = { 2,3 };
//	Point ptArray[10] = { {1,1},{2,2},{3,3} };
//	Point* pa = ptArray;
//
//	for (int i = 0; i < 10; ++i)
//		printf("(%d, %d)\n", ptArray[i].x, ptArray[i].y);
//	for (int i = 0; i < 10; ++i)
//		printf("(%d, %d)\n", pa[i].x, pa[i].y);
//}

//#include <stdio.h>
//typedef struct _Point //±¸Á¶Ã¼ Point Á¤ÀÇ
//{
//	int x; //±¸Á¶Ã¼ PointÀÇ ¸â¹ö x
//	int y;
//} Point, * PPoint; // struct _Point ±¸Á¶Ã¼ÀÇ ÀÌ¸§ Point
////struct _Point * ±¸Á¶Ã¼ Æ÷ÀÎÅÍ ÀÌ¸§ PPoint
//
//int main()
//{
//	Point pt = { 2,3 };
//	PPoint p = &pt;
//
//	printf("%d, %d\n", pt.x, pt.y);
//	printf("%d, %d\n", p->x, p->y);
//}

//#include <stdio.h>
//typedef struct _Point //±¸Á¶Ã¼ Point Á¤ÀÇ
//{
//	int x; //±¸Á¶Ã¼ PointÀÇ ¸â¹ö x
//	int y;
//} Point, *PPoint; // struct _Point ±¸Á¶Ã¼ÀÇ ÀÌ¸§ Point
////struct _Point * ±¸Á¶Ã¼ Æ÷ÀÎÅÍ ÀÌ¸§ PPoint
//
//int main()
//{
//	Point pt = { 2,3 };
//	PPoint p = &pt;
//
//	printf("%d, %d\n", pt.x, pt.y);
//	printf("%d, %d\n", p->x, p->y);
//}

//#include <stdio.h>
//typedef struct _Point
//{
//	int x;
//	int y;
//} Point;
//void PrintPoint(Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//int main()
//{
//	struct _Point pt = { 2,3 };
//
//	SetPoint(&pt, 4, 5);
//	PrintPoint(pt);
//
//	Point* p = &pt;
//	printf("%d , %d\n", p->x, p->y);
//}

//#include <stdio.h>
//struct _Point
//{
//	int x;
//	int y;
//};
//typedef struct _Point Point;
//void PrintPoint(Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//void SetPoint(Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//int main()
//{
//	Point pt = { 2,3 };
//
//	SetPoint(&pt, 4, 5);
//	PrintPoint(pt);
//
//	Point* p = &pt;
//	printf("%d , %d\n", p->x, p->y);
//}

//#include <stdio.h>
//struct Point
//{
//	int x;
//	int y;
//};
//void PrintPoint(struct Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//void SetPoint(struct Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//int main()
//{
//	struct Point pt = { 2,3 };
//
//	SetPoint(&pt, 4, 5);
//	PrintPoint(pt);
//
//	struct Point* p = &pt;
//	printf("%d , %d\n", p->x, p->y);
//}

//#include <stdio.h>
//struct Point
//{
//	int x;
//	int y;
//};
//void PrintPoint(struct Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//void SetPoint(struct Point* p, int x, int y)
//{
//	p->x = x;
//	p->y = y;
//}
//int main()
//{
//	struct Point pt = { 2,3 };
//
//	SetPoint(&pt, 4, 5);
//	PrintPoint(pt);
//}

//#include <stdio.h>
//struct Point
//{
//	int x;
//	int y;
//};
//void PrintPoint(struct Point pt)
//{
//	printf("(%d, %d)\n", pt.x, pt.y);
//}
//void SetPoint(struct Point* p, int x, int y)
//{
//	(*p).x = x;
//	(*p).y = y;
//}
//int main()
//{
//	struct Point pt = { 2,3 };
//
//	SetPoint(&pt, 4, 5);
//	PrintPoint(pt);
//}

//#include <stdio.h>
//struct Point
//{
//	int x;
//	int y;
//};
//int main()
//{
//	struct Point pt= { 2,3 };
//
//	printf("(%d, %d)\n", pt.x, pt.y);
//}

//#include <stdio.h>
//struct Point
//{
//	double x;
//	double y;
//};
//int main()
//{
//	int n = 10;
//	struct Point k = { 2,3 };
//
//	printf("int size : %d\n", sizeof(n));
//	printf("Point size : %d\n", sizeof(k));
//	printf("x size : %d\n", sizeof(k.x));
//	printf("%d\n", n);
//	printf("(%g,%g)\n", k.x, k.y);
//}

//#include <stdio.h>
//struct Point
//{
//	double x;
//	double y;
//};
//int main()
//{
//	int n = 10;
//	struct Point k = { 2,3 };
//
//	printf("int size : %d\n", sizeof(n));
//	printf("Point size : %d\n", sizeof(k));
//	printf("%d\n", n);
//	printf("(%g,%g)\n", k.x, k.y);
//}


//#include <stdio.h>
//struct Point
//{
//	double x;
//	double y;
//};
//int main()
//{
//	int n = 10;
//	struct Point k = { 2,3 };
//
//	printf("int size : %d\n", sizeof(n));
//	printf("Point size : %d\n", sizeof(k));
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	printf("%d\n", strlen("ABC"));
//	printf("%d\n", strlen("È«±æµ¿"));
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	char* s = "È«±æµ¿";
//	char a[] = "È«±æµ¿";
//	char* h = (char*)malloc(100);
//
//	s = "È«±æ´ç";
//	strcpy_s(a, strlen("È«±æ´ç") + 1, "È«±æ´ç");
//	//h = "È«±æ´ç"; //X
//	strcpy_s(h, strlen("È«±æ´ç") + 1, "È«±æ´ç");
//
//	printf("name : %s\n", s);
//	printf("name : %s\n", a);
//	printf("name : %s\n", h);
//
//	free(h);
//}

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main()
//{
//	char* s = "È«±æµ¿";
//	char a[] = "È«±æµ¿";
//	char* h = (char*)malloc(100);
//
//	s = "È«±æ´ç";
//	strcpy_s(a, strlen("È«±æ´ç") + 1, "È«±æ´ç");
//	h = "È«±æ´ç";
//
//	printf("name : %s\n", s);
//	printf("name : %s\n", a);
//	printf("name : %s\n", h);
//
//	//free(h);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	char* s = "È«±æµ¿";
//	char a[] = "È«±æµ¿";
//
//	s = "È«±æ´ç";
//	//a = "È«±æ´ç";
//	strcpy_s(a, strlen("È«±æ´ç")+1, "È«±æ´ç");
//	printf("name : %s\n", s);
//	printf("name : %s\n", a);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "È«±æµ¿";
//	char a[] = "È«±æµ¿";
//	
//	printf("name : %s\n", s);
//	printf("name : %s\n", a);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABCD";
//	char a[] = "ABCD";
//
//	printf("%s %s %s\n", s, a, "ABCD");
//	printf("%c %c %c\n", s[1], a[1], "ABCD"[1]);
//}

//#include <stdio.h>
//int main()
//{
//	char* s = "ABCD";
//	char a[] = "ABCD";
//
//	printf("%p %s\n", s, s);
//	printf("%p %s\n", a, a);
//	printf("%c %d\n", s[0], s[0]);
//	printf("%c %d\n", a[0], a[0]);
//	s[0] = 'H'; // X
//	a[0] = 'H'; // O
//}

//#include <stdio.h>
//#include <stdlib.h> //
//void PrintArray(const int pa[], int size) //int* pa , int pa[1000]
//{
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//}
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	int* pa = arr;
//
//	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//	PrintArray(arr, 5);
//
//	printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
//}

//#include <stdio.h>
//#include <stdlib.h> //
//void PrintArray(int pa[], int size) //int* pa , int pa[1000]
//{
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//}
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	int* pa = arr;
//
//	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//	PrintArray(arr, 5);
//
//	printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
//}

//#include <stdio.h>
//#include <stdlib.h> //
//void PrintArray(int* pa, int size)
//{
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//}
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	int* pa = arr;
//
//	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//	PrintArray(arr, 5);
//
//	printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
//}

//#include <stdio.h>
//#include <stdlib.h> //
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//	int* pa = arr;
//
//	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
//	printf("%d %d %d %d %d\n", pa[0], pa[1], pa[2], pa[3], pa[4]);
//	printf("%p %p %p %p %p\n", arr, arr + 1, arr + 2, arr + 3, arr + 4);
//}

//#include <stdio.h>
//#include <stdlib.h> //
//int main()
//{
//	int arr[5] = { 10,20,30,40,50 };
//
//	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
//	printf("%p %p %p %p %p\n", arr, arr+1, arr+2, arr+3, arr+4);
//}

//#include <stdio.h>
//#include <stdlib.h> //
//int main()
//{
//	int arr[5] = { 0 };
//	int* pa = (int*)malloc(sizeof(int) * 5);
//	for (int i = 0; i < 5; ++i)
//	{
//		arr[i] = (i + 1) * 10;
//		pa[i] = (i + 1) * 10;
//	}
//
//	for (int i = 0; i < 5; ++i)
//		printf("%d %d\n", arr[i], pa[i]);
//
//	free(pa);
//}

//#include <stdio.h>
//void PrintChar(char* pc)
//{
//	printf("char : %c\n", *pc);
//}
//void PrintInt(int* pn)
//{
//	printf("int : %d\n", *pn);
//}
//int main()
//{
//	char c = 'A';
//	int n = 100;
//
//	char* pc = &c;
//	int* pn = &n;
//
//	printf("char : %c\n", *pc);
//	PrintChar(&c);
//	printf("int : %d\n", *pn);
//	PrintInt(&n);
//}

//#include <stdio.h>
//void PrintChar(char* pc)
//{
//	printf("char : %c\n", *pc);
//}
//void PrintInt(int* pn)
//{
//	printf("int : %d\n", *pn);
//}
//int main()
//{
//	char c = 'A';
//	int n = 100;
//
//	char* pc = &c;
//	int* pn = &n;
//
//	printf("char : %c\n", *pc);
//	PrintChar(&c);
//	printf("int : %d\n", *pn);
//	PrintInt(&n);
//}
