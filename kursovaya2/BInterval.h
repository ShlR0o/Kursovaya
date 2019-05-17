//#pragma once
//#include "pch.h"
//
//class BInterval;
//class proxy;
//
//typedef std::shared_ptr<BInterval>	BIntervalPtr;
//
//
//class proxy
//{
//public:
//	proxy(uint8_t* cerPartVec, uint8_t* unkPartVec, uint64_t pos);
//	proxy(proxy& p);
//	proxy(proxy&& p);
//	~proxy();
//	operator char();
//	proxy& operator=(char& r);
//	proxy& operator=(char&& r);
//	//proxy& operator=(proxy r);
//	proxy& operator=(proxy&& r);
//	//proxy& operator=(proxy&& r);
//private:
//	uint8_t *m_cerPartVec;
//	uint8_t *m_unkPartVec;
//	uint64_t m_pos;
//};
//
//
//class BInterval:
//	std::enable_shared_from_this<BInterval>
//{
//public:
//	BInterval();
//	BInterval(BIntervalPtr bInterval);
//	//BInterval(BInterval&& bInterval);
//	BInterval(std::string& str);
//	~BInterval();
//	
//	//BInterval& operator=(BInterval r);
//	BIntervalPtr operator=(BIntervalPtr r);
//	//BIntervalPtr operator=(BInterval&& r);
//	BIntervalPtr operator=(std::string& r);
//	BIntervalPtr operator=(std::string&& r);
//	std::string str();
//	proxy getPosition(uint64_t pos);
//
//	BIntervalPtr operator&(BIntervalPtr r);
//	BIntervalPtr operator&=(BIntervalPtr r);
//	BIntervalPtr operator|(BIntervalPtr r);
//
//private:
//
//	void to_str(std::string& str);
//
//	uint8_t *m_certainComp;
//	uint8_t *m_unkComp;
//	uint64_t m_size;
//};
//
