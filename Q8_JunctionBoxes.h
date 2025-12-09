#pragma once
#include <iostream>
#include <sstream>
#include <string>

struct Vec3
{
public:
    Vec3(int _x, int _y, int _z)
    {
        x = _x; y = _y; z = _z;
    }

    int x;
    int y;
    int z;

    int circuitID = -1;

    std::string GetString()
    {
        std::ostringstream os;
        os << "(" << x << ", " << y << ", " << z << ")";
        return os.str();
    }
};

class Q8_JunctionBoxes
{
public:
	void Solve(long long& circuitProduct, long long& fullCircuitProduct, int maxConnections = 0);
private:
    double DistanceBetween2Vectors(Vec3& v1, Vec3& v2);
};
