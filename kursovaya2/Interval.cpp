#include "pch.h"
#include "Interval.h"



Interval::Interval():
	m_size(0),
	m_ASize(1)
{
	m_certainComp = new byte[1];
	m_unkComp = new byte[1];

	m_certainComp[0] = 0;
	m_unkComp[0] = 0;
}

Interval::Interval(Interval const& r):
	m_size(r.m_size),
	m_ASize(r.m_ASize)
{
	m_certainComp = new byte[m_ASize];
	m_unkComp = new byte[m_ASize];

	_copy(r);
}

Interval::Interval(Interval const&& r):
	m_size(r.m_size),
	m_ASize(r.m_ASize)
{
	m_certainComp = new byte[m_ASize];
	m_unkComp = new byte[m_ASize];

	_copy(r);
}

Interval::Interval(std::string & str):
	m_size(str.size()),
	m_ASize(str.size()/8 + 1)
{
	m_certainComp = new byte[m_ASize];
	m_unkComp = new byte[m_ASize];
	_str_to(str);
}

Interval::Interval(std::string && str):
	m_size(str.size()),
	m_ASize(str.size() / 8 + 1)
{
	m_certainComp = new byte[m_ASize];
	m_unkComp = new byte[m_ASize];
	_str_to(str);
}

Interval & Interval::operator=(Interval const& r)
{
	return operator=(std::move(r));
}

Interval & Interval::operator=(Interval const&& r)
{
	m_size = r.m_size;
	_myRealloc(r.m_ASize);
	_copy(r);

	return *this;
}

Interval & Interval::operator=(std::string const& str)
{
	return operator=(std::move(str));
}

Interval & Interval::operator=(std::string const&& str)
{
	m_size = str.size();
	_myRealloc(str.size() / 8 + 1);
	_str_to(str);

	return *this;
}



Interval::~Interval()
{
	_clear();
}

Interval Interval::operator&(Interval & r)
{
	int maxSize = std::max(m_ASize, r.m_ASize);

	Interval ans;
	ans.m_ASize = maxSize;
	ans.m_size = std::max(m_size, r.m_size);
	ans.m_certainComp = new byte[maxSize];
	ans.m_unkComp = new byte[maxSize];

	for (int i = 0; i < maxSize; ++i) 
	{
		if (i < m_ASize && i < r.m_ASize)
		{
			byte mask = r.m_unkComp[i] | m_unkComp[i];
			if ((mask | m_certainComp[i]) != (mask | r.m_certainComp[i]))
			{
				return Interval();
			}

			ans.m_certainComp[i] = (m_certainComp[i] | r.m_certainComp[i]);
			ans.m_unkComp[i] = (m_unkComp[i] & r.m_unkComp[i]);
			ans.m_certainComp[i] &= (~ans.m_unkComp[i]);
		}
		else if (i < m_ASize)
		{
			ans.m_certainComp[i] = m_certainComp[i];
			ans.m_unkComp[i] = m_unkComp[i];
		}
		else
		{
			ans.m_certainComp[i] = r.m_certainComp[i];
			ans.m_unkComp[i] = r.m_unkComp[i];
		}
	}

	return ans;
}

Interval & Interval::operator&=(Interval & r)
{
	int maxSize = std::max(m_ASize, r.m_ASize);
	byte *cer = new byte[maxSize];
	byte *unk = new byte[maxSize];

	for (int i = 0; i < maxSize; ++i)
	{
		if (i < m_ASize && i < r.m_ASize)
		{
			byte mask = r.m_unkComp[i] | m_unkComp[i];
			if ((mask | m_certainComp[i]) != (mask | r.m_certainComp[i]))
			{
				return *this;
			}

			cer[i] = (m_certainComp[i] | r.m_certainComp[i]);
			unk[i] = (m_unkComp[i] & r.m_unkComp[i]);
			cer[i] &= (~unk[i]);
		}
		else if (i < m_ASize)
		{
			cer[i] = m_certainComp[i];
			unk[i] = m_unkComp[i];
		}
		else
		{
			cer[i] = r.m_certainComp[i];
			unk[i] = r.m_unkComp[i];
		}
	}

	_clear();

	m_certainComp = cer;
	m_unkComp = unk;
	m_ASize = maxSize;
	m_size = std::max(m_size, r.m_size);

	return *this;
}

bool Interval::operator==(Interval & r)
{
	if (m_size != r.m_size)
		return false;

	int minSize = std::min(m_ASize, r.m_ASize);
	for (int i = 0; i < minSize; i++)
	{
		if (m_unkComp[i] != r.m_unkComp[i] || m_certainComp[i] != r.m_certainComp[i])
			return false;
	}

	return true;
}

ProxyBit Interval::operator[](uint64_t pos)
{
	return ProxyBit( m_certainComp[pos/8], m_unkComp[pos/8] , pos % 8);
}

std::string Interval::to_str()
{
	std::string str;
	byte tmp = 1;
	for (int i = 0; i < m_size; ++i)
	{
		tmp = (byte)1 << (i % 8);
		if (m_unkComp[i / 8] & tmp)
			str.push_back('-');
		else if (m_certainComp[i / 8] & tmp)
			str.push_back('1');
		else 
			str.push_back('0');
	}

	return str;
}

int Interval::size()
{
	return m_size;
}

void Interval::_str_to(std::string const& str)
{
	byte tmp = 0;
	byte tmpUnk = 0;
	int i = 0;
	byte t;
	for  (; i < str.size(); ++i)
	{
		t = (byte)1 << (i % 8);
		if (str[i] == '1')
			tmp |= t;

		if (str[i] == '-')
			tmpUnk |= t;

		if (i % 8 == 7 || i == str.size() - 1)
		{
			m_certainComp[i / 8] = tmp;
			m_unkComp[i / 8] = tmpUnk;
			tmp = tmpUnk = 0;
		}
	}
}

void Interval::_clear()
{
	if (m_ASize)
	{
		if (m_ASize != 1)
		{
			delete[] m_unkComp;
			delete[] m_certainComp;
		}
		else
		{
			delete m_unkComp;
			delete m_certainComp;
		}
	}
}

void Interval::_copy(Interval const& r)
{
	for (int i = 0; i < m_ASize; ++i)
	{
		m_certainComp[i] = r.m_certainComp[i];
		m_unkComp[i] = r.m_unkComp[i];
	}
}

inline void Interval::_myRealloc(int newSize)
{
	if (m_ASize < newSize)
	{
		_clear();

		m_ASize = newSize;
		m_certainComp = new byte[m_ASize];
		m_unkComp = new byte[m_ASize];
	}
}


