/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file HyperGeometricDistribution.cpp
    \brief This file is a testing binary for the HyperGeometricDistribution
           class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/HyperGeometricDistribution.h"

int main(int argc, char** argv) {
  HyperGeometricDistribution<2> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getNumTrials(): " << dist.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist.getMarbles(): " << std::endl
    << dist.getMarbles() << std::endl << std::endl;

  Eigen::Matrix<size_t, 2, 1> marbles;
  marbles(0) = 5;
  marbles(1) = 10;
  const size_t numTrials = 5;
  std::cout << "dist.setMarbles(5, 10)" << std::endl << std::endl;
  dist.setMarbles(marbles);
  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  dist.setNumTrials(numTrials);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getMarbles() != marbles)
    return 1;
  if (dist.getNumTrials() != numTrials)
    return 1;

  const int min = -10.0;
  const int max = 10.0;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["white"] = marbles(0);
  R["black"] = marbles(1);
  R["n"] = numTrials;
  R["min"] = min;
  R["max"] = max;
  std::string expression = "dhyper(min:max, white, black, n)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  int value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist(value) << std::endl;
      return 1;
    }
    value++;
  }

  const double sum = marbles.sum();
  std::cout << "dist.getMean(): " << std::fixed << dist.getMean()(0)
    << std::endl << std::endl;
  if (fabs(dist.getMean()(0) - numTrials / sum *
      marbles(0)) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed
    << dist.getCovariance()(0, 0) << std::endl << std::endl;
  if (fabs(dist.getCovariance()(0, 0) - numTrials * marbles(0) / sum *
      (sum - marbles(0)) / sum * (sum - numTrials) / (sum - 1)) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
  std::cout << "dist.setNumTrials(20)" << std::endl;
    dist.setNumTrials(20);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

//  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
//    << std::endl << std::endl;
//  std::vector<double> samples;
//  dist.getSamples(samples, 10);
//  std::cout << "dist.getSamples(samples, 10): " << std::endl;
//  for (size_t i = 0; i < 10; ++i)
//    std::cout << std::endl << samples[i] << std::endl;
//  std::cout << std::endl;

  HyperGeometricDistribution<2> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getNumTrials() != dist.getNumTrials())
    return 1;
  if (distCopy.getMarbles() != dist.getMarbles())
    return 1;
  HyperGeometricDistribution<2> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getNumTrials() != dist.getNumTrials())
    return 1;
  if (distCopy.getMarbles() != dist.getMarbles())
    return 1;

  return 0;
}
