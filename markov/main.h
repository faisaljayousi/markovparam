#ifndef MAIN_H
#define MAIN_H

#include <vector>

typedef std::vector<std::vector<double>> DoubleVec2D;

/**
 * @brief Calculates the Markov parameter of a 2D vector.
 * @param dep The input 2D vector.
 * @param dx The x-direction offset.
 * @param dy The y-direction offset.
 * @return The Markov parameter.
 */
double varCond(const DoubleVec2D &dep, int dx, int dy);

/**
 * @brief Calculates the mean value of a 2D vector.
 * @param dep The input 2D vector.
 * @return The mean value.
 */
double computeMean(const DoubleVec2D &dep);

#endif
