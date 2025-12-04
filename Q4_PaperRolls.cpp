#include "Q4_PaperRolls.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Q4_PaperRolls::Solve(int& numAccessible, bool shouldRetry)
{
    std::ifstream infile("Q4_PaperRolls.txt");
    std::string line = "";
    int rowLength = 0;
    int columnLength = 0;
    std::string fullLine = "";
    bool first = true;
    while (infile >> line)
    {
        if (first == true)
        {
            rowLength = line.length();
            first = false;
        }
        //std::cout << line << std::endl;
        fullLine += line;
        ++columnLength;
    }
    //std::cout << rowLength << " x " << columnLength << " " << fullLine << std::endl;

    int fullLineLength = fullLine.length();

    auto getWindowIndices = [this, rowLength, columnLength](int& centreIndex, std::string& grid, std::vector<int>& windowIndices) {
        windowIndices = 
        {
            centreIndex - rowLength - 1,
            centreIndex - rowLength,
            centreIndex - rowLength + 1,
            centreIndex - 1,
            centreIndex + 1,
            centreIndex + rowLength - 1,
            centreIndex + rowLength,
            centreIndex + rowLength + 1
        };
        };

    bool tryAgain = true;
    int tryCount = 1;
    std::vector<int> neighbours(8);
    int paperCount = 0;
    int numAccessibleCache = 0;
    while (tryAgain == true)
    {
        //std::cout << "TRY " << tryCount++ << std::endl;
        numAccessibleCache = numAccessible;
        for (int i = 0; i < fullLine.length(); ++i)
        {
            if (fullLine[i] == '@')
            {
                //std::cout << "(" << i % rowLength << ", " << (int)i / rowLength << ")" << std::endl;
                getWindowIndices(i, fullLine, neighbours);

                paperCount = 0;
                for (int n : neighbours)
                {
                    //std::cout << "(" << n % rowLength << ", " << (int)n / rowLength << ")" << std::endl;
                    if (n < 0 || n > fullLineLength)
                    {
                        //std::cout << n << " out of bounds" << std::endl;
                    }
                    else if ((i % rowLength) - (n % rowLength) < -1 || (i % rowLength) - (n % rowLength) > 1)
                    {
                        //std::cout << n << " out of bounds" << std::endl;
                    }
                    else if (fullLine[n] == '@')
                    {
                        ++paperCount;
                    }
                }
                //std::cout << "Paper count: " << paperCount << std::endl;
                if (paperCount < 4)
                {
                    ++numAccessible;
                    if (shouldRetry)
                    {
                        fullLine[i] = '.';
                    }
                }
            }
        }
        //std::cout << "Picked Paper Count: " << numAccessible - numAccessibleCache << std::endl;
        tryAgain = numAccessible > numAccessibleCache && shouldRetry;
    }
}


