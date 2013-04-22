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

/** \file AdaptiveRejectionSampler.cpp
    \brief This file is a testing binary for the AdaptiveRejectionSampler class
  */

#include <iostream>

#include "statistics/AdaptiveRejectionSampler.h"
#include "statistics/GammaDistribution.h"

class LogPdf :
  public Function<double, double> {
public:
  virtual double getValue(const double& argument) const {
    static const GammaDistribution<> gammaDist(9.0, 2.0);
    return gammaDist.logpdf(argument);
  }
};

class LogPdfPrime :
  public Function<double, double> {
public:
  virtual double getValue(const double& argument) const {
    return 8.0 / argument - 2.0;
  }
};

int main(int argc, char** argv) {
  std::vector<double> samples;
  std::vector<double> initPoints;
  initPoints.push_back(2.0);
  initPoints.push_back(8.0);
  AdaptiveRejectionSampler::getSamples(LogPdf(), LogPdfPrime(), initPoints,
    samples, 10);
  return 0;
}
