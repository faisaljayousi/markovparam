/**
 * @file main.cpp
 * @brief Provides a function for calculating the Markovian parameter.
 * @author Faisal Jayousi
 * @date June 29, 2023
 */

#include "main.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

double varCond(const DoubleVec2D &dep, int dx, int dy)
{
    int dimX = dep.size();
    int dimY = dep[0].size();

    // Initialisation
    DoubleVec2D neighbours(dimX, std::vector<double>(dimY, (computeMean(dep) + 1)));
    DoubleVec2D squares = calculateSquare(dep);

    std::vector<double> mean(256, 0.0);
    std::vector<double> variance(256, 0.0);
    std::vector<double> numOccurrences(256, 0.0);

    // Calculate average of neighbours at each point following the 2 directions
    int ofx = abs(dx);
    int ofy = abs(dy);

    for (int i = ofx + 1; i < dimX - ofx; i++)
    {
        for (int j = ofy + 1; j < dimY - ofy; j++)
        {
            int a1 = i + dx;
            int b1 = j + dy;
            int a2 = i - dx;
            int b2 = j - dy;

            double neighbour = dep[a1][b1] + dep[a2][b2];
            neighbours[i][j] = 1.0 + neighbour / 2.0; // + 1 to convert from [0,255] to [1,256]
        }
    }

    neighbours = floorMatrix(neighbours);

    // Sliding window
    for (int i = ofx + 1; i < dimX - ofx; i++)
    {
        for (int j = ofy + 1; j < dimY - ofy; j++)
        {
            int index = neighbours[i][j];
            numOccurrences[index] += 1;
            mean[index] += double(dep[i][j]);
            variance[index] += double(squares[i][j]);
        }
    }

    double tempe = 0.0;
    double totalOccurrences = 0.0;

    for (int x = 2; x <= 256; x++)
    {
        if (numOccurrences[x] != 0)
        {
            tempe += variance[x] - (mean[x] * mean[x]) / numOccurrences[x];
            totalOccurrences += numOccurrences[x];
        }
    }

    tempe /= totalOccurrences;

    return tempe;
}

double computeMean(const DoubleVec2D &dep)
{
    double sum = 0.0;
    int count = 0;

    for (const auto &row : dep)
    {
        count += row.size();
        sum += std::accumulate(row.begin(), row.end(), 0.0);
    }

    return sum / count;
}

DoubleVec2D calculateSquare(const DoubleVec2D &matrix)
{
    int dimX = matrix.size();
    int dimY = matrix[0].size();

    DoubleVec2D result(dimX, std::vector<double>(dimY));

    for (int i = 0; i < dimX; i++)
    {
        for (int j = 0; j < dimY; j++)
        {
            result[i][j] = matrix[i][j] * matrix[i][j];
        }
    }

    return result;
}

DoubleVec2D floorMatrix(const DoubleVec2D &matrix)
{
    DoubleVec2D result(matrix);
    int dimX = result.size();
    int dimY = result[0].size();

    for (int i = 0; i < dimX; i++)
    {
        for (int j = 0; j < dimY; j++)
        {
            result[i][j] = std::floor(result[i][j]);
        }
    }

    return result;
}
