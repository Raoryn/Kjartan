// RingbufferInnlevering.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ring.cpp"
#include <thread>

void writer(RingBuffer<char>& buffer); 
void reader(RingBuffer<char>& buffer); 
void keyboardInput(RingBuffer<char>& buffer); 

int main()
{
	RingBuffer<char> RingBuffer(5); //BigDaddy

	thread writerThread(&writer, ref(RingBuffer)); //child
	thread keyboardInputThread(&keyboardInput, ref(RingBuffer)); //child
	thread readerThread(&reader, ref(RingBuffer)); //child




	keyboardInputThread.join(); 
	writerThread.join(); 
	readerThread.join(); 



	return 0; //yey	
}



void writer(RingBuffer<char>& buffer) 
{

	string s = "0123456789";
	for (char c : s)
	{
		buffer.put(c);
		this_thread::sleep_for(chrono::milliseconds(200));
		

	}

};

void keyboardInput(RingBuffer<char>& buffer) 
{
	string s;
	do
	{
		cin >> s;

		{
			for (char c : s)
			{
				buffer.put(c);
				
			}

		}

	} while (s != "EXIT");
};


void reader(RingBuffer<char>& buffer) 
{

	
	while ((true))
	{
		char tmp;

		tmp = buffer.get();
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << tmp;
		



	}
};
