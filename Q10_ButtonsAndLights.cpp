#include "Q10_ButtonsAndLights.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

void Q10_ButtonsAndLights::Solve(long long& numOfPresses)
{
    std::ifstream infile("Q10_MachineDiagram.txt");
    std::string line;

    char lightsStart = '[';
    char lightsEnd = ']';
    char joltageStart = '{';
    char joltageEnd = '}';
    char buttonStart = '(';
    char buttonEnd = ')';
    char separator = ',';

    auto findChar = [this](std::string& input, char& c, int startIndex = 0) {
        for (int i = startIndex; i < input.length(); ++i)
        {
            if (input[i] == c)
            {
                return i;
            }
        }
        return -1;
        };

    std::vector<std::pair<std::vector<int>, std::map<int, std::vector<std::vector<int>>>>> lightsToButtonPressResultMap;

    std::vector <std::vector<unsigned char>> targetsPerLine;
    std::vector <int> targetsPerLineInt;
    std::vector<int> minPressesPerLine;

    int lineIndex = 0;

    // Parse targets and buttons per line;
    while (std::getline(infile, line))
    {
        //std::cout << line << "\n";
        int lightsEndIndex = findChar(line, lightsEnd);

        std::string lightString = line.substr(1, lightsEndIndex - 1);

        std::vector<unsigned char> lightTarget;
        int lightTargetInt = 0;
        for (int i = 0; i < lightString.length(); ++i)
        {
            if (lightString[i] == '.')
            {
                lightTarget.push_back(0);
            }
            else if (lightString[i] == '#')
            {
                lightTarget.push_back(1);
                lightTargetInt += 1 << i;
            }
        }
        targetsPerLine.push_back(lightTarget);
        targetsPerLineInt.push_back(lightTargetInt);

        int joltageStartIndex = findChar(line, joltageStart);

        std::vector<int> buttonToggles;
        buttonsPerLine.push_back({});
        std::vector<std::vector<unsigned char>>& buttonsThisLine = buttonsPerLine[lineIndex];

        unsigned char buttonNum = 0;
        int bIndex = findChar(line, buttonStart, lightsEndIndex) + 1;

        std::map<int, std::vector<ButtonCombo>> pressCountToResultInt;
        std::map<unsigned int, std::vector<ButtonCombo>> lightValueToButtonCombo;

        int minPressCount = 100;
        while (bIndex < joltageStartIndex)
        {
            int buttonEndIndex = findChar(line, buttonEnd, bIndex);

            if (buttonEndIndex < 0)
            {
                break;
            }

            std::vector<unsigned char> buttons;
            unsigned int buttonLightInt = 0;
            // Parse next button impact
            while (bIndex < buttonEndIndex)
            {
                int lightIndex = std::atoi(&line[bIndex]);
                buttons.push_back(lightIndex);
                buttonLightInt += (1 << lightIndex);

                int nextIndex = findChar(line, separator, bIndex);
                if (nextIndex > buttonEndIndex)
                {
                    bIndex = findChar(line, buttonStart, bIndex);
                }
                else
                {
                    bIndex = nextIndex;
                }

                if (bIndex < 0 || bIndex > joltageStartIndex)
                {
                    bIndex = joltageStartIndex;
                }
                else
                {
                    ++bIndex;
                }
            }

            int pressCount = 1;
            if (pressCountToResultInt.contains(pressCount) == false)
            {
                pressCountToResultInt.insert({ pressCount, {} });
            }
            pressCountToResultInt[pressCount].push_back({ buttonLightInt, {buttonNum} });
            if (buttonLightInt == lightTargetInt && pressCount < minPressCount)
            {
                minPressCount = pressCount;
            }
            if (lightValueToButtonCombo.contains(buttonLightInt) == false)
            {
                lightValueToButtonCombo.insert({ buttonLightInt, {} });
            }
            ButtonCombo newCombo;
            newCombo.lightValue = buttonLightInt;
            newCombo.buttonSequence.insert(buttonNum);
            lightValueToButtonCombo[buttonLightInt].push_back({ newCombo });

            for (auto it = pressCountToResultInt.begin(); it != pressCountToResultInt.end(); ++it)
            {
                auto& entry = *it;
                int pressCount = entry.first + 1;
                for (int j = 0; j < entry.second.size(); ++j)
                {
                    auto& combo = entry.second[j];
                    if (combo.buttonSequence.contains(buttonNum))
                    {
                        continue;
                    }
                    ButtonCombo newCombo;
                    newCombo.lightValue = combo.lightValue ^ buttonLightInt;
                    newCombo.buttonSequence = combo.buttonSequence;
                    newCombo.buttonSequence.insert(buttonNum);
                    if (pressCountToResultInt.contains(pressCount) == false)
                    {
                        pressCountToResultInt.insert({ pressCount, {} });
                    }
                    pressCountToResultInt[pressCount].push_back(newCombo);
                    if (newCombo.lightValue == lightTargetInt && pressCount < minPressCount)
                    {
                        minPressCount = pressCount;
                    }
                    if (lightValueToButtonCombo.contains(newCombo.lightValue) == false)
                    {
                        lightValueToButtonCombo.insert({ newCombo.lightValue, {} });
                    }
                    lightValueToButtonCombo[newCombo.lightValue].push_back({ newCombo });
                }
            }



            buttonsThisLine.push_back(buttons);
            ++buttonNum;
        }
        minPressesPerLine.push_back(minPressCount);
        lightValueToComboPerline.push_back(lightValueToButtonCombo);
        ++lineIndex;
    }

    for (auto& presses : minPressesPerLine)
    {
        numOfPresses += presses;
    }
}

