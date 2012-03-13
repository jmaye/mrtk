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

/** \file EstimatorML.cpp
    \brief This file is a testing binary for the EstimatorML class in batch
  */

#include <iostream>

#include "statistics/EstimatorML.h"
#include "statistics/MixtureSampleDistribution.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 5);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorML<NormalDistribution<1> > estNorm1;
  estNorm1.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation1: " << std::endl << estNorm1 << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5),
    (Eigen::Matrix<double, 2, 2>() << 5.0, 0.5, 0.5, 5.0).finished());
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorML<NormalDistribution<2> > estNorm2;
  estNorm2.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation2: " << std::endl << estNorm2 << std::endl;
  CategoricalDistribution<4> distCat4(
    (Eigen::Matrix<double, 4, 1>() << 0.1, 0.2, 0.2, 0.5).finished());
  std::vector<Eigen::Matrix<int, 4, 1> > samplesCat4;
  distCat4.getSamples(samplesCat4, 1000);
  EstimatorML<CategoricalDistribution<4> > estCat4;
  estCat4.addPoints(samplesCat4.begin(), samplesCat4.end());
  std::cout << "Estimation3: " << std::endl << estCat4 << std::endl;
  MultinomialDistribution<4> distMult4(20,
    (Eigen::Matrix<double, 4, 1>() << 0.1, 0.2, 0.2, 0.5).finished());
  std::vector<Eigen::Matrix<int, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorML<MultinomialDistribution<4> > estMult4;
  estMult4.addPoints(samplesMult4.begin(), samplesMult4.end());
  std::cout << "Estimation4: " << std::endl << estMult4 << std::endl;
  ExponentialDistribution distExp(5);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorML<ExponentialDistribution> estExp;
  estExp.addPoints(samplesExp.begin(), samplesExp.end());
  std::cout << "Estimation5: " << std::endl << estExp << std::endl;
  GeometricDistribution distGeom(0.7);
  std::vector<int> samplesGeom;
  distGeom.getSamples(samplesGeom, 1000);
  EstimatorML<GeometricDistribution> estGeom;
  estGeom.addPoints(samplesGeom.begin(), samplesGeom.end());
  std::cout << "Estimation6: " << std::endl << estGeom << std::endl;
  PoissonDistribution distPois(5.0);
  std::vector<int> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorML<PoissonDistribution> estPois;
  estPois.addPoints(samplesPois.begin(), samplesPois.end());
  std::cout << "Estimation7: " << std::endl << estPois << std::endl;
  std::vector<NormalDistribution<1> > distributionsNorm1;
  distributionsNorm1.push_back(NormalDistribution<1>(0, 1.5));
  distributionsNorm1.push_back(NormalDistribution<1>(5, 1.7));
  distributionsNorm1.push_back(NormalDistribution<1>(10, 1.2));
  distributionsNorm1.push_back(NormalDistribution<1>(-5, 1.3));
  distributionsNorm1.push_back(NormalDistribution<1>(-10, 1.5));
  MixtureSampleDistribution<NormalDistribution<1>, 5> distMixtNorm1(
    distributionsNorm1, CategoricalDistribution<5>(
    (Eigen::Matrix<double, 5, 1>() << 0.1, 0.2, 0.2, 0.4, 0.1).finished()));
  std::vector<double> samplesMixtNorm1;
  distMixtNorm1.getSamples(samplesMixtNorm1, 1000);
  std::vector<NormalDistribution<1> > distributionsNorm1Init;
  distributionsNorm1Init.push_back(NormalDistribution<1>(1, 2.4));
  distributionsNorm1Init.push_back(NormalDistribution<1>(6, 3.1));
  distributionsNorm1Init.push_back(NormalDistribution<1>(12, 4.7));
  distributionsNorm1Init.push_back(NormalDistribution<1>(-5.5, 2.1));
  distributionsNorm1Init.push_back(NormalDistribution<1>(-9.5, 1.4));
  MixtureSampleDistribution<NormalDistribution<1>, 5> distMixtNorm1Init(
    distributionsNorm1Init, CategoricalDistribution<5>());
  EstimatorML<MixtureDistribution<NormalDistribution<1>, 5> >
    estMixtNorm1(distMixtNorm1Init);
  size_t numIter = estMixtNorm1.addPointsEM(samplesMixtNorm1.begin(),
    samplesMixtNorm1.end());
  std::cout << "Estimation10: " << std::endl << estMixtNorm1 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  estMixtNorm1 = EstimatorML<MixtureDistribution<NormalDistribution<1>, 5> >
    (distMixtNorm1Init);
  numIter = estMixtNorm1.addPointsCEM(samplesMixtNorm1.begin(),
    samplesMixtNorm1.end());
  std::cout << "Estimation11: " << std::endl << estMixtNorm1 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  estMixtNorm1 = EstimatorML<MixtureDistribution<NormalDistribution<1>, 5> >
    (distMixtNorm1Init);
  numIter = estMixtNorm1.addPointsSEM(samplesMixtNorm1.begin(),
    samplesMixtNorm1.end());
  std::cout << "Estimation12: " << std::endl << estMixtNorm1 << std::endl;
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
  std::vector<NormalDistribution<3> > distributionsNorm3Init;
  distributionsNorm3Init.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(0.1, 0.2, 0.3)));
  distributionsNorm3Init.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(5.5, 6, 5.1)));
  distributionsNorm3Init.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(10.5, 11, 12)));
  distributionsNorm3Init.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-5, -5.4, -4.2)));
  distributionsNorm3Init.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-10.5, -10.2, -11)));
  MixtureSampleDistribution<NormalDistribution<3>, 5> distMixtNorm3Init(
    distributionsNorm3Init, CategoricalDistribution<5>());
  EstimatorML<MixtureDistribution<NormalDistribution<3>, 5> > estMixtNorm3(
    distMixtNorm3Init);
  numIter = estMixtNorm3.addPointsEM(samplesMixtNorm3.begin(),
    samplesMixtNorm3.end());
  std::cout << "Estimation13: " << std::endl << estMixtNorm3 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  return 0;
}
