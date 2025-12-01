// AdventOfCode2025.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "Q1_SafeCode.h"

int main()
{
    std::cout << "ADVENT OF CODE 2025\n";
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
    std::cout << "Q1 ANSWER 1: " << q1_A1 << " Q1 ANSWER 2: " << q1_A2 << " Time: " << q1_Duration.count()/avgCount << "\n";
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
