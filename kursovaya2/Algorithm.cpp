#include "pch.h"
#include "Interval.h"
#include <queue>
#include <list>
#include <Windows.h>
#include <fstream>

using PluralityIntervals = std::list<Interval>;

void SplitAndIntersection(PluralityIntervals& plurality, PluralityIntervals& pluralityDC);
void SplitAndIntersectionRec(PluralityIntervals& plurality, PluralityIntervals& pluralityDC);


int CountDrops(Interval& a, Interval& b)
{
	int count = 0;
	for (int i = 0; i < max(a.size(), b.size()); ++i)
	{
		if (i >= a.size())
		{
			if (b[i] != '0')
				++count;
		}
		else if (i >= b.size())
		{
			if (a[i] != '0')
				++count;
		}
		else if (a[i] != '-' && b[i] != '-' && a[i] != b[i])
		{
			++count;
		}

	}

	return count;
}

void PushPlurality(PluralityIntervals& plurality, PluralityIntervals& add)
{
	if (plurality.size() > 0 && add.size() > 0)
	{
		Interval pluralityFront = plurality.front();
		Interval pluralityBack = plurality.back();
		Interval addFront = add.front();
		Interval addBack = add.back();

		int pushFront = CountDrops(pluralityFront, addBack);
		int pushBack = CountDrops(pluralityBack, addFront);

		if (pushFront < pushBack)
			plurality.splice(plurality.begin(), add, add.begin(), add.end());
		else
			plurality.splice(plurality.end(), add, add.begin(), add.end());
	}
	else
	{
		plurality.splice(plurality.end(), add, add.begin(), add.end());
	}
}


int MaxDefinedWithDiff(PluralityIntervals& plurality)
{
	int max = 0, pos = -1;

	for (int i = 0; i < plurality.begin()->size(); ++i)
	{
		int count = 0;
		bool flagOne = false, flagZero = false;
		for (auto& interval : plurality)
		{
			char val = interval[i];
			if (val != '-')
				++count;
			if (!flagOne && val == '1')
				flagOne = true;
			if (!flagZero && val == '0')
				flagZero = true;
		}

		if (flagOne && flagZero && count > max)
		{
			max = count;
			pos = i;
		}
	}

	return pos;
}



void StartMethod( PluralityIntervals& plurality, PluralityIntervals& ans )
{
	if (plurality.size())
	{
	
		PluralityIntervals DC;

		SplitAndIntersectionRec( plurality, DC);

		ans.swap(plurality);
		
		if (DC.size())
		{
			PluralityIntervals addition;
			StartMethod(DC, addition);
		
			PushPlurality(ans, addition);
			//ans.splice(ans.end(), addition, addition.begin(), addition.end());
		}
	}
}




