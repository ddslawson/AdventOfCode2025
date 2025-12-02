#include "Q2_ProductIDCheck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void Q2_ProductIDCheck::Solve(long long& invalidIDCount)
{
	invalidIDCount = 0;
	std::ifstream infile("Q2_ProductIDs.txt");
	std::stringstream iss;
	iss << infile.rdbuf();
	std::string segment = "";
	char delimiter = ',';
	char rangeSeparator = '-';
	while (std::getline(iss, segment, delimiter))
	{
		std::cout << segment << "\n";
		auto rangeSepIndex = segment.find(rangeSeparator);
		std::string rangeStartStr = segment.substr(0, rangeSepIndex);
		std::string rangeEndStr = segment.substr(rangeSepIndex + 1);

		if (rangeStartStr.empty() || rangeEndStr.empty())
		{
			std::cout << "Empty" << "\n";
			++invalidIDCount;
		}
		else if (rangeStartStr[0] == '0' || rangeEndStr[0] == '0')
		{
			std::cout << "Zero" << "\n";
			++invalidIDCount;
		}
		else if (rangeStartStr.length() == rangeEndStr.length() && rangeStartStr.length() % 2 != 0)
		{
			std::cout << "Odd length = Valid" << "\n";
		}
		else
		{
			long long rangeStart = std::atoll(rangeStartStr.c_str());
			long long rangeEnd = std::atoll(rangeEndStr.c_str());
			std::cout << rangeStart << " " << rangeEnd << "\n";

			if (rangeStart == LLONG_MAX || rangeEnd == LLONG_MAX)
			{
				std::cout << "MAX\n";
			}

			if (rangeStart > rangeEnd)
			{
				std::cout << "BACKWARDS\n";
			}

			std::string numAsStr;
			for (; rangeStart <= rangeEnd; ++rangeStart)
			{
				numAsStr = std::to_string(rangeStart);
				int divisor = 2;
				bool matching = CheckStringDivisions(numAsStr, divisor);

				if (matching)
				{
					invalidIDCount += rangeStart;
					//std::cout << "Matching " << numAsStr << "\n";
				}

				//if (numLength % 2 == 0)
				//{
				//	numLength /= 2;
				//	int s1Index = 0;
				//	int s2Index = numLength;
				//	bool matching = true;

				//	for (; s1Index < numLength && matching; ++s1Index, ++s2Index)
				//	{
				//		if (numAsStr[s1Index] != numAsStr[s2Index])
				//		{
				//			matching = false;
				//		}
				//	}

				//	if (matching)
				//	{
				//		invalidIDCount += rangeStart;
				//		std::cout << "Matching " << numAsStr << "\n";
				//	}
				//}
				//else
				//{
				//	//std::cout << "Odd length = Valid" << "\n";
				//}
			}
		}
	}
}

void Q2_ProductIDCheck::Solve2(long long& invalidIDCountType1, long long& invalidIDCount)
{
	invalidIDCount = 0;
	std::ifstream infile("Q2_ProductIDs.txt");
	std::stringstream iss;
	iss << infile.rdbuf();
	std::string segment = "";
	char delimiter = ',';
	char rangeSeparator = '-';

	auto findChar = [this](std::string& input, char& c) {
			for (int i = 0; i < input.length(); ++i)
			{
				if (input[i] == c)
				{
					return i;
				}
			}
		};
	while (std::getline(iss, segment, delimiter))
	{
		//std::cout << segment << "\n";
		int rangeSepIndex = findChar(segment, rangeSeparator);
		std::string rangeStartStr = segment.substr(0, rangeSepIndex);
		std::string rangeEndStr = segment.substr(rangeSepIndex + 1);

		if (rangeStartStr.empty() || rangeEndStr.empty())
		{
			std::cout << "Empty" << "\n";
			++invalidIDCount;
		}
		else if (rangeStartStr[0] == '0' || rangeEndStr[0] == '0')
		{
			std::cout << "Zero" << "\n";
			++invalidIDCount;
		}
		else
		{
			long long rangeStart = std::atoll(rangeStartStr.c_str());
			long long rangeEnd = std::atoll(rangeEndStr.c_str());
			//std::cout << rangeStart << " " << rangeEnd << "\n";

			if (rangeStart == LLONG_MAX || rangeEnd == LLONG_MAX)
			{
				std::cout << "MAX\n";
			}

			if (rangeStart > rangeEnd)
			{
				std::cout << "BACKWARDS\n";
			}

			std::string numAsStr;
			for (; rangeStart <= rangeEnd; ++rangeStart)
			{
				std::string numAsStr;
				for (; rangeStart <= rangeEnd; ++rangeStart)
				{
					if (rangeStart / 10 == 0)
					{
						break;
					}
					numAsStr = std::to_string(rangeStart);
					int numLength = numAsStr.length();
					int halfLength = numLength / 2;
					std::vector<std::string> subNums;
					for (int i = numLength - 1; i > 0; --i)
					{
						bool matching = CheckStringDivisions(numAsStr, i);
						/*int subNumLength = i;
						int subNumCount = numLength / i;
						std::vector<int> subNums(subNumCount);

						bool matching = true;
						for (int j = 0; j < subNumCount; ++j)
						{
							subNums[j] = std::atoi(numAsStr.substr(j * subNumLength, subNumLength).c_str());
						}

						int checkNum = subNums.front();

						for (int j = 1; j < subNumCount && matching; ++j)
						{
							if (checkNum != subNums[j])
							{
								matching = false;
							}
						}*/

						if (matching)
						{
							invalidIDCount += rangeStart;
							if (numLength % 2 == 0 && i == halfLength)
							{
								invalidIDCountType1 += rangeStart;
							}
							//std::cout << "Matching " << i << "-string " << numAsStr << "\n";
							break;
						}
					}
				}

			}
		}
	}
}

bool Q2_ProductIDCheck::CheckStringDivisions(std::string& numAsStr, int& divisor)
{
	int numLength = numAsStr.length();
	if (numLength % divisor == 0)
	{
		bool matching = true;
		int numCount = numLength / divisor;

		std::vector<int> indices(numCount);

		for (int i = 0; i < numCount; ++i)
		{
			indices[i] = i * divisor;
		}

		while (indices[0] < divisor && matching)
		{
			char check = numAsStr[indices[0]];
			for (int i = 1; i < numCount && matching; ++i)
			{
				if (check != numAsStr[indices[i]])
				{
					matching = false;
				}
			}

			for (int i = 0; i < numCount; ++i)
			{
				++indices[i];
			}
		}
		return matching;
	}
	return false;
}


