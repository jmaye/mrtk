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

/** \file StudentDistribution.cpp
    \brief This file is a testing binary for the StudentDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/StudentDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing Student's t-distribution 1-D" << std::endl;
  StudentDistribution<1> dist1D;
  std::cout << "Distribution default parameters: " << std::endl << dist1D
    << std::endl << std::endl;

  std::cout << "dist1D.getLocation(): " << dist1D.getLocation() << std::endl
    << std::endl;
  std::cout << "dist1D.getScale(): " << dist1D.getScale() << std::endl
    << std::endl;
  std::cout << "dist1D.getInverseScale(): " << dist1D.getInverseScale()
    << std::endl << std::endl;
  std::cout << "dist1D.getNormalizer(): " << dist1D.getNormalizer()
    << std::endl << std::endl;
  std::cout << "dist1D.getDegrees(): " << dist1D.getDegrees()
    << std::endl << std::endl;

  std::cout << "dist1D.setLocation(1)" << std::endl;
  std::cout << "dist1D.setScale(2)" << std::endl;
  std::cout << "dist1D.setDegrees(5)" << std::endl;
  const double loc = 1.0;
  const double scale = 2.0;
  const size_t degrees = 5;
  dist1D.setLocation(loc);
  dist1D.setScale(scale);
  dist1D.setDegrees(degrees);
  std::cout << "Distribution new parameters: " << std::endl << dist1D
    << std::endl << std::endl;
  if (dist1D.getLocation() != loc)
    return 1;
  if (dist1D.getScale() != scale)
    return 1;
  if (dist1D.getDegrees() != degrees)
    return 1;

  const double min = -10.0;
  const double max = 10.0;
  const double inc = 0.1;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["degrees"] = degrees;
  double value = min;
  while (value < max) {
    R["x"] = (value - loc) / sqrt(scale);
    std::string expression = "dt(x, degrees)";
    SEXP ans = R.parseEval(expression);
    Rcpp::NumericVector v(ans);
    if (fabs(dist1D(value) * sqrt(scale) - v[0]) > 1e-12) {
      std::cout << v[0] << " " << dist1D(value) * sqrt(scale) << std::endl;
      return 1;
    }
//    expression = "pt(x, degrees)";
//    ans = R.parseEval(expression);
//    v = ans;
//    if (fabs(dist1D.cdf(value) - v[0]) > 1e-12) {
//      std::cout << v[0] << " " << dist1D.cdf(value) << std::endl;
//      return 1;
//    }
    value += inc;
  }

  std::cout << "dist1D.getMean(): " << std::fixed << dist1D.getMean()
    << std::endl << std::endl;
  if (fabs(dist1D.getMean() - loc) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist1D.getVariance(): " << std::fixed << dist1D.getVariance()
    << std::endl << std::endl;
  if (fabs(dist1D.getVariance() - degrees / (degrees - 2.0) * scale) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist1D.getMode(): " << std::fixed << dist1D.getMode()
    << std::endl << std::endl;
  if (fabs(dist1D.getMode() - loc) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist1D.getMedian(): " << std::fixed << dist1D.getMedian()
    << std::endl << std::endl;
  if (fabs(dist1D.getMedian() - loc) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist1D.setScale(0.0)" << std::endl;
    dist1D.setScale(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist1D.setDegrees(0)" << std::endl;
    dist1D.setDegrees(0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist1D.getSample(): " << std::endl << dist1D.getSample()
    << std::endl << std::endl;
  std::vector<double> samples;
  dist1D.getSamples(samples, 10);
  std::cout << "dist1D.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  StudentDistribution<1> distCopy(dist1D);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getLocation() != dist1D.getLocation())
    return 1;
  if (distCopy.getScale() != dist1D.getScale())
    return 1;
  if (distCopy.getDegrees() != dist1D.getDegrees())
    return 1;
  StudentDistribution<1> distAssign = dist1D;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getLocation() != dist1D.getLocation())
    return 1;
  if (distAssign.getScale() != dist1D.getScale())
    return 1;
  if (distAssign.getDegrees() != dist1D.getDegrees())
    return 1;

  std::cout << "Testing Student's t-distribution 2-D" << std::endl;
  StudentDistribution<2> dist2D;
  std::cout << "Distribution default parameters: " << std::endl << dist2D
    << std::endl << std::endl;

  std::cout << "dist2D.getLocation(): " << std::endl << dist2D.getLocation()
    << std::endl << std::endl;
  std::cout << "dist2D.getScale(): " << std::endl << dist2D.getScale()
    << std::endl << std::endl;
  std::cout << "dist2D.getInverseScale(): " << std::endl
    << dist2D.getInverseScale() << std::endl << std::endl;
  std::cout << "dist2D.getDeterminant(): " << dist2D.getDeterminant()
    << std::endl << std::endl;
  std::cout << "dist2D.getNormalizer(): " << dist2D.getNormalizer()
    << std::endl << std::endl;

  std::cout << "dist2D.setLocation((1, 1))" << std::endl;
  std::cout << "dist2D.setScale((2,0,0,2))" << std::endl;
  std::cout << "dist2D.setDegrees(5)" << std::endl;
  const Eigen::Matrix<double, 2, 1> loc2d(1.0, 1.0);
  const Eigen::Matrix<double, 2, 2> scale2d((Eigen::Matrix<double, 2, 2>() <<
    2, 0, 0, 2).finished());
  const size_t degrees2d = 5;
  dist2D.setLocation(loc2d);
  dist2D.setScale(scale2d);
  dist2D.setDegrees(degrees2d);
  std::cout << "Distribution new parameters: " << std::endl << dist2D
    << std::endl << std::endl;
  if (dist2D.getLocation() != loc2d)
    return 1;
  if (dist2D.getScale() != scale2d)
    return 1;
  if (dist2D.getDegrees() != degrees)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  for (size_t i = 0; i < 100; ++i) {
    std::string expression = "library('mvtnorm');\
      rmvt(1, matrix(c(2,0,0,2),2,2), 5, c(1,1))";
    SEXP ans = R.parseEval(expression);
    Rcpp::NumericVector x(ans);
    R["x"] = x;
    expression = "dmvt(x, c(1,1), matrix(c(2,0,0,2),2,2), 5, FALSE)";
    ans = R.parseEval(expression);
    Rcpp::NumericVector y(ans);
    if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(x[0], x[1])) - y[0]) > 1e-12) {
      std::cout << y[0] << " " <<
        dist2D(Eigen::Matrix<double, 2, 1>(x[0], x[1])) << std::endl;
      return 1;
    }
  }

  std::cout << "dist2D.getMean(): " << std::endl << std::fixed
    << dist2D.getMean() << std::endl << std::endl;
  if (dist2D.getMean() != loc2d)
    return 1;
  std::cout << "dist2D.getCovariance(): " << std::endl << std::fixed
    << dist2D.getCovariance() << std::endl << std::endl;
  std::cout << "dist2D.getMode(): " << std::endl << std::fixed
    << dist2D.getMode() << std::endl << std::endl;
  if (dist2D.getMode() != loc2d)
    return 1;

  try {
    std::cout << "dist2D.setScale(2,3,0,2))" << std::endl;
    dist2D.setScale((Eigen::Matrix<double, 2, 2>() << 2, 3, 0, 2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist2D.setScale(-2,0,0,-2))" << std::endl;
    dist2D.setScale((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist2D.setScale(1,-1.2,-1.2,1))" << std::endl;
    dist2D.setScale((Eigen::Matrix<double, 2, 2>() << 1, -1.2, -1.2, 1).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist2D.getSample(): " << std::endl << dist2D.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<double, 2, 1> > samples2d;
  dist2D.getSamples(samples2d, 10);
  std::cout << "dist2D.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples2d[i] << std::endl;
  std::cout << std::endl;

  StudentDistribution<2> distCopy2d(dist2D);
  std::cout << "Copy constructor: " << std::endl << distCopy2d << std::endl
    << std::endl;
  if (distCopy2d.getLocation() != dist2D.getLocation())
    return 1;
  if (distCopy2d.getScale() != dist2D.getScale())
    return 1;
  if (distCopy2d.getDegrees() != dist2D.getDegrees())
    return 1;
  StudentDistribution<2> distAssign2d = dist2D;
  std::cout << "Assignment operator: " << std::endl << distAssign2d
    << std::endl;
  if (distAssign2d.getLocation() != dist2D.getLocation())
    return 1;
  if (distAssign2d.getScale() != dist2D.getScale())
    return 1;
  if (distAssign2d.getDegrees() != dist2D.getDegrees())
    return 1;

  std::cout << "Testing normal distribution M-D" << std::endl;
  StudentDistribution<Eigen::Dynamic> distMd(5.0, Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Zero(5), Eigen::Matrix<double, Eigen::Dynamic,
    Eigen::Dynamic>::Identity(5, 5));
  std::cout << "Distribution default parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << distMd.getSample().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getMean(): " << distMd.getMean().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getCovariance(): " << std::endl << distMd.getCovariance()
    << std::endl << std::endl;

  return 0;
}
