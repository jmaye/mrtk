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

/** \file InvWishartDistribution.cpp
    \brief This file is a testing binary for the InvWishartDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/InvWishartDistribution.h"

int main(int argc, char** argv) {
  InvWishartDistribution<2> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getDegrees(): " << dist.getDegrees() << std::endl;
  std::cout << "dist.getScale(): " << std::endl << dist.getScale() << std::endl;
  std::cout << "dist.getDeterminant(): " << dist.getDeterminant() << std::endl;
  std::cout << "dist.getNormalizer(): " << dist.getNormalizer() << std::endl;
  std::cout << "dist.getTransformation(): " << std::endl <<
    dist.getTransformation().matrixL() << std::endl;

  std::cout << "dist.setDegrees(5)" << std::endl;
  std::cout << "dist.setScale((1, 0, 0, 1))" << std::endl;
  const Eigen::Matrix<double, 2, 2> scale =
    (Eigen::Matrix<double, 2, 2>() << 1, 0, 0, 1).finished();
  const size_t degrees = 5;
  dist.setScale(scale);
  dist.setDegrees(degrees);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getScale() != scale)
    return 1;
  if (dist.getDegrees() != degrees)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["degrees"] = degrees;
  for (size_t i = 0; i < 100; ++i) {
    std::string expression = "library('MCMCpack');\
      riwish(degrees, matrix(c(1,0,0,1),2,2))";
    SEXP ans = R.parseEval(expression);
    Rcpp::NumericMatrix x(ans);
    R["X"] = x;
    expression = "library('MCMCpack');\
      diwish(X, degrees, matrix(c(1,0,0,1),2,2))";
    ans = R.parseEval(expression);
    Rcpp::NumericVector y(ans);
    if (fabs(dist((Eigen::Matrix<double, 2, 2>() << x(0, 0), x(0, 1), x(1, 0),
        x(1, 1)).finished()) - y[0]) > 1e-12) {
      std::cout << y[0] << " " << dist((Eigen::Matrix<double, 2, 2>() <<
        x(0, 0), x(0, 1), x(1, 0), x(1, 1)).finished()) << std::endl;
      return 1;
    }
  }
  std::cout << std::endl;

  std::cout << "dist.getMean(): " << std::endl << std::fixed << dist.getMean()
    << std::endl << std::endl;
  std::cout << "dist.getMode(): " << std::endl << std::fixed << dist.getMode()
    << std::endl << std::endl;

  try {
    std::cout << "dist.setDegrees(1)" << std::endl;
    dist.setDegrees(1);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setScale((10, 10, 10, 10))" << std::endl;
    dist.setScale((Eigen::Matrix<double, 2, 2>() << 10, 10, 10, 10).finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<double, 2, 2> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  InvWishartDistribution<2> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getDegrees() != dist.getDegrees())
    return 1;
  if (distCopy.getScale() != dist.getScale())
    return 1;
  InvWishartDistribution<2> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getDegrees() != dist.getDegrees())
    return 1;
  if (distAssign.getScale() != dist.getScale())
    return 1;
  std::cout << std::endl;

  std::cout << "Testing Wishart distribution M-D" << std::endl;
  WishartDistribution<Eigen::Dynamic> distMd(6,
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Identity(4, 4));
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << std::endl << distMd.getSample()
    << std::endl << std::endl;

  std::cout << "distMd.getMean(): " << std::endl << distMd.getMean()
    << std::endl << std::endl;
  std::cout << "distMd.getMode(): " << std::endl << distMd.getMode()
    << std::endl;

  return 0;
}
