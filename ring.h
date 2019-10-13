#pragma once

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include "..\..\std_lib_facilities.h"

template<class T>
class RingBuffer
{
public:
	RingBuffer();
	RingBuffer(int size);
	~RingBuffer();

	void put(T val);
	
	T get();
	void printindex();
/*
	T tryGet();
	T peek();
*/
	bool notFull();
	bool notEmpty();

	//int size();
	//int bufferSize();

	//Ring& operator<<(T obj);
	//Ring& operator<<(T& obj);
	//

private:
	void incWriteIndex();
	void incReadIndex();
	T* Buffer;

	int NumOfElements = 0;
	int BufferSize = 0;

	int ReadIndex = 0;
	int WriteIndex = 0;

	mutex lock;
	/*std::mutex mAccessMutex;
	std::mutex mReadMutex;
	std::mutex mWriteMutex;
	std::mutex mNumberMutex;*/
	condition_variable FullCv;
	condition_variable EmptyCv;

};

