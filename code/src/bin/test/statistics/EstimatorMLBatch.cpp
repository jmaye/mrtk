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
    \brief This file is a testing binary for the EstimatorML class in batch
  */

#include "statistics/EstimatorML.h"
#include "statistics/MixtureSampleDistribution.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorML<NormalDistribution<1> > estNorm1;
  estNorm1.addPoints(samplesNorm1);
  std::cout << "Estimation1: " << std::endl << estNorm1 << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5));
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorML<NormalDistribution<2>, 2> estNorm2;
  estNorm2.addPoints(samplesNorm2);
  std::cout << "Estimation2: " << std::endl << estNorm2 << std::endl;
  CategoricalDistribution<4> distCat4;
  std::vector<Eigen::Matrix<size_t, 4, 1> > samplesCat4;
  distCat4.getSamples(samplesCat4, 1000);
  EstimatorML<CategoricalDistribution<4>, 4> estCat4;
  estCat4.addPoints(samplesCat4);
  std::cout << "Estimation3: " << std::endl << estCat4 << std::endl;
  MultinomialDistribution<4> distMult4(20);
  std::vector<Eigen::Matrix<size_t, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorML<MultinomialDistribution<4>, 4> estMult4;
  estMult4.addPoints(samplesMult4);
  std::cout << "Estimation4: " << std::endl << estMult4 << std::endl;
  ExponentialDistribution distExp(2);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorML<ExponentialDistribution> estExp;
  estExp.addPoints(samplesExp);
  std::cout << "Estimation5: " << std::endl << estExp << std::endl;
  GeometricDistribution distGeom(0.7);
  std::vector<size_t> samplesGeom;
  distGeom.getSamples(samplesGeom, 1000);
  EstimatorML<GeometricDistribution> estGeom;
  estGeom.addPoints(samplesGeom);
  std::cout << "Estimation6: " << std::endl << estGeom << std::endl;
  PoissonDistribution distPois(2.0);
  std::vector<size_t> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorML<PoissonDistribution> estPois;
  estPois.addPoints(samplesPois);
  std::cout << "Estimation7: " << std::endl << estPois << std::endl;
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 0.0, 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x += 0.01) {
    distLine.setBasis(x);
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(x, distLine.getSample()));
  }
  EstimatorML<LinearRegression<2>, 2> estLine;
  estLine.addPoints(samplesLine);
  std::cout << "Estimation8: " << std::endl << estLine << std::endl;
  LinearRegression<3> distPlane(Eigen::Matrix<double, 3, 1>(2.0, 2.0, 2.0),
    Eigen::Matrix<double, 2, 1>(0.0, 0.0), 2.0);
  std::vector<Eigen::Matrix<double, 3, 1> > samplesPlane;
  for (double x = -10; x < 10; x += 0.1)
    for (double y = -10; y < 10; y += 0.1) {
      distPlane.setBasis(Eigen::Matrix<double, 2, 1>(x, y));
      samplesPlane.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distPlane.getSample()));
     }
  EstimatorML<LinearRegression<3>, 3> estPlane;
  estPlane.addPoints(samplesPlane);
  std::cout << "Estimation9: " << std::endl << estPlane << std::endl;
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
  EstimatorML<MixtureDistribution<NormalDistribution<1>, 5>, 1, 5> estMixtNorm1(
    initMeansMixtNorm1, initVariancesMixtNorm1, initWeightsMixtNorm1);
  size_t numIter = estMixtNorm1.addPoints(samplesMixtNorm1);
  std::cout << "Estimation10: " << std::endl << estMixtNorm1 << std::endl;
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
  std::vector<Eigen::Matrix<double, 3, 1> > initMeansMixtNorm3(5);
  initMeansMixtNorm3[0] << 0.12, 0.11, 0.13;
  initMeansMixtNorm3[1] << 5.05, 5.1, 5.04;
  initMeansMixtNorm3[2] << 10.1, 10.2, 10.4;
  initMeansMixtNorm3[3] << -5.14, -5.1, -5.04;
  initMeansMixtNorm3[4] << -10.2, -10.1, -10.04;
  std::vector<Eigen::Matrix<double, 3, 3> > initCovariancesMixtNorm3(5);
  initCovariancesMixtNorm3[0] = Eigen::Matrix<double, 3, 3>::Identity();
  initCovariancesMixtNorm3[1] = Eigen::Matrix<double, 3, 3>::Identity();
  initCovariancesMixtNorm3[2] = Eigen::Matrix<double, 3, 3>::Identity();
  initCovariancesMixtNorm3[3] = Eigen::Matrix<double, 3, 3>::Identity();
  initCovariancesMixtNorm3[4] = Eigen::Matrix<double, 3, 3>::Identity();
  Eigen::Matrix<double, 5, 1> initWeightsMixtNorm3;
  initWeightsMixtNorm3 << 0.2, 0.3, 0.1, 0.3, 0.1;
  EstimatorML<MixtureDistribution<NormalDistribution<3>, 5>, 3, 5> estMixtNorm3(
    initMeansMixtNorm3, initCovariancesMixtNorm3, initWeightsMixtNorm3);
  numIter = estMixtNorm3.addPoints(samplesMixtNorm3);
  std::cout << "Estimation11: " << std::endl << estMixtNorm3 << std::endl;
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
      distMixtLin3.setCompDistributions(distributionsLin3);
      samplesMixtLin3.push_back(Eigen::Matrix<double, 3, 1>(x, y,
        distMixtLin3.getSample()));
     }
  Eigen::Matrix<double, 5, 3> initCoefficientsMixtLin;
  initCoefficientsMixtLin << 1, 1, 1, 2, 2, 2, -1, -1, -1, -2, -2, -2, -3, -3,
    -3;
  Eigen::Matrix<double, 5, 1> initVariancesMixtLin;
  initVariancesMixtLin << 1.0, 1.0, 1.0, 1.0, 1.0;
  Eigen::Matrix<double, 5, 1> initWeightsMixtLin;
  initWeightsMixtLin << 0.2, 0.3, 0.1, 0.3, 0.1;
  EstimatorML<MixtureDistribution<LinearRegression<3>, 5>, 3, 5> estMixtLin(
    initCoefficientsMixtLin, initVariancesMixtLin, initWeightsMixtLin);
  numIter = estMixtLin.addPoints(samplesMixtLin3);
  std::cout << "Estimation12: " << std::endl << estMixtLin << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  return 0;
}
