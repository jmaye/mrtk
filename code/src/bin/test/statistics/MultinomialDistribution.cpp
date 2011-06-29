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

#include "statistics/MultinomialDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing MultinomialDistribution<2>" << std::endl << std::endl;
  MultinomialDistribution<2> dist1;
  std::cout << "Distribution default parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getNumTrials(): " << dist1.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist1.getSuccessProbabilities(): " << std::endl
    << dist1.getSuccessProbabilities() << std::endl << std::endl;
  std::cout << "dist1.setNumTrials(5)" << std::endl << std::endl;
  dist1.setNumTrials(5);
  Eigen::Matrix<double, 2, 1> success1;
  success1(0) = 0.1;
  success1(1) = 0.9;
  std::cout << "dist1.setSuccessProbabilities(0.1, 0.9)" << std::endl
    << std::endl;
  dist1.setSuccessProbabilities(success1);
  std::cout << "Distribution new parameters: " << std::endl << dist1
    << std::endl << std::endl;

  Eigen::Matrix<size_t, 2, 1> value1;
  value1(0) = 2;
  value1(1) = 3;
  std::cout << "pmf(2, 3): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.0729) > 1e-4)
    return 1;

  value1(0) = 5;
  value1(1) = 0;
  std::cout << "pmf(5, 0): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0) > 1e-4)
    return 1;

  value1(0) = 0;
  value1(1) = 5;
  std::cout << "pmf(0, 5): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.5905) > 1e-4)
    return 1;

  std::cout << "pmf(2): " << std::fixed << dist1(2) << std::endl
    << std::endl;
  if (fabs(dist1(2) - 0.0729) > 1e-4)
    return 1;

  std::cout << "logpmf(0, 5): " << std::fixed << dist1.logpmf(value1)
    << std::endl << std::endl;
  std::cout << "logpmf(2): " << std::fixed << dist1.logpmf(2) << std::endl
    << std::endl;

  //std::cout << "dist1.getSample(): " << std::endl << dist1.getSample()
    //<< std::endl << std::endl;

  try {
    value1(0) = 2;
    value1(1) = 2;
    std::cout << "dist1.pmf(2, 2)" << dist1(value1) << std::endl << std::endl;
  }
  catch (BadArgumentException<Eigen::Matrix<size_t, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    dist1.setNumTrials(0);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    success1(0) = 0.1;
    success1(1) = 0.8;
    std::cout << "dist1.setSuccessProbabilities(0.1, 0.8)" << std::endl
      << std::endl;
    dist1.setSuccessProbabilities(success1);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "Testing MultinomialDistribution<3>" << std::endl << std::endl;
  MultinomialDistribution<3> dist2;
  std::cout << "Distribution default parameters: " << std::endl << dist2
    << std::endl << std::endl;
  std::cout << "dist2.getNumTrials(): " << dist2.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist2.getSuccessProbabilities(): " << std::endl
    << dist2.getSuccessProbabilities() << std::endl << std::endl;
  std::cout << "dist2.setNumTrials(5)" << std::endl << std::endl;
  dist2.setNumTrials(5);
  Eigen::Matrix<double, 3, 1> success2;
  success2(0) = 0.1;
  success2(1) = 0.7;
  success2(2) = 0.2;
  std::cout << "dist2.setSuccessProbabilities(0.1, 0.7, 0.2)" << std::endl
    << std::endl;
  dist2.setSuccessProbabilities(success2);
  std::cout << "Distribution new parameters: " << std::endl << dist2
    << std::endl << std::endl;

  Eigen::Matrix<size_t, 3, 1> value2;
  value2(0) = 2;
  value2(1) = 2;
  value2(2) = 1;
  std::cout << "pmf(2, 2, 1): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0.0294) > 1e-4)
    return 1;

  value2(0) = 5;
  value2(1) = 0;
  value2(2) = 0;
  std::cout << "pmf(5, 0, 0): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0) > 1e-4)
    return 1;

  value2(0) = 0;
  value2(1) = 4;
  value2(2) = 1;
  std::cout << "pmf(0, 4, 1): " << std::fixed << dist2(value2) << std::endl
    << std::endl;
  if (fabs(dist2(value2) - 0.2401) > 1e-4)
    return 1;

  value1(0) = 0;
  value1(1) = 4;
  std::cout << "pmf(0, 4): " << std::fixed << dist2(value1) << std::endl
    << std::endl;
  if (fabs(dist2(value1) - 0.2401) > 1e-4)
    return 1;

  std::cout << "logpmf(0, 4, 1): " << std::fixed << dist2.logpmf(value2)
    << std::endl << std::endl;
  std::cout << "logpmf(0, 4): " << std::fixed << dist2.logpmf(value1)
    << std::endl << std::endl;

  //std::cout << "dist2.getSample(): " << std::endl << dist2.getSample()
    //<< std::endl << std::endl;

  return 0;
}
