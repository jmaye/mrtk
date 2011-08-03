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

/** \file KMeansClustering.cpp
    \brief This file is a testing binary for the KMeansClustering class
  */

#include "statistics/KMeansClustering.h"
#include "statistics/NormalDistribution.h"
#include "statistics/CategoricalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"

int main(int argc, char** argv) {
  std::vector<NormalDistribution<2> > distributions;
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(0, 0),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(5, 5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(10, 10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-5, -5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-10, -10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  MixtureSampleDistribution<NormalDistribution<2>, 5> dist(distributions,
    CategoricalDistribution<5>());

  std::vector<Eigen::Matrix<double, 2, 1> > samples;
  dist.getSamples(samples, 10000);

  std::vector<Eigen::Matrix<double, 2, 1> > clusterCenters;
  std::vector<std::vector<size_t> > assignments;
  KMeansClustering<double, 2>::cluster(samples, clusterCenters, assignments, 5,
    1000, 1e-6);

  std::cout << "cluster centers: " << std::endl;
  for (size_t i = 0; i < 5; ++i)
    std::cout << clusterCenters[i] << std::endl << std::endl;

  return 0;
}
