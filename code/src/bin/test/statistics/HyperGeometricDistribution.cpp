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

/** \file HyperGeometricDistribution.cpp
    \brief This file is a testing binary for the HyperGeometricDistribution
           class
  */

#include "statistics/HyperGeometricDistribution.h"

int main(int argc, char** argv) {
  HyperGeometricDistribution<2> dist1;
  std::cout << "Distribution default parameters: " << std::endl << dist1
    << std::endl << std::endl;
  std::cout << "dist1.getNumTrials(): " << dist1.getNumTrials()
    << std::endl << std::endl;
  std::cout << "dist1.getMarbles(): " << std::endl
    << dist1.getMarbles() << std::endl << std::endl;
  Eigen::Matrix<size_t, 2, 1> marbles1;
  marbles1(0) = 5;
  marbles1(1) = 10;
  std::cout << "dist1.setMarbles(5, 10)" << std::endl << std::endl;
  dist1.setMarbles(marbles1);
  std::cout << "dist1.setNumTrials(5)" << std::endl << std::endl;
  dist1.setNumTrials(5);
  std::cout << "Distribution new parameters: " << std::endl << dist1
    << std::endl << std::endl;

  Eigen::Matrix<size_t, 2, 1> value1;
  value1(0) = 2;
  value1(1) = 3;
  std::cout << "pmf(2, 3): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.3996004) > 1e-4)
    return 1;

  value1(0) = 5;
  value1(1) = 0;
  std::cout << "pmf(5, 0): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.0003330003) > 1e-4)
    return 1;

  value1(0) = 0;
  value1(1) = 5;
  std::cout << "pmf(0, 5): " << std::fixed << dist1(value1) << std::endl
    << std::endl;
  if (fabs(dist1(value1) - 0.08391608) > 1e-4)
    return 1;

  std::cout << "pmf(2): " << std::fixed << dist1(2) << std::endl
    << std::endl;
  if (fabs(dist1(2) - 0.3996004) > 1e-4)
    return 1;

  std::cout << "logpmf(0, 5): " << std::fixed << dist1.logpmf(value1)
    << std::endl << std::endl;
  std::cout << "logpmf(2): " << std::fixed << dist1.logpmf(2) << std::endl
    << std::endl;

  std::cout << "dist1.getSample(): " << std::endl << dist1.getSample()
    << std::endl << std::endl;

  try {
    dist1.setNumTrials(20);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
