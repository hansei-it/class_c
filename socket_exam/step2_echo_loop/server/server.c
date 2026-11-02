/*
 * server.c - TCP 에코 서버 (2단계: 반복 에코와 오류 처리)
 *
 * 1단계에 두 가지를 더했다.
 *  - 클라이언트가 연결을 끊을 때까지 메시지를 반복해서 돌려보낸다.
 *  - 소켓 함수의 실패를 확인하고, 실패하면 오류 코드를 출력한 뒤 정리하고 종료한다.
 *
 * send가 한 번에 전부 전송한다고 가정했다. 일부만 전송되는 경우는 3단계에서 다룬다.
 */

/* 아래 설정은 모든 #include보다 앞에 있어야 효과가 있다. */
#define WIN32_LEAN_AND_MEAN             /* windows.h가 구버전 winsock.h를 포함해 생기는 재정의 오류 방지 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS /* inet_addr 등 구형 Winsock 함수의 C4996 오류 방지 */
#define _CRT_SECURE_NO_WARNINGS         /* scanf, strcpy 등 CRT 함수의 C4996 오류 방지 */

#include <winsock2.h> /* windows.h를 직접 포함한다면 반드시 이 헤더보다 뒤에 둘 것 */
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9001
#define BUFFER_SIZE 1024

int main(void)
{
    WSADATA wsa_data;
    SOCKET listen_sock;
    SOCKET client_sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int exit_code = 0;
    int result;

    /* WSAStartup은 WSAGetLastError가 아니라 반환값으로 오류 코드를 알려준다. */
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        fprintf(stderr, "[서버] WSAStartup 실패: %d\n", result);
        return 1;
    }

    listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        fprintf(stderr, "[서버] socket 실패: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    /* 모든 네트워크 인터페이스에서 접속을 받는다. 다른 PC의 접속은 방화벽 허용이 필요하다. */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "[서버] bind 실패: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }

    if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "[서버] listen 실패: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }
    printf("[서버] 포트 %d에서 접속 대기 중...\n", PORT);

    client_sock = accept(listen_sock, NULL, NULL);
    if (client_sock == INVALID_SOCKET) {
        fprintf(stderr, "[서버] accept 실패: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }
    printf("[서버] 클라이언트가 접속했습니다.\n");

    /* 단일 연결만 처리하므로 리슨 소켓을 닫아 추가 접속을 거부한다. */
    closesocket(listen_sock);

    for (;;) {
        int received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

        /* 상대방이 정상적으로 연결을 끊으면 recv는 0을 반환한다. */
        if (received == 0) {
            printf("[서버] 클라이언트가 연결을 종료했습니다.\n");
            break;
        }
        /* 상대방이 비정상 종료하면 보통 10054(WSAECONNRESET)가 발생한다. */
        if (received == SOCKET_ERROR) {
            fprintf(stderr, "[서버] recv 실패: %d\n", WSAGetLastError());
            exit_code = 1;
            break;
        }

        buffer[received] = '\0';
        printf("[서버] %d바이트 수신: %s\n", received, buffer);

        if (send(client_sock, buffer, received, 0) == SOCKET_ERROR) {
            fprintf(stderr, "[서버] send 실패: %d\n", WSAGetLastError());
            exit_code = 1;
            break;
        }
    }

    closesocket(client_sock);
    WSACleanup();
    printf("[서버] 종료했습니다.\n");
    return exit_code;
}
