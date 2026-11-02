/*
 * server.c - 계산 서버 (6단계: 가변 길이 메시지)
 *
 * 5단계와 기능은 같지만, 메시지를 헤더와 본문으로 나눠 긴 문자열도 처리한다.
 * 메시지 형식은 protocol.h에 있다. 헤더의 length를 믿고 읽기 전에 항상 상한을 확인한다.
 *
 * 서버는 스스로 종료하지 않으므로 Ctrl+C로 끝낸다. 이때 소켓과 Winsock 자원은 OS가 회수한다.
 */

/* 아래 설정은 모든 #include보다 앞에 있어야 효과가 있다. */
#define WIN32_LEAN_AND_MEAN             /* windows.h가 구버전 winsock.h를 포함해 생기는 재정의 오류 방지 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS /* inet_addr 등 구형 Winsock 함수의 C4996 오류 방지 */
#define _CRT_SECURE_NO_WARNINGS         /* scanf, strcpy 등 CRT 함수의 C4996 오류 방지 */

#include <winsock2.h> /* windows.h를 직접 포함한다면 반드시 이 헤더보다 뒤에 둘 것 */
#include <ws2tcpip.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../protocol.h"

#pragma comment(lib, "ws2_32.lib")

#define IP_SIZE 16   /* "255.255.255.255"와 '\0' */
#define NAME_SIZE 22 /* "255.255.255.255:65535"와 '\0' */

/* 스레드에 넘기는 클라이언트 정보 */
typedef struct {
    SOCKET sock;
    char name[NAME_SIZE]; /* 로그에 표시할 "IP:포트" */
} client_info;

/* socket, bind, listen을 수행한다. 실패하면 소켓을 닫고 INVALID_SOCKET을 반환한다. */
static SOCKET create_listen_socket(void)
{
    SOCKET listen_sock;
    struct sockaddr_in server_addr;

    listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        fprintf(stderr, "[서버] socket 실패: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    /* 모든 네트워크 인터페이스에서 접속을 받는다. 다른 PC의 접속은 방화벽 허용이 필요하다. */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "[서버] bind 실패: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        return INVALID_SOCKET;
    }

    if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "[서버] listen 실패: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        return INVALID_SOCKET;
    }
    return listen_sock;
}

/* 요청 하나를 처리하고 응답을 보낸다. body에는 끝의 '\0'을 쓸 공간이 있어야 한다.
   응답 전송에 실패하면 SOCKET_ERROR를 반환한다. */
static int handle_request(const client_info *client, uint32_t type, char *body, uint32_t length)
{
    char result[8];

    /* 숫자 요청은 본문 길이가 정해져 있으므로 길이가 맞을 때만 읽는다. */
    if (type == TYPE_INT_ADD && length == 8) {
        int32_t a = get_int32(body);
        int32_t b = get_int32(body + 4);
        int64_t sum = (int64_t)a + b; /* 32비트 두 값의 합은 64비트에 항상 들어가므로 넘치지 않는다 */

        put_int64(result, sum);
        printf("[서버][%s] 정수 덧셈: %d + %d = %lld\n", client->name, a, b, sum);
        return send_message(client->sock, TYPE_INT_ADD, result, sizeof(result));
    }

    if (type == TYPE_DOUBLE_ADD && length == 16) {
        double a = get_double(body);
        double b = get_double(body + 8);
        double sum = a + b;

        put_double(result, sum);
        printf("[서버][%s] 실수 덧셈: %.15g + %.15g = %.15g\n", client->name, a, b, sum);
        return send_message(client->sock, TYPE_DOUBLE_ADD, result, sizeof(result));
    }

    if (type == TYPE_STRING) {
        /* 본문에는 '\0'이 없으므로 출력하려면 직접 붙여야 한다. */
        body[length] = '\0';
        printf("[서버][%s] 문자열 수신 (%u바이트): %s\n", client->name, length, body);
        return send_message(client->sock, TYPE_STRING, body, length);
    }

    /* 본문까지 다 읽었으므로 다음 메시지의 시작 위치는 어긋나지 않는다. 연결은 유지한다. */
    fprintf(stderr, "[서버][%s] 처리할 수 없는 요청입니다. (종류 %u, 본문 %u바이트)\n", client->name, type, length);
    return send_message(client->sock, TYPE_ERROR, NULL, 0);
}

