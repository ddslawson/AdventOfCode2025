#pragma once
#include <string>

class Q2_ProductIDCheck
{
public:
	void Solve(long long& invalidIDCount);
	void Solve2(long long& invalidIDSumType1, long long& invalidIDSum);
private:
	bool CheckStringDivisions(std::string& numAsStr, int& divisor);
};

