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

#include "statistics/DirichletDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing DirichletDistribution<2>" << std::endl << std::endl;
  Eigen::Matrix<double, 2, 1> alpha1;
  alpha1(0) = 0.1;
  alpha1(1) = 0.9;
  DirichletDistribution<2> dist1;
  std::cout << "Distribution default parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getAlpha(): " << std::endl << dist1.getAlpha()
    << std::endl << std::endl;
  std::cout << "dist1.setAlpha(0.1, 0.9)" << std::endl << std::endl;
  dist1.setAlpha(alpha1);
  std::cout << "Distribution new parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getAlpha(): " << std::endl << dist1.getAlpha()
    << std::endl << std::endl;

  std::cout << "dist1.getMean(): " << std::endl <<
    dist1.getMean() << std::endl << std::endl;
  std::cout << "dist1.getCovariance(): " << std::endl <<
    dist1.getCovariance() << std::endl << std::endl;

  Eigen::Matrix<double, 2, 1> value1;
  value1(0) = 0.9;
  value1(1) = 0.1;
  std::cout << "pdf(0.9, 0.1): " << std::fixed << dist1(value1) << std::endl
     << std::endl;
  if (fabs(dist1(value1) - 0.1361) > 1e-4)
    return 1;

  value1(0) = 0.1;
  value1(1) = 0.9;
  std::cout << "pdf(0.1, 0.9): " << std::fixed << dist1(value1) << std::endl
     << std::endl;
  if (fabs(dist1(value1) - 0.7896) > 1e-4)
    return 1;

  std::cout << "pdf(0.1): " << std::fixed << dist1(0.1) << std::endl
    << std::endl;
  if (fabs(dist1(0.1) - 0.7896) > 1e-4)
    return 1;
  std::cout << "pdf(0.9): " << std::fixed << dist1(0.9) << std::endl
    << std::endl;
  if (fabs(dist1(0.9) - 0.1361) > 1e-4)
    return 1;

  std::cout << "logpdf(0.1, 0.9): " << std::fixed << dist1.logpdf(value1)
    << std::endl << std::endl;
  std::cout << "logpdf(0.1): " << std::fixed << dist1.logpdf(0.1) << std::endl
    << std::endl;

  std::cout << "dist1.getSample(): " << std::endl << dist1.getSample()
    << std::endl << std::endl;

  try {
    alpha1(0) = 0.0;
    alpha1(1) = 0.9;
    dist1.setAlpha(alpha1);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "Testing DirichletDistribution<3>" << std::endl << std::endl;

  Eigen::Matrix<double, 3, 1> alpha2;
  alpha2(0) = 0.1;
  alpha2(1) = 0.9;
  alpha2(2) = 1.2;
  DirichletDistribution<3> dist2;
  std::cout << "Distribution default parameters: " << std::endl << dist2
    << std::endl << std::endl;
  std::cout << "dist2.getAlpha(): " << std::endl << dist2.getAlpha()
    << std::endl << std::endl;
  std::cout << "dist2.setAlpha(0.1, 0.9)" << std::endl << std::endl;
  dist2.setAlpha(alpha2);
  std::cout << "Distribution new parameters: " << std::endl << dist2
    << std::endl << std::endl;
  std::cout << "dist2.getAlpha(): " << std::endl << dist2.getAlpha()
    << std::endl << std::endl;

  Eigen::Matrix<double, 3, 1> value2;
  value2(0) = 0.8;
  value2(1) = 0.1;
  value2(2) = 0.1;
  std::cout << "pdf(0.8, 0.1, 0.1): " << std::fixed << dist2(value2)
    << std::endl << std::endl;
  if (fabs(dist2(value2) - 0.1146) > 1e-4)
    return 1;

  value2(0) = 0.1;
  value2(1) = 0.8;
  value2(2) = 0.1;
  std::cout << "pdf(0.1, 0.8, 0.1): " << std::fixed << dist2(value2)
     << std::endl << std::endl;
  if (fabs(dist2(value2) - 0.6049) > 1e-4)
    return 1;

  value1(0) = 0.1;
  value1(1) = 0.8;
  std::cout << "pdf(0.1, 0.8): " << std::fixed << dist2(value1)
     << std::endl << std::endl;
  if (fabs(dist2(value1) - 0.6049) > 1e-4)
    return 1;

  std::cout << "logpdf(0.1, 0.8, 0.1): " << std::fixed << dist2.logpdf(value2)
    << std::endl << std::endl;
  std::cout << "logpdf(0.1, 0.8): " << std::fixed << dist2.logpdf(value1)
    << std::endl << std::endl;

  std::cout << "dist2.getSample(): " << std::endl << dist2.getSample()
    << std::endl << std::endl;

  return 0;
}