/* 클라이언트가 연결을 끊을 때까지 요청을 받아 처리한다. */
static void request_loop(const client_info *client)
{
    char body[MAX_BODY_SIZE + 1];

    for (;;) {
        uint32_t type;
        uint32_t length;
        int status = recv_message(client->sock, &type, body, &length);

        if (status == MESSAGE_CLOSED) {
            printf("[서버][%s] 클라이언트가 연결을 종료했습니다.\n", client->name);
            return;
        }
        if (status == MESSAGE_SOCKET_ERROR) {
            fprintf(stderr, "[서버][%s] recv 실패: %d\n", client->name, WSAGetLastError());
            return;
        }
        if (status == MESSAGE_TRUNCATED) {
            fprintf(stderr, "[서버][%s] 메시지 중간에 연결이 끊겼습니다.\n", client->name);
            return;
        }

        /* 본문을 읽지 않았으므로 다음 메시지의 시작 위치를 알 수 없다. 연결을 끊을 수밖에 없다. */
        if (status == MESSAGE_TOO_LONG) {
            fprintf(stderr, "[서버][%s] 허용 길이를 넘는 메시지입니다. (%u바이트) 연결을 끊습니다.\n", client->name, length);
            return;
        }

        if (handle_request(client, type, body, length) == SOCKET_ERROR) {
            fprintf(stderr, "[서버][%s] send 실패: %d\n", client->name, WSAGetLastError());
            return;
        }
    }
}

/* 클라이언트 한 명을 맡는 스레드. 소켓과 client_info의 정리도 여기서 한다. */
static unsigned __stdcall client_thread(void *arg)
{
    client_info *client = arg;

    request_loop(client);

    closesocket(client->sock);
    free(client);
    return 0;
}

/* 클라이언트 정보를 만들어 전용 스레드를 시작한다. 실패하면 그 클라이언트의 연결만 닫는다. */
static void start_client_thread(SOCKET client_sock, const struct sockaddr_in *client_addr)
{
    client_info *client;
    char client_ip[IP_SIZE];
    HANDLE thread;

    /* 다음 accept가 값을 덮어쓰지 않도록 클라이언트마다 따로 할당한다. */
    client = malloc(sizeof(*client));
    if (client == NULL) {
        fprintf(stderr, "[서버] 메모리 할당 실패\n");
        closesocket(client_sock);
        return;
    }

    client->sock = client_sock;
    inet_ntop(AF_INET, &client_addr->sin_addr, client_ip, sizeof(client_ip));
    snprintf(client->name, sizeof(client->name), "%s:%d", client_ip, ntohs(client_addr->sin_port));
    printf("[서버][%s] 클라이언트 접속\n", client->name);

    thread = (HANDLE)_beginthreadex(NULL, 0, client_thread, client, 0, NULL);
    if (thread == 0) {
        fprintf(stderr, "[서버][%s] 스레드 생성 실패\n", client->name);
        closesocket(client_sock);
        free(client);
        return;
    }

    /* 핸들만 닫는 것이며 스레드는 계속 실행된다. 이 시점부터 client는 스레드의 소유다. */
    CloseHandle(thread);
}

/* 접속을 계속 받아 스레드에 넘긴다. 복구할 수 없는 accept 오류가 나야 반환한다. */
static void accept_loop(SOCKET listen_sock)
{
    for (;;) {
        struct sockaddr_in client_addr;
        int client_addr_len = sizeof(client_addr); /* accept가 값을 바꾸므로 매번 초기화한다 */
        SOCKET client_sock;

        client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == INVALID_SOCKET) {
            int error = WSAGetLastError();

            fprintf(stderr, "[서버] accept 실패: %d\n", error);

            /* 접속 직후 끊어진 클라이언트 하나 때문에 서버 전체가 멈추면 안 된다. */
            if (error == WSAECONNRESET) {
                continue;
            }
            return;
        }

        start_client_thread(client_sock, &client_addr);
    }
}

int main(void)
{
    WSADATA wsa_data;
    SOCKET listen_sock;
    int result;

    /* WSAStartup은 WSAGetLastError가 아니라 반환값으로 오류 코드를 알려준다. */
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        fprintf(stderr, "[서버] WSAStartup 실패: %d\n", result);
        return EXIT_FAILURE;
    }

    listen_sock = create_listen_socket();
    if (listen_sock != INVALID_SOCKET) {
        printf("[서버] 포트 %d에서 접속 대기 중... (종료: Ctrl+C)\n", PORT);
        accept_loop(listen_sock);
        closesocket(listen_sock);
    }

    /* 정상 종료 경로는 Ctrl+C뿐이므로 여기까지 왔다면 오류로 끝난 것이다. */
    WSACleanup();
    printf("[서버] 종료했습니다.\n");
    return EXIT_FAILURE;
}
