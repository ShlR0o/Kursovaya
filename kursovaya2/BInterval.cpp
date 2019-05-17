//#include "pch.h"
//
//proxy::proxy(uint8_t* cerPartVec, uint8_t* unkPartVec, uint64_t pos):
//	m_pos(pos)
//{
//	m_cerPartVec = cerPartVec;
//	m_unkPartVec = unkPartVec;
//}
//
//proxy::proxy(proxy& p):
//	m_pos(p.m_pos)
//{
//	m_cerPartVec = p.m_cerPartVec;
//	m_unkPartVec = p.m_unkPartVec;
//}
//
//proxy::proxy(proxy&& p):
//	m_pos(p.m_pos)
//{
//	m_cerPartVec = p.m_cerPartVec;
//	m_unkPartVec = p.m_unkPartVec;
//}
//
//proxy::~proxy()
//{
//}
//
//proxy::operator char()
//{
//	uint64_t tmp = ((uint64_t)1 << m_pos);
//	if (tmp & *m_unkPartVec)
//		return '-';
//
//	return (tmp & *m_cerPartVec) ? '1' : '0';
//}
//
//proxy& proxy::operator=(char& r)
//{
//	uint64_t tmp = ((uint64_t)1 << m_pos);
//	if (r == '1')
//		*m_cerPartVec |= tmp;
//	else if (r == '-')
//		*m_unkPartVec |= tmp;
//	else if (r == '0')
//		*m_cerPartVec |= (~tmp);
//	
//	return *this;
//}
//
//proxy& proxy::operator=(char&& r)
//{
//	uint64_t tmp = ((uint64_t)1 << m_pos);
//	if (r == '1')
//		*m_cerPartVec |= tmp;
//	else if (r == '-')
//		*m_unkPartVec |= tmp;
//	else if (r == '0')
//		*m_cerPartVec |= (~tmp);
//
//	return *this;
//}
//
////proxy& proxy::operator=(proxy r)
////{
////	uint64_t mask = ((uint64_t)1 << r.m_pos);
////	if (mask & *r.m_unkPartVec)
////	{
////		mask >>= std::abs((long long)(m_pos - r.m_pos));
////		*m_unkPartVec |= mask;
////	}
////	else
////	{
////		mask &= *r.m_cerPartVec;
////		mask >>= std::abs((long long)(m_pos - r.m_pos));
////		*m_cerPartVec |= mask;
////	}
////	return *this;
////}
//
//proxy& proxy::operator=(proxy&& r)
//{
//	uint64_t mask = ((uint64_t)1 << r.m_pos);
//	if (mask & *(r.m_cerPartVec))
//	{
//		mask >>= std::abs((long long)(m_pos - r.m_pos));
//		*m_unkPartVec |= mask;
//	}
//	else
//	{
//		mask &= *(r.m_cerPartVec);
//		mask >>= std::abs((long long)(m_pos - r.m_pos));
//		*m_cerPartVec |= mask;
//	}
//	return *this;
//}
//
////proxy & proxy::operator=(proxy && r)
////{
////	uint64_t mask = ((uint64_t)1 << r.m_pos);
////	if (mask & *r.m_unkPartVec)
////	{
////		mask >>= std::abs((long long)(m_pos - r.m_pos));
////		*m_unkPartVec |= mask;
////	}
////	else
////	{
////		mask &= *r.m_cerPartVec;
////		mask >>= std::abs((long long)(m_pos - r.m_pos));
////		*m_cerPartVec |= mask;
////	}
////	return *this;
////}
//
//BInterval::BInterval() :
//	m_size(0)
//{
//	m_certainComp = new uint8_t[0];
//	m_unkComp = new uint8_t[0];
//}
//
//BInterval::BInterval(BIntervalPtr bInterval):
//	m_size(bInterval->m_size)
//{
//	m_certainComp = new uint8_t[bInterval->m_size / 8 + 1];
//	m_unkComp = new uint8_t[bInterval->m_size / 8 + 1];
//
//	for (uint64_t i = 0; i < bInterval->m_size / 8; ++i)
//	{
//		m_certainComp[i] = bInterval->m_certainComp[i];
//		m_unkComp[i] = bInterval->m_unkComp[i];
//	}
//}
//
////BInterval::BInterval(BInterval && bInterval):
////	m_size(bInterval.m_size)
////{
////	m_certainComp = new uint8_t[bInterval.m_size / 8 + 1];
////	m_unkComp = new uint8_t[bInterval.m_size / 8 + 1];
////
////	for ( uint64_t i = 0; i < bInterval.m_size/8; ++i )
////	{
////		m_certainComp[i] = bInterval.m_certainComp[i];
////		m_unkComp[i] = bInterval.m_unkComp[i];
////	}
////}
//
//
//BInterval::BInterval(std::string& str)
//{
//	m_certainComp = new uint8_t[str.size() / 8 + 1];
//	m_unkComp = new uint8_t[str.size() / 8 + 1];
//	m_size = str.size();
//	to_str(str);
//}
//
//BInterval::~BInterval()
//{
//	if(m_certainComp)
//		delete[]m_certainComp;
//	
//	if(m_unkComp)
//		delete[]m_unkComp;
//}
//
////BInterval& BInterval::operator=(BInterval r)
////{
////	if (r.m_size <= m_size)
////	{
////		delete[]m_certainComp;
////		delete[]m_unkComp;
////
////		m_certainComp = new uint8_t[r.m_size / 8 + 1];
////		m_unkComp = new uint8_t[r.m_size / 8 + 1];
////	}
////
////	m_size = r.m_size;
////
////	for (uint64_t i = 0; i < r.m_size / 8 + 1; ++i)
////	{
////		m_certainComp[i] = r.m_certainComp[i];
////		m_unkComp[i] = r.m_unkComp[i];
////	}
////
////	return *this;
////}
//
//BIntervalPtr BInterval::operator=(BIntervalPtr r)
//{
//	if (r->m_size <= m_size)
//	{
//		delete[] m_certainComp;
//		delete[] m_unkComp;
//
//		m_certainComp = new uint8_t[r->m_size / 8 + 1];
//		m_unkComp = new uint8_t[r->m_size / 8 + 1];
//	}
//
//	m_size = r->m_size;
//
//	for (uint64_t i = 0; i < r->m_size / 8; ++i)
//	{
//		m_certainComp[i] = r->m_certainComp[i];
//		m_unkComp[i] = r->m_unkComp[i];
//	}
//
//	return shared_from_this();
//}
//
////BInterval & BInterval::operator=(BInterval&& r)
////{
////	delete[] m_certainComp;
////	delete[] m_unkComp;
////
////	m_certainComp = r.m_certainComp;
////	m_unkComp = r.m_unkComp;
////	m_size = r.m_size;
////
////	return *this;
////}
//
//BIntervalPtr BInterval::operator=(std::string& str)
//{
//	if (str.size() <= m_size)
//	{
//		delete[] m_certainComp;
//		delete[] m_unkComp;
//
//		m_certainComp = new uint8_t[str.size() / 8 + 1];
//		m_unkComp = new uint8_t[str.size() / 8 + 1];
//	}
//
//	m_size = str.size();
//
//	to_str(str);
//
//	return shared_from_this();
//}
//
//BIntervalPtr  BInterval::operator=(std::string&& str)
//{
//	if (str.size() <= m_size)
//	{
//		delete[] m_certainComp;
//		delete[] m_unkComp;
//
//		m_certainComp = new uint8_t[str.size() / 8 + 1];
//		m_unkComp = new uint8_t[str.size() / 8 + 1];
//	}
//
//	m_size = str.size();
//
//	to_str(str);
//
//	return shared_from_this();
//}
//
//std::string BInterval::str()
//{
//	std::string str;
//	if (m_certainComp != nullptr && m_unkComp != nullptr)
//	{
//		for (uint64_t i = 0; i < m_size; ++i)
//		{
//			uint64_t tmp = ((uint64_t)1 << i);
//			if (m_unkComp[i / 8] & tmp)
//				str.push_back('-');
//			else if (m_certainComp[i / 8] & tmp)
//				str.push_back('1');
//			else str.push_back('0');
//		}
//	}
//	return str;
//}
//
//proxy BInterval::getPosition(uint64_t pos)
//{
//	return proxy((m_certainComp + (pos / 8)), (m_unkComp + (pos / 8)), pos);
//}
//
//BIntervalPtr BInterval::operator&(BIntervalPtr r)
//{
//	BIntervalPtr ans(std::make_shared<BInterval>());
//
//	ans->m_size = std::max(r->m_size, m_size);
//	ans->m_certainComp = new uint8_t[std::max(r->m_size, m_size) / 8 + 1];
//	ans->m_unkComp = new uint8_t[std::max(r->m_size, m_size) / 8 + 1];
//	for (int i = 0; i < std::max(r->m_size/8, m_size/8); ++i)
//	{
//		if (i < r->m_size && i < m_size)
//		{
//			uint64_t mask = r->m_unkComp[i] | m_unkComp[i];
//			if ((mask | m_certainComp[i]) != (mask | r->m_certainComp[i]))
//			{
//				delete[]ans->m_unkComp;
//				delete[]ans->m_certainComp;
//				ans->m_size = (uint64_t)0;
//				return std::move(ans);
//			}
//
//			ans->m_certainComp[i] = (m_certainComp[i] | r->m_certainComp[i]);
//			ans->m_unkComp[i] = (m_unkComp[i] & r->m_unkComp[i]);
//
//			continue;
//		}
//		else if (i < r->m_size)
//		{
//			ans->m_certainComp[i] = r->m_certainComp[i];
//			ans->m_unkComp[i] = r->m_unkComp[i];
//			continue;
//		}
//		else
//		{
//			ans->m_certainComp[i] = m_certainComp[i];
//			ans->m_unkComp[i] = m_unkComp[i];
//			continue;
//		}	
//	}
//
//	return ans;
//}
//
//BIntervalPtr BInterval::operator&=(BIntervalPtr r)
//{
//	BIntervalPtr ans (std::make_shared<BInterval>());
//
//	ans->m_size = std::max(r->m_size, m_size);
//	ans->m_certainComp = new uint8_t[std::max(r->m_size, m_size) / 8 + 1];
//	ans->m_unkComp = new uint8_t[std::max(r->m_size, m_size) / 8 + 1];
//
//	for (int i = 0; i < std::max(r->m_size / 8, m_size / 8); ++i)
//	{
//		if (i < r->m_size && i < m_size)
//		{
//			uint64_t mask = r->m_unkComp[i] | m_unkComp[i];
//			if ((mask | m_certainComp[i]) != (mask | r->m_certainComp[i]))
//			{
//				return shared_from_this();
//			}
//
//			ans->m_certainComp[i] = (m_certainComp[i] | r->m_certainComp[i]);
//			ans->m_unkComp[i] = (m_unkComp[i] & r->m_unkComp[i]);
//
//			continue;
//		}
//		else if (i < r->m_size)
//		{
//			ans->m_certainComp[i] = r->m_certainComp[i];
//			ans->m_unkComp[i] = r->m_unkComp[i];
//			continue;
//		}
//		else
//		{
//			ans->m_certainComp[i] = m_certainComp[i];
//			ans->m_unkComp[i] = m_unkComp[i];
//			continue;
//		}
//	}
//
//	delete[] m_certainComp;
//	delete[] m_unkComp;
//
//	m_certainComp = r->m_certainComp;
//	m_unkComp = r->m_unkComp;
//	m_size = ans->m_size;
//
//	return shared_from_this();
//}
//
//BIntervalPtr BInterval::operator|(BIntervalPtr r)
//{
//	//NOTIMPL
//	return shared_from_this();
//}
//
//void BInterval::to_str(std::string & str)
//{
//	uint8_t tmp = 0;
//	uint8_t tmpUnk = 0;
//	uint64_t i = 0;
//	for (; i < str.size(); ++i)
//	{
//		uint8_t t = ((uint8_t)1 << i);
//		if (str[i] == '1')
//			tmp |= t;
//
//		if (str[i] == '-')
//			tmpUnk |= t;
//
//		if (i % 8 == 7)
//		{
//			m_certainComp[i / 8] = tmp;
//			m_unkComp[i / 8] = tmpUnk;
//		}
//	}
//
//	m_certainComp[i / 8] = tmp;
//	m_unkComp[i / 8] = tmpUnk;
//}
