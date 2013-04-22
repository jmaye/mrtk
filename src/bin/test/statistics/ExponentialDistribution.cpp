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

/** \file ExponentialDistribution.cpp
    \brief This file is a testing binary for the ExponentialDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/ExponentialDistribution.h"

int main(int argc, char** argv) {
  ExponentialDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getRate(): " << dist.getRate() << std::endl << std::endl;

  std::cout << "dist.setRate(1.5)" << std::endl << std::endl;
  const double rate = 1.5;
  dist.setRate(rate);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getRate() != rate)
    return 1;

  const double min = -10.0;
  const double max = 10.0;
  const double inc = 0.1;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["rate"] = rate;
  R["min"] = min;
  R["max"] = max;
  R["inc"] = inc;
  std::string expression = "dexp(seq(min, max, by=inc), rate)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  double value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(value) < 1e-12)
      value = 0;
    if (fabs(dist(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist(value) << std::endl;
      return 1;
    }
    value += inc;
  }
  expression = "pexp(seq(min, max, by=inc), rate)";
  ans = R.parseEval(expression);
  v = ans;
  value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist.cdf(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist.cdf(value) << std::endl;
      return 1;
    }
    value += inc;
  }

  std::cout << "dist.getMean(): " << std::fixed << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - 1.0 / rate) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - 1.0 / rate / rate) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode()) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMedian(): " << std::fixed << dist.getMedian()
    << std::endl << std::endl;
  if (fabs(dist.getMedian() - 1.0 / rate * log(2)) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setRate(0.0)" << std::endl;
    dist.setRate(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<double> samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  ExponentialDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getRate() != dist.getRate())
    return 1;
  ExponentialDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getRate() != dist.getRate())
    return 1;

  return 0;
}