void Q10_ButtonsAndLights::Solve2(long long& numOfPresses)
{
    std::ifstream infile("Q10_MachineDiagram.txt");
    std::string line;

    char lightsStart = '[';
    char lightsEnd = ']';
    char joltageStart = '{';
    char joltageEnd = '}';
    char buttonStart = '(';
    char buttonEnd = ')';
    char separator = ',';

    auto findChar = [this](std::string& input, char& c, int startIndex = 0) {
        for (int i = startIndex; i < input.length(); ++i)
        {
            if (input[i] == c)
            {
                return i;
            }
        }
        return -1;
        };

    std::vector <std::vector<int>> joltTargetsPerLine;
    std::vector<int> minPressesPerLine;

    int lineIndex = 0;

    // Parse targets and buttons per line;
    while (std::getline(infile, line))
    {
        //std::cout << line << "\n";
        int joltageStartIndex = findChar(line, joltageStart);
        int joltageEndIndex = findChar(line, joltageEnd);

        std::string joltageString = line.substr(joltageStartIndex + 1, joltageEndIndex - joltageStartIndex - 1);

        std::vector<int> joltageTarget;
        int joltTargetInt = 0;
        for (int i = 0; i < joltageString.length();)
        {
            int joltageCount = std::atoi(&joltageString[i]);
            joltageTarget.push_back(joltageCount);


            i = findChar(joltageString, separator, i);
            if (i < 0)
            {
                break;
            }
            else
            {
                ++i;
            }
        }
        joltTargetsPerLine.push_back(joltageTarget);

        std::map<unsigned char, int> buttonTracker;

        int minPresses = GetMinPresses(joltageTarget, lineIndex, buttonTracker);
        std::cout << "For target: (";

        for (auto& t : joltageTarget)
        {
            std::cout << t << ",";
        }
        std::cout << ") Min presses = " << minPresses << "\n";

        for (auto& buttonPresses : buttonTracker)
        {
            std::cout << "Button " << (int)buttonPresses.first << " Count: " << buttonPresses.second << "\n";
        }

        minPressesPerLine.push_back(minPresses);
        ++lineIndex;
    }

    for (auto& presses : minPressesPerLine)
    {
        numOfPresses += presses;
    }
}

bool Q10_ButtonsAndLights::TallyPresses(std::vector<unsigned char>& startingState, std::vector<unsigned char>& buttonToggles)
{
	for (int i = 0; i < buttonToggles.size(); ++i)
	{
		unsigned char lightToToggle = buttonToggles[i];

        if (lightToToggle > 0)
        {
            if (lightToToggle < startingState.size())
            {
                ++startingState[lightToToggle];
            }
            else
            {
                std::cout << "Light button mismatch" << "\n";
                return false;
            }
        }
	}
	return true;
}

