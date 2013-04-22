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

/** \file ImportanceSampler.cpp
    \brief This file is a testing binary for the ImportanceSampler class
  */

#include <iostream>

#include "statistics/ImportanceSampler.h"
#include "statistics/GammaDistribution.h"
#include "statistics/CauchyDistribution.h"

int main(int argc, char** argv) {
  GammaDistribution<> gammaDist(2.0, 2.0);
  CauchyDistribution cauchyDist(1.0, 2.0);
  std::vector<double> samples;
  std::vector<double> weights;
  const size_t numSamples = 1000;
  ImportanceSampler::getSamples(gammaDist, cauchyDist, weights, samples,
    numSamples);
  double mean = 0;
  for (size_t i = 0; i < numSamples; ++i)
    mean += weights[i] * samples[i];
  std::cout << "Importance sampler mean: " << mean << std::endl;
  std::cout << "Distribution mean: " << gammaDist.getMean() << std::endl;
  return 0;
}
