#include "CNetworkSocket.h"

#include "WinSock2.h"
#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32")
void* CNetworkSocket::Read(size_t readSize)
{
    return nullptr; // right now I don't really care to read from a netsocket. Thanks though. 
}

void CNetworkSocket::Write(const void* writeBlk, size_t writeSize)
{
	m_Basis->Write(this->m_SocketFd, writeBlk, writeSize);
}

CSocketInterface::SocketResult<int> CSocketInterface::OpenSocket(const sNetworkCxnBase& base) {
	struct addrinfo* result = nullptr;
	struct addrinfo hints = {};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP; // @Todo: Fix

	int addrResult = GetAddrInfoA(base.IP, base.Port, &hints, &result);
	if (addrResult != 0 || result == nullptr) {
		SocketResult<int> res = SocketResult<int>(-1);
		res.DidActionSucceed = false;
		res.m_Err = "GetAddrInfoA failed.";
		return res;
	}
	SOCKET sock = INVALID_SOCKET;
	for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sock == INVALID_SOCKET) {
			continue;
		}
		if (connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen) == 0) {
			break; // success
		}
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
	FreeAddrInfoA(result);
	if (sock == INVALID_SOCKET) {
		SocketResult<int> res = SocketResult<int>(-1);
		res.DidActionSucceed = false;
		res.m_Err = "Failed to connect to Socket.";
		return res;
	}
	SocketResult<int> res = SocketResult<int>(sock);
	res.DidActionSucceed = true;
	res.m_Err = "";
	return res;
}

void CSocketInterface::CloseSocket(int ValidSocketAddress) {
	shutdown(ValidSocketAddress, SD_SEND);
	// Wait briefly for outgoing data to flush
	char buf[64];
	while (recv(ValidSocketAddress, buf, sizeof(buf), 0) > 0) {}
	closesocket(ValidSocketAddress);
}

void CSocketInterface::Write(int SocketDesc, const void* Buffer, const size_t Size) {
	Write(SocketDesc, Buffer, Size, 0);
	return;
}

void CSocketInterface::Write(int SocketDesc, const void* Buffer, const size_t Size, const int Flags) {
	const char* data = static_cast<const char*>(Buffer);
	size_t totalSent = 0;

	while (totalSent < Size) {
		int sent = send(SocketDesc, data + totalSent, static_cast<int>(Size - totalSent), Flags);
		if (sent == SOCKET_ERROR) {
			int err = WSAGetLastError();
			// optionally print/log err here
			break;
		}
		if (sent == 0) break; // connection closed
		totalSent += sent;
	}
	return;
}

void CNetworkInit::InitWSA() {
	if (sm_IsWSAInit) { return; }
	int iResult = 0;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return;
	}
	sm_IsWSAInit = true;
}
