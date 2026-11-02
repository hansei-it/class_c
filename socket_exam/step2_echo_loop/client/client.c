/*
 * client.c - TCP 에코 클라이언트 (2단계: 반복 에코와 오류 처리)
 *
 * 1단계에 두 가지를 더했다.
 *  - 콘솔 입력을 반복해서 주고받고, "exit"를 입력하면 종료한다.
 *  - 소켓 함수의 실패를 확인하고, 실패하면 오류 코드를 출력한 뒤 정리하고 종료한다.
 *
 * send와 recv가 한 번에 전부 처리된다고 가정했다. 나뉘어 처리되는 경우는 3단계에서 다룬다.
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

#define SERVER_IP "127.0.0.1"
#define PORT 9001
#define BUFFER_SIZE 1024

int main(void)
{
    WSADATA wsa_data;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    char echo[BUFFER_SIZE];
    int exit_code = 0;
    int result;

    /* WSAStartup은 WSAGetLastError가 아니라 반환값으로 오류 코드를 알려준다. */
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        fprintf(stderr, "[클라이언트] WSAStartup 실패: %d\n", result);
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "[클라이언트] socket 실패: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1) {
        fprintf(stderr, "[클라이언트] 잘못된 서버 주소: %s\n", SERVER_IP);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    /* 서버가 실행 중이 아니면 10061(WSAECONNREFUSED)이 발생한다. */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] connect 실패: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("[클라이언트] %s:%d에 접속했습니다. 종료하려면 exit를 입력하세요.\n", SERVER_IP, PORT);

    for (;;) {
        int length;
        int received;

        printf("> ");
        fflush(stdout);

        /* 입력 스트림이 끝나면(Ctrl+Z) "exit"와 동일하게 종료한다. */
        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        /* fgets가 함께 저장한 줄바꿈을 지운다. 입력이 버퍼보다 길면 줄바꿈이 없을 수 있어 확인한다. */
        length = (int)strlen(message);
        if (length > 0 && message[length - 1] == '\n') {
            length--;
            message[length] = '\0';
        }

        if (strcmp(message, "exit") == 0) {
            break;
        }

        /* 빈 줄은 전송할 데이터가 없어 에코도 오지 않으므로, 그대로 recv하면 영원히 대기한다. */
        if (length == 0) {
            continue;
        }

        if (send(sock, message, length, 0) == SOCKET_ERROR) {
            fprintf(stderr, "[클라이언트] send 실패: %d\n", WSAGetLastError());
            exit_code = 1;
            break;
        }

        received = recv(sock, echo, BUFFER_SIZE - 1, 0);
        if (received == 0) {
            fprintf(stderr, "[클라이언트] 서버가 연결을 종료했습니다.\n");
            exit_code = 1;
            break;
        }
        if (received == SOCKET_ERROR) {
            fprintf(stderr, "[클라이언트] recv 실패: %d\n", WSAGetLastError());
            exit_code = 1;
            break;
        }

        echo[received] = '\0';
        printf("[클라이언트] 에코: %s\n", echo);
    }

    /* closesocket이 연결 종료를 알리므로 서버의 recv는 0을 반환한다. */
    closesocket(sock);
    WSACleanup();
    printf("[클라이언트] 연결을 종료했습니다.\n");
    return exit_code;
}
