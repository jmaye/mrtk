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

/** \file NegativeBinomialDistribution.cpp
    \brief This file is a testing binary for the NegativeBinomialDistribution
           class
  */

#include <iostream>

#include "statistics/NegativeBinomialDistribution.h"

int main(int argc, char** argv) {
  NegativeBinomialDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getNumTrials(): " << dist.getNumTrials() << std::endl
    << std::endl;
  std::cout << "dist.getSuccessProbability(): " << dist.getSuccessProbability()
    << std::endl << std::endl;
  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  dist.setNumTrials(5);
  std::cout << "dist.setSuccessProbability(0.7)" << std::endl << std::endl;
  dist.setSuccessProbability(0.7);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  std::cout << "pmf(2): " << std::fixed << dist(2) << std::endl << std::endl;
  Eigen::Matrix<size_t, 2, 1> value;
  if (fabs(dist(2) - 0.0178604) > 1e-4)
    return 1;
  value << 5, 2;
  std::cout << "pmf(5, 2): " << std::fixed << dist(value) << std::endl
    << std::endl;
  if (fabs(dist(value) - 0.0178604) > 1e-4)
    return 1;

  return 0;
}
