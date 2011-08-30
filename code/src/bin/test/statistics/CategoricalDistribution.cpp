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

#include "statistics/CategoricalDistribution.h"

int main(int argc, char** argv) {
  CategoricalDistribution<2> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getSuccessProbabilities(): " << std::endl
    << dist.getSuccessProbabilities() << std::endl << std::endl;
  std::cout << "dist.setSuccessProbability(0.7, 0.3)" << std::endl << std::endl;
  dist.setSuccessProbabilities(Eigen::Vector2d(0.7, 0.3));
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  Eigen::Matrix<size_t, 2, 1> value;
  value(0) = 1;
  value(1) = 0;
  std::cout << "pmf(1, 0): " << std::fixed << dist(value) << std::endl
    << std::endl;
  if (fabs(dist(value) - 0.7) > 1e-4)
    return 1;

  value(0) = 0;
  value(1) = 1;
  std::cout << "pmf(0, 1): " << std::fixed << dist(value) << std::endl
    << std::endl;
  if (fabs(dist(value) - 0.3) > 1e-4)
    return 1;

  try {
    std::cout << "dist.setSuccessProbabilities(0.8, 0.9)" << std::endl;
    dist.setSuccessProbabilities(Eigen::Vector2d(0.8, 0.9));
  }
  catch (BadArgumentException<Eigen::Vector2d>& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl
    << dist.getSample() << std::endl << std::endl;

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
