#pragma once
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32")

#define DEFAULT_PORT "27015"

class Logger {
public:
	static void Init();
    template<typename... T> static void Write(const char* fmt, T&&... args) {
        char buff[1028]{'\0'};
        sprintf_s(buff, fmt, args...);
        size_t Total = strnlen_s(buff, 1028);
        int sent = send(m_pLoggerFilePointer, buff, Total, 0);
        while (sent < Total) {
            const char* a = buff + sent;
            sent += send(m_pLoggerFilePointer, a, Total - sent, 0); // ahh so this tells me how much bytes it actually SENT not the total amount of bytes sent across. got it.
        }
    }
	static void Destroy();
private:
    static inline unsigned long long m_pLoggerFilePointer = 0ull;
};

#define FMT_LOG(format, msg, ...) ::Logger::Write(format msg, __VA_ARGS__)