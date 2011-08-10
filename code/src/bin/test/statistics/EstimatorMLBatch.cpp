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
#include "statistics/MixtureSampleDistribution.h"

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
  PoissonDistribution distPois(2.0);
  std::vector<size_t> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorMLBatch<PoissonDistribution>::estimate(distPois, samplesPois);
  std::cout << "Estimation7: " << std::endl << distPois << std::endl;
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x+=0.01)
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(x, distLine(x)));
  EstimatorMLBatch<LinearRegression<2>, 2>::estimate(distLine, samplesLine);
  std::cout << "Estimation8: " << std::endl << distLine << std::endl;
  LinearRegression<3> distPlane((Eigen::Matrix<double, 3, 1>()
    << 2.0, 2.0, 2.0).finished(), 2);
  std::vector<Eigen::Matrix<double, 3, 1> > samplesPlane;
  for (double x = -10; x < 10; x += 0.1)
    for (double y = -10; y < 10; y += 0.1)
      samplesPlane.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distPlane((Eigen::Matrix<double, 2, 1>() << x, y).finished())));
  EstimatorMLBatch<LinearRegression<3>, 3>::estimate(distPlane, samplesPlane);
  std::cout << "Estimation9: " << std::endl << distPlane << std::endl;
  LinearRegression<3> distPlaneTestFail((Eigen::Matrix<double, 3, 1>()
    << 2.0, 2.0, 2.0).finished(), 2);
  std::vector<Eigen::Matrix<double, 3, 1> > samplesPlaneTestFail;
  for (double x = -10; x < 10; x += 0.1) {
    for (double y = -10; y < 10; y += 0.1)
      samplesPlaneTestFail.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distPlane((Eigen::Matrix<double, 2, 1>() << x, y).finished())));
    break;
  }
  try {
    EstimatorMLBatch<LinearRegression<3>, 3>::estimate(distPlaneTestFail,
      samplesPlaneTestFail);
  }
  catch (InvalidOperationException& e) {
    std::cout << e.what() << std::endl;
  }
  std::vector<NormalDistribution<1> > distributions;
  distributions.push_back(NormalDistribution<1>(0, 1));
  distributions.push_back(NormalDistribution<1>(5, 1));
  distributions.push_back(NormalDistribution<1>(10, 1));
  distributions.push_back(NormalDistribution<1>(-5, 1));
  distributions.push_back(NormalDistribution<1>(-10, 1));
  MixtureSampleDistribution<NormalDistribution<1>, 5> distMixtNorm1(
    distributions, CategoricalDistribution<5>());
  std::vector<double> samplesMixtNorm1;
  distMixtNorm1.getSamples(samplesMixtNorm1, 1000);
  EstimatorMLBatch<MixtureDistribution<NormalDistribution<1>, 5>, 1, 5>::
    estimate(distMixtNorm1, samplesMixtNorm1);
  return 0;
}
