#include "netLog.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32")
void Logger::Init() {
    int iResult{};
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        return;
    }
    struct addrinfo* result = NULL,
        * ptr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = GetAddrInfoA("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        return;
    }
    m_pLoggerFilePointer = INVALID_SOCKET;
    ptr = result;
    m_pLoggerFilePointer = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (m_pLoggerFilePointer == INVALID_SOCKET) {
        FreeAddrInfoA(result);
        WSACleanup();
        return;
    }
    iResult = connect(m_pLoggerFilePointer, ptr->ai_addr, (int)ptr->ai_addrlen);
    while (iResult < 0) {
        iResult = connect(m_pLoggerFilePointer, ptr->ai_addr, (int)ptr->ai_addrlen);;
    }
    FreeAddrInfoA(result);
    if (m_pLoggerFilePointer == INVALID_SOCKET) {
        WSACleanup();
        return;
    }
}

void Logger::Destroy() {
    int iRes = shutdown(m_pLoggerFilePointer, SD_SEND);
    if (iRes == SOCKET_ERROR) {
        closesocket(m_pLoggerFilePointer);
        WSACleanup();
        return;
    }
}
