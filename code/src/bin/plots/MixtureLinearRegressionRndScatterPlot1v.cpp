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

/** \file MixtureLinearRegressionRndScatterPlot1v.cpp
    \brief This file is a testing binary for plotting random samples of a 
           a mixture of univariate linear regressions
  */

#include "visualization/ScatterPlot.h"
#include "statistics/LinearRegression.h"
#include "statistics/MixtureSampleDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<LinearRegression<2> > distributions;
  distributions.push_back(LinearRegression<2>(
    Eigen::Matrix<double, 2, 1>(1, 1), 0.0, 1.0));
  distributions.push_back(LinearRegression<2>(
    Eigen::Matrix<double, 2, 1>(2, 2), 0.0, 1.0));
  distributions.push_back(LinearRegression<2>(
    Eigen::Matrix<double, 2, 1>(-1, -1), 0.0, 1.0));
  distributions.push_back(LinearRegression<2>(
    Eigen::Matrix<double, 2, 1>(-2, -2), 0.0, 1.0));
  MixtureSampleDistribution<LinearRegression<2>, 4> dist(distributions,
    CategoricalDistribution<4>());
  std::vector<Eigen::Matrix<double, 2, 1> > data;
  for (size_t i = 0; i < 100; ++i)
    for (double x = -10; x < 10; x += 0.01) {
      for (size_t j = 0; j < distributions.size(); ++j)
        distributions[j].setBasis(x);
      dist.setCompDistributions(distributions);
      data.push_back(Eigen::Matrix<double, 2, 1>(x, dist.getSample()));
    }
  ScatterPlot<2> plot("MixtureLinearRegressionRndScatterPlot1v", data);
  plot.show();
  return app.exec();
}
