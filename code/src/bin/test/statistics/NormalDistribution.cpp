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

#include "statistics/NormalDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing normal distribution 1-D" << std::endl;
  NormalDistribution<1> dist1D;
  std::cout << "Distribution default parameters: " << std::endl << dist1D
    << std::endl << std::endl;
  std::cout << "dist.getMean(): " << dist1D.getMean() << std::endl
    << std::endl;
  std::cout << "dist.getVariance(): " << dist1D.getVariance() << std::endl
    << std::endl;
  std::cout << "dist.getPrecision(): " << dist1D.getPrecision() << std::endl
    << std::endl;
  std::cout << "dist.getStandardDeviation(): " << dist1D.getStandardDeviation()
    << std::endl << std::endl;
  std::cout << "dist.getNormalizer(): " << dist1D.getNormalizer()
    << std::endl << std::endl;
  std::cout << "dist.setMean(1)" << std::endl;
  dist1D.setMean(1);
  std::cout << "dist.setVariance(2)" << std::endl;
  dist1D.setVariance(2);
  std::cout << "Distribution new parameters: " << std::endl << dist1D
    << std::endl << std::endl;

  std::cout << "pdf(1): " << std::fixed << dist1D(1) << std::endl
    << std::endl;
  if (fabs(dist1D(1) - 0.2820948) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << dist1D(3) << std::endl
    << std::endl;
  if (fabs(dist1D(3) - 0.1037769) > 1e-4)
    return 1;

  std::cout << "pdf(-1): " << std::fixed << dist1D(-1) << std::endl
    << std::endl;
  if (fabs(dist1D(-1) - 0.1037769) > 1e-4)
    return 1;

  std::cout << "logpdf(2): " << std::fixed << dist1D.logpdf(2) << std::endl
    << std::endl;
  if (fabs(dist1D.logpdf(2) + 1.515512) > 1e-4)
    return 1;

  std::cout << "cdf(1): " << std::fixed << dist1D.cdf(1) << std::endl
    << std::endl;
  if (fabs(dist1D.cdf(1) - 0.5) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << dist1D.getSample() << std::endl
    << std::endl;

  try {
    dist1D.setVariance(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "Testing normal distribution 2-D" << std::endl;
  NormalDistribution<2> dist2D;
  std::cout << "Distribution default parameters: " << std::endl << dist2D
    << std::endl << std::endl;
  std::cout << "dist.getMean(): " << std::endl << dist2D.getMean()
    << std::endl << std::endl;
  std::cout << "dist.getCovariance(): " << std::endl << dist2D.getCovariance()
    << std::endl << std::endl;
  std::cout << "dist.getPrecision(): " << std::endl << dist2D.getPrecision()
    << std::endl << std::endl;
  std::cout << "dist.getDeterminant(): " << dist2D.getDeterminant()
    << std::endl << std::endl;
  std::cout << "dist.getNormalizer(): " << dist2D.getNormalizer()
    << std::endl << std::endl;
  std::cout << "dist.setMean((1, 1))" << std::endl;
  dist2D.setMean(Eigen::Matrix<double, 2, 1>(1, 1));
  std::cout << "dist.setCovariance((2,0,0,2))" << std::endl;
  dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).
    finished());
  std::cout << "Distribution new parameters: " << std::endl << dist2D
    << std::endl << std::endl;

  std::cout << "pdf((1, 1)): " << std::fixed
    << dist2D(Eigen::Matrix<double, 2, 1>(1, 1)) << std::endl << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(1, 1)) -  0.0796) > 1e-4)
    return 1;

  std::cout << "pdf((3, 3)): " << std::fixed
    << dist2D(Eigen::Matrix<double, 2, 1>(3, 3)) << std::endl << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(3, 3)) - 0.0108) > 1e-4)
    return 1;

  std::cout << "pdf((-1, -1)): " << std::fixed
    << dist2D(Eigen::Matrix<double, 2, 1>(-1, -1)) << std::endl << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(-1, -1)) - 0.0108) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << dist2D.getSample()
    << std::endl << std::endl;

  try {
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 2, 3, 0, 2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 1, -1.2, -1.2, 1).
      finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
