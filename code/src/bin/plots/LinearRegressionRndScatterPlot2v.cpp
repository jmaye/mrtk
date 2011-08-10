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

/** \file LinearRegressionRndScatterPlot2v.cpp
    \brief This file is a testing binary for plotting random samples of a
           bivariate linear regression
  */

#include "visualization/ScatterPlot.h"
#include "statistics/LinearRegression.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 3, 1> > data;
  LinearRegression<3> dist;
  for (double x = -10; x < 10; x += 0.1)
    for (double y = -10; y < 10; y += 0.1) {
      dist.setBasis(Eigen::Matrix<double, 2, 1>(x, y));
      data.push_back(Eigen::Matrix<double, 3, 1>(x, y, dist.getSample()));
     }
  ScatterPlot<3> plot("LinearRegressionRndScatterPlot2v", data);
  plot.show();
  return app.exec();
}
