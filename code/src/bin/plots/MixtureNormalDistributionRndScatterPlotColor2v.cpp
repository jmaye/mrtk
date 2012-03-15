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

/** \file MixtureNormalDistributionRndScatterPlotColor2v.cpp
    \brief This file is a testing binary for plotting random samples of a 
           a mixture of bivariate normal distributions with colors
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<NormalDistribution<2> > distributions;
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(0, 0),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(5, 5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(10, 10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-5, -5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-10, -10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  MixtureSampleDistribution<NormalDistribution<2>, 5> dist(distributions,
    CategoricalDistribution<5>());
  std::vector<std::tuple<Eigen::Matrix<double, 2, 1>, size_t> > data;
  dist.getJointSamples(data, 100000);
  ScatterPlot<2> plot("MixtureNormalDistributionRndScatterPlotColor2v", data);
  plot.show();
  return app.exec();
}
