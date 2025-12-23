#pragma once
#include <vector>
#include <set>
#include <map>

struct ButtonCombo
{
	unsigned int lightValue;
	std::set<unsigned char> buttonSequence;
};

class Q10_ButtonsAndLights
{
public:
	void Solve(long long& numOfPresses);
	void Solve2(long long& numOfPresses);
private:
	std::vector<std::map<unsigned int, std::vector<ButtonCombo>>> lightValueToComboPerline = {};
	std::vector<std::vector<std::vector<unsigned char>>> buttonsPerLine = {};
	bool TallyPresses(std::vector<unsigned char>& startingState, std::vector<unsigned char>& buttonToggles);
	bool CheckForMaxPresses(std::vector<unsigned char>& target, std::vector<unsigned char>& current);
	bool VectorsEqual(std::vector<unsigned char>& v1, std::vector<unsigned char>& v2);
	int GetMinPresses(std::vector<int>& joltageTarget, int& lineIndex, std::map<unsigned char, int>& buttonTracker, int depthTracker = 0);
};

