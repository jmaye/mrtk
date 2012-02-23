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

/** \file CategoricalDistribution.cpp
    \brief This file is a testing binary for the CategoricalDistribution class
  */

#include <iostream>

#include "statistics/CategoricalDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing CategoricalDistribution<2>" << std::endl << std::endl;
  CategoricalDistribution<2> dist1;
  std::cout << "Distribution default parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getSuccessProbabilities(): " << std::endl
    << dist1.getSuccessProbabilities() << std::endl << std::endl;
  std::cout << "dist1.setSuccessProbabilities(0.7, 0.3)" << std::endl
    << std::endl;
  dist1.setSuccessProbabilities(Eigen::Vector2d(0.7, 0.3));
  std::cout << "Distribution new parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getSuccessProbability(0): "
    << dist1.getSuccessProbability(0) << std::endl << std::endl;
  std::cout << "dist1.getSuccessProbability(1): "
    << dist1.getSuccessProbability(1) << std::endl << std::endl;

  try {
    std::cout << "dist1.getSuccessProbability(2): "
      << dist1.getSuccessProbability(2) << std::endl << std::endl;
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  Eigen::Matrix<size_t, 2, 1> value1;
  value1(0) = 1;
  value1(1) = 0;
  std::cout << "pmf(1, 0): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.7) > 1e-4)
    return 1;

  value1(0) = 0;
  value1(1) = 1;
  std::cout << "pmf(0, 1): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.3) > 1e-4)
    return 1;

  try {
    std::cout << "dist1.setSuccessProbabilities(0.8, 0.9)" << std::endl;
    dist1.setSuccessProbabilities(Eigen::Vector2d(0.8, 0.9));
  }
  catch (BadArgumentException<Eigen::Vector2d>& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << std::endl;

  std::cout << "dist1.getSample(): " << std::endl
    << dist1.getSample() << std::endl << std::endl;

  std::cout << "Testing CategoricalDistribution<3>" << std::endl << std::endl;
  CategoricalDistribution<3> dist2;
  std::cout << "Distribution default parameters: " << std::endl << dist2
    << std::endl << std::endl;
  std::cout << "dist2.getNumTrials(): " << dist2.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist2.getSuccessProbabilities(): " << std::endl
    << dist2.getSuccessProbabilities() << std::endl << std::endl;
  try {
    std::cout << "dist2.setNumTrials(5)" << std::endl << std::endl;
    dist2.setNumTrials(5);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "dist2.setSuccessProbabilities(0.1, 0.7, 0.2)" << std::endl
    << std::endl;
  dist2.setSuccessProbabilities(Eigen::Matrix<double, 3, 1>(0.1, 0.7, 0.2));
  std::cout << "Distribution new parameters: " << std::endl << dist2
    << std::endl << std::endl;

  Eigen::Matrix<size_t, 3, 1> value2;
  value2(0) = 0;
  value2(1) = 0;
  value2(2) = 1;
  std::cout << "pmf(0, 0, 1): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0.2) > 1e-4)
    return 1;

  value2(0) = 1;
  value2(1) = 0;
  value2(2) = 0;
  std::cout << "pmf(1, 0, 0): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0.1) > 1e-4)
    return 1;

  value2(0) = 0;
  value2(1) = 1;
  value2(2) = 0;
  std::cout << "pmf(0, 1, 0): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0.7) > 1e-4)
    return 1;

  value1(0) = 0;
  value1(1) = 1;
  std::cout << "pmf(0, 1): " << std::fixed << dist2(value1) << std::endl
    << std::endl;
  if (fabs(dist2(value1) - 0.2) > 1e-4)
    return 1;

  std::cout << "logpmf(0, 1, 0): " << std::fixed << dist2.logpmf(value2)
    << std::endl << std::endl;
  std::cout << "logpmf(0, 1): " << std::fixed << dist2.logpmf(value1)
    << std::endl << std::endl;

  std::cout << "dist2.getSample(): " << std::endl << dist2.getSample()
    << std::endl << std::endl;

  std::cout << "Testing categorical distribution M-D" << std::endl;
  CategoricalDistribution<Eigen::Dynamic> distMd(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Constant(5, 1.0 / 5.0));
  std::cout << "distMd.getSample(): " << distMd.getSample().transpose()
    << std::endl;
  std::cout << "distMd.getMean(): " << distMd.getMean().transpose()
    << std::endl;
  std::cout << "distMd.getCovariance(): " << std::endl << distMd.getCovariance()
    << std::endl;

  return 0;
}
