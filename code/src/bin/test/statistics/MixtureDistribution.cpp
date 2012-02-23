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

/** \file MixtureDistribution.cpp
    \brief This file is a testing binary for the MixtureDistribution class
  */

#include <iostream>

#include "statistics/NormalDistribution.h"
#include "statistics/MixtureDistribution.h"

int main(int argc, char** argv) {
  std::vector<NormalDistribution<1> > distributions;
  distributions.push_back(NormalDistribution<1>(0, 1));
  distributions.push_back(NormalDistribution<1>(5, 1));
  distributions.push_back(NormalDistribution<1>(10, 1));
  distributions.push_back(NormalDistribution<1>(-5, 1));
  distributions.push_back(NormalDistribution<1>(-10, 1));
  MixtureDistribution<NormalDistribution<1>, 5> dist(distributions,
    CategoricalDistribution<5>());
  std::cout << "Mixture distribution: " << std::endl
    << dist << std::endl;
  std::cout << "dist.getAssignDistribution(): " << std::endl
    << dist.getAssignDistribution() << std::endl;

  std::cout << "dist.pdf(0): " << dist(0) << std::endl;
  if (fabs(dist(0) - 0.07979) > 1e-4)
    return 1;
  std::cout << "dist.pdf(5): " << dist(5) << std::endl;
  if (fabs(dist(5) - 0.07979) > 1e-4)
    return 1;
  std::cout << "dist.pdf(10): " << dist(10) << std::endl;
  if (fabs(dist(10) - 0.07979) > 1e-4)
    return 1;
  std::cout << "dist.pdf(-5): " << dist(-5) << std::endl;
  if (fabs(dist(-5) - 0.07979) > 1e-4)
    return 1;
  std::cout << "dist.pdf(-10): " << dist(-10) << std::endl;
  if (fabs(dist(-10) - 0.07979) > 1e-4)
    return 1;

  std::cout << "Testing M-d mixtures" << std::endl;
  MixtureDistribution<NormalDistribution<1>, Eigen::Dynamic> distMd(
    distributions, CategoricalDistribution<Eigen::Dynamic>(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Constant(5, 1.0 / 5.0)));
  std::cout << "dist.pdf(0): " << distMd(0) << std::endl;
  if (fabs(distMd(0) - 0.07979) > 1e-4)
    return 1;

  return 0;
}
