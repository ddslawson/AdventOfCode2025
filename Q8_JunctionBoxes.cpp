#include "Q8_JunctionBoxes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

void Q8_JunctionBoxes::Solve(long long& circuitProduct, long long& fullCircuitProduct, int maxConnections)
{
    std::ifstream infile("Q8_JBoxLocations.txt");
    std::string line;

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

    std::vector<Vec3> vectors;

    std::map<double, std::pair<int, int>> distanceToPointIndex;

    std::map<int, std::set<int>> circuits;

    char separator = ',';
    // Parse and sort points by distance
    while (infile >> line)
    {
        //std::cout << line << "\n";
        int secondNumIndex = findChar(line, separator) + 1;
        int thirdNumIndex = findChar(line, separator, secondNumIndex) + 1;
        Vec3 vec = Vec3(atoi(&line[0]), atoi(&line[secondNumIndex]), atoi(&line[thirdNumIndex]));
        int vIndex = vectors.size();

        for (int i = 0; i < vectors.size(); ++i)
        {
            Vec3 prevPoint = vectors[i];

            double distance = DistanceBetween2Vectors(vec, prevPoint);

            distanceToPointIndex.insert({ distance, {vIndex, i} });
        }

        vectors.push_back(vec);

        //std::cout << vec.x << "\n";
        //std::cout << vec.y << "\n";
        //std::cout << vec.z << "\n";
    }

   /* for (auto it = distanceToPointIndex.begin(); it != distanceToPointIndex.end(); ++it)
    {
        int v1Index = (*it).second.first;
        int v2Index = (*it).second.second;

        Vec3& v1 = vectors[v1Index];
        Vec3& v2 = vectors[v2Index];

        std::cout << "DISTANCE: " << (*it).first << ": " << v1.GetString() << " - " << v2.GetString() << "\n";
    }*/

    int count = 1;
    bool limitConnections = maxConnections > 0;
    int maxCount = maxConnections;
    int circuitIDCounter = 1;
    // Connect circuits
    for (auto it = distanceToPointIndex.begin(); it != distanceToPointIndex.end(); ++it, ++count)
    {
        if (limitConnections && count > maxCount)
        {
            break;
        }
        int v1Index = (*it).second.first;
        int v2Index = (*it).second.second;

        Vec3& v1 = vectors[v1Index];
        Vec3& v2 = vectors[v2Index];

        if (v1.circuitID == -1 && v2.circuitID == -1)
        {
            // New circuit
            int newCircuitID = circuitIDCounter++;
            v1.circuitID = newCircuitID;
            v2.circuitID = newCircuitID;

            circuits.insert({ newCircuitID, {v1Index, v2Index} });
        }
        else if (v1.circuitID == -1 && v2.circuitID > -1)
        {
            // Add v1 to v2 circuit
            v1.circuitID = v2.circuitID;

            if (circuits[v2.circuitID].contains(v1Index))
            {
                std::cout << "Circuit error" << "\n";
            }

            circuits[v2.circuitID].insert(v1Index);
        }
        else if (v2.circuitID == -1 && v1.circuitID > -1)
        {
            // Add v2 to v1 circuit
            v2.circuitID = v1.circuitID;

            if (circuits[v1.circuitID].contains(v2Index))
            {
                std::cout << "Circuit error" << "\n";
            }

            circuits[v1.circuitID].insert(v2Index);
        }
        else if (v1.circuitID != v2.circuitID)
        {
            // Merge circuits
            int circuitToRemove = v2.circuitID;
            for (auto it = circuits[circuitToRemove].begin(); it != circuits[circuitToRemove].end(); ++it)
            {
                int vecToMoveIndex = *it;

                Vec3& vecToMove = vectors[vecToMoveIndex];
                vecToMove.circuitID = v1.circuitID;

                if (circuits[v1.circuitID].contains(vecToMoveIndex))
                {
                    std::cout << "Circuit error" << "\n";
                }

                circuits[v1.circuitID].insert(vecToMoveIndex);
            }
            circuits.erase(circuitToRemove);
        }
        else
        {
            // Same circuit already - SKIP
        }

        // All points connected
        if (circuits[v1.circuitID].size() == vectors.size())
        {
            fullCircuitProduct = v1.x * v2.x;
            break;
        }
    }

    // Find 3 longest circuits
    std::vector<int> circuitLengths(3,0);
    for (auto it = circuits.begin(); it != circuits.end(); ++it)
    {
        int circuitLength = (*it).second.size();
        if (circuitLength > circuitLengths.back())
        {
            bool placed = false;
            for (int i = circuitLengths.size() - 1; i >= 0 && placed == false; --i)
            {
                if (circuitLengths[i] >= circuitLength)
                {
                    circuitLengths.insert(circuitLengths.begin() + i + 1, circuitLength);
                    placed = true;
                }
            }

            if (placed == false)
            {
                circuitLengths.insert(circuitLengths.begin(), circuitLength);
            }

            circuitLengths.pop_back();
        }
    }

    circuitProduct = circuitLengths[0] * circuitLengths[1] * circuitLengths[2];
    std::cout << circuitLengths[0] << "*" << circuitLengths[1] << "*" << circuitLengths[1] << "=" << circuitProduct << "\n";
}

double Q8_JunctionBoxes::DistanceBetween2Vectors(Vec3& v1, Vec3& v2)
{
    return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2) + pow((v2.z - v1.z), 2));
}
