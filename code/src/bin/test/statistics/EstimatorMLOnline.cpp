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

/** \file EstimatorMLOnline.cpp
    \brief This file is a testing binary for the EstimatorML class online
  */

#include <iostream>

#include "statistics/EstimatorML.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorML<NormalDistribution<1> > estNorm1;
  for (size_t i = 0; i < samplesNorm1.size(); ++i)
    estNorm1.addPoint(samplesNorm1[i]);
  std::cout << "Estimation1: " << std::endl << estNorm1 << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5));
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorML<NormalDistribution<2>, 2> estNorm2;
  for (size_t i = 0; i < samplesNorm2.size(); ++i)
    estNorm2.addPoint(samplesNorm2[i]);
  std::cout << "Estimation2: " << std::endl << estNorm2 << std::endl;
  CategoricalDistribution<4> distCat4;
  std::vector<Eigen::Matrix<int, 4, 1> > samplesCat4;
  distCat4.getSamples(samplesCat4, 1000);
  EstimatorML<CategoricalDistribution<4>, 4> estCat4;
  for (size_t i = 0; i < samplesCat4.size(); ++i)
    estCat4.addPoint(samplesCat4[i]);
  std::cout << "Estimation3: " << std::endl << estCat4 << std::endl;
  MultinomialDistribution<4> distMult4(20);
  std::vector<Eigen::Matrix<int, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorML<MultinomialDistribution<4>, 4> estMult4(20);
  for (size_t i = 0; i < samplesMult4.size(); ++i)
    estMult4.addPoint(samplesMult4[i]);
  std::cout << "Estimation4: " << std::endl << estMult4 << std::endl;
  ExponentialDistribution distExp(2);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorML<ExponentialDistribution> estExp;
  for (size_t i = 0; i < samplesExp.size(); ++i)
    estExp.addPoint(samplesExp[i]);
  std::cout << "Estimation5: " << std::endl << estExp << std::endl;
  GeometricDistribution distGeom(0.7);
  std::vector<int> samplesGeom;
  distGeom.getSamples(samplesGeom, 1000);
  EstimatorML<GeometricDistribution> estGeom;
  for (size_t i = 0; i < samplesGeom.size(); ++i)
    estGeom.addPoint(samplesGeom[i]);
  std::cout << "Estimation6: " << std::endl << estGeom << std::endl;
  PoissonDistribution distPois(2.0);
  std::vector<int> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorML<PoissonDistribution> estPois;
  for (size_t i = 0; i < samplesPois.size(); ++i)
    estPois.addPoint(samplesPois[i]);
  std::cout << "Estimation7: " << std::endl << estPois << std::endl;
  return 0;
}
