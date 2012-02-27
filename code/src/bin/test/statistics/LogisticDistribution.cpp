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

/** \file LogisticDistribution.cpp
    \brief This file is a testing binary for the LogisticDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/LogisticDistribution.h"

int main(int argc, char** argv) {
  LogisticDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getLocation(): " << dist.getLocation() << std::endl
    << std::endl;
  std::cout << "dist.getScale(): " << dist.getScale() << std::endl
    << std::endl;
  std::cout << "dist.getInverseScale(): " << dist.getInverseScale() << std::endl
    << std::endl;

  std::cout << "dist.setLocation(1)" << std::endl;
  std::cout << "dist.setScale(2)" << std::endl;
  const double location = -2.0;
  const double scale = 2.0;
  dist.setLocation(location);
  dist.setScale(scale);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getLocation() != location)
    return 1;
  if (dist.getScale() != scale)
    return 1;

  const double min = -10.0;
  const double max = 10.0;
  const double inc = 0.1;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["location"] = location;
  R["scale"] = scale;
  R["min"] = min;
  R["max"] = max;
  R["inc"] = inc;
  std::string expression = "dlogis(seq(min, max, by=inc), location, scale)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  double value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist(value) << std::endl;
      return 1;
    }
    value += inc;
  }
  expression = "plogis(seq(min, max, by=inc), location, scale)";
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

  std::cout << "dist.getMean(): " << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - location) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMedian(): " << dist.getMedian() << std::endl
    << std::endl;
  if (fabs(dist.getMedian() - location) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode() - location) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << dist.getVariance() << std::endl
    << std::endl;
  if (fabs(dist.getVariance() - M_PI * M_PI / 3.0 * scale * scale) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setScale(0.0)" << std::endl;
    dist.setScale(0.0);
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

  LogisticDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getLocation() != dist.getLocation())
    return 1;
  if (distCopy.getScale() != dist.getScale())
    return 1;
  LogisticDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getLocation() != dist.getLocation())
    return 1;
  if (distAssign.getScale() != dist.getScale())
    return 1;

  return 0;
}
