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

/** \file GeometricDistribution.cpp
    \brief This file is a testing binary for the GeometricDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/GeometricDistribution.h"

int main(int argc, char** argv) {
  GeometricDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getSuccessProbability(): "
    << dist.getSuccessProbability() << std::endl << std::endl;

  std::cout << "dist.setSuccessProbability(0.7)" << std::endl << std::endl;
  const double p = 0.7;
  dist.setSuccessProbability(p);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;
  if (dist.getSuccessProbability() != p)
    return 1;

  const int min = -10.0;
  const int max = 10.0;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["min"] = min;
  R["max"] = max;
  R["p"] = p;
  std::string expression = "dgeom(min:max, p)";
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
  expression = "pgeom(min:max, p)";
  ans = R.parseEval(expression);
  v = ans;
  value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist.cdf(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist.cdf(value) << std::endl;
      return 1;
    }
    value++;
  }

  std::cout << "dist.getMean(): " << std::fixed << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - (1.0 - p) / p) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - (1.0 - p) / (p * p)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode()) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setSuccessProbability(1.2)" << std::endl;
    dist.setSuccessProbability(1.2);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<int> samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  GeometricDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getSuccessProbability() != dist.getSuccessProbability())
    return 1;
  GeometricDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getSuccessProbability() != dist.getSuccessProbability())
    return 1;

  return 0;
}
