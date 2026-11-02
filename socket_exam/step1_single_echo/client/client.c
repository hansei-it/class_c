/*
 * client.c - TCP 에코 클라이언트 (1단계: 메시지 한 번 주고받기)
 *
 * 소켓 함수의 호출 순서를 익히기 위한 가장 단순한 형태다.
 * 127.0.0.1:9001 서버에 접속해 고정된 메시지를 보내고, 에코를 출력한 뒤 바로 종료한다.
 * 흐름이 잘 보이도록 오류 처리는 생략했다. (2단계에서 추가)
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
    const char *message = "Hello, Server!";
    char buffer[BUFFER_SIZE];
    int received;

    /* 1. Winsock 초기화 */
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    /* 2. TCP 소켓 생성 */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* 3. 서버에 접속 */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* 4. 메시지 전송 */
    send(sock, message, (int)strlen(message), 0);

    /* 5. 에코를 받아 출력한다. recv는 실패 시 -1을 반환하므로 인덱스로 쓰기 전에 확인한다. */
    received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("[클라이언트] 에코: %s\n", buffer);
    } else {
        printf("[클라이언트] 에코를 받지 못했습니다. 서버가 실행 중인지 확인하세요.\n");
    }

    /* 6. 소켓 닫기와 Winsock 정리 */
    closesocket(sock);
    WSACleanup();
    return 0;
}
