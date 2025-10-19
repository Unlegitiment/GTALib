#pragma once
#include "network\CNetworkSocket.h"
#include <stdio.h>
#include <stdarg.h>
#include "Colors.h"
class Logger {
public:
	static void Init() {
		m_Interface = new CSocketInterface();
		m_Description = new sNetworkCxnBase();
		m_Description->IP = "127.0.0.1";
		m_Description->Port = "27015";
		m_Description->Proto = eNetProtocol::ENP_TCP;
		m_Socket = new CNetworkSocket(m_Interface, m_Description);
	}
	static void Write(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		char buffer[1028] = { 0 };
		_vsnprintf_s(buffer, sizeof(buffer), fmt, args);
		va_end(args);
		int res = strnlen_s(buffer, 1028);
		m_Socket->Write(buffer, res);
	}
	static void Writeln(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		char buffer[1028] = { 0 };
		_vsnprintf_s(buffer, sizeof(buffer), fmt, args);
		va_end(args);
		int res = strnlen_s(buffer, 1028);
		m_Socket->Write(buffer, res);
		m_Socket->Write("\n", 1);
	}
	static void Shutdown() {
		Logger::Writeln("Shutdown Triggered!");

		delete m_Socket; m_Socket = nullptr;
		delete m_Description; m_Description = nullptr;
		delete m_Interface; m_Interface = nullptr;
	}
private:
	Logger() {

	}
	~Logger() {
		Writeln("~Logger Triggered!");
		Shutdown();
	}
	static inline CNetworkSocket* m_Socket = nullptr;
	static inline CSocketInterface* m_Interface = nullptr;
	static inline sNetworkCxnBase* m_Description = nullptr;
};

//Major improvements must come for the logging solution. 
#define CHANNEL_COLOR(Name, Color) static constexpr const char* Channel_##Name = Color;
#define __LAG_LOGF__(channel, fmt, ...) Logger::Writeln("%s" "[INFO]" fmt RNorm, Channel_##channel, __VA_ARGS__)
#define __LAG_WARNF__(channel, fmt, ...) Logger::Writeln(RYellow "[WARN]" fmt RNorm, __VA_ARGS__)