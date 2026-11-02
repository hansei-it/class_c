/*
 * data_basics.c - 데이터 표현 기초 (5단계 준비)
 *
 * 5단계부터는 정수, 실수, 문자열을 바이트로 바꿔 주고받는다. 그때 필요한 내용을 소켓 연결 없이 익힌다.
 *  - 예제 1: 바이트 순서. 같은 값도 메모리에 놓이는 순서가 다를 수 있다.
 *  - 예제 2: 구조체 패딩. 구조체를 그대로 전송하면 안 되는 이유를 보여 준다.
 *  - 예제 3: 직렬화. 값을 정해진 순서로 버퍼에 담고 다시 꺼낸다.
 */

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h> /* htonl, ntohl, htond, ntohd */
#include <stddef.h>   /* offsetof */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 64

/* 메모리에 놓인 순서대로 바이트를 16진수로 출력한다. */
static void print_bytes(const char *label, const void *data, size_t size)
{
    const unsigned char *bytes = data;
    size_t i;

    printf("  %-16s:", label);
    for (i = 0; i < size; i++) {
        printf(" %02X", bytes[i]);
    }
    printf("\n");
}

/* 예제 1: x86/x64 PC는 낮은 자리 바이트를 먼저 저장한다(리틀 엔디안).
   네트워크에서는 높은 자리 바이트를 먼저 보내기로 약속했다(빅 엔디안, 네트워크 바이트 순서). */
static void example1_byte_order(void)
{
    uint32_t value = 0x12345678;
    uint32_t network_value = htonl(value);
    double real = 3.25;
    unsigned __int64 network_real = htond(real);

    printf("=== 예제 1: 바이트 순서 ===\n");

    printf("  정수 0x%08X\n", value);
    print_bytes("이 PC의 메모리", &value, sizeof(value));
    print_bytes("네트워크 순서", &network_value, sizeof(network_value));
    printf("  ntohl로 되돌린 값: 0x%08X\n", ntohl(network_value));

    /* 받는 쪽이 변환을 잊으면 전혀 다른 값이 된다. */
    printf("  변환을 잊고 읽은 값: 0x%08X\n\n", network_value);

    printf("  실수 %.2f\n", real);
    print_bytes("이 PC의 메모리", &real, sizeof(real));
    print_bytes("네트워크 순서", &network_real, sizeof(network_real));
    printf("  ntohd로 되돌린 값: %.2f\n\n", ntohd(network_real));
}

/* 컴파일러는 필드를 정렬하려고 필드 사이에 빈 공간(패딩)을 넣는다. */
struct sample {
    char type;
    int32_t value;
    char flag;
    double real;
};

/* 예제 2: 패딩의 크기는 컴파일러와 설정에 따라 달라질 수 있고, 초기화되지 않은 메모리가 그대로 나갈 수도 있다.
   그래서 구조체를 send로 그대로 보내지 않고, 필드를 하나씩 버퍼에 담는다. */
static void example2_padding(void)
{
    printf("=== 예제 2: 구조체 패딩 ===\n");

    printf("  필드 크기의 합: %zu바이트\n", sizeof(char) + sizeof(int32_t) + sizeof(char) + sizeof(double));
    printf("  구조체 크기   : %zu바이트\n", sizeof(struct sample));
    printf("  필드 위치     : type=%zu value=%zu flag=%zu real=%zu\n\n", offsetof(struct sample, type),
           offsetof(struct sample, value), offsetof(struct sample, flag), offsetof(struct sample, real));
}

/* 값을 네트워크 순서로 버퍼에 쓰고, 쓴 바이트 수를 반환한다.
   버퍼의 임의 위치에 정수를 직접 대입하면 정렬 문제가 생길 수 있어 memcpy를 쓴다. */
static size_t put_int32(char *buffer, int32_t value)
{
    uint32_t network = htonl((uint32_t)value);

    memcpy(buffer, &network, sizeof(network));
    return sizeof(network);
}

static size_t put_double(char *buffer, double value)
{
    unsigned __int64 network = htond(value);

    memcpy(buffer, &network, sizeof(network));
    return sizeof(network);
}

static int32_t get_int32(const char *buffer)
{
    uint32_t network;

    memcpy(&network, buffer, sizeof(network));
    return (int32_t)ntohl(network);
}

static double get_double(const char *buffer)
{
    unsigned __int64 network;

    memcpy(&network, buffer, sizeof(network));
    return ntohd(network);
}

/* 예제 3: 보내는 쪽과 받는 쪽이 같은 순서로 쓰고 읽기만 하면 패딩과 바이트 순서 문제가 사라진다.
   문자열은 길이가 제각각이므로 길이를 먼저 담는다. 6단계의 메시지 형식이 이 방식이다. */
static void example3_serialize(void)
{
    char buffer[BUFFER_SIZE];
    const char *text = "hello";
    int32_t text_length = (int32_t)strlen(text);
    size_t written = 0;
    size_t offset = 0;
    int32_t number;
    double real;
    int32_t read_length;

    printf("=== 예제 3: 직렬화 ===\n");

    /* 쓰기: 정수, 실수, 문자열 길이, 문자열 순서로 담는다. */
    written += put_int32(buffer + written, -7);
    written += put_double(buffer + written, 3.25);
    written += put_int32(buffer + written, text_length);
    memcpy(buffer + written, text, (size_t)text_length);
    written += (size_t)text_length;

    print_bytes("버퍼 내용", buffer, written);
    printf("  전체 크기: %zu바이트\n", written);

    /* 읽기: 쓴 순서 그대로 꺼낸다. 문자열의 끝은 먼저 읽은 길이로 알 수 있다. */
    number = get_int32(buffer + offset);
    offset += sizeof(int32_t);
    real = get_double(buffer + offset);
    offset += sizeof(double);
    read_length = get_int32(buffer + offset);
    offset += sizeof(int32_t);

    printf("  꺼낸 값: 정수 %d, 실수 %.2f, 문자열 %.*s\n", number, real, read_length, buffer + offset);
}

int main(void)
{
    example1_byte_order();
    example2_padding();
    example3_serialize();
    return 0;
}
