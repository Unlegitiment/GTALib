#pragma once
#include "../IOBase.h"
#include <string>
#include <string.h>
#include <sstream>



class CNetworkInit {
public:
	static void InitWSA();
	static inline bool sm_IsWSAInit = false;
};
enum eNetProtocol {
	ENP_TCP,
	ENP_UDP
};
struct sNetworkCxnBase {
	const char* IP, * Port;
	eNetProtocol Proto;
};
class CSocketInterface {
public:
	template<typename T> struct SocketResult {
	private:
		friend class CSocketInterface;
		bool DidActionSucceed = false;
		const char* m_Err = "";
		T m_FinalData;
	public:
		operator bool() const {
			return DidActionSucceed; // check this works.
		}
		SocketResult(T data) {
			this->m_FinalData = data;
		}
		const char* GetErr() { return this->m_Err; }
		bool Succeeded() { return DidActionSucceed; }
		T Target() { return this->m_FinalData; }
	};
	template<typename T> using Res = SocketResult<T>;
	SocketResult<int> OpenSocket(const sNetworkCxnBase& base);
	void CloseSocket(int ValidSocketAddress);
	void Write(int SocketDesc, const void* Buffer, const size_t Size);
	void Write(int SocketDesc, const void* Buffer, const size_t Size, const int Flags);
};
class CNetworkSocket : public IOBase{
public:
	CNetworkSocket(CSocketInterface* CxnBasis, const sNetworkCxnBase* cxn) :
		m_Basis(CxnBasis), 
		m_Connection(cxn) 
	{
		auto res = m_Basis->OpenSocket(*cxn);
		if (!res.Succeeded()) {
			//FUCK
			return;
		}
		this->m_SocketFd = res.Target();
	}
	const char* GetIP() {
		return this->m_Connection->IP;
	}
	const char* GetPort() {
		return this->m_Connection->Port;
	}
	std::string GetConnectionAddress() {
		std::stringstream str;
		str << GetIP() << "::" << GetPort() << std::endl;
		return str.str();
	}
	const sNetworkCxnBase* GetConnectionDetails() {
		return this->m_Connection;
	}
	// Inherited via IOBase
	void* Read(size_t readSize) override;

	void Write(const void* writeBlk, size_t writeSize) override;

	~CNetworkSocket() {
		Write("Goodbye!", 8);
		m_Basis->CloseSocket(m_SocketFd);
	}
private:
	int m_SocketFd = 0;
	const sNetworkCxnBase* m_Connection = nullptr;
	CSocketInterface* m_Basis = nullptr;
};