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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file GMM-CEM.cpp
    \brief This file is a testing binary for plotting ML clustering on GMM.
  */

#include <limits>

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"
#include "statistics/EstimatorML.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<NormalDistribution<2> > distributionsNorm2;
  distributionsNorm2.reserve(5);
  distributionsNorm2.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(0, 0)));
  distributionsNorm2.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(5, 5)));
  distributionsNorm2.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(10, 10)));
  distributionsNorm2.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-5, -5)));
  distributionsNorm2.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-10, -10)));
  MixtureSampleDistribution<NormalDistribution<2>, 5> distMixtNorm2(
    distributionsNorm2, CategoricalDistribution<5>(
    (Eigen::Matrix<double, 5, 1>() << 0.1, 0.2, 0.2, 0.4, 0.1).finished()));
  std::vector<Eigen::Matrix<double, 2, 1> > samplesMixtNorm2;
  distMixtNorm2.getSamples(samplesMixtNorm2, 10000);
  std::vector<NormalDistribution<2> > distributionsNorm2Init;
  distributionsNorm2Init.reserve(5);
  distributionsNorm2Init.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(1.0, -1.0)));
  distributionsNorm2Init.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(2.0, 2.0)));
  distributionsNorm2Init.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(11.0, 9.0)));
  distributionsNorm2Init.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-6.0, -4.0)));
  distributionsNorm2Init.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-11.0, -9.0)));
  MixtureSampleDistribution<NormalDistribution<2>, 5> distMixtNorm2Init(
    distributionsNorm2Init, CategoricalDistribution<5>());
  EstimatorML<MixtureDistribution<NormalDistribution<2>, 5> > estMixtNorm2(
    distMixtNorm2Init);
  size_t numIter =
    estMixtNorm2.addPointsCEM(samplesMixtNorm2.begin(), samplesMixtNorm2.end());
  std::cout << "Estimation: " << std::endl << estMixtNorm2 << std::endl;
  std::cout << "Converged in: " << numIter << " iterations" << std::endl;
  auto responsibilities = estMixtNorm2.getResponsibilities();
  std::vector<std::tuple<Eigen::Matrix<double, 2, 1>, size_t> > data;
  data.reserve(10000);
  for (auto it = samplesMixtNorm2.cbegin(); it != samplesMixtNorm2.cend();
      ++it) {
    const size_t row = it - samplesMixtNorm2.cbegin();
    double max = -std::numeric_limits<double>::infinity();
    size_t argmax = 0;
    for (size_t i = 0; i < (size_t)responsibilities.cols(); ++i)
      if (responsibilities(row, i) > max) {
        max = responsibilities(row, i);
        argmax = i;
      }
    data.push_back(std::tuple<Eigen::Matrix<double, 2, 1>, size_t>(*it,
      argmax));
  }
  ScatterPlot<2> plot("GMM-CEM", data);
  plot.show();
  return app.exec();
}
