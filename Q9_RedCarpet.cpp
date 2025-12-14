#include "Q9_RedCarpet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <execution>
#include <algorithm>

void Q9_RedCarpet::Solve(long long& largestRedCarpetArea)
{
    std::ifstream infile("Q9_CarpetLayout.txt");
    std::string line;
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

    std::vector<Vec2> tiles;

    std::map<long long, std::pair<int, int>> areaToTileCorners;
    // Parse and sort points by area
    while (infile >> line)
    {
        //std::cout << line << "\n";
        int secondNumIndex = findChar(line, separator) + 1;
        Vec2 newTile = Vec2(atoi(&line[0]), atoi(&line[secondNumIndex]));
        int tIndex = tiles.size();

        for (int i = 0; i < tiles.size(); ++i)
        {
            Vec2 prevTile = tiles[i];

            long long area = CarpetAreaBetween2Tiles(newTile, prevTile);

            areaToTileCorners.insert({ area, {tIndex, i} });
        }

        tiles.push_back(newTile);

        //std::cout << vec.x << "\n";
        //std::cout << vec.y << "\n";
        //std::cout << vec.z << "\n";
    }

    largestRedCarpetArea = (*(--areaToTileCorners.end())).first;
}

void Q9_RedCarpet::Solve2(long long& largestRedCarpetAreaOnGreen)
{
    std::ifstream infile("Q9_CarpetLayout.txt");
    std::string line;

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

    std::vector<Vec2> tiles;

    std::vector<std::pair<Vec2, Vec2>> edges;
    std::map<long long, std::vector<std::pair<int, int>>> areaToTileCorners;
    xIndexCompression.clear();
    yIndexCompression.clear();
    // Parse and sort points by area
    while (infile >> line)
    {
        //std::cout << line << "\n";
        int secondNumIndex = findChar(line, separator) + 1;
        Vec2 newTile = Vec2(atoi(&line[0]), atoi(&line[secondNumIndex]));
        int tIndex = tiles.size();

        // Add new coordinates into compression map
        xIndexCompression.insert({ newTile.x, 0 });
        yIndexCompression.insert({ newTile.y, 0 });

        // Calculate area against all previous points
        for (int i = 0; i < tiles.size(); ++i)
        {
            Vec2 prevTile = tiles[i];

            long long area = CarpetAreaBetween2Tiles(newTile, prevTile);

            if (areaToTileCorners.contains(area))
            {
                areaToTileCorners[area].push_back({ tIndex, i });
            }
            else
            {
                areaToTileCorners.insert({ area, std::vector<std::pair<int, int>>()});
                areaToTileCorners[area].push_back({ tIndex, i });
            }

        }

        tiles.push_back(newTile);

        if (tIndex > 0)
        {
            edges.push_back({ tiles[tIndex - 1], newTile });
        }
    }
    edges.push_back({ tiles[tiles.size() - 1], tiles[0]});

    int count = 0;
    long long prevXCoord = -1;
    for (auto& xInd : xIndexCompression)
    {
        // Add numbers to represent gaps in coordinates - DISABLED
        /*if (prevXCoord >= 0 && xInd.first - prevXCoord > 1)
        {
            ++count;
        }*/
        xInd.second = count++;
        prevXCoord = xInd.first;
    }
    count = 0;
    long long prevYCoord = -1;
    for (auto& yInd : yIndexCompression)
    {
        // Add numbers to represent gaps in coordinates - DISABLED
        /*if (prevYCoord >= 0 && yInd.first - prevYCoord > 1)
        {
            ++count;
        }*/
        yInd.second = count++;
        prevYCoord = yInd.first;
    }

    long long prevXCoord2 = -1;
    long long prevYCoord2 = -1;
    for (auto& edge : edges)
    {
        edge.first.x = xIndexCompression[edge.first.x];
        edge.first.y = yIndexCompression[edge.first.y];
        edge.second.x = xIndexCompression[edge.second.x];
        edge.second.y = yIndexCompression[edge.second.y];
    }
    for (auto& tile : tiles)
    {
        tile.x = xIndexCompression[tile.x];
        tile.y = yIndexCompression[tile.y];
    }

    bool found = false;
    int totalToCheck = areaToTileCorners.size();
    int currentCheck = 1;

    Vec2 v1(0, 0);
    Vec2 v2(0, 0);
    for (auto carpetIt = --areaToTileCorners.end(); found == false; --carpetIt)
    {
        //std::cout << "CHECK: " << currentCheck++ << "/" << totalToCheck << " - Area: " << (*carpetIt).first << "\n";
        for (int i = 0; i < (*carpetIt).second.size() && found == false; ++i)
        {
            v1 = tiles[(*carpetIt).second[i].first];
            v2 = tiles[(*carpetIt).second[i].second];

            found = IsRectangleInPolygon(v1, v2, edges);
            if (found == true)
            {
                largestRedCarpetAreaOnGreen = (*carpetIt).first;
                std::cout << v1.GetString() << " - " << v2.GetString() << "\n";
            }
        }
        if (carpetIt == areaToTileCorners.begin())
        {
            break;
        }
    }
}

