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

/** \file BetaDistribution.cpp
    \brief This file is a testing binary for the BetaDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/BetaDistribution.h"

int main(int argc, char** argv) {
  BetaDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getAlpha(): " << dist.getAlpha() << std::endl << std::endl;
  std::cout << "dist.getBeta(): " << dist.getBeta() << std::endl << std::endl;

  std::cout << "dist.setAlpha(2.0)" << std::endl << std::endl;
  std::cout << "dist.setBeta(5.0)" << std::endl << std::endl;
  const double alpha = 2.0;
  const double beta = 5.0;
  dist.setAlpha(alpha);
  dist.setBeta(beta);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getAlpha() != alpha)
    return 1;
  if (dist.getBeta() != beta)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  std::string expression = "dbeta(seq(-2, 2, by=0.1), 2.0, 5.0)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  double value = -2.0;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (v[i] != std::numeric_limits<double>::infinity() &&
        fabs(dist(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist(value) << std::endl;
      return 1;
    }
    value += 0.1;
  }
  expression = "pbeta(seq(-2, 2, by=0.1), 2.0, 5.0)";
  ans = R.parseEval(expression);
  v = ans;
  value = -2.0;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist.cdf(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist.cdf(value) << std::endl;
      return 1;
    }
    value += 0.1;
  }

  std::cout << "dist.getMean(): " << std::fixed << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - alpha / (alpha + beta)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - alpha * beta / (alpha + beta) / (alpha + beta) /
      (alpha + beta + 1)) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << dist.getMode() << std::endl
    << std::endl;
  if (fabs(dist.getMode() - (alpha - 1) / (alpha + beta - 2)) >
      std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setAlpha(0.0)" << std::endl;
    dist.setAlpha(0.0);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setBeta(0.0)" << std::endl;
    dist.setBeta(0.0);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<double, 2, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  BetaDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getAlpha() != dist.getAlpha())
    return 1;
  if (distCopy.getBeta() != dist.getBeta())
    return 1;
  BetaDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getAlpha() != dist.getAlpha())
    return 1;
  if (distAssign.getBeta() != dist.getBeta())
    return 1;

  return 0;
}
