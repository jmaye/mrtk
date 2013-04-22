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

/** \file NegativeMultinomialDistribution.cpp
    \brief This file is a testing binary for the NegativeMultinomialDistribution
           class
  */

#include <iostream>

#include "statistics/NegativeMultinomialDistribution.h"

int main(int argc, char** argv) {
  NegativeMultinomialDistribution<3> dist;
 std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getNumTrials(): " << dist.getNumTrials() << std::endl
    << std::endl;
  std::cout << "dist.getProbabilities(): " << std::endl
    << dist.getProbabilities() << std::endl << std::endl;

  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  std::cout << "dist.setProbabilities(0.5, 0.3, 0.2)" << std::endl
    << std::endl;
  const size_t n = 5;
  const Eigen::Matrix<double, 3, 1> p(0.5, 0.3, 0.2);
  dist.setNumTrials(n);
  dist.setProbabilities(p);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;
  if (dist.getNumTrials() != n)
    return 1;
  if (dist.getProbabilities() != p)
    return 1;

  return 0;
}
