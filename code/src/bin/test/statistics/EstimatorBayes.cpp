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

/** \file EstimatorBayes.cpp
    \brief This file is a testing binary for the EstimatorBayes class
  */

#include <iostream>

#include "statistics/EstimatorBayes.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorBayes<NormalDistribution<1> > estNorm1(5, 1, 1, 2);
  estNorm1.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation1: " << std::endl << estNorm1 << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5),
    (Eigen::Matrix<double, 2, 2>() << 2, 1, 1, 2).finished());
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorBayes<NormalDistribution<2>, 2> estNorm2;
  estNorm2.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation2: " << std::endl << estNorm2 << std::endl;
  MultinomialDistribution<4> distMult4(20);
  std::vector<Eigen::Matrix<size_t, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorBayes<MultinomialDistribution<4>, 4> estMult4(20);
  estMult4.addPoints(samplesMult4.begin(), samplesMult4.end());
  std::cout << "Estimation4: " << std::endl << estMult4 << std::endl;
  PoissonDistribution distPois(2.0);
  std::vector<size_t> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorBayes<PoissonDistribution> estPois;
  estPois.addPoints(samplesPois.begin(), samplesPois.end());
  std::cout << "Estimation5: " << std::endl << estPois << std::endl;
  ExponentialDistribution distExp(2);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorBayes<ExponentialDistribution> estExp;
  estExp.addPoints(samplesExp.begin(), samplesExp.end());
  std::cout << "Estimation6: " << std::endl << estExp << std::endl;
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x += 0.01) {
    distLine.setBasis(Eigen::Matrix<double, 2, 1>(1.0, x));
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(x, distLine.getSample()));
  }
  EstimatorBayes<LinearRegression<2>, 2> estLine;
  estLine.addPoints(samplesLine.begin(), samplesLine.end());
  std::cout << "Estimation7: " << std::endl << estLine << std::endl;
  return 0;
}
