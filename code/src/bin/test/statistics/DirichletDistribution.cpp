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

/** \file DirichletDistribution.cpp
    \brief This file is a testing binary for the DirichletDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/DirichletDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing DirichletDistribution<3>" << std::endl << std::endl;
  DirichletDistribution<3> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getAlpha(): " << std::endl << dist.getAlpha()
    << std::endl << std::endl;

  std::cout << "dist.setAlpha(2.0, 5.0, 10.0)" << std::endl << std::endl;
  const Eigen::Matrix<double, 3, 1> alpha(2.0, 5.0, 10.0);
  dist.setAlpha(alpha);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getAlpha() != alpha)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  std::string expression = "library('MCMCpack');\
    rdirichlet(100, c(2,5,10))";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericMatrix x(ans);
  R["X"] = x;
  expression = "library('MCMCpack');\
    ddirichlet(X, c(2,5,10))";
  ans = R.parseEval(expression);
  Rcpp::NumericVector y(ans);
  for (size_t i = 0; i < (size_t)x.rows(); ++i) {
    if (fabs(dist( Eigen::Matrix<double, 3, 1>(x(i, 0), x(i, 1), x(i, 2)))
        - y[i]) > 1e-12) {
      std::cout << y[i] << " "
        << dist( Eigen::Matrix<double, 3, 1>(x(i, 0), x(i, 1), x(i, 2)))
        << std::endl;
      return 1;
    }
  }
  std::cout << std::endl;

  std::cout << "dist.getMean(): " << std::endl <<
    dist.getMean() << std::endl << std::endl;
  std::cout << "dist.getMode(): " << std::endl <<
    dist.getMode() << std::endl << std::endl;
  std::cout << "dist.getCovariance(): " << std::endl <<
    dist.getCovariance() << std::endl << std::endl;

  try {
    std::cout << "dist.setAlpha(0.0, 0.9, 10.9)" << std::endl;
    Eigen::Matrix<double, 3, 1> alphaWrong(0.0, 0.9, 10.9);
    dist.setAlpha(alphaWrong);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 3, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<double, 3, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  DirichletDistribution<3> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getAlpha() != dist.getAlpha())
    return 1;
  DirichletDistribution<3> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getAlpha() != dist.getAlpha())
    return 1;
  std::cout << std::endl;

  std::cout << "Testing Dirichlet distribution M-D" << std::endl;
  DirichletDistribution<Eigen::Dynamic> distMd(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Constant(5, 1.0));
  std::cout << "Distribution default parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getAlpha(): " << std::endl << distMd.getAlpha()
    << std::endl << std::endl;

  std::cout << "distMd.setAlpha(2.0, 5.0, 10.0, 3.0, 4.0)" << std::endl
    << std::endl;
  Eigen::Matrix<double, Eigen::Dynamic, 1> alphaMd(5);
  alphaMd(0) = 2.0;
  alphaMd(1) = 5.0;
  alphaMd(2) = 10.0;
  alphaMd(3) = 3.0;
  alphaMd(4) = 4.0;
  distMd.setAlpha(alphaMd);
  std::cout << "Distribution new parameters: " << std::endl << distMd
    << std::endl << std::endl;
  if (distMd.getAlpha() != alphaMd)
    return 1;

  std::cout << "distMd.getMean(): " << std::endl <<
    distMd.getMean() << std::endl << std::endl;
  std::cout << "distMd.getMode(): " << std::endl <<
    distMd.getMode() << std::endl << std::endl;
  std::cout << "distMd.getCovariance(): " << std::endl <<
    distMd.getCovariance() << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << std::endl << distMd.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<double, Eigen::Dynamic, 1> > samplesMd;
  distMd.getSamples(samplesMd, 10);
  std::cout << "distMd.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samplesMd[i] << std::endl;
  std::cout << std::endl;

  DirichletDistribution<Eigen::Dynamic> distCopyMd(distMd);
  std::cout << "Copy constructor: " << std::endl << distCopyMd << std::endl
    << std::endl;
  if (distCopyMd.getAlpha() != distMd.getAlpha())
    return 1;
  DirichletDistribution<Eigen::Dynamic> distAssignMd = distMd;
  std::cout << "Assignment operator: " << std::endl << distAssignMd
    << std::endl;
  if (distAssignMd.getAlpha() != distMd.getAlpha())
    return 1;
  std::cout << std::endl;

  return 0;
}
