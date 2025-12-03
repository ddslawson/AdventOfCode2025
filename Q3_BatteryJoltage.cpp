#include "Q3_BatteryJoltage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Q3_BatteryJoltage::Solve(unsigned long long& joltageSum, int& numLength)
{
    std::vector<long> maxNums(numLength);
    std::ifstream infile("Q3_JoltageInfo.txt");
    std::string line = "";
    while (infile >> line)
    {
        //std::cout << line << "\n";

        /*unsigned char max1 = 0;
        int max1Index = -1;

        for (int i = 0; i < line.length() - 1; ++i)
        {
            unsigned char num = line[i] - '0';

            if (num > max1)
            {
                max1 = num;
                max1Index = i;
            }
        }

        unsigned char max2 = 0;
        int max2Index = -1;

        for (int i = max1Index + 1; i < line.length(); ++i)
        {
            unsigned char num = line[i] - '0';

            if (num > max2)
            {
                max2 = num;
            }
        }*/

        int maxNumRunningStart = 0;

        for (int j = 0; j < numLength; ++j)
        {
            maxNums[j] = 0;
            for (int i = maxNumRunningStart; line.length() - i > numLength - j - 1; ++i)
            {
                unsigned char num = line[i] - '0';

                if (num > maxNums[j])
                {
                    maxNums[j] = num;
                    maxNumRunningStart = i + 1;
                }
            }
        }

        //std::cout << "Max for line: ";
        for (int i = 0, j = numLength - 1; i < numLength; ++i, --j)
        {
            //std::cout << maxNums[i];
            //std::cout << maxNums[j] << " x " << pow(10, i) << "\n";
            joltageSum += maxNums[j] * pow(10, i);
        }
        //std::cout << "\n";
        //std::cout << "Running Sum: " << joltageSum << "\n";

        //std::cout << "Max for line " << (max1 * 10) + max2 << "\n";
        //joltageSum += ((int)max1 * 10) + max2;
        //std::cout << "Running Sum " << joltageSum << "\n";

    }
}
