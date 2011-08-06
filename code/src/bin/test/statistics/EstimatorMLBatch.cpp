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

/** \file EstimatorMLBatch.cpp
    \brief This file is a testing binary for the EstimatorMLBatch class
  */

#include "statistics/EstimatorMLBatch.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorMLBatch<NormalDistribution<1> >::estimate(distNorm1, samplesNorm1);
  std::cout << "Estimation1: " << std::endl << distNorm1 << std::endl;
  NormalDistribution<2> distNorm2;
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorMLBatch<NormalDistribution<2>, 2>::estimate(distNorm2, samplesNorm2);
  std::cout << "Estimation2: " << std::endl << distNorm2 << std::endl;
  CategoricalDistribution<4> distCat4;
  std::vector<Eigen::Matrix<size_t, 4, 1> > samplesCat4;
  distCat4.getSamples(samplesCat4, 1000);
  EstimatorMLBatch<CategoricalDistribution<4>, 4>::estimate(distCat4,
    samplesCat4);
  std::cout << "Estimation3: " << std::endl << distCat4 << std::endl;
  MultinomialDistribution<4> distMult4(20);
  std::vector<Eigen::Matrix<size_t, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorMLBatch<MultinomialDistribution<4>, 4>::estimate(distMult4,
    samplesMult4);
  std::cout << "Estimation4: " << std::endl << distMult4 << std::endl;
  ExponentialDistribution distExp(2);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorMLBatch<ExponentialDistribution>::estimate(distExp, samplesExp);
  std::cout << "Estimation5: " << std::endl << distExp << std::endl;
  GeometricDistribution distGeom(0.7);
  std::vector<size_t> samplesGeom;
  distGeom.getSamples(samplesGeom, 1000);
  EstimatorMLBatch<GeometricDistribution>::estimate(distGeom, samplesGeom);
  std::cout << "Estimation6: " << std::endl << distGeom << std::endl;
  PoissonDistribution distPois;
  std::vector<size_t> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorMLBatch<PoissonDistribution>::estimate(distPois, samplesPois);
  std::cout << "Estimation7: " << std::endl << distPois << std::endl;
  return 0;
}
