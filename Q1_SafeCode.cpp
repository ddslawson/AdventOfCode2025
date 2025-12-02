#include "Q1_SafeCode.h"
#include <iostream>
#include <fstream>
#include <string>

void Q1_SafeCode::Solve(int& zeroCount, int& zeroClickCount)
{
    std::ifstream infile("Q1_SafeCode.txt");

    std::string line = "";
    int currentNumber = 50;
    int absCount = 0;
    zeroCount = 0;
    zeroClickCount = 0;
    char direction;
    int nextSteps = 0;
    bool atZero = false;
    while (infile >> line)
    {
        // Parse direction and step count
        direction = line[0];
        nextSteps = atoi(&line[1]);

        // Apply steps in correct direction
        if (direction == 'L')
        {
            currentNumber -= nextSteps;
        }
        else
        {
            currentNumber += nextSteps;
        }

        // Add 1 zero click if number has gone negative without starting at zero
        if (currentNumber <= 0 && !atZero)
        {
            ++zeroClickCount;
        }

        // Add zero clicks per 100 crossed
        absCount = std::abs(currentNumber);
        if (absCount >= 100)
        {
            zeroClickCount += absCount / 100;
        }

        // Detect landing on zero
        currentNumber %= 100;
        atZero = currentNumber == 0;
        if (atZero)
        {
            ++zeroCount;
        }

        // Wrap negative numbers to 0-99
        if (currentNumber < 0)
        {
            currentNumber += 100;
        }
    }
}