void SplitAndIntersection( PluralityIntervals& plurality, PluralityIntervals& pluralityDC )
{
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	//	1. Найти максимально определённую компоненту
	//	2. Разбить по ней исходное множество 
	//	3. Запустить рекурсию для каждого из этих множеств 
	//	4. Полученные множества попытаться пересечь с DC 
	//	5. Вернуть ответ и те вектора что не получилось пересечь с ответным 
	/////////////////////////////////////////////////////////////////////////////////////////////	

	PluralityIntervals ans;
	PluralityIntervals DC;
	std::queue<PluralityIntervals> qPlurality;
	qPlurality.push(plurality);

	while (!qPlurality.empty())
	{
		PluralityIntervals one;
		PluralityIntervals zero;
		PluralityIntervals current = qPlurality.front();
		qPlurality.pop();

		int splitPos = MaxDefinedWithDiff(current);
		if ( splitPos == -1 )
		{
			Interval Interaction = current.back();
			current.pop_back();
			while ( !current.empty() )
			{
				Interaction &= current.back();
				current.pop_back();
			}
			current.push_back(Interaction);
		}

		if (current.size() == 1)
		{
			//ans.push_back(current.back());
			PushPlurality(ans, current);
			continue;
		}

		one.clear();
		zero.clear();
		for ( auto& interval : current )
		{
			if ((char)interval[splitPos] == '1')
				one.push_back(interval);
			else if ((char)interval[splitPos] == '0')
				zero.push_back(interval);
			else
			{
				//bool flag = false;
				//for (auto& i : one)
				//{
				//	Interval tmp = interval & i;
				//	if (tmp.size() != 0)
				//	{
				//		i = tmp;
				//		flag = true;
				//		break;
				//	}
				//}
				//if(!flag)
				//	for (auto& i : zero)
				//	{
				//		Interval tmp = interval & i;
				//		if (tmp.size() != 0)
				//		{
				//			i = tmp;
				//			flag = true;
				//			break;
				//		}
				//	}

				//if(!flag)
					DC.push_back(interval);
			}
		}

		qPlurality.push(one);
		qPlurality.push(zero);
	}


	for ( auto& dcInterval : DC)
	{
		bool flag = false;
		for ( auto& ansInterval : ans)
		{
			Interval tmp = ansInterval & dcInterval;
			if (tmp.size() != 0)
			{
				ansInterval = tmp;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			pluralityDC.push_back(dcInterval);
		}
	}

	plurality.swap(ans);
	//pluralityDC.splice(pluralityDC.end(), DC, DC.begin(), DC.end());
}


void SplitAndIntersectionRec(PluralityIntervals& plurality, PluralityIntervals& pluralityDC)
{

	PluralityIntervals one;
	PluralityIntervals zero;
	PluralityIntervals DC;

	int splitPos = MaxDefinedWithDiff(plurality);
	if (splitPos == -1)
	{
		Interval Interaction = plurality.back();
		plurality.pop_back();
		while (!plurality.empty())
		{
			Interaction &= plurality.back();
			plurality.pop_back();
		}
		plurality.push_back(Interaction);
	}

	if (plurality.size() == 1)
	{
		return;
	}

	one.clear();
	zero.clear();
	for (auto& interval : plurality)
	{
		if ((char)interval[splitPos] == '1')
			one.push_back(interval);
		else if ((char)interval[splitPos] == '0')
			zero.push_back(interval);
		else
			DC.push_back(interval);
	}

	SplitAndIntersectionRec(one, pluralityDC);
	plurality.swap(one);
	SplitAndIntersectionRec(zero, pluralityDC);
	PushPlurality(plurality, zero);

	for (auto& dcInterval : DC)
	{
		bool flag = false;
		for (auto& ansInterval : plurality)
		{
			Interval tmp = ansInterval & dcInterval;
			if (tmp.size() != 0)
			{
				ansInterval = tmp;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			pluralityDC.push_back(dcInterval);
		}
	}
}


int main()
{

	//std::string v1("-11-0");
	//std::string v2("10-1-");
	//std::string v3("-0110");
	//std::string v4("00-10");
	//std::string v5("1-0-1");

	//PluralityIntervals p, ans;
	//p.push_back(v1);
	//p.push_back(v2);
	//p.push_back(v3);
	//p.push_back(v4);
	//p.push_back(v5);

	//StartMethod(p, ans);

	//for (auto& i: ans)
	//{
	//	std::cout << i.to_str()<<std::endl;
	//}

	std::ifstream in;
	std::ofstream out;
	
	std::wstring path(L"C:\\Users\\ShlR0\\source\\repos\\kursovaya2\\kursovaya2\\pr\\"), inFile(L"*.txt"), outFolder(L"ans2\\");

	WIN32_FIND_DATAW folder;

	HANDLE const hr = FindFirstFileW((path + inFile).c_str(), &folder);

	if (INVALID_HANDLE_VALUE != hr)
	{
		do
		{
			inFile = &folder.cFileName[0];

			in.open((path + inFile).c_str());
			out.open((path + outFolder + inFile).c_str());
			if (in.is_open() && out.is_open())
			{

				std::string str;
				PluralityIntervals Intervals, Ans;

				while (!in.eof())
				{
					in >> str;
					Intervals.push_back(Interval(str));
				}

				StartMethod(Intervals, Ans);

				out << Ans.size() << std::endl;
				for (auto& i : Ans)
					out << i.to_str() << std::endl;

				in.close();
				out.close();
			}

		} while (NULL != FindNextFileW(hr, &folder));
		FindClose(hr);
	}

	std::cout << "end";

	return 0;
}