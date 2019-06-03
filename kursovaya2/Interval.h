#pragma once
#include "ProxyBit.h"

class Interval;

using PluralityIntervals = std::list<Interval>;

class Interval
{
public:
	
	Interval();
	Interval(Interval const & r);
	Interval(Interval const && r);
	Interval(std::string& str);
	Interval(std::string&& str);
	Interval& operator=(Interval const & r);
	Interval& operator=(Interval const && r);
	Interval& operator=(std::string const & str);
	Interval& operator=(std::string const && str);
	~Interval();

	Interval operator&(Interval& r);
	Interval& operator&=(Interval& r);
	bool operator==(Interval& r);
	ProxyBit operator[](uint64_t pos);

	std::string to_str();
	int size();

private:
	void _str_to(std::string const& str);
	inline void _clear();
	inline void _copy(Interval const& r);
	inline void _myRealloc(int newSize);

	byte *m_certainComp;
	byte *m_unkComp;
	int m_size;
	int m_ASize;
};

