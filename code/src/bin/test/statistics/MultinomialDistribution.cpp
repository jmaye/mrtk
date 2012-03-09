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

/** \file MultinomialDistribution.cpp
    \brief This file is a testing binary for the MultinomialDistribution class
  */

#include <iostream>
#include <limits>

#include <RInside.h>

#include "statistics/MultinomialDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing MultinomialDistribution<3>" << std::endl << std::endl;
  MultinomialDistribution<3> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getNumTrials(): " << dist.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist.getProbabilities(): " << std::endl
    << dist.getProbabilities() << std::endl << std::endl;

  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  std::cout << "dist.setProbabilities(0.1, 0.2, 0.7)" << std::endl
    << std::endl;
  const size_t n = 5;
  const Eigen::Matrix<double, 3, 1> p(0.1, 0.2, 0.7);
  dist.setNumTrials(n);
  dist.setProbabilities(p);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getNumTrials() != n)
    return 1;
  if (dist.getProbabilities() != p)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["n"] = n;
  for (size_t i = 0; i < 100; ++i) {
    std::string expression = "rmultinom(1, n, c(0.1,0.2,0.7))";
    SEXP ans = R.parseEval(expression);
    Rcpp::NumericVector x(ans);
    R["x"] = x;
    expression = "dmultinom(x, n, c(0.1,0.2,0.7))";
    ans = R.parseEval(expression);
    Rcpp::NumericVector y(ans);
    if (fabs(dist((Eigen::Matrix<int, 3, 1>() << x[0], x[1],
        x[2]).finished()) - y[0]) > 1e-12) {
      std::cout << y[0] << " " << dist((Eigen::Matrix<int, 3, 1>() << x[0],
        x[1], x[2]).finished()) << std::endl;
      return 1;
    }
  }

  std::cout << "dist.getMean(): " << std::endl <<
    dist.getMean() << std::endl << std::endl;
  std::cout << "dist.getMode(): " << std::endl <<
    dist.getMode() << std::endl << std::endl;
  std::cout << "dist.getCovariance(): " << std::endl <<
    dist.getCovariance() << std::endl << std::endl;

  try {
    std::cout << "dist.setNumTrials(0)" << std::endl;
    dist.setNumTrials(0);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setProbabilities(0.1, 0.3, 0.7)" << std::endl
      << std::endl;
    dist.setProbabilities(Eigen::Matrix<double, 3, 1>(0.1, 0.3, 0.7));
  }
  catch (BadArgumentException<Eigen::Matrix<double, 3, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<int, 3, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  MultinomialDistribution<3> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getNumTrials() != dist.getNumTrials())
    return 1;
  if (distCopy.getProbabilities() != dist.getProbabilities())
    return 1;
  MultinomialDistribution<3> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getNumTrials() != dist.getNumTrials())
    return 1;
  if (distCopy.getProbabilities() != dist.getProbabilities())
    return 1;
  std::cout << std::endl;

  std::cout << "Testing multinomial distribution M-D" << std::endl;
  MultinomialDistribution<Eigen::Dynamic> distMd(20, Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Constant(5, 1.0 / 5.0));
  std::cout << "Distribution parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << distMd.getSample().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getMean(): " << distMd.getMean().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getMode(): " << distMd.getMode().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getCovariance(): " << std::endl << distMd.getCovariance()
    << std::endl << std::endl;

  return 0;
}
