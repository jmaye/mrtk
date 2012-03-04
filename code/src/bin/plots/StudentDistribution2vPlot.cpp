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

/** \file StudentDistribution2vPlot.cpp
    \brief This file is a testing binary for plotting the bivariate Student
           distribution pdf
  */

#include <QtGui/QApplication>

#include "visualization/FunctionPlot.h"
#include "statistics/StudentDistribution.h"

int main(int argc, char** argv) {
  Eigen::Matrix<double, 2, 1> minimum(-2, -2);
  Eigen::Matrix<double, 2, 1> maximum(2, 2);
  Eigen::Matrix<double, 2, 1> resolution(0.05, 0.05);
  QApplication app(argc, argv);
  FunctionPlot<StudentDistribution<2>, 2> plot("StudentDistribution2v",
    StudentDistribution<2>(5, Eigen::Matrix<double, 2, 1>(1.0, 1.0),
    (Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).finished()), minimum,
    maximum, resolution);
  plot.show();
  return app.exec();
}
