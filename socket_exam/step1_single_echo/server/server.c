/*
 * server.c - TCP 에코 서버 (1단계: 메시지 한 번 주고받기)
 *
 * 소켓 함수의 호출 순서를 익히기 위한 가장 단순한 형태다.
 * 클라이언트 하나를 받아 메시지를 한 번 돌려보내고 바로 종료한다.
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

#define PORT 9001
#define BUFFER_SIZE 1024

int main(void)
{
    WSADATA wsa_data;
    SOCKET listen_sock;
    SOCKET client_sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int received;

    /* 1. Winsock 초기화 */
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    /* 2. TCP 소켓 생성 */
    listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* 3. 소켓에 주소와 포트 지정 */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* 4. 접속 대기 시작 */
    listen(listen_sock, SOMAXCONN);
    printf("[서버] 포트 %d에서 접속 대기 중...\n", PORT);

    /* 5. 클라이언트 접속 수락 */
    client_sock = accept(listen_sock, NULL, NULL);

    /* 6. 메시지를 받아 출력하고 그대로 돌려보낸다. recv는 실패 시 -1을 반환하므로 인덱스로 쓰기 전에 확인한다. */
    received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("[서버] %d바이트 수신: %s\n", received, buffer);
        send(client_sock, buffer, received, 0);
    } else {
        printf("[서버] 받은 메시지가 없습니다.\n");
    }

    /* 7. 소켓 닫기와 Winsock 정리 */
    closesocket(client_sock);
    closesocket(listen_sock);
    WSACleanup();
    printf("[서버] 종료했습니다.\n");
    return 0;
}
