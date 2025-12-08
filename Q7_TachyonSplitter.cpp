#include "Q7_TachyonSplitter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void Q7_TachyonSplitter::Solve(int& numberOfSplits, long long& numOfPaths)
{
    std::ifstream infile("Q7_TachyonSplitDiagram.txt");
    std::string line = "";

    std::map<int, long long> tIndices;

    char lineDelim = '\n';

    std::vector<std::string> lines;
    int maxLineLength = 0;

    char startChar = 'S';
    char splitChar = '^';

    auto findChar = [this](std::string& input, char& c) {
        for (int i = 0; i < input.length(); ++i)
        {
            if (input[i] == c)
            {
                return i;
            }
        }
        return -1;
        };


    while (std::getline(infile, line, lineDelim))
    {
        if (line.length() > maxLineLength)
        {
            maxLineLength = line.length();
        }
        lines.push_back(line);


        if (tIndices.empty())
        {
            int startIndex = findChar(line, startChar);

            if (startIndex >= 0)
            {
                tIndices.insert({ startIndex, 1 });
            }
        }
        else
        {
            for (auto it = tIndices.begin(); it != tIndices.end();)
            {
                int tIndex = (*it).first;
                if (line[tIndex] == splitChar)
                {
                    ++numberOfSplits;

                    long long incomingCount = (*it).second;
                    it = tIndices.erase(it);

                    if (tIndex > 0)
                    {
                        int splitIndex = tIndex - 1;
                        line[splitIndex] = '|';

                        if (tIndices.contains(splitIndex))
                        {
                            tIndices[splitIndex] += incomingCount;
                        }
                        else
                        {
                            tIndices.insert({ splitIndex, incomingCount });
                        }

                    }

                    if (tIndex < maxLineLength + 1)
                    {
                        int splitIndex = tIndex + 1;
                        line[splitIndex] = '|';

                        if (tIndices.contains(splitIndex))
                        {
                            tIndices[splitIndex] += incomingCount;
                        }
                        else
                        {
                            tIndices.insert({ splitIndex, incomingCount });
                        }
                    }

                }
                else
                {
                    line[tIndex] = '|';
                    ++it;
                }
            }
        }
        //std::cout << line << "\n";
    }

    for (auto t : tIndices)
    {
        numOfPaths += t.second;
        //std::cout << t.second << "\n";
    }
}
