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

/** \file EstimatorMLMixture.cpp
    \brief This file is a testing binary for the EstimatorMLMixture class.
  */

#include <iostream>

//#include "statistics/EstimatorMLMixture.h"
#include "statistics/MixtureSampleDistribution.h"
#include "statistics/NormalDistribution.h"

int main(int argc, char** argv) {
  std::vector<NormalDistribution<1> > distributionsNorm1;
  distributionsNorm1.push_back(NormalDistribution<1>(0, 1));
  distributionsNorm1.push_back(NormalDistribution<1>(5, 1));
  distributionsNorm1.push_back(NormalDistribution<1>(10, 1));
  distributionsNorm1.push_back(NormalDistribution<1>(-5, 1));
  distributionsNorm1.push_back(NormalDistribution<1>(-10, 1));
  MixtureSampleDistribution<NormalDistribution<1>, 5> distMixtNorm1(
    distributionsNorm1, CategoricalDistribution<5>());
  std::vector<double> samplesMixtNorm1;
  distMixtNorm1.getSamples(samplesMixtNorm1, 1000);
  Eigen::Matrix<double, 5, 1> initMeansMixtNorm1;
  initMeansMixtNorm1 << 1, 6, 12, -5.5, -9.5;
  Eigen::Matrix<double, 5, 1> initVariancesMixtNorm1;
  initVariancesMixtNorm1 << 1.5, 1.2, 1.1, 0.9, 2.0;
  Eigen::Matrix<double, 5, 1> initWeightsMixtNorm1;
  initWeightsMixtNorm1 << 0.2, 0.3, 0.1, 0.3, 0.1;
  //EstimatorMLMixture<NormalDistribution<1>, 5> estMixNorm1(distMixtNorm1);
  return 0;
}
