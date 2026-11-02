/*
 * client.c - 계산 클라이언트 (5단계: 고정 길이 메시지)
 *
 * 메뉴에서 작업을 고르면 값을 입력받아 서버로 보내고 결과를 출력한다.
 * 메시지 형식은 protocol.h에 있다. 메시지의 크기가 항상 같으므로 긴 문자열은 보낼 수 없다.
 */

/* 아래 설정은 모든 #include보다 앞에 있어야 효과가 있다. */
#define WIN32_LEAN_AND_MEAN             /* windows.h가 구버전 winsock.h를 포함해 생기는 재정의 오류 방지 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS /* inet_addr 등 구형 Winsock 함수의 C4996 오류 방지 */
#define _CRT_SECURE_NO_WARNINGS         /* scanf, strcpy 등 CRT 함수의 C4996 오류 방지 */

#include <winsock2.h> /* windows.h를 직접 포함한다면 반드시 이 헤더보다 뒤에 둘 것 */
#include <ws2tcpip.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../protocol.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define LINE_SIZE 256

/* socket, connect를 수행한다. 실패하면 소켓을 닫고 INVALID_SOCKET을 반환한다. */
static SOCKET connect_to_server(void)
{
    SOCKET sock;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "[클라이언트] socket 실패: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1) {
        fprintf(stderr, "[클라이언트] 잘못된 서버 주소: %s\n", SERVER_IP);
        closesocket(sock);
        return INVALID_SOCKET;
    }

    /* 서버가 실행 중이 아니면 10061(WSAECONNREFUSED)이 발생한다. */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] connect 실패: %d\n", WSAGetLastError());
        closesocket(sock);
        return INVALID_SOCKET;
    }
    return sock;
}

/* 프롬프트를 출력하고 한 줄을 읽어 길이를 반환한다. 입력이 끝나면 -1을 반환한다.
   줄이 버퍼보다 길면 나머지를 버리고 size를 반환하므로, 호출한 쪽에서 길이로 걸러낼 수 있다. */
static int read_line(const char *prompt, char *line, int size)
{
    int length;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(line, size, stdin) == NULL) {
        return -1;
    }

    length = (int)strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        length--;
        line[length] = '\0';
        return length;
    }

    /* 줄바꿈 없이 버퍼가 찼다면 남은 입력이 다음 질문의 답으로 넘어가지 않도록 버린다. */
    if (length == size - 1) {
        int ch = getchar();

        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }
        return size;
    }
    return length;
}

/* 정수를 입력받는다. 올바른 값이면 1, 아니면 0을 반환한다. */
static int input_int32(const char *prompt, int32_t *value)
{
    char line[LINE_SIZE];
    char *end;
    long parsed;
    int length = read_line(prompt, line, sizeof(line));

    if (length < 0 || length >= LINE_SIZE) {
        return 0;
    }

    errno = 0;
    parsed = strtol(line, &end, 10);
    if (end == line || *end != '\0' || errno == ERANGE) {
        return 0;
    }
    *value = (int32_t)parsed;
    return 1;
}

/* 실수를 입력받는다. 올바른 값이면 1, 아니면 0을 반환한다. */
static int input_double(const char *prompt, double *value)
{
    char line[LINE_SIZE];
    char *end;
    double parsed;
    int length = read_line(prompt, line, sizeof(line));

    if (length < 0 || length >= LINE_SIZE) {
        return 0;
    }

    errno = 0;
    parsed = strtod(line, &end);
    if (end == line || *end != '\0' || errno == ERANGE) {
        return 0;
    }
    *value = parsed;
    return 1;
}

/* 요청을 보내고 응답을 받는다. 통신에 실패하면 SOCKET_ERROR를 반환한다. */
static int exchange_message(SOCKET sock, const char *request, char *response)
{
    int received;

    if (send_all(sock, request, MESSAGE_SIZE) == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] send 실패: %d\n", WSAGetLastError());
        return SOCKET_ERROR;
    }

    received = recv_all(sock, response, MESSAGE_SIZE);
    if (received == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] recv 실패: %d\n", WSAGetLastError());
        return SOCKET_ERROR;
    }
    if (received < MESSAGE_SIZE) {
        fprintf(stderr, "[클라이언트] 서버가 연결을 종료했습니다.\n");
        return SOCKET_ERROR;
    }
    return 0;
}

