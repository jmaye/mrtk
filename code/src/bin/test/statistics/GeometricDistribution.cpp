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

/** \file GeometricDistribution.cpp
    \brief This file is a testing binary for the GeometricDistribution class
  */

#include "statistics/GeometricDistribution.h"

int main(int argc, char** argv) {
  GeometricDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getSuccessProbability(): "
    << dist.getSuccessProbability() << std::endl << std::endl;
  std::cout << "dist.setSuccessProbability(0.7)" << std::endl << std::endl;
  dist.setSuccessProbability(0.7);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  std::cout << "pmf(0): " << std::fixed << dist(0) << std::endl << std::endl;
  if (fabs(dist(0) - 0.7) > 1e-4)
    return 1;
  std::cout << "pmf(1): " << std::fixed << dist(1) << std::endl << std::endl;
  if (fabs(dist(1) - 0.21) > 1e-4)
    return 1;

  std::cout << "logpmf(1): " << std::fixed << dist.logpmf(1) << std::endl
    << std::endl;

  std::cout << "dist.getSample(): " << dist.getSample() << std::endl
    << std::endl;

  try {
    dist.setSuccessProbability(1.2);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
