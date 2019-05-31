#include "pch.h"
#include "algorithmObj.h"


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

	//Interval a = v1;

	////algorithmObj::method(p, ans);

	//auto it1 = p.begin();
	//auto it2 = it1;
	//++it2;
	//(*it1)[0] = (*it2)[0];
	////(*it1)[0] = '1';
	//std::cout << (*it1)[0] ;


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

				algorithmObj::method(Intervals, Ans);

				out << algorithmObj::countDrops(Ans)<<std::endl;

				algorithmObj::sort(Ans, 0);

				out << algorithmObj::countDrops(Ans) << std::endl;
				out << Ans.size() << std::endl;
				//for (auto& i : Ans)
				//	out << i.to_str() << std::endl;

				in.close();
				out.close();
			}

		} while (NULL != FindNextFileW(hr, &folder));
		FindClose(hr);
	}

	std::cout << "end";

	return 0;
}