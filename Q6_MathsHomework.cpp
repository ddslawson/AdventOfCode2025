#include "Q6_MathsHomework.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void Q6_MathsHomework::Solve(long long& answerSum)
{
    std::ifstream infile("Q6_MathsHW.txt");
    std::string line = "";
    std::string segment = "";

    std::vector<std::vector<int>> sums;
    std::vector<std::string> operations;

    char lineDelim = '\n';
    while (std::getline(infile, line, lineDelim))
    {
        std::stringstream iss;
        iss << line;
        bool readOperations = false;
        int colNum = 0;

        while (iss >> segment)
        {
            if (colNum > (int)sums.size() - 1)
            {
                sums.push_back(std::vector<int>());
            }

            if (!readOperations && (segment[0] == '*' || segment[0] == '+'))
            {
                readOperations = true;
            }

            if (!readOperations)
            {
                int num = std::atoi(&segment[0]);
                sums[colNum].push_back(num);
            }
            else
            {
                operations.push_back(segment);
            }
            ++colNum;
        }
    }

    long long columnSum = 0;

    for (int i = 0; i < sums.size(); ++i)
    {
        //std::cout << "EQ: ";

        for (int j = 0; j < sums[i].size(); ++j)
        {
            if (j == 0)
            {
                //std::cout << sums[i][j] << " ";
                columnSum = sums[i][j];
            }
            else
            {
                char op = operations[i][0];
                if (op == '+')
                {
                    //std::cout << "+ " << sums[i][j] << " ";
                    columnSum += sums[i][j];
                }
                else
                {
                    //std::cout << "* " << sums[i][j] << " ";
                    columnSum *= sums[i][j];
                }
            }
        }
        //std::cout << "= " << columnSum << std::endl;
        answerSum += columnSum;
    }
}

void Q6_MathsHomework::Solve2(long long& answer2Sum)
{
    std::ifstream infile("Q6_MathsHW.txt");
    std::string line = "";

    std::vector<std::vector<int>> sums;
    std::vector<std::string> operations;

    char lineDelim = '\n';

    std::vector<std::string> lines;
    int maxLineLength = 0;
    while (std::getline(infile, line, lineDelim))
    {
        if (line.length() > maxLineLength)
        {
            maxLineLength = line.length();
        }
        lines.push_back(line);
    }

    // Grab operations
    std::stringstream iss;
    std::string operationLine = lines.back();
    lines.pop_back();
    iss << operationLine;

    std::string operation;
    while (iss >> operation)
    {
        operations.push_back(operation);
    }

    int columnIndex = 0;

    for (int lineIndex = 0; lineIndex < maxLineLength; ++lineIndex)
    {
        if (columnIndex > (int)sums.size() - 1)
        {
            sums.push_back(std::vector<int>());
        }
        std::string numString = "";

        bool isSpace = true;
        for (int i = 0; i < lines.size(); ++i)
        {
            if (!isspace(lines[i][lineIndex]))
            {
                isSpace = false;
                numString += lines[i][lineIndex];
            }
        }

        if (isSpace)
        {
            ++columnIndex;
        }
        else
        {
            sums[columnIndex].push_back(atoi(&numString[0]));
        }
    }

    long long columnSum = 0;

    for (int i = 0; i < sums.size(); ++i)
    {
        //std::cout << "EQ: ";

        for (int j = 0; j < sums[i].size(); ++j)
        {
            if (j == 0)
            {
                //std::cout << sums[i][j] << " ";
                columnSum = sums[i][j];
            }
            else
            {
                char op = operations[i][0];
                if (op == '+')
                {
                    //std::cout << "+ " << sums[i][j] << " ";
                    columnSum += sums[i][j];
                }
                else
                {
                    //std::cout << "* " << sums[i][j] << " ";
                    columnSum *= sums[i][j];
                }
            }
        }
        //std::cout << "= " << columnSum << std::endl;
        answer2Sum += columnSum;
    }
}
