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
#include "statistics/MixtureSampleDistribution.h"
#include "base/Timestamp.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >
    estNorm1Mean(2);
  estNorm1Mean.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation1: " << std::endl << estNorm1Mean << std::endl;
  EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>
    estNorm1Variance(5);
  estNorm1Variance.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation2: " << std::endl << estNorm1Variance << std::endl;
  EstimatorBayes<NormalDistribution<1> >
    estNorm1MeanVariance;
  estNorm1MeanVariance.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation3: " << std::endl << estNorm1MeanVariance
    << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5),
    (Eigen::Matrix<double, 2, 2>() << 2, 1, 1, 2).finished());
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorBayes<NormalDistribution<2>, NormalDistribution<2> >
    estNorm2Mean((Eigen::Matrix<double, 2, 2>() << 2, 1, 1, 2).finished());
  estNorm2Mean.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation4: " << std::endl << estNorm2Mean << std::endl;
  EstimatorBayes<NormalDistribution<2>, InvWishartDistribution<2> >
    estNorm2Covariance(Eigen::Matrix<double, 2, 1>(5, 5));
  estNorm2Covariance.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation5: " << std::endl << estNorm2Covariance << std::endl;
  EstimatorBayes<NormalDistribution<2> >
    estNorm2MeanCovariance;
  estNorm2MeanCovariance.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation6: " << std::endl << estNorm2MeanCovariance
    << std::endl;
  MultinomialDistribution<4> distMult4(20);
  std::vector<Eigen::Matrix<int, 4, 1> > samplesMult4;
  distMult4.getSamples(samplesMult4, 1000);
  EstimatorBayes<MultinomialDistribution<4> >
    estMult4;
  estMult4.addPoints(samplesMult4.begin(), samplesMult4.end());
  std::cout << "Estimation7: " << std::endl << estMult4 << std::endl;
  CategoricalDistribution<4> distCat4;
  std::vector<Eigen::Matrix<int, 4, 1> > samplesCat4;
  distCat4.getSamples(samplesCat4, 1000);
  EstimatorBayes<CategoricalDistribution<4> >
    estCat4;
  estCat4.addPoints(samplesCat4.begin(), samplesCat4.end());
  std::cout << "Estimation8: " << std::endl << estCat4 << std::endl;
  PoissonDistribution distPois(5.0);
  std::vector<int> samplesPois;
  distPois.getSamples(samplesPois, 1000);
  EstimatorBayes<PoissonDistribution> estPois;
  estPois.addPoints(samplesPois.begin(), samplesPois.end());
  std::cout << "Estimation9: " << std::endl << estPois << std::endl;
  ExponentialDistribution distExp(5);
  std::vector<double> samplesExp;
  distExp.getSamples(samplesExp, 1000);
  EstimatorBayes<ExponentialDistribution> estExp;
  estExp.addPoints(samplesExp.begin(), samplesExp.end());
  std::cout << "Estimation10: " << std::endl << estExp << std::endl;
  GeometricDistribution distGeom(0.8);
  std::vector<int> samplesGeom;
  distGeom.getSamples(samplesGeom, 1000);
  EstimatorBayes<GeometricDistribution> estGeom;
  estGeom.addPoints(samplesGeom.begin(), samplesGeom.end());
  std::cout << "Estimation11: " << std::endl << estGeom << std::endl;
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
  DirichletDistribution<5> dirPrior;
  NormalScaledInvChiSquareDistribution<> compPrior(0.0, 1, 1, 1.5);
  EstimatorBayes<MixtureDistribution<NormalDistribution<1>, 5> >
    estMixtNorm1(dirPrior, compPrior, 500);
  double before = Timestamp::now();
  estMixtNorm1.addPoints(samplesMixtNorm1.begin(), samplesMixtNorm1.end());
  double after = Timestamp::now();
  std::cout << "Estimation11: " << std::endl << estMixtNorm1 << std::endl;
  std::cout << "Time: " << after - before << " [s]" << std::endl;
//  before = Timestamp::now();
//  estMixtNorm1.addPoints3(samplesMixtNorm1.begin(), samplesMixtNorm1.end());
//  after = Timestamp::now();
//  std::cout << "Estimation13: " << std::endl << estMixtNorm1 << std::endl;
//  std::cout << "Time: " << after - before << " [s]" << std::endl;
  return 0;
}
