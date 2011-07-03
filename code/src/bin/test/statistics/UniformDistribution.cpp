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

/** \file UniformDistribution.cpp
    \brief This file is a testing binary for the UniformDistribution class
  */

#include "statistics/UniformDistribution.h"

int main(int argc, char** argv) {
  UniformDistribution<double> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getMinSupport(): " << dist.getMinSupport() << std::endl
    << std::endl;
  std::cout << "dist.getMaxSupport(): " << dist.getMaxSupport() << std::endl
    << std::endl;
  std::cout << "dist.setSupport(2, 5)" << std::endl << std::endl;
  dist.setSupport(2, 5);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  std::cout << "pdf(2): " << std::fixed << dist(2) << std::endl << std::endl;
  if (fabs(dist(2) - 1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(5): " << std::fixed << dist(5) << std::endl << std::endl;
  if (fabs(dist(5) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << dist(3) << std::endl << std::endl;
  if (fabs(dist(3) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(10): " << std::fixed << dist(10) << std::endl << std::endl;
  if (fabs(dist(10) - 0.0) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  return 0;
}
