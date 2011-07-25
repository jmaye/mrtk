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

#include "statistics/StudentDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing Student distribution 1-D" << std::endl;
  StudentDistribution<1> dist1D;
  std::cout << "Distribution default parameters: " << std::endl << dist1D
    << std::endl << std::endl;
  std::cout << "dist.getDegrees(): " << dist1D.getDegrees() << std::endl
    << std::endl;
  std::cout << "dist.getNormalizer(): " << dist1D.getNormalizer()
    << std::endl << std::endl;
  std::cout << "dist.setDegrees(2)" << std::endl;
  dist1D.setDegrees(2);
  std::cout << "Distribution new parameters: " << std::endl << dist1D
    << std::endl << std::endl;

  std::cout << "pdf(1): " << std::fixed << dist1D(1) << std::endl
    << std::endl;
  if (fabs(dist1D(1) - 0.1924501) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << dist1D(3) << std::endl
    << std::endl;
  if (fabs(dist1D(3) - 0.02741012) > 1e-4)
    return 1;

  std::cout << "pdf(-1): " << std::fixed << dist1D(-1) << std::endl
    << std::endl;
  if (fabs(dist1D(-1) - 0.1924501) > 1e-4)
    return 1;

  std::cout << "logpdf(2): " << std::fixed << dist1D.logpdf(2) << std::endl
    << std::endl;
  if (fabs(dist1D.logpdf(2) + 2.687639) > 1e-4)
    return 1;

  std::cout << "cdf(1): " << std::fixed << dist1D.cdf(1) << std::endl
    << std::endl;
  if (fabs(dist1D.cdf(1) - 0.7886751) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << dist1D.getSample() << std::endl
    << std::endl;

  try {
    dist1D.setDegrees(-1.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "Testing Student distribution 2-D" << std::endl;
  StudentDistribution<2> dist2D;
  std::cout << "Distribution default parameters: " << std::endl << dist2D
    << std::endl << std::endl;
  std::cout << "dist.getLocation(): " << std::endl << dist2D.getLocation()
    << std::endl << std::endl;
  std::cout << "dist.getScale(): " << std::endl << dist2D.getScale()
    << std::endl << std::endl;
  std::cout << "dist.getInverseScale(): " << std::endl <<
    dist2D.getInverseScale() << std::endl << std::endl;
  std::cout << "dist.getDeterminant(): " << dist2D.getDeterminant()
    << std::endl << std::endl;
  std::cout << "dist.getNormalizer(): " << dist2D.getNormalizer()
    << std::endl << std::endl;
  std::cout << "dist.setLocation((1, 1))" << std::endl;
  dist2D.setLocation(Eigen::Matrix<double, 2, 1>(1, 1));
  std::cout << "dist.setScale((2,0,0,2))" << std::endl;
  dist2D.setScale((Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).
    finished());
  std::cout << "dist.setDegrees(2)" << std::endl;
  dist2D.setDegrees(2);
  std::cout << "Distribution new parameters: " << std::endl << dist2D
    << std::endl << std::endl;

  std::cout << "pdf((1, 1)): " << std::fixed << dist2D(Eigen::Matrix<double, 2, 1>(1, 1)) << std::endl
    << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(1, 1)) - 0.07957747) > 1e-4)
    return 1;

  std::cout << "pdf((3, 3)): " << std::fixed << dist2D(Eigen::Matrix<double, 2, 1>(3, 3)) << std::endl
    << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(3, 3)) - 0.008841941) > 1e-4)
    return 1;

  std::cout << "pdf((-1, -1)): " << std::fixed << dist2D(Eigen::Matrix<double, 2, 1>(-1, -1)) << std::endl
    << std::endl;
  if (fabs(dist2D(Eigen::Matrix<double, 2, 1>(-1, -1)) - 0.008841941) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << dist2D.getSample()
    << std::endl << std::endl;

//  try {
//    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 2, 3, 0, 2).
//      finished());
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
//    std::cout << e.what() << std::endl;
//  }

//  try {
//    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).
//      finished());
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
//    std::cout << e.what() << std::endl;
//  }

//  try {
//    dist2D.setCovariance((Eigen::Matrix<double, 2, 2>() << 1, -1.2, -1.2, 1).
//      finished());
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
//    std::cout << e.what() << std::endl;
//  }

  return 0;
}
