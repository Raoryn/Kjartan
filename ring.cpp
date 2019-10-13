#include "pch.h"
#include "ring.h"

template<class T>
RingBuffer<T>::RingBuffer()
{
	
}

template<class T>
RingBuffer<T>::RingBuffer(int size)
{
	Buffer = new T[size];
	BufferSize = size;
	NumOfElements = 0;
	ReadIndex = 0;
	WriteIndex = 0;
	
}


template<class T>
RingBuffer<T>::~RingBuffer()
{
	delete[] Buffer;
}

template<class T>
bool RingBuffer<T>::notEmpty()
{
	return NumOfElements != 0;
}

template<class T>
bool RingBuffer<T>::notFull()
{
	return NumOfElements != BufferSize; 
}

template<class T>
void RingBuffer<T>::put(T val) 
{
	unique_lock<mutex> lck(lock); 
	EmptyCv.wait(lck, [this]() {return notFull(); }); 

	Buffer[WriteIndex] = val; 
	incWriteIndex(); 

	lck.unlock(); 

	FullCv.notify_one(); 

}

template<class T>
T RingBuffer<T>::get() 
{

	unique_lock<mutex> lck(lock); 

	FullCv.wait(lck, [this]() {return notEmpty(); }); 

	T consumed = Buffer[ReadIndex]; 
	incReadIndex(); 

	lck.unlock(); 
	EmptyCv.notify_one(); 

	return consumed; 

}

template<class T>
void RingBuffer<T>::printindex()
{


	cout << "numofelements: " << NumOfElements << endl; 


}

template<class T>
void RingBuffer<T>::incWriteIndex()
{
	WriteIndex = (WriteIndex + 1) % BufferSize; 
	NumOfElements++; 
}

template<class T>
void RingBuffer<T>::incReadIndex()
{
	ReadIndex = (ReadIndex + 1) % BufferSize; 
	NumOfElements--; 
}
