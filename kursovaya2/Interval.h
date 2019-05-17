#pragma once
#include "ProxyBit.h"


class Interval
{
public:
	
	Interval();
	Interval(Interval& r);
	Interval(Interval&& r);
	Interval(std::string& str);
	Interval(std::string&& str);
	Interval& operator=(Interval& r);
	Interval& operator=(Interval&& r);
	Interval& operator=(std::string& str);
	Interval& operator=(std::string&& str);
	~Interval();

	Interval operator&(Interval& r);
	Interval& operator&=(Interval& r);
	bool operator==(Interval& r);
	ProxyBit operator[](uint64_t pos);

	std::string to_str();
	int size();

private:
	void _str_to(std::string& str);
	inline void _clear();
	inline void _copy(Interval& r);
	inline void _myRealloc(int newSize);

	byte *m_certainComp;
	byte *m_unkComp;
	int m_size;
	int m_ASize;
};

