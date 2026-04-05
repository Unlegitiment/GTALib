#pragma once
#define NO_COPY(T) T& operator=(const T&) = delete; T(const T&) = delete;