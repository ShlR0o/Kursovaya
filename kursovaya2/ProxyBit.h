#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <list>

typedef unsigned char byte;

class ProxyBit
{
public:
	ProxyBit() = delete;
	ProxyBit(byte &cer_, byte &unk_, int pos_);
	//Конструкторы производят не глубокое копирование
	ProxyBit(ProxyBit& r);
	ProxyBit(ProxyBit&& r);
	//Операторы присваивания производят глубокое копирование
	ProxyBit& operator=(ProxyBit& r);
	ProxyBit& operator=(ProxyBit&& r);
	ProxyBit& operator=(char& r);
	ProxyBit& operator=(char&& r);
	operator char();
	
	~ProxyBit();

private:
	inline void offsetToCurrent( byte& mask, int pos );

	byte *m_cer;
	byte *m_unk;
	int   m_pos;
};

