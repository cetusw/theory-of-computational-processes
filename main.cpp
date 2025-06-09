#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<int>> adjMatrix;
std::vector<std::string> allCodes;
std::vector<std::string> vertexCodes;
std::vector<bool> usedCodes;
size_t numVertices;

void GenerateAllCodes()
{
    for (int i = 0; i < 16; ++i)
    {
        std::string binaryString;
        int temp = i;
        for (int j = 0; j < 4; ++j)
        {
            binaryString += (temp % 2 == 0 ? "0" : "1");
            temp /= 2;
        }
        allCodes.push_back(binaryString);
    }
}

int HammingDistance(const std::string& s1, const std::string& s2)
{
    int distance = 0;
    for (size_t i = 0; i < s1.length(); ++i)
    {
        if (s1[i] != s2[i])
        {
            distance++;
        }
    }
    return distance;
}

bool CheckRules(int currentVertexIdx)
{
    int diff2Count = 0;
    int diff3Count = 0;

    for (int i = 0; i <= currentVertexIdx; ++i)
    {
        if (vertexCodes[i].empty()) continue;

        for (int j = i + 1; j <= currentVertexIdx; ++j)
        {
            if (vertexCodes[j].empty()) continue;

            if (adjMatrix[i][j] == 1)
            {
                const int dist = HammingDistance(vertexCodes[i], vertexCodes[j]);

                if (dist == 4)
                {
                    return false;
                }
                if (dist == 2)
                {
                    diff2Count++;
                }
                else if (dist == 3)
                {
                    diff3Count++;
                }
            }
        }
    }

    if (diff2Count > 3)
    {
        return false;
    }
    if (diff3Count > 1)
    {
        return false;
    }

    return true;
}

bool Solve(const int vertexIdx)
{
    if (vertexIdx == numVertices)
    {
        return true;
    }

    for (int i = 0; i < allCodes.size(); ++i)
    {
        if (!usedCodes[i])
        {
            vertexCodes[vertexIdx] = allCodes[i];
            usedCodes[i] = true;

            if (CheckRules(vertexIdx))
            {
                if (Solve(vertexIdx + 1))
                {
                    return true;
                }
            }

            usedCodes[i] = false;
            vertexCodes[vertexIdx] = "";
        }
    }

    return false;
}


int main()
{
    adjMatrix = {
        {0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}
    };

    numVertices = adjMatrix.size();

    vertexCodes.resize(numVertices);
    usedCodes.resize(16, false);

    GenerateAllCodes();

    std::cout << "Поиск решения..." << std::endl;

    if (Solve(0))
    {
        std::cout << "Решение найдено:" << std::endl;
        for (int i = 0; i < numVertices; ++i)
        {
            std::cout << "Вершина " << i << ": " << vertexCodes[i] << std::endl;
        }

        int totalDiff2 = 0;
        int totalDiff3 = 0;
        int totalDiff4 = 0;
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = i + 1; j < numVertices; ++j)
            {
                if (adjMatrix[i][j] == 1)
                {
                    const int dist = HammingDistance(vertexCodes[i], vertexCodes[j]);
                    if (dist == 2)
                    {
                        totalDiff2++;
                    }
                    else if (dist == 3)
                    {
                        totalDiff3++;
                    }
                    else if (dist == 4)
                    {
                        totalDiff4++;
                    }
                }
            }
        }
        std::cout << "\nОбщее количество разниц в 2 единицы: " << totalDiff2 << std::endl;
        std::cout << "Общее количество разниц в 3 единицы: " << totalDiff3 << std::endl;
        std::cout << "Общее количество разниц в 4 единицы: " << totalDiff4 << std::endl;

    }
    else
    {
        std::cout << "Решение не найдено. Возможно, граф не удовлетворяет условиям или требует очень долгого перебора." << std::endl;
    }

    return 0;
}