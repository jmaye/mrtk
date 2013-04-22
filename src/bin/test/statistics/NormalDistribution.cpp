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

/** \file NormalDistribution.cpp
    \brief This file is a testing binary for the NormalDistribution class
  */

#include <iostream>
#include <limits>
#include <string>

#include <RInside.h>

#include "statistics/NormalDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing normal distribution 1-D" << std::endl;
  NormalDistribution<1> dist1D;
  std::cout << "Distribution default parameters: " << std::endl << dist1D
    << std::endl << std::endl;

  std::cout << "dist1D.getMean(): " << dist1D.getMean() << std::endl
    << std::endl;
  std::cout << "dist1D.getVariance(): " << dist1D.getVariance() << std::endl
    << std::endl;
  std::cout << "dist1D.getPrecision(): " << dist1D.getPrecision() << std::endl
    << std::endl;
  std::cout << "dist1D.getStandardDeviation(): "
    << dist1D.getStandardDeviation() << std::endl << std::endl;
  std::cout << "dist1D.getNormalizer(): " << dist1D.getNormalizer()
    << std::endl << std::endl;

  std::cout << "dist1D.setMean(1)" << std::endl;
  std::cout << "dist1D.setVariance(2)" << std::endl;
  const double mu = 1.0;
  const double sigma2 = 2.0;
  dist1D.setMean(mu);
  dist1D.setVariance(sigma2);
  std::cout << "Distribution new parameters: " << std::endl << dist1D
    << std::endl << std::endl;
  if (dist1D.getMean() != mu)
    return 1;
  if (dist1D.getVariance() != sigma2)
    return 1;

  const double min = -10.0;
  const double max = 10.0;
  const double inc = 0.1;
  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  RInside R(argc, argv);
  R["mu"] = mu;
  R["sd"] = sqrt(sigma2);
  R["min"] = min;
  R["max"] = max;
  R["inc"] = inc;
  std::string expression = "dnorm(seq(min, max, by=inc), mu, sd)";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector v(ans);
  double value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist1D(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist1D(value) << std::endl;
      return 1;
    }
    value += inc;
  }
  expression = "pnorm(seq(min, max, by=inc), mu, sd)";
  ans = R.parseEval(expression);
  v = ans;
  value = min;
  for (size_t i = 0; i < (size_t)v.size(); ++i) {
    if (fabs(dist1D.cdf(value) - v[i]) > 1e-12) {
      std::cout << v[i] << " " << dist1D.cdf(value) << std::endl;
      return 1;
    }
    value += inc;
  }

  std::cout << "dist1D.getMean(): " << std::fixed << dist1D.getMean()
    << std::endl << std::endl;
  if (fabs(dist1D.getMean() - mu) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist1D.getVariance(): " << std::fixed << dist1D.getVariance()
    << std::endl << std::endl;
  if (fabs(dist1D.getVariance() - sigma2) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist1D.getMode(): " << std::fixed << dist1D.getMode()
    << std::endl << std::endl;
  if (fabs(dist1D.getMode() - mu) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist1D.setVariance(0.0)" << std::endl;
    dist1D.setVariance(0.0);
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

  NormalDistribution<1> distComp(1.0, 2.5);
  std::cout << "dist1D.KLDivergence(distComp(1.5, 2.5)): "
    << dist1D.KLDivergence(distComp) << std::endl << std::endl;

  NormalDistribution<1> distCopy(dist1D);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getMean() != dist1D.getMean())
    return 1;
  if (distCopy.getVariance() != dist1D.getVariance())
    return 1;
  NormalDistribution<1> distAssign = dist1D;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getMean() != dist1D.getMean())
    return 1;
  if (distAssign.getVariance() != dist1D.getVariance())
    return 1;

  std::cout << "Testing normal distribution 2-D" << std::endl;
  NormalDistribution<2> dist2D;
  std::cout << "Distribution default parameters: " << std::endl << dist2D
    << std::endl << std::endl;

  std::cout << "dist2D.getMean(): " << std::endl << dist2D.getMean()
    << std::endl << std::endl;
  std::cout << "dist2D.getCovariance(): " << std::endl << dist2D.getCovariance()
    << std::endl << std::endl;
  std::cout << "dist2D.getPrecision(): " << std::endl << dist2D.getPrecision()
    << std::endl << std::endl;
  std::cout << "dist2D.getDeterminant(): " << dist2D.getDeterminant()
    << std::endl << std::endl;
  std::cout << "dist2D.getNormalizer(): " << dist2D.getNormalizer()
    << std::endl << std::endl;

  std::cout << "dist2D.setMean((1, 1))" << std::endl;
  std::cout << "dist2D.setCovariance((2,0,0,2))" << std::endl;
  const Eigen::Matrix<double, 2, 1> mu2d(1.0, 1.0);
  const Eigen::Matrix<double, 2, 2> sigma22d((Eigen::Matrix<double, 2, 2>() <<
    2, 0, 0, 2).finished());
  dist2D.setMean(mu2d);
  dist2D.setCovariance(sigma22d);
  std::cout << "Distribution new parameters: " << std::endl << dist2D
    << std::endl << std::endl;
  if (dist2D.getMean() != mu2d)
    return 1;
  if (dist2D.getCovariance() != sigma22d)
    return 1;

  std::cout << "Evaluating distribution with GNU-R" << std::endl << std::endl;
  for (size_t i = 0; i < 100; ++i) {
    std::string expression = "library('mvtnorm');\
      rmvnorm(1, c(1,1), matrix(c(2,0,0,2),2,2))";
    SEXP ans = R.parseEval(expression);
    Rcpp::NumericVector x(ans);
    R["x"] = x;
    expression = "dmvnorm(x, c(1,1), matrix(c(2,0,0,2),2,2))";
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
  if (dist2D.getMean() != mu2d)
    return 1;
  std::cout << "dist2D.getCovariance(): " << std::endl << std::fixed
    << dist2D.getCovariance() << std::endl << std::endl;
  if (dist2D.getCovariance() != sigma22d)
    return 1;
  std::cout << "dist2D.getMode(): " << std::endl << std::fixed
    << dist2D.getMode() << std::endl << std::endl;
  if (dist2D.getMode() != mu2d)
    return 1;

  try {
    std::cout << "dist2D.setCovariance(2,3,0,2))" << std::endl;
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 2, 3, 0, 2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist2D.setCovariance(-2,0,0,-2))" << std::endl;
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist2D.setCovariance(1,-1.2,-1.2,1))" << std::endl;
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 1, -1.2, -1.2, 1).
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

  NormalDistribution<2> distComp2d(Eigen::Matrix<double, 2, 1>(1.0, 1.0),
    (Eigen::Matrix<double, 2, 2>() << 2.5, 0, 0, 2.5).finished());
  std::cout << "dist2D.KLDivergence(distComp2d((1.0,1.0), (2.5,0,0,2.5)): "
    << dist2D.KLDivergence(distComp2d) << std::endl << std::endl;

  NormalDistribution<2> distCopy2d(dist2D);
  std::cout << "Copy constructor: " << std::endl << distCopy2d << std::endl
    << std::endl;
  if (distCopy2d.getMean() != dist2D.getMean())
    return 1;
  if (distCopy2d.getCovariance() != dist2D.getCovariance())
    return 1;
  NormalDistribution<2> distAssign2d = dist2D;
  std::cout << "Assignment operator: " << std::endl << distAssign2d
    << std::endl;
  if (distAssign2d.getMean() != dist2D.getMean())
    return 1;
  if (distAssign2d.getCovariance() != dist2D.getCovariance())
    return 1;

  std::cout << "Testing normal distribution M-D" << std::endl;
  NormalDistribution<Eigen::Dynamic> distMd(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Zero(5), Eigen::Matrix<double, Eigen::Dynamic,
    Eigen::Dynamic>::Identity(5, 5));
  std::cout << "Distribution parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << distMd.getSample().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getMean(): " << distMd.getMean().transpose()
    << std::endl << std::endl;
  std::cout << "distMd.getCovariance(): " << std::endl << distMd.getCovariance()
    << std::endl << std::endl;

  return 0;
}
