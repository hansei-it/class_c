/*
 * server.c - TCP 에코 서버 (단일 연결)
 *
 * 클라이언트 하나의 연결을 받아, 수신한 메시지를 콘솔에 출력한 뒤 그대로 돌려보낸다.
 * 클라이언트가 연결을 종료하면 소켓을 정리하고 프로그램도 함께 종료한다.
 */

/* 아래 설정은 모든 #include보다 앞에 있어야 효과가 있다. */
#define WIN32_LEAN_AND_MEAN             /* windows.h가 구버전 winsock.h를 포함해 생기는 재정의 오류 방지 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS /* inet_addr 등 구형 Winsock 함수의 C4996 오류 방지 */
#define _CRT_SECURE_NO_WARNINGS         /* scanf, strcpy 등 CRT 함수의 C4996 오류 방지 */

#include <winsock2.h> /* windows.h를 직접 포함한다면 반드시 이 헤더보다 뒤에 둘 것 */
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9001
#define BUFFER_SIZE 1024
#define IP_SIZE 16 /* "255.255.255.255"와 '\0' */

/* send()는 요청한 길이보다 적게 보내고 반환할 수 있으므로 전부 보낼 때까지 반복한다. */
static int send_all(SOCKET sock, const char *data, int length)
{
    int total = 0;

    while (total < length) {
        int sent = send(sock, data + total, length - total, 0);
        if (sent == SOCKET_ERROR) {
            return SOCKET_ERROR;
        }
        total += sent;
    }
    return 0;
}

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

/* 클라이언트 하나를 받아 접속 정보를 출력한다. 실패하면 INVALID_SOCKET을 반환한다. */
static SOCKET accept_client(SOCKET listen_sock)
{
    SOCKET client_sock;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char client_ip[IP_SIZE];

    client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == INVALID_SOCKET) {
        fprintf(stderr, "[서버] accept 실패: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("[서버] 클라이언트 접속: %s:%d\n", client_ip, ntohs(client_addr.sin_port));
    return client_sock;
}

/* 클라이언트가 연결을 끊을 때까지 수신한 메시지를 그대로 돌려보낸다. */
static int echo_loop(SOCKET client_sock)
{
    char buffer[BUFFER_SIZE];

    for (;;) {
        int received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

        /* 상대방이 정상적으로 연결을 끊으면 recv는 0을 반환한다. */
        if (received == 0) {
            printf("[서버] 클라이언트가 연결을 종료했습니다.\n");
            return EXIT_SUCCESS;
        }
        /* 상대방이 비정상 종료하면 보통 10054(WSAECONNRESET)가 발생한다. */
        if (received == SOCKET_ERROR) {
            fprintf(stderr, "[서버] recv 실패: %d\n", WSAGetLastError());
            return EXIT_FAILURE;
        }

        buffer[received] = '\0';
        printf("[서버] %d바이트 수신: %s\n", received, buffer);

        if (send_all(client_sock, buffer, received) == SOCKET_ERROR) {
            fprintf(stderr, "[서버] send 실패: %d\n", WSAGetLastError());
            return EXIT_FAILURE;
        }
    }
}

int main(void)
{
    WSADATA wsa_data;
    SOCKET listen_sock;
    int exit_code = EXIT_FAILURE;
    int result;

    /* WSAStartup은 WSAGetLastError가 아니라 반환값으로 오류 코드를 알려준다. */
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        fprintf(stderr, "[서버] WSAStartup 실패: %d\n", result);
        return EXIT_FAILURE;
    }

    listen_sock = create_listen_socket();
    if (listen_sock != INVALID_SOCKET) {
        SOCKET client_sock;

        printf("[서버] 포트 %d에서 접속 대기 중...\n", PORT);
        client_sock = accept_client(listen_sock);

        /* 단일 연결만 처리하므로 리슨 소켓을 닫아 추가 접속을 거부한다. */
        closesocket(listen_sock);

        if (client_sock != INVALID_SOCKET) {
            exit_code = echo_loop(client_sock);
            closesocket(client_sock);
        }
    }

    WSACleanup();
    printf("[서버] 종료했습니다.\n");
    return exit_code;
}
