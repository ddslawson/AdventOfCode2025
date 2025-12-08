// AdventOfCode2025.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "Q1_SafeCode.h"
#include "Q2_ProductIDCheck.h"
#include "Q3_BatteryJoltage.h"
#include "Q4_PaperRolls.h"
#include "Q5_IngredientExpiryCheck.h"
#include "Q6_MathsHomework.h"

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

void Question4()
{
    std::cout << "QUESTION 4\n";

    Q4_PaperRolls q4 = Q4_PaperRolls();

    int avgCount = 10;

    int paperCount = 0;

    auto q4Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        paperCount = 0;
        q4.Solve(paperCount, false);
    }
    auto q4End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q4_Duration = q4End - q4Start;
    std::cout << "Q4 ANSWER 1: " << paperCount << " Time: " << q4_Duration.count() / avgCount << "ms\n";

    q4Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        paperCount = 0;
        q4.Solve(paperCount, true);
    }
    q4End = std::chrono::high_resolution_clock::now();

    q4_Duration = q4End - q4Start;
    std::cout << "Q4 ANSWER 2: " << paperCount << " Time: " << q4_Duration.count() / avgCount << "ms\n";
}

void Question5()
{
    std::cout << "QUESTION 5\n";

    Q5_IngredientExpiryCheck q5 = Q5_IngredientExpiryCheck();

    int avgCount = 20;
    int expiredIngredientCount = 0;
    long long freshIDCount = 0;

    auto q5Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        expiredIngredientCount = 0;
        freshIDCount = 0;
        q5.Solve(expiredIngredientCount, freshIDCount);
    }
    auto q5End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q5_Duration = q5End - q5Start;
    std::cout << "Q5 ANSWER 1: " << expiredIngredientCount << " ANSWER 2: " << freshIDCount << " Time: " << q5_Duration.count() / avgCount << "ms\n";
}

void Question6()
{
    std::cout << "QUESTION 6\n";

    Q6_MathsHomework q6 = Q6_MathsHomework();

    int avgCount = 10;
    long long answerSum = 0;
    long long answerSum2 = 0;

    auto q6Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        answerSum = 0;
        q6.Solve(answerSum);
    }
    auto q6End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> q6_Duration = q6End - q6Start;
    std::cout << "Q6 ANSWER 1: " << answerSum << " Time: " << q6_Duration.count() / avgCount << "ms\n";

    q6Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < avgCount; ++i)
    {
        answerSum2 = 0;
        q6.Solve2(answerSum2);
    }
    q6End = std::chrono::high_resolution_clock::now();

    q6_Duration = q6End - q6Start;
    std::cout << "Q6 ANSWER 2: " << answerSum2 << " Time: " << q6_Duration.count() / avgCount << "ms\n";
}


int main()
{
    std::cout << "ADVENT OF CODE 2025\n";

    //Question1();

    //Question2();

    //Question3();

    //Question4();

    //Question5();

    Question6();
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
