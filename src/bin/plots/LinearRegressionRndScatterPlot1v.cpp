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

/** \file LinearRegressionRndScatterPlot1v.cpp
    \brief This file is a testing binary for plotting random samples of a
           univariate linear regression
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/LinearRegression.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 2, 1> > data;
  LinearRegression<2> dist;
  for (double x = -10; x < 10; x += 0.01) {
    dist.setBasis((Eigen::Matrix<double, 1, 1>() << x).finished());
    data.push_back(dist.getSample());
  }
  ScatterPlot<2> plot("LinearRegressionRndScatterPlot1v", data);
  plot.show();
  return app.exec();
}
