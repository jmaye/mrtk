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

/** \file NegativeBinomialDistribution.cpp
    \brief This file is a testing binary for the NegativeBinomialDistribution
           class
  */

#include <iostream>
#include <limits>

#include <RInside.h>

#include "statistics/NegativeBinomialDistribution.h"

int main(int argc, char** argv) {
  NegativeBinomialDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getNumTrials(): " << dist.getNumTrials() << std::endl
    << std::endl;
  std::cout << "dist.getProbability(): " << dist.getProbability()
    << std::endl << std::endl;

  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  std::cout << "dist.setProbability(0.7)" << std::endl << std::endl;
  const size_t n = 5;
  const double p = 0.7;
  dist.setNumTrials(n);
  dist.setProbability(p);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;
  if (dist.getNumTrials() != n)
    return 1;
  if (dist.getProbability() != p)
    return 1;

  const int min = -10.0;
  const int max = 10.0;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["min"] = min;
  R["max"] = max;
  R["p"] = p;
  R["n"] = n;
  std::string expression = "dnbinom(min:max, n, 1.0 - p)"; // GNU R specific
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
  expression = "pnbinom(min:max, n, 1.0 - p)";
  ans = R.parseEval(expression);
  v = ans;
  value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist.cmf(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist.cmf(value) << std::endl;
      return 1;
    }
    value++;
  }

  std::cout << "dist.getMean(): " << std::fixed << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - p * n / (1 - p)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - p * n / (1 - p) / (1 - p)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode() - floor((n - 1) * p / (1 - p))) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setProbability(1.2)" << std::endl;
    dist.setProbability(1.2);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<int, 2, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i](0) << std::endl;
  std::cout << std::endl;

  NegativeBinomialDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getProbability() != dist.getProbability())
    return 1;
  if (distCopy.getNumTrials() != dist.getNumTrials())
    return 1;
  NegativeBinomialDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getProbability() != dist.getProbability())
    return 1;
  if (distAssign.getNumTrials() != dist.getNumTrials())
    return 1;


  return 0;
}
