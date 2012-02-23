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

/** \file BernoulliDistribution.cpp
    \brief This file is a testing binary for the BernoulliDistribution class
  */

#include <iostream>

#include "statistics/BernoulliDistribution.h"

int main(int argc, char** argv) {
  BernoulliDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getSuccessProbability(): " << dist.getSuccessProbability()
    << std::endl << std::endl;
  std::cout << "dist.setSuccessProbability(0.7)" << std::endl << std::endl;
  dist.setSuccessProbability(0.7);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  std::cout << "pmf(0): " << std::fixed << dist(0) << std::endl << std::endl;
  if (fabs(dist(0) - 0.3) > 1e-4)
    return 1;

  std::cout << "pmf(1): " << std::fixed << dist(1) << std::endl << std::endl;
  if (fabs(dist(1) - 0.7) > 1e-4)
    return 1;

  try {
    std::cout << "dist.setSuccessProbability(1.2)" << std::endl;
    dist.setSuccessProbability(1.2);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  std::vector<Eigen::Matrix<size_t, 2, 1> > samples;
  dist.getSamples(samples, 10);

  std::cout << "dist.getSamples(samples, 10): " << std::endl;

  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;

  return 0;
}