/* 아래 요청 함수들은 통신에 실패할 때만 SOCKET_ERROR를 반환한다. 입력이 잘못되면 메뉴로 돌아간다. */
static int request_int_add(SOCKET sock)
{
    char request[MESSAGE_SIZE] = { 0 };
    char response[MESSAGE_SIZE];
    int32_t a;
    int32_t b;

    if (!input_int32("a> ", &a) || !input_int32("b> ", &b)) {
        printf("[클라이언트] 32비트 정수를 입력해야 합니다.\n");
        return 0;
    }

    put_uint32(request, TYPE_INT_ADD);
    put_int32(request + TYPE_SIZE, a);
    put_int32(request + TYPE_SIZE + 4, b);

    if (exchange_message(sock, request, response) == SOCKET_ERROR) {
        return SOCKET_ERROR;
    }
    if (get_uint32(response) != TYPE_INT_ADD) {
        printf("[클라이언트] 서버가 요청을 처리하지 못했습니다.\n");
        return 0;
    }

    printf("[클라이언트] 결과: %lld\n", get_int64(response + TYPE_SIZE));
    return 0;
}

static int request_double_add(SOCKET sock)
{
    char request[MESSAGE_SIZE] = { 0 };
    char response[MESSAGE_SIZE];
    double a;
    double b;

    if (!input_double("a> ", &a) || !input_double("b> ", &b)) {
        printf("[클라이언트] 실수를 입력해야 합니다.\n");
        return 0;
    }

    put_uint32(request, TYPE_DOUBLE_ADD);
    put_double(request + TYPE_SIZE, a);
    put_double(request + TYPE_SIZE + 8, b);

    if (exchange_message(sock, request, response) == SOCKET_ERROR) {
        return SOCKET_ERROR;
    }
    if (get_uint32(response) != TYPE_DOUBLE_ADD) {
        printf("[클라이언트] 서버가 요청을 처리하지 못했습니다.\n");
        return 0;
    }

    printf("[클라이언트] 결과: %.15g\n", get_double(response + TYPE_SIZE));
    return 0;
}

static int request_string(SOCKET sock)
{
    char line[LINE_SIZE];
    char request[MESSAGE_SIZE] = { 0 };
    char response[MESSAGE_SIZE];
    int length = read_line("문자열> ", line, sizeof(line));

    if (length < 0) {
        return 0;
    }
    if (length > MAX_TEXT_LENGTH) {
        printf("[클라이언트] 고정 길이 메시지에는 %d바이트까지만 담을 수 있습니다.\n", MAX_TEXT_LENGTH);
        return 0;
    }

    put_uint32(request, TYPE_STRING);
    memcpy(request + TYPE_SIZE, line, (size_t)length);

    if (exchange_message(sock, request, response) == SOCKET_ERROR) {
        return SOCKET_ERROR;
    }
    if (get_uint32(response) != TYPE_STRING) {
        printf("[클라이언트] 서버가 요청을 처리하지 못했습니다.\n");
        return 0;
    }

    /* 서버가 '\0'을 넣었다고 믿을 수 없으므로 끝을 직접 막는다. */
    response[MESSAGE_SIZE - 1] = '\0';
    printf("[클라이언트] 결과: %s\n", response + TYPE_SIZE);
    return 0;
}

/* 0을 입력하거나 입력이 끝날 때까지 메뉴를 반복한 뒤 전송 종료를 알린다. */
static int menu_loop(SOCKET sock)
{
    char line[LINE_SIZE];

    for (;;) {
        int result = 0;

        printf("\n1) 정수 덧셈  2) 실수 덧셈  3) 문자열 전송  0) 종료\n");

        /* 입력 스트림이 끝나면(Ctrl+Z) 0을 입력한 것과 동일하게 종료한다. */
        if (read_line("선택> ", line, sizeof(line)) < 0) {
            break;
        }

        if (strcmp(line, "0") == 0) {
            break;
        } else if (strcmp(line, "1") == 0) {
            result = request_int_add(sock);
        } else if (strcmp(line, "2") == 0) {
            result = request_double_add(sock);
        } else if (strcmp(line, "3") == 0) {
            result = request_string(sock);
        } else {
            printf("[클라이언트] 메뉴에 없는 번호입니다.\n");
        }

        if (result == SOCKET_ERROR) {
            return EXIT_FAILURE;
        }
    }

    /* 더 보낼 데이터가 없음을 서버에 알린다. 서버의 recv는 0을 반환한다. */
    if (shutdown(sock, SD_SEND) == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] shutdown 실패: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(void)
{
    WSADATA wsa_data;
    SOCKET sock;
    int exit_code = EXIT_FAILURE;
    int result;

    /* WSAStartup은 WSAGetLastError가 아니라 반환값으로 오류 코드를 알려준다. */
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        fprintf(stderr, "[클라이언트] WSAStartup 실패: %d\n", result);
        return EXIT_FAILURE;
    }

    sock = connect_to_server();
    if (sock != INVALID_SOCKET) {
        printf("[클라이언트] %s:%d에 접속했습니다.\n", SERVER_IP, PORT);
        exit_code = menu_loop(sock);
        closesocket(sock);
    }

    WSACleanup();
    printf("[클라이언트] 연결을 종료했습니다.\n");
    return exit_code;
}
