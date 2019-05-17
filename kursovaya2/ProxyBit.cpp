#include "pch.h"
#include "ProxyBit.h"


ProxyBit::ProxyBit(byte &cer_, byte &unk_, int pos_):
	m_cer(&cer_),
	m_unk(&unk_),
	m_pos(pos_)
{
}

ProxyBit::ProxyBit(ProxyBit & r):
	m_cer(r.m_cer),
	m_unk(r.m_unk),
	m_pos(r.m_pos)
{
}

ProxyBit::ProxyBit(ProxyBit && r):
	m_cer(r.m_cer),
	m_unk(r.m_unk),
	m_pos(r.m_pos)
{
}

ProxyBit & ProxyBit::operator=(ProxyBit & r)
{
	return operator=(std::move(r));
}

ProxyBit & ProxyBit::operator=(ProxyBit && r)
{
	byte mask = ((byte)1 << r.m_pos);

	if (mask & (*r.m_unk))
	{
		offsetToCurrent(mask, r.m_pos);
		m_unk[0] |= mask;
		m_cer[0] &= (~(*m_unk));
		return *this;
	}

	if (mask & (*r.m_cer))
	{
		offsetToCurrent(mask, r.m_pos);
		m_cer[0] |= mask;
	}
	else
	{
		offsetToCurrent(mask, r.m_pos);
		m_cer[0] &= (~mask);
	}

	return *this;
}

ProxyBit & ProxyBit::operator=(char & r)
{
	return operator=(std::move(r));
}

ProxyBit & ProxyBit::operator=(char && r)
{
	byte tmp = ((byte)1 << m_pos);
	
	if (r == '-')
	{
		m_unk[0] |= tmp;
		m_cer[0] &= (~(*m_unk));
	}
	else if (r == '1')
		m_cer[0] |= tmp;
	else if (r == '0')
		m_cer[0] &= (~tmp);

	return *this;

}

ProxyBit::operator char()
{
	byte tmp = ((byte)1 << m_pos);
	if (tmp & m_unk[0])
		return '-';

	return (tmp & m_cer[0]) ? '1' : '0';
}


ProxyBit::~ProxyBit()
{
}

void ProxyBit::offsetToCurrent( byte& mask, int pos)
{
	if (m_pos - pos > 0)
		mask <<= (m_pos - pos);
	else
		mask >>= (pos - m_pos);
}
