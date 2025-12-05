#include "Q5_IngredientExpiryCheck.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void Q5_IngredientExpiryCheck::Solve(int& expiredIngredientCount, long long& freshIDCount)
{
    std::ifstream infile("Q5_Ingredients.txt");
    std::string line = "";
    int rowLength = 0;
    int columnLength = 0;
    std::string fullLine = "";
    bool first = true;
    bool processRanges = true;

    auto findChar = [this](std::string& input, char& c) {
        for (int i = 0; i < input.length(); ++i)
        {
            if (input[i] == c)
            {
                return i;
            }
        }
        };

    char rangeDash = '-';
    long long rangeStart = 0;
    long long rangeEnd = 0;

    std::map<long long, long long> validIDRanges;

    int idRangesCountedIndex = -1;

    while (std::getline(infile, line))
    {
        //std::cout << line << std::endl;

        if (line.empty())
        {
            // Empty line - Switch to processing ingredients
            processRanges = false;
            long long itPrevKey = validIDRanges.cbegin()->first;
            auto it = validIDRanges.cbegin();
            ++it;

            for (; it != validIDRanges.cend();)
            {
                if (it->first <= validIDRanges[itPrevKey] + 1)
                {
                    if (it->second <= validIDRanges[itPrevKey])
                    {
                        // Range included in previous range
                        it = validIDRanges.erase(it);
                    }
                    else
                    {
                        validIDRanges[itPrevKey] = it->second;
                        it = validIDRanges.erase(it);
                    }
                }
                else
                {
                    itPrevKey = it->first;
                    ++it;
                }
            }
        }
        else if (processRanges)
        {
            // Process ranges
            int dashIndex = findChar(line, rangeDash);

            rangeStart = atoll(&line[0]);
            rangeEnd = atoll(&line[dashIndex + 1]);

            if (rangeStart == LLONG_MAX || rangeEnd == LLONG_MAX)
            {
                std::cout << "MAX" << std::endl;
            }

            //std::cout << "Range:" << rangeStart << "-" << rangeEnd << std::endl;

            if (rangeStart <= rangeEnd)
            {
                if (validIDRanges.contains(rangeStart))
                {
                    //std::cout << "CONFLICT" << std::endl;
                    if (rangeEnd > validIDRanges[rangeStart])
                    {
                        validIDRanges[rangeStart] = rangeEnd;
                    }
                }
                else
                {
                    validIDRanges.insert({ rangeStart, rangeEnd });
                }
            }
        }
        else
        {
            // Process Ingredients
            long long ingedientID = atoll(&line[0]);
            bool valid = false;
            int index = 0;
            for (auto it = validIDRanges.cbegin(); it != validIDRanges.cend(); ++it)
            {
                if (index > idRangesCountedIndex)
                {
                    //std::cout << "Adding " << (it->second - it->first) + (long long)1 << std::endl;
                    freshIDCount += (it->second - it->first) + 1;
                    //std::cout << "TOTAL: " << freshIDCount << std::endl;
                    idRangesCountedIndex = index;
                }
                if (it->first <= ingedientID && it->second >= ingedientID)
                {
                    //std::cout << ingedientID << " valid in range:" << it->first << "-" << it->second << std::endl;
                    valid = true;
                    break;
                }
                ++index;
            }
            expiredIngredientCount += valid;
        }
    }
}
