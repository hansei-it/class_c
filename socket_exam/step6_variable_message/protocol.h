/*
 * protocol.h - 서버와 클라이언트가 함께 쓰는 통신 규약 (6단계: 가변 길이 메시지)
 *
 * 메시지는 고정 길이 헤더와 가변 길이 본문으로 이루어진다.
 *   [type 4바이트][length 4바이트][본문 length바이트]
 * 받는 쪽은 헤더 8바이트를 먼저 읽고, 헤더에 적힌 length만큼 본문을 읽는다.
 *
 * 종류별 본문 내용 (숫자는 네트워크 바이트 순서)
 *   정수 덧셈  요청 [a 4][b 4]    응답 [합 8]
 *   실수 덧셈  요청 [a 8][b 8]    응답 [합 8]
 *   문자열     요청 [문자열 N]    응답 [같은 문자열 N]   ('\0' 없음, N은 0일 수 있음)
 *   처리 불가  응답의 type만 TYPE_ERROR, 본문 없음
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <winsock2.h>
#include <stdint.h>
#include <string.h>

#define PORT 9001

#define HEADER_SIZE 8
#define MAX_BODY_SIZE 4096

#define TYPE_INT_ADD 1
#define TYPE_DOUBLE_ADD 2
#define TYPE_STRING 3
#define TYPE_ERROR 4

/* recv_message의 결과 */
#define MESSAGE_OK 0
#define MESSAGE_CLOSED 1       /* 메시지 사이에서 상대방이 연결을 끊음 (정상 종료) */
#define MESSAGE_SOCKET_ERROR 2 /* recv 실패 */
#define MESSAGE_TRUNCATED 3    /* 메시지 중간에서 상대방이 연결을 끊음 */
#define MESSAGE_TOO_LONG 4     /* 헤더의 length가 MAX_BODY_SIZE를 넘음 */

/* 값을 네트워크 바이트 순서로 버퍼에 쓴다. 버퍼의 임의 위치에 쓸 수 있도록 memcpy를 쓴다. */
static inline void put_uint32(char *buffer, uint32_t value)
{
    uint32_t network = htonl(value);

    memcpy(buffer, &network, sizeof(network));
}

static inline uint32_t get_uint32(const char *buffer)
{
    uint32_t network;

    memcpy(&network, buffer, sizeof(network));
    return ntohl(network);
}

static inline void put_int32(char *buffer, int32_t value)
{
    put_uint32(buffer, (uint32_t)value);
}

static inline int32_t get_int32(const char *buffer)
{
    return (int32_t)get_uint32(buffer);
}

static inline void put_int64(char *buffer, int64_t value)
{
    unsigned __int64 network = htonll((unsigned __int64)value);

    memcpy(buffer, &network, sizeof(network));
}

static inline int64_t get_int64(const char *buffer)
{
    unsigned __int64 network;

    memcpy(&network, buffer, sizeof(network));
    return (int64_t)ntohll(network);
}

static inline void put_double(char *buffer, double value)
{
    unsigned __int64 network = htond(value);

    memcpy(buffer, &network, sizeof(network));
}

static inline double get_double(const char *buffer)
{
    unsigned __int64 network;

    memcpy(&network, buffer, sizeof(network));
    return ntohd(network);
}

/* send()는 요청한 길이보다 적게 보내고 반환할 수 있으므로 전부 보낼 때까지 반복한다. */
static inline int send_all(SOCKET sock, const char *data, int length)
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

/* recv()는 메시지가 나뉘어 도착하면 일부만 돌려주므로 length바이트를 채울 때까지 반복한다.
   받은 바이트 수를 반환한다. length보다 작으면 상대방이 연결을 끊은 것이고, 오류면 SOCKET_ERROR다. */
static inline int recv_all(SOCKET sock, char *data, int length)
{
    int total = 0;

    while (total < length) {
        int received = recv(sock, data + total, length - total, 0);
        if (received == SOCKET_ERROR) {
            return SOCKET_ERROR;
        }
        if (received == 0) {
            break;
        }
        total += received;
    }
    return total;
}

/* 메시지 하나를 보낸다. length는 MAX_BODY_SIZE 이하여야 한다.
   헤더와 본문을 따로 send하면 네이글 알고리즘 때문에 응답이 늦어질 수 있어 한 버퍼에 모아 보낸다. */
static inline int send_message(SOCKET sock, uint32_t type, const char *body, uint32_t length)
{
    char packet[HEADER_SIZE + MAX_BODY_SIZE];

    put_uint32(packet, type);
    put_uint32(packet + 4, length);
    if (length > 0) {
        memcpy(packet + HEADER_SIZE, body, length);
    }
    return send_all(sock, packet, HEADER_SIZE + (int)length);
}

/* 메시지 하나를 받아 MESSAGE_OK 등의 결과를 반환한다. body는 MAX_BODY_SIZE 이상이어야 한다. */
static inline int recv_message(SOCKET sock, uint32_t *type, char *body, uint32_t *length)
{
    char header[HEADER_SIZE];
    int received = recv_all(sock, header, HEADER_SIZE);

    if (received == SOCKET_ERROR) {
        return MESSAGE_SOCKET_ERROR;
    }
    if (received == 0) {
        return MESSAGE_CLOSED;
    }
    if (received < HEADER_SIZE) {
        return MESSAGE_TRUNCATED;
    }

    *type = get_uint32(header);
    *length = get_uint32(header + 4);

    /* 상대방이 보낸 길이는 믿을 수 없다. 버퍼에 담기 전에 반드시 상한을 확인한다. */
    if (*length > MAX_BODY_SIZE) {
        return MESSAGE_TOO_LONG;
    }

    received = recv_all(sock, body, (int)*length);
    if (received == SOCKET_ERROR) {
        return MESSAGE_SOCKET_ERROR;
    }
    if (received < (int)*length) {
        return MESSAGE_TRUNCATED;
    }
    return MESSAGE_OK;
}

#endif
