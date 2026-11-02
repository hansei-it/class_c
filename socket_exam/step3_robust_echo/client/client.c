/*
 * client.c - TCP 에코 클라이언트
 *
 * 127.0.0.1:9001 서버에 접속해 콘솔 입력을 전송하고, 에코된 메시지를 화면에 출력한다.
 * "exit"를 입력하면 연결을 종료하고 리소스를 해제한다.
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

#define SERVER_IP "127.0.0.1"
#define PORT 9001
#define BUFFER_SIZE 1024

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

/* 메시지를 보내고 에코를 모두 받아 출력한다. 실패하면 SOCKET_ERROR를 반환한다. */
static int exchange_message(SOCKET sock, const char *message, int length)
{
    char echo[BUFFER_SIZE];
    int total = 0;

    if (send_all(sock, message, length) == SOCKET_ERROR) {
        fprintf(stderr, "[클라이언트] send 실패: %d\n", WSAGetLastError());
        return SOCKET_ERROR;
    }

    /* TCP는 메시지 경계가 없어 에코가 나뉘어 도착할 수 있으므로 보낸 길이만큼 받는다. */
    while (total < length) {
        int received = recv(sock, echo + total, length - total, 0);

        if (received == 0) {
            fprintf(stderr, "[클라이언트] 서버가 연결을 종료했습니다.\n");
            return SOCKET_ERROR;
        }
        if (received == SOCKET_ERROR) {
            fprintf(stderr, "[클라이언트] recv 실패: %d\n", WSAGetLastError());
            return SOCKET_ERROR;
        }
        total += received;
    }

    echo[total] = '\0';
    printf("[클라이언트] 에코: %s\n", echo);
    return 0;
}

/* "exit"를 입력할 때까지 콘솔 입력을 서버와 주고받은 뒤 전송 종료를 알린다. */
static int chat_loop(SOCKET sock)
{
    char message[BUFFER_SIZE];

    for (;;) {
        int length;

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

        if (exchange_message(sock, message, length) == SOCKET_ERROR) {
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
        printf("[클라이언트] %s:%d에 접속했습니다. 종료하려면 exit를 입력하세요.\n", SERVER_IP, PORT);
        exit_code = chat_loop(sock);
        closesocket(sock);
    }

    WSACleanup();
    printf("[클라이언트] 연결을 종료했습니다.\n");
    return exit_code;
}