long long Q9_RedCarpet::CarpetAreaBetween2Tiles(Vec2& tile1, Vec2& tile2)
{
    long long xDist = abs(tile2.x - tile1.x) + 1;
    long long yDist = abs(tile2.y - tile1.y) + 1;
    return xDist * yDist;
}

bool Q9_RedCarpet::IsRectangleInPolygon(Vec2& tile1, Vec2& tile2, std::vector<std::pair<Vec2, Vec2>>& edges)
{
    std::vector<Vec2> newCorners = {
        {tile1.x, tile2.y},
        {tile2.x, tile1.y}
    };
    bool allInside = true;

    /*std::cout << "Box: " << corners[0].GetString() << ", "
        << corners[1].GetString() << ", "
        << corners[2].GetString() << ", "
        << corners[3].GetString() << "\n";*/

    for (auto& corner : newCorners)
    {
        bool inside = IsPointInPolygon(edges, corner);
        if (inside == false)
        {
            //std::cout << "Corner not in polygon" << "\n";
            return false;
        }
    }

    std::vector<std::pair<Vec2, Vec2>> boxLines = {
        {tile1, {tile1.x, tile2.y}},
        {{tile1.x, tile2.y}, tile2},
        {tile2,{tile2.x, tile1.y}},
        {{tile2.x, tile1.y}, tile1}
    };
    int direction;
    bool horizontal;
    int fixedDimensionVal;
    int startVal;
    int endVal;
    Vec2 point(0, 0);

    // Step along each line of rectangle boundary
    for (int lineIndex = 0; lineIndex < boxLines.size(); ++lineIndex)
    {
        //std::cout << "Line: " << boxLines[lineIndex].first.GetString() << " - " << boxLines[lineIndex].second.GetString() << "\n";
        direction = 1;
        horizontal = boxLines[lineIndex].first.y == boxLines[lineIndex].second.y;

        fixedDimensionVal = horizontal == true ? boxLines[lineIndex].first.y : boxLines[lineIndex].first.x;
        startVal = horizontal == true ? boxLines[lineIndex].first.x : boxLines[lineIndex].first.y;
        endVal = horizontal == true ? boxLines[lineIndex].second.x : boxLines[lineIndex].second.y;

        if (horizontal == true && boxLines[lineIndex].first.x > boxLines[lineIndex].second.x)
        {
            direction = -1;
        }
        else if (horizontal == false && boxLines[lineIndex].first.y > boxLines[lineIndex].second.y)
        {
            direction = -1;
        }

        bool inside = true;
        for (int coordVal = startVal; (direction == 1 ? coordVal <= endVal : coordVal >= endVal) && inside == true; coordVal += direction)
        {
            if (horizontal == true)
            {
                point.y = fixedDimensionVal;
                point.x = coordVal;
            }
            else
            {
                point.x = fixedDimensionVal;
                point.y = coordVal;
            }

            //std::cout << "Point: " << point.x << ", " << point.y << "\n";

            inside = IsPointInPolygon(edges, point);
        }

        if (inside == false)
        {
            //std::cout << "Outside" << "\n";
            allInside = false;
            break;
        }
        else
        {
            //std::cout << "Inside" << "\n";
        }
    }
    return allInside;
}

bool Q9_RedCarpet::IsPointInPolygon(std::vector<std::pair<Vec2, Vec2>>& edges, Vec2& point)
{
    int intersectCount = 0;

    for (auto& edge : edges)
    {
        /*if (IsPointOnLine(edge, point) == true)
        {
            inside = true;
            return inside;
        }*/
        if (edge.first.x == edge.second.x)
        {
            if (point.x < edge.first.x && point.y >= std::min(edge.first.y, edge.second.y) && point.y < std::max(edge.first.y, edge.second.y))
            {
                ++intersectCount;
            }
        }
    }

    // Intersection factor of 2 means point is outside of enclosed polygon
    return intersectCount % 2 == 1;
}

bool Q9_RedCarpet::IsPointOnLine(std::pair<Vec2, Vec2>& line, Vec2& point)
{
    int direction = 1;
    bool horizontal = line.first.y == line.second.y;
    int fixedDimensionVal = horizontal == true ? line.first.y : line.first.x;

    if (horizontal == true && point.y != fixedDimensionVal)
    {
        return false;
    }
    else if (horizontal == false && point.x != fixedDimensionVal)
    {
        return false;
    }
    else if (horizontal == true && point.x >= std::min(line.first.x, line.second.x) && point.x <= std::max(line.first.x, line.second.x))
    {
        return true;
    }
    else if (horizontal == false && point.y >= std::min(line.first.y, line.second.y) && point.y <= std::max(line.first.y, line.second.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}
