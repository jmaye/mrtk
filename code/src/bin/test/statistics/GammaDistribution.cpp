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

/** \file GammaDistribution.cpp
    \brief This file is a testing binary for the GammaDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/GammaDistribution.h"

int main(int argc, char** argv) {
  GammaDistribution<double> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getShape(): " << dist.getShape() << std::endl << std::endl;
  std::cout << "dist.getInvScale(): " << dist.getInvScale() << std::endl
    << std::endl;

  std::cout << "dist.setShape(1.5)" << std::endl << std::endl;
  std::cout << "dist.setInvScale(2.5)" << std::endl << std::endl;
  const double shape = 1.5;
  const double invScale = 2.5;
  dist.setShape(shape);
  dist.setInvScale(invScale);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getShape() != shape)
    return 1;
  if (dist.getInvScale() != invScale)
    return 1;

  const double min = -10.0;
  const double max = 10.0;
  const double inc = 0.1;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["shape"] = shape;
  R["invScale"] = invScale;
  R["min"] = min;
  R["max"] = max;
  R["inc"] = inc;
  std::string expression = "dgamma(seq(min, max, by=inc), shape, invScale)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  double value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (v[i] != std::numeric_limits<double>::infinity() &&
        fabs(dist(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist(value) << std::endl;
      return 1;
    }
    value += inc;
  }
  expression = "pgamma(seq(min, max, by=inc), shape, invScale)";
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
  if (fabs(dist.getMean() - shape / invScale) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - shape / (invScale * invScale)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode() - (shape - 1) / invScale) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setShape(0.0): " << std::endl;
    dist.setShape(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setInvScale(0.0): " << std::endl;
    dist.setInvScale(0.0);
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

  GammaDistribution<double> distComp(1.5, 3.0);
  std::cout << "dist.KLDivergence(distComp(1.5, 3.0)): "
    << dist.KLDivergence(distComp) << std::endl << std::endl;

  GammaDistribution<double> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getShape() != dist.getShape())
    return 1;
  if (distCopy.getInvScale() != dist.getInvScale())
    return 1;
  GammaDistribution<double> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getShape() != dist.getShape())
    return 1;
  if (distAssign.getInvScale() != dist.getInvScale())
    return 1;

  return 0;
}
