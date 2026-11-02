/*
 * protocol.h - 서버와 클라이언트가 함께 쓰는 통신 규약 (5단계: 고정 길이 메시지)
 *
 * 요청과 응답 모두 항상 68바이트다. 안 쓰는 부분은 0으로 채운다.
 *   [type 4바이트][payload 64바이트]
 *
 * 종류별 payload 내용 (숫자는 네트워크 바이트 순서)
 *   정수 덧셈  요청 [a 4][b 4]       응답 [합 8]
 *   실수 덧셈  요청 [a 8][b 8]       응답 [합 8]
 *   문자열     요청 [문자열, '\0']   응답 [같은 문자열, '\0']
 *   처리 불가  응답의 type만 TYPE_ERROR
 *
 * 짧은 문자열도 68바이트를 쓰고, 63바이트보다 긴 문자열은 담을 수 없는 것이 이 방식의 한계다.
 * 6단계에서 가변 길이 메시지로 해결한다.
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <winsock2.h>
#include <stdint.h>
#include <string.h>

#define PORT 9001

#define TYPE_SIZE 4
#define PAYLOAD_SIZE 64
#define MESSAGE_SIZE (TYPE_SIZE + PAYLOAD_SIZE)
#define MAX_TEXT_LENGTH (PAYLOAD_SIZE - 1) /* 끝의 '\0' 자리를 뺀 길이 */

#define TYPE_INT_ADD 1
#define TYPE_DOUBLE_ADD 2
#define TYPE_STRING 3
#define TYPE_ERROR 4

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

#endif
