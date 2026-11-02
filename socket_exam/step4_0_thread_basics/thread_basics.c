/*
 * thread_basics.c - 스레드 기초 (4단계 준비)
 *
 * 4단계 서버에서 쓰는 스레드 사용법을 소켓 없이 익힌다. 예제 세 개를 차례로 실행한다.
 *  - 예제 1: 스레드를 만들고 끝날 때까지 기다린다.
 *  - 예제 2: 스레드에 값을 넘긴다. 4단계에서 client_info를 malloc으로 할당하는 이유를 보여 준다.
 *  - 예제 3: 끝나기를 기다리지 않는 스레드를 만든다. 4단계의 start_client_thread가 이 방식이다.
 */

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <process.h> /* _beginthreadex */
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 3

/* 스레드를 시작한다. 이 예제에서는 생성에 실패하면 더 진행할 수 없으므로 프로그램을 끝낸다. */
static HANDLE start_thread(_beginthreadex_proc_type function, void *arg)
{
    /* 인자 순서: 보안 속성, 스택 크기(0은 기본값), 시작 함수, 함수에 넘길 값, 생성 옵션, 스레드 ID */
    HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, function, arg, 0, NULL);

    if (thread == 0) {
        fprintf(stderr, "스레드 생성 실패\n");
        exit(EXIT_FAILURE);
    }
    return thread;
}

/* 스레드들이 모두 끝날 때까지 기다린다. 핸들은 스레드가 끝나도 직접 닫아야 한다. */
static void wait_and_close(HANDLE *threads, int count)
{
    int i;

    WaitForMultipleObjects((DWORD)count, threads, TRUE, INFINITE);
    for (i = 0; i < count; i++) {
        CloseHandle(threads[i]);
    }
}

/* 스레드 시작 함수의 형식은 정해져 있다. void * 하나를 받고 unsigned를 반환한다. */
static unsigned __stdcall count_thread(void *arg)
{
    const char *name = arg;
    int i;

    for (i = 1; i <= 5; i++) {
        printf("  [%s] %d\n", name, i);
        Sleep(100);
    }
    return 0;
}

/* 예제 1: 두 스레드가 동시에 실행되어 출력이 번갈아 나온다. 순서는 실행할 때마다 달라질 수 있다. */
static void example1_create_and_wait(void)
{
    HANDLE threads[2];

    printf("=== 예제 1: 생성과 대기 ===\n");

    threads[0] = start_thread(count_thread, "스레드 A");
    threads[1] = start_thread(count_thread, "스레드 B");

    /* 기다리지 않으면 main이 먼저 끝날 수 있고, 그러면 스레드도 함께 종료된다. */
    wait_and_close(threads, 2);
    printf("  [main] 두 스레드가 모두 끝났습니다.\n\n");
}

/* 스레드가 실제로 언제 실행될지는 보장되지 않는다. 그 차이가 잘 보이도록 값을 잠시 늦게 읽는다. */
static unsigned __stdcall print_shared_number(void *arg)
{
    int number;

    Sleep(50);
    number = *(int *)arg;
    printf("  스레드가 받은 값: %d\n", number);
    return 0;
}

/* 예제 2-1: 일부러 넣은 버그다. 모든 스레드가 같은 변수 i를 가리키므로 결과가 보장되지 않는다. */
static void example2_wrong_argument(void)
{
    HANDLE threads[THREAD_COUNT];
    int i;

    printf("=== 예제 2-1: 잘못된 값 전달 (같은 변수의 주소) ===\n");

    for (i = 0; i < THREAD_COUNT; i++) {
        threads[i] = start_thread(print_shared_number, &i);
    }

    /* 스레드가 값을 읽을 때쯤이면 반복문이 끝나 i가 이미 바뀌어 있다. */
    wait_and_close(threads, THREAD_COUNT);
    printf("\n");
}

static unsigned __stdcall print_own_number(void *arg)
{
    int *number = arg;

    Sleep(50);
    printf("  스레드가 받은 값: %d\n", *number);
    free(number); /* 이 값은 이 스레드만 쓰므로 여기서 해제한다 */
    return 0;
}

/* 예제 2-2: 스레드마다 값을 따로 할당하면 서로 영향을 주지 않는다. 출력 순서는 달라질 수 있다. */
static void example2_right_argument(void)
{
    HANDLE threads[THREAD_COUNT];
    int i;

    printf("=== 예제 2-2: 올바른 값 전달 (스레드마다 따로 할당) ===\n");

    for (i = 0; i < THREAD_COUNT; i++) {
        int *number = malloc(sizeof(int));

        if (number == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(EXIT_FAILURE);
        }
        *number = i;
        threads[i] = start_thread(print_own_number, number);
    }

    wait_and_close(threads, THREAD_COUNT);
    printf("\n");
}

static unsigned __stdcall background_thread(void *arg)
{
    const char *name = arg;

    Sleep(100);
    printf("  [%s] 핸들을 닫은 뒤에도 계속 실행 중입니다.\n", name);
    return 0;
}

/* 예제 3: 끝나기를 기다릴 필요가 없으면 핸들을 바로 닫아도 된다. 스레드는 멈추지 않는다. */
static void example3_no_wait(void)
{
    HANDLE thread;

    printf("=== 예제 3: 기다리지 않는 스레드 ===\n");

    thread = start_thread(background_thread, "스레드");
    CloseHandle(thread);
    printf("  [main] 핸들을 닫았습니다.\n");

    /* main이 끝나면 스레드도 종료되므로 출력을 볼 수 있게 잠시 기다린다.
       4단계 서버는 accept_loop가 계속 돌기 때문에 이런 대기가 필요 없다. */
    Sleep(300);
}

int main(void)
{
    example1_create_and_wait();
    example2_wrong_argument();
    example2_right_argument();
    example3_no_wait();
    return EXIT_SUCCESS;
}
