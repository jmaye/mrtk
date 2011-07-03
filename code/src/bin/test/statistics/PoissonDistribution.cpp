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

/** \file PoissonDistribution.cpp
    \brief This file is a testing binary for the PoissonDistribution class
  */

#include "statistics/PoissonDistribution.h"

int main(int argc, char** argv) {
  PoissonDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getRate(): " << dist.getRate() << std::endl
    << std::endl;
  std::cout << "dist.setRate(2.5)" << std::endl << std::endl;
  dist.setRate(2.5);
  std::cout << "Distribution new parameters: " << std::endl << dist << std::endl
    << std::endl;

  std::cout << "pmf(2): " << std::fixed << dist(2) << std::endl << std::endl;
  if (fabs(dist(2) - 0.2565156) > 1e-4)
    return 1;

  std::cout << "pmf(5): " << std::fixed << dist(5) << std::endl << std::endl;
  if (fabs(dist(5) - 0.06680094) > 1e-4)
    return 1;

  std::cout << "pmf(0): " << std::fixed << dist(0) << std::endl << std::endl;
  if (fabs(dist(0) - 0.082085) > 1e-4)
    return 1;

  std::cout << "logpmf(2): " << std::fixed << dist.logpmf(2) << std::endl
    << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  return 0;
}
