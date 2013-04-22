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

/** \file MixtureNormalDistributionRndScatterPlot3v.cpp
    \brief This file is a testing binary for plotting random samples of a 
           a mixture of trivariate normal distributions
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<NormalDistribution<3> > distributions;
  distributions.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(0, 0, 0),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributions.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(5, 5, 5),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributions.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(10, 10, 10),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributions.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-5, -5, -5),
    Eigen::Matrix<double, 3, 3>::Identity()));
  distributions.push_back(NormalDistribution<3>(
    Eigen::Matrix<double, 3, 1>(-10, -10, -10),
    Eigen::Matrix<double, 3, 3>::Identity()));
  MixtureSampleDistribution<NormalDistribution<3>, 5> dist(distributions,
    CategoricalDistribution<5>());
  std::vector<Eigen::Matrix<double, 3, 1> > data;
  dist.getSamples(data, 100000);
  ScatterPlot<3> plot("MixtureNormalDistributionRndScatterPlot3v", data);
  plot.show();
  return app.exec();
}
