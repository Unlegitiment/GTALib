#pragma once
class IOBase {
public:
	virtual void* Read(size_t readSize) = 0;
	virtual void Write(const void* writeBlk, size_t writeSize) = 0;
	virtual ~IOBase() {};
};