bool Q10_ButtonsAndLights::CheckForMaxPresses(std::vector<unsigned char>& target, std::vector<unsigned char>& current)
{
    if (target.size() != current.size())
    {
        return false;
    }

    for (int i = 0; i < current.size(); ++i)
    {
        unsigned char currentVal = current[i];

        if (currentVal > target[i])
        {
            return false;
        }
    }
    return true;
}

bool Q10_ButtonsAndLights::VectorsEqual(std::vector<unsigned char>& v1, std::vector<unsigned char>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < v1.size(); ++i)
        {
            if (v1[i] != v2[i])
            {
                return false;
            }
        }
        return true;
    }
}

int Q10_ButtonsAndLights::GetMinPresses(std::vector<int>& joltageTarget, int& lineIndex, std::map<unsigned char, int>& buttonTracker, int depthTracker)
{
    // Check for all zero - no presses required
    bool allZero = true;
    for (auto& target : joltageTarget)
    {
        if (target != 0)
        {
            allZero = false;
            break;
        }
    }
    if (allZero == true)
    {
        return 0;
    }

    /*std::cout << "Finding combo for (";
    for (auto& target : joltageTarget)
    {
        std::cout << target << ",";
    }
    std::cout << "). Depth: " << depthTracker << "\n";*/

    // Get Odd-Even 1-0 mask for voltage target
    unsigned int joltTargetInt = 0;
    for (int joltCount = 0; joltCount < joltageTarget.size(); ++joltCount)
    {
        joltTargetInt += (joltageTarget[joltCount] % 2) << joltCount;
    }
    
    int minPresses = 100000;
    std::map<unsigned char, int> minButtonTracker;

    auto& buttons = buttonsPerLine[lineIndex];

    // Find minimum button combo to reach mask value
    if (joltTargetInt != 0 && lightValueToComboPerline[lineIndex].contains(joltTargetInt) == false)
    {
        // Mask not present in cache. SHOULDN'T HAPPEN.
        //std::cout << "No Jolt Cache. Depth: " << depthTracker << "\n";
        if (depthTracker == 0)
        {
            std::cout << "No 0 Jolt Cache. Depth: " << depthTracker << "\n";
        }
        return -1;
    }
    
    if (joltTargetInt == 0)
    {
        // Copy target
        std::vector<int> targetAfter(joltageTarget);

        // All even values. Half target and find min again.
        for (auto& targetVal : targetAfter)
        {
            targetVal /= 2;
        }
        std::map<unsigned char, int> doubleInternalButtonTracker;

        int halfOfTargetPresses = GetMinPresses(targetAfter, lineIndex, doubleInternalButtonTracker, depthTracker + 1);


        // Check for no combo found. Skip to next combo.
        if (halfOfTargetPresses == -1)
        {
            //std::cout << "No combo found\n";
        }
        else
        {
            int numOfPresses = 2 * halfOfTargetPresses;
            if (numOfPresses < minPresses)
            {
                minPresses = numOfPresses;
                for (auto& buttonPress : doubleInternalButtonTracker)
                {
                    buttonPress.second *= 2;
                }
                minButtonTracker = doubleInternalButtonTracker;
            }
            else
            {
                //std::cout << "Not min" << "\n";
            }
        }
    }
    

    {
        // Test each mask matching button combo as a starting point
        for (int i = 0; i < lightValueToComboPerline[lineIndex][joltTargetInt].size(); ++i)
        {
            auto& buttonCombo = lightValueToComboPerline[lineIndex][joltTargetInt][i];
            // Copy target
            std::vector<int> targetAfter(joltageTarget);

            bool badCombo = false;
            std::map<unsigned char, int> internalButtonTracker;

            for (auto& buttonIndex : buttonCombo.buttonSequence)
            {
                auto& button = buttons[buttonIndex];

                if (internalButtonTracker.contains(buttonIndex))
                {
                    ++internalButtonTracker[buttonIndex];
                }
                else
                {
                    internalButtonTracker.insert({ {buttonIndex, 1} });
                }

                for (int lightIndex : button)
                {
                    if (lightIndex < targetAfter.size())
                    {
                        --targetAfter[lightIndex];

                        if (targetAfter[lightIndex] < 0)
                        {
                            badCombo = true;
                            break;
                        }
                    }
                }

                if (badCombo == true)
                {
                    break;
                }
            }

            if (badCombo == true)
            {
                continue;
            }

            // All even values. Half target and find min again.
            for (auto& targetVal : targetAfter)
            {
                targetVal /= 2;
            }

            std::map<unsigned char, int> doubleInternalButtonTracker;
            int halfOfTargetPresses = GetMinPresses(targetAfter, lineIndex, doubleInternalButtonTracker, depthTracker + 1);

            // Check for no combo found. Skip to next combo.
            if (halfOfTargetPresses == -1)
            {
                continue;
            }

            int numOfPresses = buttonCombo.buttonSequence.size() + (2 * halfOfTargetPresses);

            if (numOfPresses < minPresses)
            {
                minPresses = numOfPresses;
                for (auto& buttonPress : doubleInternalButtonTracker)
                {
                    buttonPress.second *= 2;
                    if (internalButtonTracker.contains(buttonPress.first))
                    {
                        internalButtonTracker[buttonPress.first] += buttonPress.second;
                    }
                    else
                    {
                        internalButtonTracker.insert({ {buttonPress.first, buttonPress.second} });
                    }
                }
                minButtonTracker = internalButtonTracker;
            }
            else
            {
                //std::cout << "Not min" << "\n";
            }
        }
    }
    if (minPresses >= 100000)
    {
        if (depthTracker == 0)
        {
            //std::cout << "No combo - Trying Buttons. Depth: " << depthTracker << "\n";

            for (int buttonIndex = 0; buttonIndex < buttonsPerLine[lineIndex].size(); ++buttonIndex)
            {
                // Trial button presses if no solution foundbool badCombo = false;
                std::map<unsigned char, int> internalButtonTracker;
                // Copy target
                std::vector<int> targetAfter(joltageTarget);
                int pressfactor = 1;
                if (joltTargetInt == 0)
                {
                    pressfactor = 2;
                    for (auto& target : targetAfter)
                    {
                        target /= 2;
                    }
                }

                bool badCombo = false;

                auto& button = buttonsPerLine[lineIndex][buttonIndex];
                if (internalButtonTracker.contains(buttonIndex))
                {
                    ++internalButtonTracker[buttonIndex];
                }
                else
                {
                    internalButtonTracker.insert({ {buttonIndex, 1} });
                }

                for (int lightIndex : button)
                {
                    if (lightIndex < targetAfter.size())
                    {
                        --targetAfter[lightIndex];

                        if (targetAfter[lightIndex] < 0)
                        {
                            badCombo = true;
                            break;
                        }
                    }
                }

                if (badCombo == true)
                {
                    continue;
                }

                int targetPresses = GetMinPresses(targetAfter, lineIndex, internalButtonTracker, depthTracker + 1);

                // Check for no combo found. Skip to next combo.
                if (targetPresses == -1)
                {
                    continue;
                }

                int numOfPresses = 1 + (targetPresses * pressfactor);

                if (numOfPresses < minPresses)
                {
                    minPresses = numOfPresses;
                    for (auto& buttonPress : internalButtonTracker)
                    {
                    }
                    minButtonTracker = internalButtonTracker;
                }
                else
                {
                    //std::cout << "Not min" << "\n";
                }
            }
        }
    }


    if (minPresses >= 100000)
    {
        //std::cout << "STILL NOT FOUND COMBO\n";
        return -1;
    }

    /*std::cout << "Found combo for (";
    for (auto& target : joltageTarget)
    {
        std::cout << target << ",";
    }
    std::cout << "). Presses: " << minPresses << " Depth: " << depthTracker << "\n";


    for (auto& buttonPress : minButtonTracker)
    {
        if (buttonTracker.contains(buttonPress.first))
        {
            buttonTracker[buttonPress.first] += buttonPress.second;
        }
        else
        {
            buttonTracker.insert({ {buttonPress.first, buttonPress.second} });
        }

        auto& button = buttons[buttonPress.first];

        std::cout << "(";
        for (auto& light : button)
        {
            std::cout << (int)light << ",";
        }
        std::cout << "). x " << buttonPress.second << "\n";
    }*/
    return minPresses;
}
