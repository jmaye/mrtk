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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "statistics/KMeansClustering.h"
#include "statistics/UniformDistribution.h"
#include "statistics/Randomizer.h"

#include <vector>
#include <iostream>

#include <stdint.h>

int main(int argc, char** argv) {
  UniformDistribution uniDist(0, 1);
  Randomizer randomizer;
  for (uint32_t i = 0; i < 10; i++)
    //std::cout << uniDist.sample() << std::endl;
    std::cout << randomizer.sampleNormal(10, 0.1) << std::endl;
  std::vector<std::vector<double> > inputPointsVector;
  std::vector<std::vector<double> > clusterCentersVector;
  std::vector<std::vector<uint32_t> > assignmentsVector;
  uint32_t u32K;
  uint32_t u32MaxIterations;
  double f64Tol;

  KMeansClustering::cluster(inputPointsVector, clusterCentersVector,
    assignmentsVector, u32K, u32MaxIterations, f64Tol);
}
