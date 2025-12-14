#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

struct Vec2
{
public:
    Vec2(int _x, int _y)
    {
        x = _x; y = _y;
    }

    int x;
    int y;

    std::string GetString()
    {
        std::ostringstream os;
        os << "(" << x << ", " << y << ")";
        return os.str();
    }
};

class Q9_RedCarpet
{
public:
	void Solve(long long& largestRedCarpetArea);
    void Solve2(long long& largestRedCarpetAreaOnGreen);
private:
    long long CarpetAreaBetween2Tiles(Vec2& tile1, Vec2& tile2);

    bool IsRectangleInPolygon(Vec2& tile1, Vec2& tile2, std::vector<std::pair<Vec2, Vec2>>& lines);
    bool IsPointInPolygon(std::vector<std::pair<Vec2, Vec2>>& edges, Vec2& point);

    // Unused in final solution
    bool IsPointOnLine(std::pair<Vec2, Vec2>& line, Vec2& point);

    std::map<long long, long long> xIndexCompression = {};
    std::map<long long, long long> yIndexCompression = {};
};

