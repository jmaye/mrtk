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

/** \file MetropolisHastingsSampler.cpp
    \brief This file is a testing binary for the MetropolisHastingsSampler class
  */

#include <iostream>

#include "statistics/MetropolisHastingsSampler.h"
#include "statistics/NormalDistribution.h"

int main(int argc, char** argv) {
  NormalDistribution<2> dist(Eigen::Matrix<double, 2, 1>(1.0, 1.0),
    (Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).finished());
  NormalDistribution<2> proposal(Eigen::Matrix<double, 2, 1>(10.0, 10.0),
    Eigen::Matrix<double, 2, 2>::Identity() * 0.5);
  std::vector<Eigen::Matrix<double, 2, 1> > samples;
  const size_t numSamples = 1000;
  MetropolisHastingsSampler::getSamples<double, double, 2>(dist, proposal,
    samples, numSamples);
  return 0;
}
