// AdventOfCode2025.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "Q1_SafeCode.h"
#include "Q2_ProductIDCheck.h"
#include "Q3_BatteryJoltage.h"

void Question1()
{
    std::cout << "QUESTION 1\n";

    Q1_SafeCode q1 = Q1_SafeCode();

    int q1_A1 = 0;
    int q1_A2 = 0;

    int avgCount = 100;

    auto q1Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        q1.Solve(q1_A1, q1_A2);
    }
    auto q1End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q1_Duration = q1End - q1Start;
    std::cout << "Q1 ANSWER 1: " << q1_A1 << " Q1 ANSWER 2: " << q1_A2 << " Time: " << q1_Duration.count() / avgCount << "ms\n";
}

void Question2()
{
    std::cout << "QUESTION 2\n";

    Q2_ProductIDCheck q2 = Q2_ProductIDCheck();

    int avgCount = 1;

    long long invalidIDSum = 0;
    long long invalidIDSum2 = 0;

    auto q2Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        //q2.Solve(invalidIDSum);
        q2.Solve2(invalidIDSum, invalidIDSum2);
    }
    auto q2End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q2_Duration = q2End - q2Start;
    std::cout << "Q2 ANSWER 1: " << invalidIDSum << " ANSWER 2: " << invalidIDSum2 << " Time: " << q2_Duration.count() / avgCount << "ms\n";
}

void Question3()
{
    std::cout << "QUESTION 3\n";

    Q3_BatteryJoltage q3 = Q3_BatteryJoltage();

    int avgCount = 10;

    int numLength = 2;
    unsigned long long joltageSum = 0;

    auto q3Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        numLength = 2;
        joltageSum = 0;
        q3.Solve(joltageSum, numLength);
    }
    auto q3End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q3_Duration = q3End - q3Start;
    std::cout << "Q3 ANSWER 1: " << joltageSum << " Time: " << q3_Duration.count() / avgCount << "ms\n";

    numLength = 12;
    joltageSum = 0;
    q3Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        numLength = 12;
        joltageSum = 0;
        q3.Solve(joltageSum, numLength);
    }
    q3End = std::chrono::high_resolution_clock::now();

    q3_Duration = q3End - q3Start;
    std::cout << "Q3 ANSWER 2: " << joltageSum << " Time: " << q3_Duration.count() / avgCount << "ms\n";
}

int main()
{
    std::cout << "ADVENT OF CODE 2025\n";

    Question1();

    Question2();

    Question3();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
