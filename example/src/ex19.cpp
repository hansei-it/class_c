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
			//fwrite(logo, 2, sizeof(char), pf);
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

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//	fopen_s(&pf, "..\\test.ati", "wb");
//	{
//		//header
//		{
//			char logo[2] = { 'M','F' };
//			unsigned short empty = 0;
//			//fwrite(logo, 2, sizeof(char), pf);
//			fwrite(logo, 1, sizeof(char) * 2, pf);
//			fwrite(&empty, 1, sizeof(unsigned short), pf);
//			int dataCount = 4;
//			fwrite(&dataCount, 1, sizeof(int), pf);
//		}
//		//body
//		{
//			char dtype = 'I';
//			int ndata = 100;
//			double ddata = 2.6;
//			const char* sdata = "Hello!";
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ndata, 1, sizeof(int), pf);
//
//			dtype = 'D';
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ddata, 1, sizeof(double), pf);
//
//			dtype = 'S';
//			int slen = strlen(sdata) + 1;
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&slen, 1, sizeof(int), pf);
//			fwrite(sdata, 1, slen, pf);
//
//			dtype = 'I';
//			ndata = 25;
//			fwrite(&dtype, 1, sizeof(char), pf);
//			fwrite(&ndata, 1, sizeof(int), pf);	
//		}
//	}
//	fclose(pf);
//
//	fopen_s(&pf, "..\\test.ati", "rb");
//	{
//	}
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//	fopen_s(&pf, "test.txt", "w");
//	{
//		int ndata = 100;
//		double ddata = 2.55;
//		const char* sdata = "Hello!";
//
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//	}
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "r");
//	{
//		int ndata = 0;
//		double ddata = 0;
//		char sdata[100];
//
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//	}
//	fclose(pf);
//}


//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//	fopen_s(&pf, "test.txt", "w");
//	{
//		int ndata = 100;
//		double ddata = 2.55;
//		const char* sdata = "Hello!";
//
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//	}
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "r");
//	{
//		int ndata = 0;
//		double ddata = 0;
//		char sdata[100];
//
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//		fgets(sdata, 100, pf);
//		printf("read : %s", sdata);
//	}
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//	fopen_s(&pf, "test.txt", "w");
//	{
//		int ndata = 100;
//		double ddata = 2.55;
//		const char* sdata = "Hello!";
//
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//		fprintf(pf, "%d %g %s\n", ndata, ddata, sdata);
//	}
//	fclose(pf);
//
//	fopen_s(&pf, "test.txt", "r");
//	{
//		int ndata = 0;
//		double ddata = 0;
//		char sdata[100];
//
//		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
//		printf("read : %d %g %s\n", ndata, ddata, sdata);
//		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
//		printf("read : %d %g %s\n", ndata, ddata, sdata);
//		fscanf_s(pf, "%d %lf %s", &ndata, &ddata, sdata, 100);
//		printf("read : %d %g %s\n", ndata, ddata, sdata);
//	}
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	printf("%d %d\n", '\r', '\n'); //CR + LF
//
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "w");
//
//	char arr[2] = { 10 };
//	fwrite(arr, 1, sizeof(char), pf);
//
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	printf("%d %d\n", '\r', '\n');
//
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "w");
//
//	char arr[2] = { 10 };
//	fwrite(arr, 1, sizeof(char), pf);
//
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	printf("%d %d\n", '\r', '\n');
//
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//
//	char arr[2] = { 10 };
//	fwrite(arr, 1, sizeof(char), pf);
//
//	fclose(pf);
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//	if (pf != NULL)
//	{
//		const char* s = "Hello!\n";
//		fwrite(s, 1, strlen(s) + 1, pf);
//		int n = 100;
//		fwrite(&n, 1, sizeof(int), pf);
//		double d = 2.5;
//		fwrite(&d, 1, sizeof(double), pf);
//
//		fclose(pf);
//	}
//}

//#include <stdio.h>
//#include <string.h>
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wb");
//	if (pf != NULL)
//	{
//		const char* s = "Hello!\n";
//		fwrite(s, 1, strlen(s)+1, pf);
//		int n = 100;
//		fwrite(&n, 1, sizeof(int), pf);
//		double d = 2.5;
//		fwrite(&d, 1, sizeof(double), pf);
//
//		fclose(pf);
//	}
//}

//#include <stdio.h>
//int main()
//{
//	FILE* pf = NULL;
//
//	fopen_s(&pf, "test.txt", "wt");
//	if (pf != NULL)
//	{
//		fprintf(pf, "Hello!\n");
//		int n = 100;
//		fprintf(pf, "%d\n", n);
//		double d = 2.5;
//		fprintf(pf, "%g\n", d);
//
//		fclose(pf);
//	}
//}

//#include <stdio.h>
//int main()
//{
//	FILE* pf = NULL;
//
//	//1. 파일 열기(생성)
//	fopen_s(&pf, "test.txt", "wt");
//	//2. 파일 읽기, 쓰기
//	fprintf(pf, "Hello!\n");
//	//3. 파일 닫기
//	fclose(pf);
//}

//#include <stdio.h>
//int main()
//{
//	FILE* pf = NULL;
//
//	//1. 파일 열기(생성)
//	fopen();
//	//2. 파일 읽기, 쓰기
//	fprintf();
//	fscanf();
//	//3. 파일 닫기
//	fclose();
//}


//#include <stdio.h>
//
//typedef union data {
//	int n;
//	char arr[4];
//	double d;
//} Data;
//int main()
//{
//	Data u1 = { 0x44434241 };
//
//	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("size : %d\n", sizeof(u1));
//	printf("%p\n", &u1.n);
//	printf("%p\n", u1.arr);
//	printf("%p\n", &u1);
//}

//#include <stdio.h>
//
//typedef union data {
//	int n;
//	char arr[4];
//	double d;
//} Data;
//int main()
//{
//	Data u1 = { 0x44434241 };
//
//	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("size : %d\n", sizeof(u1));
//}

//#include <stdio.h>
//
//typedef union data {
//	int n;
//	char arr[4];
//} Data;
//int main()
//{
//	Data u1 = { 0x44434241 };
//
//	printf("%c%c%c%c\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("%x%x%x%x\n", u1.arr[0], u1.arr[1], u1.arr[2], u1.arr[3]);
//	printf("size : %d\n", sizeof(u1));
//}


//// //#include <stdio.h>
//
//struct _bitfield
//{
//	unsigned int a1 : 8;
//	unsigned int a2 : 8;
//	unsigned int a3 : 8;
//	unsigned int a4 : 8;
//};
//int main()
//{
//	struct _bitfield bit = { 0 };
//
//	bit.a1 |= 0xFF;
//	bit.a3 |= 0xFF;
//	printf("%08X\n", bit);
//	bit.a1 |= 0xFF;
//	bit.a3 ^= 0xFF;
//	printf("%08X\n", bit);
//}


//#include <stdio.h>
//
//struct _bitfield
//{
//	unsigned int a1 : 1;
//	unsigned int a2 : 1;
//	unsigned int a3 : 2;
//	unsigned int a4 : 4;
//};
//int main()
//{
//	struct _bitfield bit = { 0 };
//
//	bit.a3 = 3;
//	printf("%08X\n", bit);
//}
