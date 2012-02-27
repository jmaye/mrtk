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

/** \file PoissonDistribution.cpp
    \brief This file is a testing binary for the PoissonDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/PoissonDistribution.h"

int main(int argc, char** argv) {
  PoissonDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getMean(): " << dist.getMean() << std::endl
    << std::endl;

  std::cout << "dist.setMean(2.5)" << std::endl << std::endl;
  const double rate = 2.5;
  dist.setMean(rate);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;
  if (dist.getMean() != rate)
    return 1;

  const int min = -10.0;
  const int max = 10.0;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["min"] = min;
  R["max"] = max;
  R["lambda"] = rate;
  std::string expression = "dpois(min:max, lambda)";
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
  expression = "ppois(min:max, lambda)";
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
  if (fabs(dist.getMean() - rate) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - rate) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode() - ceil(rate) + 1) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMedian(): " << std::fixed << dist.getMedian()
    << std::endl << std::endl;
  if (fabs(dist.getMedian() - floor(rate + 1.0/ 3.0 - 0.02 / rate)) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setMean(-1.0)" << std::endl;
    dist.setMean(-1.0);
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

  PoissonDistribution distComp(3.0);
  std::cout << "dist.KLDivergence(distComp(3.0)): "
    << dist.KLDivergence(distComp) << std::endl << std::endl;

  PoissonDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getMean() != dist.getMean())
    return 1;
  PoissonDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getMean() != dist.getMean())
    return 1;

  return 0;
}
