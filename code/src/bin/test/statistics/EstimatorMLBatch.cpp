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
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 0.0, 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x += 0.01) {
    distLine.setBasis(x);
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(x, distLine.getSample()));
  }
  EstimatorMLBatch<LinearRegression<2>, 2>::estimate(distLine, samplesLine);
  std::cout << "Estimation8: " << std::endl << distLine << std::endl;
  LinearRegression<3> distPlane(Eigen::Matrix<double, 3, 1>(2.0, 2.0, 2.0),
    Eigen::Matrix<double, 2, 1>(0.0, 0.0), 2.0);
  std::vector<Eigen::Matrix<double, 3, 1> > samplesPlane;
  for (double x = -10; x < 10; x += 0.1)
    for (double y = -10; y < 10; y += 0.1) {
      distPlane.setBasis(Eigen::Matrix<double, 2, 1>(x, y));
      samplesPlane.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distPlane.getSample()));
     }
  EstimatorMLBatch<LinearRegression<3>, 3>::estimate(distPlane, samplesPlane);
  std::cout << "Estimation9: " << std::endl << distPlane << std::endl;
  LinearRegression<3> distPlaneTestFail(Eigen::Matrix<double, 3, 1>(2.0, 2.0,
    2.0), Eigen::Matrix<double, 2, 1>(0.0, 0.0), 2.0);
  std::vector<Eigen::Matrix<double, 3, 1> > samplesPlaneTestFail;
  for (double x = -10; x < 10; x += 0.1) {
    for (double y = -10; y < 10; y += 0.1) {
      distPlaneTestFail.setBasis(Eigen::Matrix<double, 2, 1>(x, y));
      samplesPlaneTestFail.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distPlaneTestFail.getSample()));
    }
    break;
  }
  try {
    EstimatorMLBatch<LinearRegression<3>, 3>::estimate(distPlaneTestFail,
      samplesPlaneTestFail);
  }
  catch (InvalidOperationException& e) {
    std::cout << e.what() << std::endl;
  }
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
  distributionsNorm1[0] = NormalDistribution<1>(1, 1.5);
  distributionsNorm1[1] = NormalDistribution<1>(6, 1.2);
  distributionsNorm1[2] = NormalDistribution<1>(12, 1.1);
  distributionsNorm1[3] = NormalDistribution<1>(-5.5, 0.9);
  distributionsNorm1[4] = NormalDistribution<1>(-9.5, 2.0);
  distMixtNorm1.setDistributions(distributionsNorm1);
  std::vector<Eigen::Matrix<double, 5, 1> > responsibilities;
  size_t numIter =
    EstimatorMLBatch<MixtureDistribution<NormalDistribution<1>, 5>, 1, 5>::
    estimate(distMixtNorm1, samplesMixtNorm1, responsibilities);
  std::cout << "Estimation10: " << std::endl << distMixtNorm1 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  std::vector<NormalDistribution<3> > distributionsNorm3;
  distributionsNorm3.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(0, 0, 0),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributionsNorm3.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(5, 5, 5),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributionsNorm3.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(10, 10, 10),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributionsNorm3.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-5, -5, -5),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributionsNorm3.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-10, -10, -10),
    Eigen::Matrix<double, 3, 3>::Identity()));
  MixtureSampleDistribution<NormalDistribution<3>, 5> distMixtNorm3(
    distributionsNorm3, CategoricalDistribution<5>());
  std::vector<Eigen::Matrix<double, 3, 1> > samplesMixtNorm3;
  distMixtNorm3.getSamples(samplesMixtNorm3, 1000);
  distributionsNorm3[0] = NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(0.12, 0.11, 0.13),
    Eigen::Matrix<double, 3, 3>::Identity());
  distributionsNorm3[1] = NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(5.05, 5.1, 5.04),
    Eigen::Matrix<double, 3, 3>::Identity());
  distributionsNorm3[2] = NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(10.1, 10.2, 10.4),
    Eigen::Matrix<double, 3, 3>::Identity());
  distributionsNorm3[3] = NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-5.14, -5.1, -5.04),
    Eigen::Matrix<double, 3, 3>::Identity());
  distributionsNorm3[4] = NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-10.2, -10.1, -10.04),
    Eigen::Matrix<double, 3, 3>::Identity());
  distMixtNorm3.setDistributions(distributionsNorm3);
  numIter =
    EstimatorMLBatch<MixtureDistribution<NormalDistribution<3>, 5>, 3, 5>::
    estimate(distMixtNorm3, samplesMixtNorm3, responsibilities);
  std::cout << "Estimation11: " << std::endl << distMixtNorm3 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  std::vector<LinearRegression<3> > distributionsLin3;
  distributionsLin3.push_back(LinearRegression<3>(
    Eigen::Matrix<double, 3, 1>(1, 1, 1)));
  distributionsLin3.push_back(LinearRegression<3>(
    Eigen::Matrix<double, 3, 1>(2, 2, 2)));
  distributionsLin3.push_back(LinearRegression<3>(
    Eigen::Matrix<double, 3, 1>(-1, -1, -1)));
  distributionsLin3.push_back(LinearRegression<3>(
    Eigen::Matrix<double, 3, 1>(-2, -2, -2)));
  distributionsLin3.push_back(LinearRegression<3>(
    Eigen::Matrix<double, 3, 1>(-3, -3, -3)));
  MixtureSampleDistribution<LinearRegression<3>, 5>
    distMixtLin3(distributionsLin3, CategoricalDistribution<5>());
  std::vector<Eigen::Matrix<double, 3, 1> > samplesMixtLin3;
  for (double x = -10; x < 10; x += 0.1)
    for (double y = -10; y < 10; y += 0.1) {
      for (size_t j = 0; j < distributionsLin3.size(); ++j)
        distributionsLin3[j].setBasis(Eigen::Matrix<double, 2, 1>(x, y));
      distMixtLin3.setDistributions(distributionsLin3);
      samplesMixtLin3.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distMixtLin3.getSample()));
     }
  numIter =
    EstimatorMLBatch<MixtureDistribution<LinearRegression<3>, 5>, 3, 5>::
    estimate(distMixtLin3, samplesMixtLin3, responsibilities);
  std::cout << "Estimation12: " << std::endl << distMixtLin3 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  return 0;
}
